include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  "/usr/include/eigen3"
)

add_executable(zmp_preview_controller_node
  src/zmp_preview_controller.cpp
  src/zmp_preview_controller_node.cpp
  include/zmp_preview_controller/cart_table.cpp
  include/zmp_preview_controller/pattern_generator.cpp
  include/zmp_preview_controller/preview_controller.cpp
  include/zmp_preview_controller/riccati_solver.cpp
  ../zmp_generator/src/zmp_generator.cpp
  ../../utils.cpp
)

target_link_libraries(zmp_preview_controller_node
  ${catkin_LIBRARIES}
)

# add_executable(zmp_preview_controller_stay_node
#   src/zmp_preview_controller_stay_node.cpp
#   src/zmp_preview_controller.cpp
#   include/zmp_preview_controller/cart_table.cpp
#   include/zmp_preview_controller/pattern_generator.cpp
#   include/zmp_preview_controller/preview_controller.cpp
#   include/zmp_preview_controller/riccati_solver.cpp
#   include/zmp_preview_controller/trajectory.cpp
#   include/zmp_preview_controller/utils.cpp
# )

# add_executable(zmp_preview_controller_straight_node
#   src/zmp_preview_controller_straight_node.cpp
#   src/zmp_preview_controller.cpp
#   include/zmp_preview_controller/cart_table.cpp
#   include/zmp_preview_controller/pattern_generator.cpp
#   include/zmp_preview_controller/preview_controller.cpp
#   include/zmp_preview_controller/riccati_solver.cpp
#   include/zmp_preview_controller/trajectory.cpp
#   include/zmp_preview_controller/utils.cpp
# )

# add_executable(zmp_preview_controller_slalom_node
#   src/zmp_preview_controller_slalom_node.cpp
#   src/zmp_preview_controller.cpp
#   include/zmp_preview_controller/cart_table.cpp
#   include/zmp_preview_controller/pattern_generator.cpp
#   include/zmp_preview_controller/preview_controller.cpp
#   include/zmp_preview_controller/riccati_solver.cpp
#   include/zmp_preview_controller/trajectory.cpp
#   include/zmp_preview_controller/utils.cpp
# )

# add_executable(zmp_preview_controller_pass_through_node
#   src/zmp_preview_controller_pass_through_node.cpp
#   src/zmp_preview_controller.cpp
#   include/zmp_preview_controller/cart_table.cpp
#   include/zmp_preview_controller/pattern_generator.cpp
#   include/zmp_preview_controller/preview_controller.cpp
#   include/zmp_preview_controller/riccati_solver.cpp
#   include/zmp_preview_controller/trajectory.cpp
#   include/zmp_preview_controller/utils.cpp
# )

# add_executable(zmp_preview_controller_slalom_through_node
#   src/zmp_preview_controller_slalom_through_node.cpp
#   src/zmp_preview_controller.cpp
#   include/zmp_preview_controller/cart_table.cpp
#   include/zmp_preview_controller/pattern_generator.cpp
#   include/zmp_preview_controller/preview_controller.cpp
#   include/zmp_preview_controller/riccati_solver.cpp
#   include/zmp_preview_controller/trajectory.cpp
#   include/zmp_preview_controller/utils.cpp
# )

# target_link_libraries(zmp_preview_controller_stay_node
#   ${catkin_LIBRARIES}
# )

# target_link_libraries(zmp_preview_controller_straight_node
#   ${catkin_LIBRARIES}
# )

# target_link_libraries(zmp_preview_controller_slalom_node
#   ${catkin_LIBRARIES}
# )

# target_link_libraries(zmp_preview_controller_pass_through_node
#   ${catkin_LIBRARIES}
# )

# target_link_libraries(zmp_preview_controller_slalom_through_node
#   ${catkin_LIBRARIES}
# )
