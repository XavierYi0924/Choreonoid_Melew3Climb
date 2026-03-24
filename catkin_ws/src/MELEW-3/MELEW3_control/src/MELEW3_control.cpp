/**
 * @file MELEW3_control.cpp
 * @author Taisei Suzuki
 * @brief
 * @version 1.0
 * @date 2023-08-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <MELEW3_control/MELEW3_HWI.h>
#include <ros/ros.h>

#include <memory>

int main(int argc, char** argv) {
  ros::init(argc, argv, "MELEW3_control");
  ros::NodeHandle nh;

  ros::Duration(3.0).sleep();

  std::shared_ptr<MELEW3_control::MELEW3_HWI> robot(new MELEW3_control::MELEW3_HWI(nh));

  ros::Rate         rate(1.0 / robot->getPeriod().toSec());
  ros::AsyncSpinner spinner(3);

  spinner.start();

  while (ros::ok()) {
    //robot->read(robot->getTime(), robot->getPeriod());
    //robot->write(robot->getTime(), robot->getPeriod());
    rate.sleep();
  }
  spinner.stop();
  return 0;
}