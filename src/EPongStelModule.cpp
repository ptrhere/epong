/*
 * Copyright (C) 2007 Fabien Chereau
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
#include <QFontDatabase>
#include  <QDebug>
#include <qthread.h>

#include "StelProjector.hpp"
#include "StelNavigator.hpp"
#include "StelPainter.hpp"
#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelLocaleMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelFileMgr.hpp"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "EPongStelModule.hpp"
#include "Pong.hpp"


#define ADDRESS "172.22.33.107"
#define PORT 9000
#define OUTPUT_BUFFER_SIZE 1024

// better divisble by 4
#define BALLS 100
#define PADDLES 4

#define PI 3.141592

void
handler (int sig)
{
  printf ("\nexiting...(%d)\n", sig);
  exit (0);
}

void
perror_exit (char *error)
{
  perror (error);
  handler (9);
}

PongBall *ball[BALLS];
PongPaddle *paddle[PADDLES];
float paddle_color[][] = {
{1.0f,0.0f,0.0f,1.0f},
{0.0f,1.0f,0.0f,1.0f},
{0.0f,0.0f,1.0f,1.0f},
{0.0f,1.0f,1.0f,1.0f},

}

PongEvent *pevent[BALLS];
int ball_countdown;

static double lastTime;
enum
{
  BALL_CREATE,
  BALL_COLLIDE,
  BALL_BOUNCE
};

bool in_game;
float gamestarttime = 0.0;

// Time in seconds a ball needs to make a halfturn
UdpTransmitSocket *transmitSocket = 0;

class ReadEventThread;

ReadEventThread *re[PADDLES];
const char *re_dev[] = {
  "/dev/input/event5",
  "/dev/input/event6",
  "/dev/input/event7",
  "/dev/input/event8",
};

QFont *pongFont;

class ReadEventThread:public QThread
{

public:
  int paddle;
  std::string event_socket;
  struct input_event ev[64];
  int fd, rd, value, size;
  char name[256];


    ReadEventThread (int p, std::string ev):paddle (p), event_socket (ev)
  {
    size = sizeof (struct input_event);
    if (event_socket == "")
      {
	printf
	  ("Please specify the path to the dev event interface device\n");
	exit (0);
      }

    if ((getuid ()) != 0)
        printf ("You are not root! This may not work...\n");

    //Open Device
    if ((fd = open (event_socket.c_str (), O_RDONLY)) == -1)
      printf ("%s is not a vaild device.\n", event_socket.c_str ());

    //Print Device Name
    ioctl (fd, EVIOCGNAME (sizeof (name)), name);
    printf ("Reading From : %s (%s)\n", event_socket.c_str (), name);

  }
  virtual void run ();

};

void start_game ();

void
ReadEventThread::run ()
{
  while (1)
    {
      if ((rd = read (fd, ev, size)) < size)
	perror_exit ((char *) ("read()"));
      const float radian_per_tick = (4.0 * PI) / 256.0f;	// empiric value
      ::paddle[this->paddle]->move (ev[0].value * radian_per_tick);
      {
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p (buffer, OUTPUT_BUFFER_SIZE);
	p << osc::BeginBundleImmediate << osc::BeginMessage ("/paddle") <<
	  this->paddle << ((ev[0].value < 0) ? "left" : "right") <<
	  osc::EndMessage << osc::EndBundle;
	//should protect this with mutex...
	transmitSocket->Send (p.Data (), p.Size ());
      }
      if (ev[0].code == 256)
	{
	  ::start_game ();
	}
    }

}

/*************************************************************************
 This method is the one called automatically by the StelModuleMgr just 
 after loading the dynamic library
*************************************************************************/
StelModule *
EPongStelModuleStelPluginInterface::getStelModule ()  const
{
  return new EPongStelModule ();
}

StelPluginInfo EPongStelModuleStelPluginInterface::getPluginInfo () const
{
  StelPluginInfo
    info;
  info.id = "EPongStelModule";
  info.displayedName = "EPong plugin";
  info.authors = "ptr_here / PrototypeX29A";
  info.contact = "e-pong.eu";
  info.description = "epong plugin";
  return info;
}

Q_EXPORT_PLUGIN2 (EPongStelModule, EPongStelModuleStelPluginInterface)
/*************************************************************************
 Constructor
*************************************************************************/
  EPongStelModule::EPongStelModule ()
{
  setObjectName ("EPongStelModule");
  font.setPixelSize (25);
}

/*************************************************************************
 Destructor
*************************************************************************/
EPongStelModule::~EPongStelModule ()
{
}

/*************************************************************************
 Reimplementation of the getCallOrder method
*************************************************************************/
double
EPongStelModule::getCallOrder (StelModuleActionName actionName) const 
{
  if (actionName == StelModule::ActionDraw)
    return StelApp::getInstance ().getModuleMgr ().getModule ("NebulaMgr")->
      getCallOrder (actionName) + 11.;
  return 0;
}


/*************************************************************************
 Init our module
*************************************************************************/
void
EPongStelModule::init ()
{

  try
  {
    const QString & fName = StelFileMgr::findFile ("data/Digir___.ttf");
    if (!fName.isEmpty ())
      QFontDatabase::addApplicationFont (fName);
  }
  catch (std::runtime_error & e)
  {
    qWarning () << "ERROR while loading font : " << e.what ();
  }
  pongFont = new QFont ("Digital Readout");
  pongFont->setPixelSize (50);


  transmitSocket = new UdpTransmitSocket (IpEndpointName (ADDRESS, PORT));
  qDebug () << "init called for EPongStelModule";
  //time = 0;
  lastTime = StelApp::getTotalRunTime ();
  int i;
  for (i = 0; i < PADDLES; i++)
    {
      paddle[i] = new PongPaddle ();
      paddle[i]->pos.set (0.0f, 1.0f, 0.0f);
      paddle[i]->normal.set (0.0f, 0.0f, 1.0f);
      paddle[i]->total_alpha = 0.0f;
      paddle[i]->size= 0.05f; // alpha
    }
  for (i = 0; i < BALLS; i++)
    {
      ball[i] = new PongBall ();
      pevent[i] = new PongEvent ();
    }
  for (int i = 0; i < PADDLES; i++)
    {
      re[i] = new ReadEventThread (i, re_dev[i]);
      re[i]->start ();
    }


  reinit ();
}


void
reinit ()
{
  in_game = false;
}

void
start_game ()
{
  if (!in_game)
    {
      ball_countdown = BALLS;
      for (int i = 0; i < BALLS; i++)
	{
	  ball[i]->pos.set (0.0f + (rand () % 100) / 1000.0,
			    0.0f + (rand () % 100) / 1000.0, 1.0f);
	  ball[i]->normal.set (sin ((rand () % 100) / 100.0 * 2.0 * PI),
			       cos ((rand () % 100) / 100.0 * 2.0 * PI),
			       0.0f);
	  ball[i]->alive = 0;
	  ball[i]->HTT = 4.0;
	  pevent[i]->type = BALL_CREATE;
	  pevent[i]->time = lastTime +
	    /* HTT * (i % (BALLS / 4)) / (BALLS / 4) + */ 10.0f * (rand () %
								   100) *
	    0.01;
	  //printf ("HTT: %f,  i:%d\n", HTT, i);
	  //printf ("Ball creation of Ball %i at %f\n", i, pevent[i]->time);
	}
      {
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p (buffer, OUTPUT_BUFFER_SIZE);
	p << osc::BeginBundleImmediate
	  << osc::BeginMessage ("/start") << osc::EndMessage << osc::
	  EndBundle;
	//should protect this with mutex...
	transmitSocket->Send (p.Data (), p.Size ());
      }
      in_game = true;
      gamestarttime = StelApp::getTotalRunTime ();
    }

}

void
EPongStelModule::reinit ()
{
  ::reinit ();
}

inline void
PongBall::move (double alpha)
{
  double x, y, z;
  double s, c, t;
  s = sin (alpha);
  c = cos (alpha);
  //printf("s = %f, c = %f\n", s,c);      
  t = 1.0f - c;
  x = pos[0] * (t * normal[0] * normal[0] + c) +
    pos[1] * (t * normal[0] * normal[1] - s * normal[2]) +
    pos[2] * (t * normal[0] * normal[2] + s * normal[1]);
  y = pos[0] * (t * normal[0] * normal[2] + s * normal[2]) +
    pos[1] * (t * normal[1] * normal[1] + c) +
    pos[2] * (t * normal[1] * normal[2] - s * normal[0]);
  z = pos[0] * (t * normal[0] * normal[2] - s * normal[1]) +
    pos[1] * (t * normal[1] * normal[2] + s * normal[0]) +
    pos[2] * (t * normal[2] * normal[2] + c);
  pos.set (x, y, z);
  //printf("x = %f, y = %f, z = %f\n",pos[0], pos[1], pos[2]); 

}

inline void
PongPaddle::move (double alpha)
{
  double x, y, z;
  double s, c, t;


  total_alpha -= alpha;
  while (total_alpha > PI)
    {
      total_alpha -= 2.0 * PI;
    }
  while (total_alpha < -PI)
    {
      total_alpha += 2.0 * PI;
    }

  s = sin (alpha);
  c = cos (alpha);
  //printf("s = %f, c = %f\n", s,c);      
  t = 1.0f - c;
  x = pos[0] * (t * normal[0] * normal[0] + c) +
    pos[1] * (t * normal[0] * normal[1] - s * normal[2]) +
    pos[2] * (t * normal[0] * normal[2] + s * normal[1]);
  y = pos[0] * (t * normal[0] * normal[2] + s * normal[2]) +
    pos[1] * (t * normal[1] * normal[1] + c) +
    pos[2] * (t * normal[1] * normal[2] - s * normal[0]);
  z = pos[0] * (t * normal[0] * normal[2] - s * normal[1]) +
    pos[1] * (t * normal[1] * normal[2] + s * normal[0]) +
    pos[2] * (t * normal[2] * normal[2] + c);
  pos.set (x, y, z);
  //printf("x = %f, y = %f, z = %f\n",pos[0], pos[1], pos[2]); 
}

double
get_bounce_time (PongBall * ball)
{
  /*
     printf ("px: %f, py: %f, pz: %f, nx: %f, ny: %f, nz: %f/n",
     ball->pos[0],
     ball->pos[1],
     ball->pos[2], ball->normal[0], ball->normal[1], ball->normal[2]);
   */ return ball->HTT * acos (ball->normal[1] * ball->pos[0] -
			       ball->normal[0] * ball->pos[1]) / PI;
}

void
get_next_event (PongEvent * event, PongBall * ball, double now)
{
  event->type = BALL_BOUNCE;
  double delta = get_bounce_time (ball);
  event->time = now + delta;
  //printf ("Setting bounce time to %f\n", delta);
}

void
handle_events (double time)
{
  //printf("enter handle\n");
  int first;
  double first_time=0.0f;
  do
    {
      first = BALLS;
      int i;
      for (i = 0; i < BALLS; i++)
	{
	  if (pevent[i]->time < time)
	    {
	      if ((first == BALLS) || ((pevent[i]->time) < first_time))
		{
		  first = i;
		  first_time = pevent[i]->time;
		}
	    }
	}
      if (first < BALLS)
	{
	  printf ("Time: %f\n", first_time);
	  switch (pevent[first]->type)
	    {
	    case BALL_CREATE:
	      printf ("\tCreate ball\n");
	      ball[first]->alive = 1;
	      ball[first]->moved = first_time;
	      break;
	    case BALL_BOUNCE:
	      //printf ("\tBounce ball\n");
	      {
		bool does_rebound = false;
		for (int i = 0; i < PADDLES; i++)
		  {
		    Vec3f v = paddle[i]->pos - ball[first]->pos;
		    if (v.lengthSquared () < (paddle[i]->size) / 4.0f)
		      {
			does_rebound = true;
			if (ball[first]->alive)
			  {
			    char buffer[OUTPUT_BUFFER_SIZE];
			    osc::OutboundPacketStream p (buffer,
							 OUTPUT_BUFFER_SIZE);
			    p << osc::BeginBundleImmediate <<
			      osc::
			      BeginMessage ("/bounce") << (int) i <<
			      ball[first]->
			      HTT << osc::EndMessage << osc::EndBundle;
			    transmitSocket->Send (p.Data (), p.Size ());
			  }
		      }
		  }
		if (does_rebound)
		  {
		    ball[first]->normal[0] = -(ball[first]->normal[0])	+0.5f * (0.5-((rand()%100) * 0.01));
		    ball[first]->normal[1] = -(ball[first]->normal[1])	+0.5f * (0.5-((rand()%100) * 0.01));
		    ball[first]->normal[2] = 0.0f;	//3*(0.5-((rand()%100) * 0.01));
		    ball[first]->pos.normalize ();
		    ball[first]->normal.normalize ();
		    ball[first]->moved = first_time;
		    if (ball[first]->HTT > .5f)
		      ball[first]->HTT -= 0.05;
		  }
		else
		  {
		    if (ball[first]->alive)
		      {
			ball[first]->alive = false;
			{
			  char buffer[OUTPUT_BUFFER_SIZE];
			  osc::OutboundPacketStream p (buffer,
						       OUTPUT_BUFFER_SIZE);
			  p << osc::BeginBundleImmediate <<
			    osc::
			    BeginMessage ("/loss") << osc::EndMessage << osc::
			    EndBundle;
			  transmitSocket->Send (p.Data (), p.Size ());
			}
			ball_countdown--;
			if (ball_countdown <= 0)
			  {
			    reinit ();
			    {
			      char buffer[OUTPUT_BUFFER_SIZE];
			      osc::OutboundPacketStream p (buffer,
							   OUTPUT_BUFFER_SIZE);
			      p << osc::BeginBundleImmediate << osc::
				BeginMessage ("/end") << osc::
				EndMessage << osc::EndBundle;
			      //should protect this with mutex...
			      transmitSocket->Send (p.Data (), p.Size ());
			  }}
		      }
		  }
	      }
	      break;
	    default:
	      break;
	    }
	  get_next_event (pevent[first], ball[first], first_time);
	}
    }
  while (first != BALLS);
  //printf("leave handle\n");
}

/*************************************************************************
*************************************************************************/
void
EPongStelModule::draw (StelCore * core)
{
  if (!in_game)
    {


      double currentTime = StelApp::getTotalRunTime ();
      Vec3f xy;
      StelProjectorP prj = core->getProjection (StelCore::FrameAltAz);
      StelPainter painter (prj);
      Vec3f countpos;
      countpos.set (0.0f, 0.0f, 1.f);
      prj->project (countpos, xy);
      painter.drawCircle (xy[0], xy[1], 1.f + 200.f * fabs (sin (currentTime)));	//qDebug() << "end of drawing epong";
      painter.drawCircle (xy[0], xy[1], 100.f + 200.f * cos (currentTime));	//qDebug() << "end of drawing epong";

    }
  else
    {
      double currentTime = StelApp::getTotalRunTime ();
      handle_events (currentTime);
      Vec3f xy;
      StelProjectorP prj = core->getProjection (StelCore::FrameAltAz);
      StelPainter painter (prj);
      painter.setColor (1, 1, 1, 1);
      painter.setFont (font);
      painter.setFont (*pongFont);

      Vec3f countpos;
      countpos.set (0.0f, 0.0f, 1.f);
      QString s = QString ("%1").arg (currentTime - gamestarttime, 3, 'f', 1);
      float shiftx = 30.0f;
      float shifty = -10.0f;
      painter.setColor (0.0f, 0.6f, 1.f);
      if (prj->project (countpos, xy))
	painter.drawText (xy[0], xy[1], s, 0, -shiftx, shifty);
      painter.setColor (1.0f, 1.f, 1.f);

      int i;
      for (i = 0; i < PADDLES; i++)
	{

	  Vec3f pos = paddle[i]->pos;

	  prj->project (paddle[i]->pos, xy);
	  //painter.drawCircle (xy[0], xy[1], 100); //qDebug() << "end of drawing epong";
	  const float h = 0.01;
	  painter.drawGreatCircleArc (Vec3d
				      (sin
				       (paddle[i]->total_alpha - paddle[i]->size),
				       cos (paddle[i]->total_alpha -
					    paddle[i]->size), 0),
				      Vec3d (sin
					     (paddle[i]->total_alpha +
					      paddle[i]->size),
					     cos (paddle[i]->total_alpha +
						  paddle[i]->size), 0), NULL);
	  painter.drawGreatCircleArc (Vec3d
				      (sin
				       (paddle[i]->total_alpha - paddle[i]->size),
				       cos (paddle[i]->total_alpha -
					    paddle[i]->size), h),
				      Vec3d (sin
					     (paddle[i]->total_alpha +
					      paddle[i]->size),
					     cos (paddle[i]->total_alpha +
						  paddle[i]->size), h), NULL);
	  painter.drawGreatCircleArc (Vec3d
				      (sin
				       (paddle[i]->total_alpha - paddle[i]->size),
				       cos (paddle[i]->total_alpha -
					    paddle[i]->size), h / 2),
				      Vec3d (sin
					     (paddle[i]->total_alpha +
					      paddle[i]->size),
					     cos (paddle[i]->total_alpha +
						  paddle[i]->size), h / 2), NULL);
	  paddle[i]->pos.normalize ();
	  //   paddle[i]->normal.normalize ();
	}
      for (i = 0; i < BALLS; i++)
	{
	  if (ball[i]->alive)
	    {

	      ball[i]->move ((currentTime - ball[i]->moved) / ball[i]->HTT *
			     PI);

	      for (int j = 0; j < i; j++)
		{
		  if (!ball[i]->alive || !ball[j]->alive)
		    continue;
		  Vec3f dv = ball[i]->pos - ball[j]->pos;
		  if (dv.lengthSquared () < 0.01)
		    {
		      char buffer[OUTPUT_BUFFER_SIZE];
		      osc::OutboundPacketStream p (buffer,
						   OUTPUT_BUFFER_SIZE);
		      p << osc::BeginBundleImmediate << osc::
			BeginMessage ("/collision") << osc::
			EndMessage << osc::EndBundle;
		      transmitSocket->Send (p.Data (), p.Size ());

		    }

		}
	      ball[i]->moved = currentTime;
	      prj->project (ball[i]->pos, xy);
	      painter.drawCircle (xy[0], xy[1], 3);	//qDebug() << "end of drawing epong";
	      painter.drawCircle (xy[0], xy[1], 2);	//qDebug() << "end of drawing epong";
	      if (pevent[i]->type == BALL_BOUNCE)
		{
		  QString text = "";
		  text.setNum (pevent[i]->time - currentTime);

		  //painter.drawText (xy[0], xy[1],text);       //qDebug() << "end of drawing epong";

		}
	      ball[i]->pos.normalize ();
	      ball[i]->normal.normalize ();
	    }
	}
      lastTime = currentTime;
    }
}
