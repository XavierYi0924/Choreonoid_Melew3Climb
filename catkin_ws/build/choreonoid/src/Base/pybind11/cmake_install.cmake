# Install script for directory: /home/mrp/catkin_ws/src/choreonoid/src/Base/pybind11

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/mrp/catkin_ws/devel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/choreonoid-2.2/cnoid/src/Base/pybind11" TYPE FILE FILES
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/pybind11/PyBase.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/pybind11/PyItemList.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/pybind11/PyQObjectHolder.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/pybind11/PyQString.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/pybind11/PyQtSignal.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Base/pybind11/exportdecl.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so.2.2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so.2.2")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so.2.2"
         RPATH "$ORIGIN")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/libCnoidPyBase.so.2.2")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so.2.2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so.2.2")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so.2.2"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so.2.2")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so"
         RPATH "$ORIGIN")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/libCnoidPyBase.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidPyBase.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtCore.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtCore.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtCore.so"
         RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/python/cnoid/QtCore.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtCore.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtCore.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtCore.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtCore.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtGui.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtGui.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtGui.so"
         RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/python/cnoid/QtGui.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtGui.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtGui.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtGui.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtGui.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtWidgets.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtWidgets.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtWidgets.so"
         RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/python/cnoid/QtWidgets.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtWidgets.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtWidgets.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtWidgets.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/QtWidgets.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/Base.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/Base.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/Base.so"
         RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/python/cnoid/Base.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/Base.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/Base.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/Base.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/../..:$ORIGIN/../../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/python/cnoid/Base.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

