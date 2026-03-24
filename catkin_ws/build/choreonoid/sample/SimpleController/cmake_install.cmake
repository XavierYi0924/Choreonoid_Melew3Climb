# Install script for directory: /home/mrp/catkin_ws/src/choreonoid/sample/SimpleController

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1MinimumController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkPatternController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1LiftupController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SR1WalkGraspController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/choreonoid-2.2/motion/SR1" TYPE FILE FILES
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1WalkPattern1.seq"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1WalkPattern2.seq"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1WalkPattern3.seq"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PA10PickupController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/UniversalRobotPickupController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SampleCrawlerJoystickController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/TankJoystickController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/DoubleArmV7Controller.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/Jaco2Controller.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuSpiderController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/AizuWheelController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SpringModelController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SpringModelController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SpringModelController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/SpringModelController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SpringModelController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SpringModelController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SpringModelController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/SpringModelController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/ConveyorController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/ConveyorController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/ConveyorController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/ConveyorController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/ConveyorController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/ConveyorController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/ConveyorController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/ConveyorController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/CameraSampleController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/FourWheelCarJoystickController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkPositionController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkForceController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkForceController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkForceController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/LinkForceController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkForceController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkForceController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkForceController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/LinkForceController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/HandyRockDrillController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so"
         RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..:$ORIGIN/../..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/simplecontroller/PendulumSampleController.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/choreonoid-2.2/project" TYPE FILE FILES
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1Minimum.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1Walk.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1WalkSlippy.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SlippyMaterialSet.yaml"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1Walk2D.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1Liftup.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SR1WalkinHouse.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/PA10Pickup.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/UR3Pickup.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/UR5Pickup.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/UR10Pickup.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SampleCrawler.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SampleCrawlerJoystick.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/SampleCrawlerSlope.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/Tank.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/TankVisionSensors.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/DoubleArmV7S.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/AizuSpiderNS.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/AizuSpiderSS.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/AizuSpiderDS.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/AizuWheel.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/ControlledSpringModel.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/ConveyorSample.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/FourWheelCarJoystick.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/LinkPositionControl.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/LinkForceControl.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/HandyRockDrill.cnoid"
    "/home/mrp/catkin_ws/src/choreonoid/sample/SimpleController/PendulumSample.cnoid"
    )
endif()

