#include <MELEW3_control/joint_pd_gainConfig.h>
#include <dynamic_reconfigure/client.h>
#include <ros/ros.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "dynamic_reconfigure_client");
  // clientの第一引数に何を入れればよいか
  dynamic_reconfigure::Client<MELEW3_control::joint_pd_gainConfig> client("MELEW3_joint_pd_gains");
  MELEW3_control::joint_pd_gainConfig                              config;

  while (ros::ok()) {
    config.Hip_Kp = 0.0;
    client.setConfiguration(config);
    ros::Duration(1).sleep();

    config.Hip_Kp = 10.0;
    client.setConfiguration(config);
    ros::Duration(1).sleep();
  }
  return 0;
}