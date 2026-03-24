# MELEW3_control
add_executable(MELEW3_control MELEW3_control.cpp MELEW3_HWI.cpp basic_op.cpp utils.cpp)
add_dependencies(MELEW3_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(MELEW3_control ${catkin_LIBRARIES})
install(TARGETS MELEW3_control
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# MELEW3_trajectory_generator_node
# add_executable(MELEW3_trajectory_generator_node
#   MELEW3_trajectory_generator.cpp
#   utils.cpp
# )
# target_link_libraries(MELEW3_trajectory_generator_node
#   ${catkin_LIBRARIES}
# )

# MELEW3_fk_calculator_node
# add_executable(MELEW3_fk_calculator_node
#   MELEW3_fk_calculator.cpp
#   utils.cpp
#   MELEW3_kinematics/MELEW3_Kinematics.cpp
# )
# target_link_libraries(MELEW3_fk_calculator_node
#   ${catkin_LIBRARIES}
# )

# MELEW3_ik_calculator_node
# add_executable(MELEW3_ik_calculator_node
#   MELEW3_ik_calculator.cpp
#   utils.cpp
#   MELEW3_kinematics/MELEW3_Kinematics.cpp
# )
# target_link_libraries(MELEW3_ik_calculator_node
#   ${catkin_LIBRARIES}
# )

add_subdirectory(controllers)
add_subdirectory(jumping_control)
add_subdirectory(wheel_control)
add_subdirectory(zmp_calculator)
# add_subdirectory(Debug)
