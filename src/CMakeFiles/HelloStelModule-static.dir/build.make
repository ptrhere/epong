# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/peter/stellarium-0.10.5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/peter/stellarium-0.10.5

# Include any dependencies generated for this target.
include plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/depend.make

# Include the progress variables for this target.
include plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/flags.make

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/flags.make
plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o: plugins/HelloStelModule/src/HelloStelModule.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/peter/stellarium-0.10.5/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -DQT_STATICPLUGIN -o CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o -c /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/HelloStelModule.cpp

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.i"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -DQT_STATICPLUGIN -E /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/HelloStelModule.cpp > CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.i

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.s"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -DQT_STATICPLUGIN -S /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/HelloStelModule.cpp -o CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.s

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.requires:
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.requires

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.provides: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.requires
	$(MAKE) -f plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/build.make plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.provides.build
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.provides

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.provides.build: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.provides.build

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/flags.make
plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o: plugins/HelloStelModule/src/moc_HelloStelModule.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/peter/stellarium-0.10.5/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -DQT_STATICPLUGIN -o CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o -c /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/moc_HelloStelModule.cxx

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.i"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -DQT_STATICPLUGIN -E /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/moc_HelloStelModule.cxx > CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.i

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.s"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -DQT_STATICPLUGIN -S /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/moc_HelloStelModule.cxx -o CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.s

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.requires:
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.requires

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.provides: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.requires
	$(MAKE) -f plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/build.make plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.provides.build
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.provides

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.provides.build: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.provides.build

plugins/HelloStelModule/src/moc_HelloStelModule.cxx: plugins/HelloStelModule/src/HelloStelModule.hpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/peter/stellarium-0.10.5/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_HelloStelModule.cxx"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && /usr/bin/moc-qt4 -I/usr/include/qt4 -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtCore -I/home/peter/stellarium-0.10.5 -I/home/peter/stellarium-0.10.5/src -I/home/peter/stellarium-0.10.5/src/core -I/home/peter/stellarium-0.10.5/src/core/modules -I/home/peter/stellarium-0.10.5/src/core/planetsephems -I/home/peter/stellarium-0.10.5/src/core/external -I/home/peter/stellarium-0.10.5/src/core/external/kfilter -I/home/peter/stellarium-0.10.5/src/core/external/glues_stel/source -I/home/peter/stellarium-0.10.5/src/core/external/glues_stel/source/libtess -I/home/peter/stellarium-0.10.5/src/gui -I/home/peter/stellarium-0.10.5/src/scripting -I/usr/include -I/home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/. -DPACKAGE_VERSION="0.10.5" -DHAVE_POW10 -DENABLE_NLS -DENABLE_SCRIPT_CONSOLE -DDEFAULT_GRAPHICS_SYSTEM="raster" -DQT_DLL -DQT_OPENGL_LIB -DQT_SCRIPT_LIB -DQT_GUI_LIB -DQT_TEST_LIB -DQT_SQL_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DINSTALL_DATADIR="/usr/local/share/stellarium" -DINSTALL_LOCALEDIR="/usr/local/share/locale" -DQT_NO_DEBUG -DNDEBUG -DQT_PLUGIN -DQT_DLL -D_REENTRANT -o /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/moc_HelloStelModule.cxx /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/HelloStelModule.hpp

# Object files for target HelloStelModule-static
HelloStelModule__static_OBJECTS = \
"CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o" \
"CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o"

# External object files for target HelloStelModule-static
HelloStelModule__static_EXTERNAL_OBJECTS =

plugins/HelloStelModule/src/libHelloStelModule.a: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o
plugins/HelloStelModule/src/libHelloStelModule.a: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o
plugins/HelloStelModule/src/libHelloStelModule.a: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/build.make
plugins/HelloStelModule/src/libHelloStelModule.a: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libHelloStelModule.a"
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && $(CMAKE_COMMAND) -P CMakeFiles/HelloStelModule-static.dir/cmake_clean_target.cmake
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloStelModule-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/build: plugins/HelloStelModule/src/libHelloStelModule.a
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/build

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/requires: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/HelloStelModule.cpp.o.requires
plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/requires: plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/moc_HelloStelModule.cxx.o.requires
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/requires

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/clean:
	cd /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src && $(CMAKE_COMMAND) -P CMakeFiles/HelloStelModule-static.dir/cmake_clean.cmake
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/clean

plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/depend: plugins/HelloStelModule/src/moc_HelloStelModule.cxx
	cd /home/peter/stellarium-0.10.5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/peter/stellarium-0.10.5 /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src /home/peter/stellarium-0.10.5 /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src /home/peter/stellarium-0.10.5/plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/HelloStelModule/src/CMakeFiles/HelloStelModule-static.dir/depend

