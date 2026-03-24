#include <math.h>
#include <melew3_msgs/MotionCommand.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "hwi_test_node");
  ros::NodeHandle nh;
  ros::Publisher  FL_leg_joint_states_pub = nh.advertise<sensor_msgs::JointState>("MELEW3/md80_FL/joint_states", 1);
  ros::Publisher  FR_leg_joint_states_pub = nh.advertise<sensor_msgs::JointState>("MELEW3/md80_FR/joint_states", 1);
  ros::Publisher  BL_leg_joint_states_pub = nh.advertise<sensor_msgs::JointState>("MELEW3/md80_BL/joint_states", 1);
  ros::Publisher  BR_leg_joint_states_pub = nh.advertise<sensor_msgs::JointState>("MELEW3/md80_BR/joint_states", 1);
  ros::Publisher  FL_leg_motion_cmd_pub =
      nh.advertise<melew3_msgs::MotionCommand>("MELEW3/leg_FL_position_controller/motion_command", 1);
  ros::Publisher FR_leg_motion_cmd_pub =
      nh.advertise<melew3_msgs::MotionCommand>("MELEW3/leg_FR_position_controller/motion_command", 1);
  ros::Publisher BL_leg_motion_cmd_pub =
      nh.advertise<melew3_msgs::MotionCommand>("MELEW3/leg_BL_position_controller/motion_command", 1);
  ros::Publisher BR_leg_motion_cmd_pub =
      nh.advertise<melew3_msgs::MotionCommand>("MELEW3/leg_BR_position_controller/motion_command", 1);
  ros::Rate loop_rate(100);

  int count = 0;
  while (ros::ok()) {
    sensor_msgs::JointState FL_leg_joint_states;
    sensor_msgs::JointState FR_leg_joint_states;
    sensor_msgs::JointState BL_leg_joint_states;
    sensor_msgs::JointState BR_leg_joint_states;

    FL_leg_joint_states.header.stamp = ros::Time::now();
    FR_leg_joint_states.header.stamp = ros::Time::now();
    BL_leg_joint_states.header.stamp = ros::Time::now();
    BR_leg_joint_states.header.stamp = ros::Time::now();

    FL_leg_joint_states.name = {"Joint 1", "Joint 2", "Joint 3", "Joint 4", "Joint 17"};
    FR_leg_joint_states.name = {"Joint 5", "Joint 6", "Joint 7", "Joint 8", "Joint 18"};
    BL_leg_joint_states.name = {"Joint 9", "Joint 10", "Joint 11", "Joint 12", "Joint 19"};
    BR_leg_joint_states.name = {"Joint 13", "Joint 14", "Joint 15", "Joint 16", "Joint 20"};

    FL_leg_joint_states.position.resize(5);
    FL_leg_joint_states.position[0] = 0.01 * (2 * (count % 2) - 1);
    FL_leg_joint_states.position[1] = 0.02 * (2 * (count % 2) - 1);
    FL_leg_joint_states.position[2] = 0.03 * (2 * (count % 2) - 1);
    FL_leg_joint_states.position[3] = 0.04 * (2 * (count % 2) - 1);
    FL_leg_joint_states.position[4] = 0.17 * (2 * (count % 2) - 1);
    FR_leg_joint_states.position.resize(5);
    FR_leg_joint_states.position[0] = 0.05 * (2 * (count % 2) - 1);
    FR_leg_joint_states.position[1] = 0.06 * (2 * (count % 2) - 1);
    FR_leg_joint_states.position[2] = 0.07 * (2 * (count % 2) - 1);
    FR_leg_joint_states.position[3] = 0.08 * (2 * (count % 2) - 1);
    FR_leg_joint_states.position[4] = 0.18 * (2 * (count % 2) - 1);
    BL_leg_joint_states.position.resize(5);
    BL_leg_joint_states.position[0] = 0.09 * (2 * (count % 2) - 1);
    BL_leg_joint_states.position[1] = 0.10 * (2 * (count % 2) - 1);
    BL_leg_joint_states.position[2] = 0.11 * (2 * (count % 2) - 1);
    BL_leg_joint_states.position[3] = 0.12 * (2 * (count % 2) - 1);
    BL_leg_joint_states.position[4] = 0.19 * (2 * (count % 2) - 1);
    BR_leg_joint_states.position.resize(5);
    BR_leg_joint_states.position[0] = 0.13 * (2 * (count % 2) - 1);
    BR_leg_joint_states.position[1] = 0.14 * (2 * (count % 2) - 1);
    BR_leg_joint_states.position[2] = 0.15 * (2 * (count % 2) - 1);
    BR_leg_joint_states.position[3] = 0.16 * (2 * (count % 2) - 1);
    BR_leg_joint_states.position[4] = 0.20 * (2 * (count % 2) - 1);

    FL_leg_joint_states.velocity.resize(5);
    FL_leg_joint_states.velocity[0] = -0.01 * (2 * (count % 2) - 1);
    FL_leg_joint_states.velocity[1] = -0.02 * (2 * (count % 2) - 1);
    FL_leg_joint_states.velocity[2] = -0.03 * (2 * (count % 2) - 1);
    FL_leg_joint_states.velocity[3] = -0.04 * (2 * (count % 2) - 1);
    FL_leg_joint_states.velocity[4] = -0.17 * (2 * (count % 2) - 1);
    FR_leg_joint_states.velocity.resize(5);
    FR_leg_joint_states.velocity[0] = -0.05 * (2 * (count % 2) - 1);
    FR_leg_joint_states.velocity[1] = -0.06 * (2 * (count % 2) - 1);
    FR_leg_joint_states.velocity[2] = -0.07 * (2 * (count % 2) - 1);
    FR_leg_joint_states.velocity[3] = -0.08 * (2 * (count % 2) - 1);
    FR_leg_joint_states.velocity[4] = -0.18 * (2 * (count % 2) - 1);
    BL_leg_joint_states.velocity.resize(5);
    BL_leg_joint_states.velocity[0] = -0.09 * (2 * (count % 2) - 1);
    BL_leg_joint_states.velocity[1] = -0.10 * (2 * (count % 2) - 1);
    BL_leg_joint_states.velocity[2] = -0.11 * (2 * (count % 2) - 1);
    BL_leg_joint_states.velocity[3] = -0.12 * (2 * (count % 2) - 1);
    BL_leg_joint_states.velocity[4] = -0.19 * (2 * (count % 2) - 1);
    BR_leg_joint_states.velocity.resize(5);
    BR_leg_joint_states.velocity[0] = -0.13 * (2 * (count % 2) - 1);
    BR_leg_joint_states.velocity[1] = -0.14 * (2 * (count % 2) - 1);
    BR_leg_joint_states.velocity[2] = -0.15 * (2 * (count % 2) - 1);
    BR_leg_joint_states.velocity[3] = -0.16 * (2 * (count % 2) - 1);
    BR_leg_joint_states.velocity[4] = -0.20 * (2 * (count % 2) - 1);

    FL_leg_joint_states.effort.resize(5);
    FL_leg_joint_states.effort[0] = -0.01 * (2 * (count % 2) - 1);
    FL_leg_joint_states.effort[1] = -0.02 * (2 * (count % 2) - 1);
    FL_leg_joint_states.effort[2] = -0.03 * (2 * (count % 2) - 1);
    FL_leg_joint_states.effort[3] = -0.04 * (2 * (count % 2) - 1);
    FL_leg_joint_states.effort[4] = -0.17 * (2 * (count % 2) - 1);
    FR_leg_joint_states.effort.resize(5);
    FR_leg_joint_states.effort[0] = -0.05 * (2 * (count % 2) - 1);
    FR_leg_joint_states.effort[1] = -0.06 * (2 * (count % 2) - 1);
    FR_leg_joint_states.effort[2] = -0.07 * (2 * (count % 2) - 1);
    FR_leg_joint_states.effort[3] = -0.08 * (2 * (count % 2) - 1);
    FR_leg_joint_states.effort[4] = -0.18 * (2 * (count % 2) - 1);
    BL_leg_joint_states.effort.resize(5);
    BL_leg_joint_states.effort[0] = -0.09 * (2 * (count % 2) - 1);
    BL_leg_joint_states.effort[1] = -0.10 * (2 * (count % 2) - 1);
    BL_leg_joint_states.effort[2] = -0.11 * (2 * (count % 2) - 1);
    BL_leg_joint_states.effort[3] = -0.12 * (2 * (count % 2) - 1);
    BL_leg_joint_states.effort[4] = -0.19 * (2 * (count % 2) - 1);
    BR_leg_joint_states.effort.resize(5);
    BR_leg_joint_states.effort[0] = -0.13 * (2 * (count % 2) - 1);
    BR_leg_joint_states.effort[1] = -0.14 * (2 * (count % 2) - 1);
    BR_leg_joint_states.effort[2] = -0.15 * (2 * (count % 2) - 1);
    BR_leg_joint_states.effort[3] = -0.16 * (2 * (count % 2) - 1);
    BR_leg_joint_states.effort[4] = -0.20 * (2 * (count % 2) - 1);

    FL_leg_joint_states_pub.publish(FL_leg_joint_states);
    FR_leg_joint_states_pub.publish(FR_leg_joint_states);
    BL_leg_joint_states_pub.publish(BL_leg_joint_states);
    BR_leg_joint_states_pub.publish(BR_leg_joint_states);

    melew3_msgs::MotionCommand FL_leg_motion_cmd;
    melew3_msgs::MotionCommand FR_leg_motion_cmd;
    melew3_msgs::MotionCommand BL_leg_motion_cmd;
    melew3_msgs::MotionCommand BR_leg_motion_cmd;

    FL_leg_motion_cmd.header.stamp = ros::Time::now();
    FR_leg_motion_cmd.header.stamp = ros::Time::now();
    BL_leg_motion_cmd.header.stamp = ros::Time::now();
    BR_leg_motion_cmd.header.stamp = ros::Time::now();

    FL_leg_motion_cmd.drive_ids = {1, 2, 3, 4, 17};
    FR_leg_motion_cmd.drive_ids = {5, 6, 7, 8, 18};
    BL_leg_motion_cmd.drive_ids = {9, 10, 11, 12, 19};
    BR_leg_motion_cmd.drive_ids = {13, 14, 15, 16, 20};

    FL_leg_motion_cmd.target_position.resize(5);
    FL_leg_motion_cmd.target_position[0] = 0.01 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_position[1] = 0.02 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_position[2] = 0.03 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_position[3] = 0.04 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_position[4] = 0.17 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_position.resize(5);
    FR_leg_motion_cmd.target_position[0] = 0.05 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_position[1] = 0.06 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_position[2] = 0.07 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_position[3] = 0.08 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_position[4] = 0.18 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_position.resize(5);
    BL_leg_motion_cmd.target_position[0] = 0.09 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_position[1] = 0.10 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_position[2] = 0.11 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_position[3] = 0.12 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_position[4] = 0.19 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_position.resize(5);
    BR_leg_motion_cmd.target_position[0] = 0.13 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_position[1] = 0.14 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_position[2] = 0.15 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_position[3] = 0.16 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_position[4] = 0.20 * (2 * (count % 2) - 1);

    FL_leg_motion_cmd.target_velocity.resize(5);
    FL_leg_motion_cmd.target_velocity[0] = -0.01 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_velocity[1] = -0.02 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_velocity[2] = -0.03 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_velocity[3] = -0.04 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_velocity[4] = -0.17 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_velocity.resize(5);
    FR_leg_motion_cmd.target_velocity[0] = -0.05 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_velocity[1] = -0.06 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_velocity[2] = -0.07 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_velocity[3] = -0.08 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_velocity[4] = -0.18 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_velocity.resize(5);
    BL_leg_motion_cmd.target_velocity[0] = -0.09 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_velocity[1] = -0.10 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_velocity[2] = -0.11 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_velocity[3] = -0.12 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_velocity[4] = -0.19 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_velocity.resize(5);
    BR_leg_motion_cmd.target_velocity[0] = -0.13 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_velocity[1] = -0.14 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_velocity[2] = -0.15 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_velocity[3] = -0.16 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_velocity[4] = -0.20 * (2 * (count % 2) - 1);

    FL_leg_motion_cmd.target_torque.resize(5);
    FL_leg_motion_cmd.target_torque[0] = -0.01 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_torque[1] = -0.02 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_torque[2] = -0.03 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_torque[3] = -0.04 * (2 * (count % 2) - 1);
    FL_leg_motion_cmd.target_torque[4] = -0.17 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_torque.resize(5);
    FR_leg_motion_cmd.target_torque[0] = -0.05 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_torque[1] = -0.06 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_torque[2] = -0.07 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_torque[3] = -0.08 * (2 * (count % 2) - 1);
    FR_leg_motion_cmd.target_torque[4] = -0.18 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_torque.resize(5);
    BL_leg_motion_cmd.target_torque[0] = -0.09 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_torque[1] = -0.10 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_torque[2] = -0.11 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_torque[3] = -0.12 * (2 * (count % 2) - 1);
    BL_leg_motion_cmd.target_torque[4] = -0.19 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_torque.resize(5);
    BR_leg_motion_cmd.target_torque[0] = -0.13 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_torque[1] = -0.14 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_torque[2] = -0.15 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_torque[3] = -0.16 * (2 * (count % 2) - 1);
    BR_leg_motion_cmd.target_torque[4] = -0.20 * (2 * (count % 2) - 1);

    FL_leg_motion_cmd_pub.publish(FL_leg_motion_cmd);
    FR_leg_motion_cmd_pub.publish(FR_leg_motion_cmd);
    BL_leg_motion_cmd_pub.publish(BL_leg_motion_cmd);
    BR_leg_motion_cmd_pub.publish(BR_leg_motion_cmd);

    count++;

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}