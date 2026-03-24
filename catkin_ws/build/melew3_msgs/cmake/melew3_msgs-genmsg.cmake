# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "melew3_msgs: 11 messages, 11 services")

set(MSG_I_FLAGS "-Imelew3_msgs:/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Imelew3_msgs:/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(melew3_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg" "std_msgs/Float64:geometry_msgs/Point32"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg" "geometry_msgs/Point32:std_msgs/Float64:melew3_msgs/leg_info"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg" "geometry_msgs/Point:std_msgs/Float64:std_msgs/Header"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg" "geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:geometry_msgs/Twist:std_msgs/Header:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg" "geometry_msgs/Point:std_msgs/Header:geometry_msgs/Vector3"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg" "geometry_msgs/Point:std_msgs/Header"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg" "geometry_msgs/Point:std_msgs/Float64:std_msgs/Header"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv" "std_msgs/Float64MultiArray:std_msgs/MultiArrayDimension:std_msgs/MultiArrayLayout"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv" "melew3_msgs/motor_info"
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv" ""
)

get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv" NAME_WE)
add_custom_target(_melew3_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "melew3_msgs" "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)

### Generating Services
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64MultiArray.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayLayout.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv"
  "${MSG_I_FLAGS}"
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_cpp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
)

### Generating Module File
_generate_module_cpp(melew3_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(melew3_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(melew3_msgs_generate_messages melew3_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_cpp _melew3_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(melew3_msgs_gencpp)
add_dependencies(melew3_msgs_gencpp melew3_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS melew3_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_msg_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)

### Generating Services
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64MultiArray.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayLayout.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv"
  "${MSG_I_FLAGS}"
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)
_generate_srv_eus(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
)

### Generating Module File
_generate_module_eus(melew3_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(melew3_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(melew3_msgs_generate_messages melew3_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_eus _melew3_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(melew3_msgs_geneus)
add_dependencies(melew3_msgs_geneus melew3_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS melew3_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_msg_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)

### Generating Services
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64MultiArray.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayLayout.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv"
  "${MSG_I_FLAGS}"
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)
_generate_srv_lisp(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
)

### Generating Module File
_generate_module_lisp(melew3_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(melew3_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(melew3_msgs_generate_messages melew3_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_lisp _melew3_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(melew3_msgs_genlisp)
add_dependencies(melew3_msgs_genlisp melew3_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS melew3_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_msg_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)

### Generating Services
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64MultiArray.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayLayout.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv"
  "${MSG_I_FLAGS}"
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)
_generate_srv_nodejs(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
)

### Generating Module File
_generate_module_nodejs(melew3_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(melew3_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(melew3_msgs_generate_messages melew3_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_nodejs _melew3_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(melew3_msgs_gennodejs)
add_dependencies(melew3_msgs_gennodejs melew3_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS melew3_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_msg_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)

### Generating Services
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Float64MultiArray.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/MultiArrayLayout.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv"
  "${MSG_I_FLAGS}"
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)
_generate_srv_py(melew3_msgs
  "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
)

### Generating Module File
_generate_module_py(melew3_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(melew3_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(melew3_msgs_generate_messages melew3_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/ImpedanceCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_info_set.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/leg_pose.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/LinkInfoArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/Motion.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/MotionCommand.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/motor_info.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/PointArray.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/msg/waypoint.msg" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/AddMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/enter_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/exit_control_mode.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/FallAvoidanceMotion.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/GenericMd80Msg.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/robot_config.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/servo_setting.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_pd_gain.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/set_position_zero.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetLimitsMd80.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrp/catkin_ws/src/MELEW-3/MELEW3_msgs/srv/SetModeMd80s.srv" NAME_WE)
add_dependencies(melew3_msgs_generate_messages_py _melew3_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(melew3_msgs_genpy)
add_dependencies(melew3_msgs_genpy melew3_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS melew3_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/melew3_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(melew3_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET std_srvs_generate_messages_cpp)
  add_dependencies(melew3_msgs_generate_messages_cpp std_srvs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(melew3_msgs_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(melew3_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET melew3_msgs_generate_messages_cpp)
  add_dependencies(melew3_msgs_generate_messages_cpp melew3_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/melew3_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(melew3_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET std_srvs_generate_messages_eus)
  add_dependencies(melew3_msgs_generate_messages_eus std_srvs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(melew3_msgs_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(melew3_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET melew3_msgs_generate_messages_eus)
  add_dependencies(melew3_msgs_generate_messages_eus melew3_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/melew3_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(melew3_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET std_srvs_generate_messages_lisp)
  add_dependencies(melew3_msgs_generate_messages_lisp std_srvs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(melew3_msgs_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(melew3_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET melew3_msgs_generate_messages_lisp)
  add_dependencies(melew3_msgs_generate_messages_lisp melew3_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/melew3_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(melew3_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET std_srvs_generate_messages_nodejs)
  add_dependencies(melew3_msgs_generate_messages_nodejs std_srvs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(melew3_msgs_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(melew3_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET melew3_msgs_generate_messages_nodejs)
  add_dependencies(melew3_msgs_generate_messages_nodejs melew3_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/melew3_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(melew3_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET std_srvs_generate_messages_py)
  add_dependencies(melew3_msgs_generate_messages_py std_srvs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(melew3_msgs_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(melew3_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET melew3_msgs_generate_messages_py)
  add_dependencies(melew3_msgs_generate_messages_py melew3_msgs_generate_messages_py)
endif()
