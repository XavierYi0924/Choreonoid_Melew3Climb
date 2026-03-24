# Install script for directory: /home/mrp/catkin_ws/src/choreonoid/src/Body

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/locale/ja/LC_MESSAGES" TYPE FILE FILES "/home/mrp/catkin_ws/build/choreonoid/share/locale/ja/LC_MESSAGES/CnoidBody-2.2.mo")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/choreonoid-2.2/cnoid/src/Body" TYPE FILE FILES
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Body.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyHandler.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyHandlerManager.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/CustomJointPathHandler.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/CustomJointPathBase.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/JointSpaceConfigurationHandler.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/LinkedJointHandler.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyCustomizerInterface.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/VRMLBody.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/AbstractBodyLoader.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/VRMLBodyLoader.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyLoader.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/StdBodyLoader.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/StdBodyWriter.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/StdBodyFileUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ZMPSeq.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Link.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ExtraJoint.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/LinkTraverse.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/LinkPath.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/JointTraverse.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/JointPath.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/LinkGroup.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Material.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ContactMaterial.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/MaterialTable.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyCollisionLinkFilter.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyCollisionDetector.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyCollisionDetectorUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/MultiDeviceStateSeq.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Device.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/DeviceList.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/HolderDevice.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/AttachmentDevice.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ConveyorDevice.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/DigitalIoDevice.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/IoConnectionMap.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ForceSensor.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/RateGyroSensor.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/AccelerationSensor.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Imu.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BasicSensorSimulationHelper.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/VisionSensor.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Camera.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/RangeCamera.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/RangeSensor.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Light.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/PointLight.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/SpotLight.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/MarkerDevice.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/SceneBody.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/SceneDevice.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/SceneCollision.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/InverseKinematics.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/CompositeIK.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/CompositeBodyIK.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/PinDragIK.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyKinematicsKit.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/KinematicBodySet.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/LeggedBodyHelper.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ZmpDevice.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/PenetrationBlocker.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ForwardDynamics.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ForwardDynamicsABM.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ForwardDynamicsCBM.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/DyBody.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/DyWorld.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/InverseDynamics.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/Jacobian.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/MassMatrix.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ConstraintForceSolver.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/PoseProvider.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyState.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyStateSeq.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyMotion.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyMotionPoseProvider.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/PoseProviderToBodyMotionConverter.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/BodyMotionUtil.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ExtraBodyStateAccessor.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/CollisionLinkPair.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/CollisionLinkPairList.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/ControllerIO.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/SimpleController.h"
    "/home/mrp/catkin_ws/src/choreonoid/src/Body/exportdecl.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so.2.2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so.2.2")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so.2.2"
         RPATH "$ORIGIN")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/libCnoidBody.so.2.2")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so.2.2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so.2.2")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so.2.2"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so.2.2")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so"
         RPATH "$ORIGIN")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/mrp/catkin_ws/build/choreonoid/lib/libCnoidBody.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so"
         OLD_RPATH "/home/mrp/catkin_ws/build/choreonoid/lib:/home/mrp/catkin_ws/build/choreonoid/lib/choreonoid-2.2:/usr/usr/lib/x86_64-linux-gnu:"
         NEW_RPATH "$ORIGIN")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCnoidBody.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/choreonoid/cmake/ext" TYPE FILE FILES "/home/mrp/catkin_ws/src/choreonoid/src/Body/ChoreonoidBodyBuildFunctions.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mrp/catkin_ws/build/choreonoid/src/Body/pybind11/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/Body/lua/cmake_install.cmake")

endif()

