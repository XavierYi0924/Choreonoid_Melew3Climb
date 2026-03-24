include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  "/usr/include/eigen3"
)

add_executable(zmp_generator_node
  src/zmp_generator.cpp
  src/zmp_generator_node.cpp
  ../../utils.cpp
)

target_link_libraries(zmp_generator_node
  ${catkin_LIBRARIES}
)