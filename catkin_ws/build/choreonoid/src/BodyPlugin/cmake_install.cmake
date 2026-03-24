# Install script for directory: /home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ja/LC_MESSAGES" TYPE FILE FILES "/home/mrp/catkin_ws/build/choreonoid/share/locale/ja/LC_MESSAGES/CnoidBodyPlugin-2.2.mo")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/choreonoid-2.2/cnoid/src/BodyPlugin" TYPE FILE FILES
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/WorldItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyWorldAddon.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodySelectionManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyItemFileIO.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/OperableSceneBody.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyItemKinematicsKit.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyItemKinematicsKitManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/LinkOffsetFrameListItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/KinematicBodyItemSet.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyPoseItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyPoseListItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/MaterialTableItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/SimulatorItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/SubSimulatorItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/ControllerItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/SimpleControllerItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/CollisionDetectionControllerItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/RegionIntrusionDetectorItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/ControllerLogItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyStateLoggerItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyContactPointLoggerItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyContactPointLogItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/SimulationScriptItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/AISTSimulatorItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/KinematicSimulatorItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/GLVisionSimulatorItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyMotionItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/ZMPSeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/WorldLogFileItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/IoConnectionMapItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/SensorVisualizerItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodySyncCameraItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyMarkerItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodySuperimposerAddon.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyOverwriteAddon.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyElementOverwriteItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/LinkOverwriteItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/DeviceOverwriteItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/KinematicFaultChecker.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/KinematicsBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/SimulationBar.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/LinkDeviceTreeWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/LinkDeviceListView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/LinkPositionView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/LinkPositionWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/JointDisplacementWidgetSet.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/MultiBodyJointDisplacementWidget.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/IoConnectionView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyLibraryView.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/BodyLibrarySelectionDialog.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/CollisionSeq.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/CollisionSeqItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/CollisionSeqEngine.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/AISTSimulatorItem.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/BodyPlugin/exportdecl.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/libCnoidBodyPlugin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/libCnoidBodyPlugin.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/libCnoidBodyPlugin.so"
         RPATH "$ORIGIN:$ORIGIN/..")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2/libCnoidBodyPlugin.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/libCnoidBodyPlugin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/libCnoidBodyPlugin.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/libCnoidBodyPlugin.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN:$ORIGIN/..")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/choreonoid-2.2/libCnoidBodyPlugin.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mrp/catkin_ws/build/choreonoid/src/BodyPlugin/pybind11/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/BodyPlugin/lua/cmake_install.cmake")

endif()

