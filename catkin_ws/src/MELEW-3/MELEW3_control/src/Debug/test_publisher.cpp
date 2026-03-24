#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "test_publisher");
  ros::NodeHandle nh;
  ros::Rate       loop_rate(100);

  std::vector<std_msgs::Float64MultiArray> cmd;
  cmd.reserve(3);

  cmd[0].data.resize(2);
  cmd[1].data.resize(2);
  cmd[2].data.resize(2);

  const double wave_freq[3] = {0.5, 1.0, 1.8};

  std::vector<ros::Publisher> cmd_pub;
  cmd_pub.resize(3);
  cmd_pub[0] = nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/Hip_position_controller/command", 1);
  cmd_pub[1] = nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/Knee_position_controller/command", 1);
  cmd_pub[2] = nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/Wheel_position_controller/command", 1);

  ros::Time t_start = ros::Time::now();

  while (ros::ok()) {
    double t = (ros::Time::now() - t_start).toSec();
    for (int i = 0; i < 3; i++) {
      cmd[i].data[0] = sin(2 * M_PI * wave_freq[i] * t);
      cmd[i].data[1] = 2 * M_PI * cos(2 * M_PI * wave_freq[i] * t);
      cmd_pub[i].publish(cmd[i]);
    }
    loop_rate.sleep();
  }
  return 0;
}