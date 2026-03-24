# Install script for directory: /home/mrp/catkin_ws/src/choreonoid/src

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mrp/catkin_ws/build/choreonoid/src/Util/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/GLSceneRenderer/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/AISTCollisionDetector/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/AssimpSceneLoader/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/Body/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/URDFBodyLoader/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/Corba/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/Base/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/AssimpPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/BodyPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/URDFPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/ManipulatorPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/PoseSeqPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/BalancerPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/BodyMotionFilterPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/MocapPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/SceneEffectsPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/SceneEditPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/MediaPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/FFmpegPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/PythonPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/PythonSimScriptPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/LuaPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/ODEPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/AGXDynamicsPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/BulletPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/PhysXPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/SpringheadPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/RokiPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/MulticopterPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/CorbaPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/TrafficControlPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/FCLPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/PCLPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/CompetitionPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/src/Choreonoid/cmake_install.cmake")

endif()

