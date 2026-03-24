// モータが4つの時正常に動作しない．
// デバッグのためのプログラム

#include <melew3_msgs/robot_config.h>
#include <ros/ros.h>

ros::ServiceClient        client;
melew3_msgs::robot_config robot_config;

int main(int argc, char** argv) {
  ros::init(argc, argv, "test_client");
  ros::NodeHandle nh;
  ros::Rate       loop_rate(100);

  client = nh.serviceClient<melew3_msgs::robot_config>("/MELEW3/robot_config");

  robot_config.request.motor.resize(4);

  robot_config.request.motor[0].can_id = 1;
  robot_config.request.motor[1].can_id = 2;
  robot_config.request.motor[2].can_id = 3;
  robot_config.request.motor[3].can_id = 4;

  client.call(robot_config);

  while (ros::ok()) {
    ros::spinOnce;
    loop_rate.sleep();
  }
  return 0;
}