/**
 * @file 　 sne_controller_node.cpp
 * @author  Taisei Suzuki
 * @brief   SNEを用いて目標脚先軌道を生成するノードを立ち上げるプログラム
 * @version 0.1
 * @date    2023-05-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <sne_controller/sne_controller.hpp>

int main(int argc, char** argv) {
  ros::init(argc, argv, "MelewWheelControllerNode");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  SneController SneController(nh, pnh);
  SneController.Run();

  return 0;
}