find_package(Python3 COMPONENTS Development NumPy)

catkin_package()

include_directories(
  zmp_generator/include
  zmp_preview_controller/include
  sne_controller/include
)

add_subdirectory(zmp_generator)
add_subdirectory(zmp_preview_controller)
add_subdirectory(sne_controller)

# wheel_controller
add_executable(wheel_controller 
wheel_controller.cpp
../controllers/BaseController.cpp
../basic_op.cpp
../MELEW3_kinematics/MELEW3_Kinematics.cpp
../utils.cpp
sne_controller/src/sne_controller.cpp
zmp_generator/src/zmp_generator.cpp
zmp_preview_controller/src/zmp_preview_controller.cpp
sne_controller/src/sne_controller.cpp
zmp_preview_controller/include/zmp_preview_controller/cart_table.cpp
zmp_preview_controller/include/zmp_preview_controller/pattern_generator.cpp
zmp_preview_controller/include/zmp_preview_controller/preview_controller.cpp
zmp_preview_controller/include/zmp_preview_controller/riccati_solver.cpp
sne_controller/include/sne_controller/nonlinear_equation_solver.hpp
sne_controller/include/sne_controller/nonlinear_equation_solver.cpp
)
add_dependencies(wheel_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(wheel_controller ${catkin_LIBRARIES})
