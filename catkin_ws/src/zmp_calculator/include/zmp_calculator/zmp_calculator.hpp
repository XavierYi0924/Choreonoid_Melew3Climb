#pragma once

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/WrenchStamped.h>
#include <ros/ros.h>

#include <Eigen/Core>

#include "msparc_utils.hpp"

enum LR : int { L, R };

/**
 * @brief 実ZMPを計測するクラス
 *
 */
class ZmpCalculator {
public:
  ZmpCalculator(ros::NodeHandle nh, ros::NodeHandle pnh);
  void Run();
  void CalcZmp(const std::vector<Eigen::Vector3d> force_sensor_value,
               const std::vector<Eigen::Vector3d> moment_sensor_value, Eigen::Vector3d& actual_zmp);
  void ZmpCalculatorCallback(const geometry_msgs::WrenchStamped left_ft_sensor,
                             const geometry_msgs::WrenchStamped right_ft_sensor);
  void LeftFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& left_ft_sensor);
  void RightFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& right_ft_sensor);
  void LinkPoseCallback(const geometry_msgs::PoseArray::ConstPtr& poses);

private:
  void _WrenchToVector3d(const geometry_msgs::WrenchStamped ft_sensor, Eigen::Vector3d& force_data,
                         Eigen::Vector3d& moment_data);
  void _Vector3dToPoint(const Eigen::Vector3d actual_zmp, geometry_msgs::Point& point_data);

  ros::NodeHandle nh_;                   //!< NodeHandle
  ros::Rate       rate_;                 //!< 制御周期
  ros::Publisher  actual_zmp_pub_;       //!< 実ZMPのパブリッシャー
  ros::Subscriber left_ft_sensor_sub_;   //!< 左脚の力覚センサ用サブスクライバ
  ros::Subscriber right_ft_sensor_sub_;  //!< 右脚の力覚センサ用サブスクライバ
  ros::Subscriber link_poses_sub_;  //!< 絶対座標系から見た全リンクの位置・速度用サブスクライバ

  geometry_msgs::WrenchStamped left_ft_sensor_data_;  //!< 左脚の力覚センサのデータを一時保存する変数
  geometry_msgs::WrenchStamped right_ft_sensor_data_;  //!< 右脚の力覚センサのデータを一時保存する変数
  geometry_msgs::PoseArray     link_poses_;

  Eigen::Vector2d support_area_min_;  //!< 1脚での支持領域における下限
  Eigen::Vector2d support_area_max_;  //!< 1脚での支持領域における上限

  std::vector<Eigen::Vector3d> ft_sensor_link_pos_;     //!< 絶対座標系から見たFTセンサの位置
  std::vector<Eigen::Matrix3d> ft_sensor_link_ori_;     //!< 絶対座標系から見たFTセンサの姿勢
  int                          ft_sensor_link_num_[2];  //!< FTセンサのあるリンクのID

  double                       dt_;                 //!< 制御周期
  int                          leg_num_;            //!< 脚の本数
  double                       min_contact_force_;  //!< 接地を判定する閾値
  std::vector<bool>            leg_is_contact_;     //!< 脚の接地状態
  std::vector<Eigen::Vector3d> leg_zmp_;            //!< 各脚でのZMP
  std::vector<double>          zmp_balance_;        //!< ZMPの分配バランス
  Eigen::Vector3d              actual_zmp_;         //!< 実ZMP

  mUtil::MsparcUtils ms_util;
};