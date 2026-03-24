/**
 * @file dynamic_reconfigure_server.cpp
 * @author your name (you@domain.com)
 * @brief Read dynamic reconfigure parameters and show it when they are changed.
 * @version 1.0
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <MELEW3_control/joint_pd_gainConfig.h>
#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>

void callback(MELEW3_control::joint_pd_gainConfig& config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %f, %f, %f, %f, %f, %f", config.Hip_Kp, config.Hip_Kd, config.Knee_Kp, config.Knee_Kd,
           config.Wheel_Kp, config.Wheel_Kd);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "MELEW3_joint_pd_gains");
  dynamic_reconfigure::Server<MELEW3_control::joint_pd_gainConfig>               server;
  dynamic_reconfigure::Server<MELEW3_control::joint_pd_gainConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);
  ros::spin();
}