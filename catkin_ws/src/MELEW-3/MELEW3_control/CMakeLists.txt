cmake_minimum_required(VERSION 3.0.2)
project(melew3_control)

# SET(CMAKE_BUILD_TYPE Debug)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  transmission_interface
  controller_manager
  melew3_msgs
  std_msgs
  geometry_msgs
  dynamic_reconfigure
  qpOASES
)

generate_dynamic_reconfigure_options(
  cfg/joint_pd_gain.cfg
)

catkin_package(
  INCLUDE_DIRS include
# LIBRARIES MELEW3_control
  CATKIN_DEPENDS roscpp std_msgs ros_control ros_controllers hardware_interface transmission_interface controller_manager
# DEPENDS system_lib
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  "/usr/include/eigen3"  # To use Eigen
)

add_subdirectory(src)

