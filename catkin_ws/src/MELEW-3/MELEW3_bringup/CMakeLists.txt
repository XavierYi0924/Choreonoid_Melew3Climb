cmake_minimum_required(VERSION 3.5.0)
project(melew3_bringup)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  melew3_msgs
  choreonoid
)

install(DIRECTORY
  model
  DESTINATION ${CHOREONOID_SHARE_SUBDIR}/MELEW3_bringup
)

catkin_package(SKIP_CMAKE_CONFIG_GENERATION SKIP_PKG_CONFIG_GENERATION)
set(CMAKE_CXX_STANDARD ${CHOREONOID_CXX_STANDARD})
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${catkin_INCLUDE_DIRS})

add_subdirectory(src)