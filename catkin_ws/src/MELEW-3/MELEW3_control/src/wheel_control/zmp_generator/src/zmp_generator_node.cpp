/**
 * @file 　 zmp_generator.cpp
 * @author  Taisei Suzuki
 * @brief   目標ZMP軌道を生成するノードを立ち上げるプログラム
 * @version 0.1
 * @date    2023-05-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <zmp_generator/zmp_generator.hpp>

int main(int argc, char** argv) {
  ros::init(argc, argv, "ZmpGeneratorNode");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  ZmpGenerator ZmpGenerator(nh, pnh);
  ZmpGenerator.Run();

  return 0;
}