include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  "/usr/include/eigen3"
)

add_executable(melew_wheel_controller_node
  src/sne_controller.cpp
  src/melew_wheel_controller_node.cpp
  include/sne_controller/nonlinear_equation_solver.hpp
  include/sne_controller/nonlinear_equation_solver.cpp
  ../zmp_generator/src/zmp_generator.cpp
  ../zmp_preview_controller/src/zmp_preview_controller.cpp
  ../zmp_preview_controller/include/zmp_preview_controller/cart_table.cpp
  ../zmp_preview_controller/include/zmp_preview_controller/pattern_generator.cpp
  ../zmp_preview_controller/include/zmp_preview_controller/preview_controller.cpp
  ../zmp_preview_controller/include/zmp_preview_controller/riccati_solver.cpp
  ../../utils.cpp
)
target_link_libraries(melew_wheel_controller_node
  ${catkin_LIBRARIES}
)

#project(plot_sne_contour)
add_executable(plot_sne_contour src/plot_sne_contour.cpp)
add_dependencies(plot_sne_contour ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(plot_sne_contour PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(plot_sne_contour ${catkin_LIBRARIES} Python3::Python Python3::NumPy)

#project(plot_sne_contour2)
add_executable(plot_sne_contour2
  src/plot_sne_contour2.cpp
  include/sne_controller/nonlinear_equation_solver.hpp
  include/sne_controller/nonlinear_equation_solver.cpp
)
add_dependencies(plot_sne_contour2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(plot_sne_contour2 PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(plot_sne_contour2 ${catkin_LIBRARIES} Python3::Python Python3::NumPy)

#project(plot_sne_contour3)
add_executable(plot_sne_contour3
  src/plot_sne_contour3.cpp
  include/sne_controller/nonlinear_equation_solver.hpp
  include/sne_controller/nonlinear_equation_solver.cpp
)
add_dependencies(plot_sne_contour3 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(plot_sne_contour3 PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(plot_sne_contour3 ${catkin_LIBRARIES} Python3::Python Python3::NumPy)