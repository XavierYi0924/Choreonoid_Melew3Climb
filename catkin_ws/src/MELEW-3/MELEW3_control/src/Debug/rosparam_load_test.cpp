// ros_control内でrosparamを取得する際に色々テストする用のノード
#include <ros/ros.h>

#include <iostream>

int main(int argc, char** argv) {
  ros::init(argc, argv, "rosparam_load_test");
  ros::NodeHandle nh;

  XmlRpc::XmlRpcValue params;
  nh.getParam("/MELEW3", params);

  for (auto params_iterator = params.begin(); params_iterator != params.end(); ++params_iterator) {
    // configの中身を閲覧
    if (params_iterator->second["config"].valid()) {
      std::cout << static_cast<std::string>(params_iterator->first).c_str() << " : "
                << static_cast<double>(params_iterator->second["config"]["Kp"]) << std::endl;
    }
  }

  return 0;
}