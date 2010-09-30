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

#ifndef EPONG_PONG_HPP_
#define EPONG_PONG_HPP_

#include "StelModule.hpp"
#include <QFont>
#include "VecMath.hpp"
//#include "osc/OscOutboundPacketStream.h"



class PongBall
{
public:
  void move (double alpha);
  void create ();
  Vec3f pos;
  Vec3f normal;
  char event;
  //double event_time;
  bool alive;
  float HTT;
  double moved;
};

class PongPaddle
{
public:
  float total_alpha;
  void move (double alpha);
  void create ();
  Vec3f pos;
  Vec3f normal;
  double moved;
  float size;
};

class PongEvent
{
public:
  float time;
  char type;
};
#endif 
