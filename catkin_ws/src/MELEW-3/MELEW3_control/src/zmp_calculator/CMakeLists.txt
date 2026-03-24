include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  "/usr/include/eigen3"
)

# add_dependencies(MELEW3_control
#   ${${PROJECT_NAME}_EXPORTED_TARGETS}
#   ${catkin_EXPORTED_TARGETS}
# )

add_executable(zmp_calculator_node 
  src/zmp_calculator.cpp 
  src/zmp_calculator_node.cpp
  src/filter.cpp
  ../utils.cpp
  ../../include/MELEW3_control/param.hpp
)

target_link_libraries(zmp_calculator_node
  ${catkin_LIBRARIES}
)

add_executable(izmp_calculator_node 
  src/izmp_calculator.cpp 
  src/izmp_calculator_node.cpp
  src/filter.cpp
  ../utils.cpp
  ../../include/MELEW3_control/param.hpp
)

target_link_libraries(izmp_calculator_node
  ${catkin_LIBRARIES}
)