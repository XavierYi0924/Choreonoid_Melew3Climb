# Install script for directory: /home/mrp/catkin_ws/src/choreonoid/sample

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
  include("/home/mrp/catkin_ws/build/choreonoid/sample/general/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/SimpleController/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/SceneEffects/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/PoseSeq/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/HRP4C/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/GRobotPlugin/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/Multicopter/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/AGXDynamics/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/Roki/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/Submersible/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/CollisionHandler/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/JoystickTest/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/WRS2018/cmake_install.cmake")
  include("/home/mrp/catkin_ws/build/choreonoid/sample/customizer/cmake_install.cmake")

endif()

