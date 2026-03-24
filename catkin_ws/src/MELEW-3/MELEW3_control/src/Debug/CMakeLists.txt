# test_pub
# add_executable(test_pub test_publisher.cpp)
# target_link_libraries(test_pub ${catkin_LIBRARIES})

# rosparam_load_test
# add_executable(rosparam_load_test rosparam_load_test.cpp)
# target_link_libraries(rosparam_load_test ${catkin_LIBRARIES})

# dynamic_reconfigure_server
# add_executable(dynamic_reconfigure_server dynamic_reconfigure_server.cpp)
# add_dependencies(dynamic_reconfigure_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# target_link_libraries(dynamic_reconfigure_server ${catkin_LIBRARIES})

# dynamic_reconfigure_client
# add_executable(dynamic_reconfigure_client dynamic_reconfigure_client.cpp)
# add_dependencies(dynamic_reconfigure_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# target_link_libraries(dynamic_reconfigure_client ${catkin_LIBRARIES})


# client_test
#add_executable(client_test          client_test.cpp)
#add_dependencies(client_test        ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(client_test   ${catkin_LIBRARIES})

# test_joint_states_node
add_executable(test_joint_states_node test_joint_states_node.cpp)
add_dependencies(test_joint_states_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_joint_states_node ${catkin_LIBRARIES})

# check_IK_FK_real
add_executable(check_IK_FK_real check_IK_FK_real.cpp ../MELEW3_kinematics/MELEW3_Kinematics.cpp)
add_dependencies(check_IK_FK_real ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(check_IK_FK_real ${catkin_LIBRARIES})

# hwi_test
add_executable(hwi_test HWI_test.cpp)
add_dependencies(hwi_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(hwi_test ${catkin_LIBRARIES})