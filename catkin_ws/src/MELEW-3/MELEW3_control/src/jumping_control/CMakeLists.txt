# jumping
add_executable(jumping
  jumping.cpp
  VHIP.cpp 
  Calc_Matrix.cpp 
  QP_solve.cpp 
  timer.cpp 
  param.cpp
  ../controllers/BaseController.cpp 
  ../utils.cpp
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp  
  
  )
target_link_libraries(jumping ${catkin_LIBRARIES})

# AM_jumping
add_executable(AM_jumping
  AM_jumping.cpp
  VHIP_AM.cpp 
  Calc_Matrix.cpp 
  QP_solve.cpp 
  timer.cpp 
  param.cpp
  ../controllers/BaseController.cpp 
  ../utils.cpp
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp  
  
  )
target_link_libraries(AM_jumping ${catkin_LIBRARIES})

# z_jumping
add_executable(z_jumping
  z_jumping.cpp
  timer.cpp 
  param.cpp
  ../controllers/BaseController.cpp 
  ../utils.cpp
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp  
  
  )
target_link_libraries(z_jumping ${catkin_LIBRARIES})

# pi_jumping
add_executable(pi_jumping
  pi_jumping.cpp
  timer.cpp 
  param.cpp
  ../controllers/BaseController.cpp 
  ../utils.cpp
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp  
  
  )
target_link_libraries(pi_jumping ${catkin_LIBRARIES})

# running
add_executable(running
  running.cpp
  timer.cpp 
  param.cpp
  ../controllers/BaseController.cpp 
  ../utils.cpp
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp  
  
  )
target_link_libraries(running ${catkin_LIBRARIES})

# body_tilt_jumping
add_executable(body_tilt_jumping
  body_tilt_jumping.cpp
  VHIP.cpp 
  Calc_Matrix.cpp 
  QP_solve.cpp 
  timer.cpp 
  param.cpp
  ../controllers/BaseController.cpp 
  ../utils.cpp
  ../basic_op.cpp 
  ../MELEW3_kinematics/MELEW3_Kinematics.cpp  
  
  )
target_link_libraries(body_tilt_jumping ${catkin_LIBRARIES})