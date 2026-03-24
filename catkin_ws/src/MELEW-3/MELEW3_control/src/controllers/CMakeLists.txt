# x_sine_wave
add_executable(x_sine_wave 
  x_sine_wave.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(x_sine_wave ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(x_sine_wave ${catkin_LIBRARIES})

# y_sine_wave
add_executable(y_sine_wave 
  y_sine_wave.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(y_sine_wave ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(y_sine_wave ${catkin_LIBRARIES})

# z_sine_wave
add_executable(z_sine_wave 
  z_sine_wave.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(z_sine_wave ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(z_sine_wave ${catkin_LIBRARIES})

# psi_sine_wave
add_executable(psi_sine_wave 
  psi_sine_wave.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(psi_sine_wave ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(psi_sine_wave ${catkin_LIBRARIES})

# dancing
add_executable(dancing 
  dancing.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(dancing ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(dancing ${catkin_LIBRARIES})

# x_wheel_running
add_executable(wheel_running
  wheel_running.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(wheel_running ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(wheel_running ${catkin_LIBRARIES})

# body_yaw_sine_wave
add_executable(body_yaw_sine_wave 
  body_yaw_sine_wave.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(body_yaw_sine_wave ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(body_yaw_sine_wave ${catkin_LIBRARIES})

# wr_z_sine
add_executable(wr_z_sine
  wr_z_sine.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(wr_z_sine ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(wr_z_sine ${catkin_LIBRARIES})

# low_posture
add_executable(low_posture 
  low_posture.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(low_posture ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(low_posture ${catkin_LIBRARIES})

# body_pitch_tilt
add_executable(body_pitch_tilt 
  body_pitch_tilt.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(body_pitch_tilt ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(body_pitch_tilt ${catkin_LIBRARIES})

# body_tilt_wheel_running
add_executable(body_tilt_wheel_running 
  body_tilt_wheel_running.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(body_tilt_wheel_running ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(body_tilt_wheel_running ${catkin_LIBRARIES})

# walk
add_executable(walk 
  walk.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(walk ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(walk ${catkin_LIBRARIES})

# leg walk walk
add_executable(lw_walk 
  lw_walk.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(lw_walk ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(lw_walk ${catkin_LIBRARIES})

# slide on the ground
add_executable(slide
  slide.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(slide ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(slide ${catkin_LIBRARIES})

# # spiral stairs on 2d_plane
# add_executable(spiral
#   spiral.cpp 
#   BaseController.cpp 
#   ../basic_op.cpp 
#   ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
#   ../utils.cpp
#   )
# add_dependencies(spiral ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# target_link_libraries(spiral ${catkin_LIBRARIES})

# turning
add_executable(turning
  turning.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(turning ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(turning ${catkin_LIBRARIES})

# leg_turning
add_executable(leg_turning
  leg_turning.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(leg_turning ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(leg_turning ${catkin_LIBRARIES})

# wheel_running_several
add_executable(wheel_running_several
  wheel_running_several.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(wheel_running_several ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(wheel_running_several ${catkin_LIBRARIES})

# trans
add_executable(trans
  trans.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(trans ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(trans ${catkin_LIBRARIES})

# trans2
add_executable(trans2
  trans2.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(trans2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(trans2 ${catkin_LIBRARIES})

# trans3
add_executable(trans3
  trans3.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(trans3 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(trans3 ${catkin_LIBRARIES})

# # step
# add_executable(step
#   step.cpp 
#   BaseController.cpp 
#   ../basic_op.cpp 
#   ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
#   ../utils.cpp
#   )
# add_dependencies(step ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# target_link_libraries(step ${catkin_LIBRARIES})

# offline
add_executable(offline
  offline.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(offline ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(offline ${catkin_LIBRARIES})

# turning1
add_executable(turning1
  turning1.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(turning1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(turning1 ${catkin_LIBRARIES})

# turning2
add_executable(turning2
  turning2.cpp 
  BaseController.cpp 
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp 
  ../utils.cpp
  )
add_dependencies(turning2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(turning2 ${catkin_LIBRARIES})