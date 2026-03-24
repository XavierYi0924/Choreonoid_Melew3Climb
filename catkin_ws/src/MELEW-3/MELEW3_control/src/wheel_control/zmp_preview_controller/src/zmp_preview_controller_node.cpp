/**
 * @file 　 zmp_preview_controller_node.cpp
 * @author  Taisei Suzuki
 * @brief   予見制御を行うノードを立ち上げるプログラム
 * @version 0.1
 * @date    2023-06-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <zmp_preview_controller/zmp_preview_controller.hpp>

int main(int argc, char** argv) {
  ros::init(argc, argv, "ZmpPreviewControllerNode");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  PreviewControl PreviewControl(nh, pnh);
  PreviewControl.Run();

  return 0;
}