#include <math.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "test_joint_states_node");
  ros::NodeHandle nh;
  ros::Publisher  test_joint_states_pub = nh.advertise<sensor_msgs::JointState>("/joint_states", 1);
  ros::Rate       loop_rate(1000);

  int count = 0;
  while (ros::ok()) {
    sensor_msgs::JointState js0;
    js0.header.stamp = ros::Time::now();

    js0.name.resize(20);
    js0.name[0] = "FL1_motor";
    js0.name[1] = "FL2_motor";
    js0.name[2] = "FL3_motor";
    js0.name[3] = "FL4_motor";
    js0.name[4] = "FR1_motor";
    js0.name[5] = "FR2_motor";
    js0.name[6] = "FR3_motor";
    js0.name[7] = "FR4_motor";
    js0.name[8] = "BL1_motor";
    js0.name[9] = "BL2_motor";
    js0.name[10] = "BL3_motor";
    js0.name[11] = "BL4_motor";
    js0.name[12] = "BR1_motor";
    js0.name[13] = "BR2_motor";
    js0.name[14] = "BR3_motor";
    js0.name[15] = "BR4_motor";
    js0.name[16] = "wheel_FL_motor";
    js0.name[17] = "wheel_FR_motor";
    js0.name[18] = "wheel_BL_motor";
    js0.name[19] = "wheel_BR_motor";

    js0.position.resize(20);
    /*
    js0.position[0] = sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[1] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[2] = -sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[3] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[4] = 0.0;
    js0.position[5] = 0.0;
    js0.position[6] = 0.0;
    js0.position[7] = 0.0;
    js0.position[8] = sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[9] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[10] = -sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[11] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[12] = 0.0;
    js0.position[13] = 0.0;
    js0.position[14] = 0.0;
    js0.position[15] = 0.0;
    js0.position[16] = 0.0;
    js0.position[17] = 0.0;
    js0.position[18] = 0.0;
    js0.position[19] = 0.0;
    */
    js0.position[0] = sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[1] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[2] = -sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[3] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0) - M_PI / 2.0;
    js0.position[4] = 0.0;
    js0.position[5] = 0.0;
    js0.position[6] = M_PI / 6.0;
    js0.position[7] = -M_PI / 3.0;
    js0.position[8] = sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[9] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[10] = -sin((float)count * (M_PI / 500.0)) * (M_PI / 6.0);
    js0.position[11] = cos((float)count * (M_PI / 500.0)) * (M_PI / 6.0) - M_PI / 2.0;
    js0.position[12] = 0.0;
    js0.position[13] = 0.0;
    js0.position[14] = M_PI / 6.0;
    js0.position[15] = -M_PI / 3.0;
    js0.position[16] = 0.0;
    js0.position[17] = 0.0;
    js0.position[18] = 0.0;
    js0.position[19] = 0.0;

    js0.velocity.resize(20);
    js0.velocity[0] = 0.0;
    js0.velocity[1] = 0.0;
    js0.velocity[2] = 0.0;
    js0.velocity[3] = 0.0;
    js0.velocity[4] = 0.0;
    js0.velocity[5] = 0.0;
    js0.velocity[6] = 0.0;
    js0.velocity[7] = 0.0;
    js0.velocity[8] = 0.0;
    js0.velocity[9] = 0.0;
    js0.velocity[10] = 0.0;
    js0.velocity[11] = 0.0;
    js0.velocity[12] = 0.0;
    js0.velocity[13] = 0.0;
    js0.velocity[14] = 0.0;
    js0.velocity[15] = 0.0;
    js0.velocity[16] = 0.0;
    js0.velocity[17] = 0.0;
    js0.velocity[18] = 0.0;
    js0.velocity[19] = 0.0;

    test_joint_states_pub.publish(js0);
    count++;

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}