cmake_minimum_required(VERSION 3.0.2)
project(melew3_msgs)

find_package(catkin REQUIRED COMPONENTS
  std_msgs
  std_srvs
  sensor_msgs
  geometry_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  ImpedanceCommand.msg
  leg_info.msg
  leg_info_set.msg
  leg_info.msg
  leg_pose.msg
  LinkInfoArray.msg
  Motion.msg
  MotionCommand.msg
  motor_info.msg
  PointArray.msg
  waypoint.msg
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  AddMd80s.srv
  enter_control_mode.srv
  exit_control_mode.srv
  FallAvoidanceMotion.srv
  GenericMd80Msg.srv
  robot_config.srv
  servo_setting.srv
  set_pd_gain.srv
  set_position_zero.srv
  SetLimitsMd80.srv
  SetModeMd80s.srv
)


## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
  std_srvs
  sensor_msgs
  geometry_msgs
  melew3_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES AKROS_bridge_msgs
#  CATKIN_DEPENDS can_msgs sensor_msgs std_msgs std_srvs trajectory_msgs
#  DEPENDS system_lib
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)