#pragma once

#include <geometry_msgs/PointStamped.h>
#include <melew3_msgs/Motion.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

#include <Eigen/Core>
#include <MELEW3_control/utils.hpp>
#include <zmp_calculator/filter.hpp>

#define LEG_NUM 4  //!< 脚の本数

/**
 * @brief Imaginary ZMP（IZMP）を計測するクラス
 *
 */
class IzmpCalculator {
public:
  IzmpCalculator(ros::NodeHandle nh, ros::NodeHandle pnh);
  void Run();
  void CalcIzmp(const Eigen::Vector3d base_position, const Eigen::Vector3d base_acceleration,
                const Eigen::Vector3d com_position, Eigen::Vector3d& imaginary_zmp);
  void IzmpCalculatorCallback(const sensor_msgs::Imu Imu, const melew3_msgs::Motion Base,
                              const melew3_msgs::Motion Com);

private:
  void ImuCallback(const sensor_msgs::Imu::ConstPtr& Imu);
  void BaseCallback(const melew3_msgs::Motion::ConstPtr& Base);
  void ComCallback(const melew3_msgs::Motion::ConstPtr& Com);

  ros::NodeHandle nh_;                 //!< NodeHandle
  ros::Rate       rate_;               //!< 制御周期
  ros::Publisher  imaginary_zmp_pub_;  //!< IZMP用パブリッシャー
  ros::Subscriber imu_sub_;            //!< IMU用サブスクライバ
  ros::Subscriber base_sub_;           //!< ベースリンク位置用サブスクライバ
  ros::Subscriber com_sub_;            //!< ベースリンク位置用サブスクライバ

  sensor_msgs::Imu    imu_data_;   //!< IMUのデータを一時保存する変数
  melew3_msgs::Motion base_data_;  //!< ベースリンク位置のデータを一時保存する変数
  melew3_msgs::Motion com_data_;   //!< ベースリンク位置のデータを一時保存する変数

  double          dt_;                  //!< 制御周期
  Eigen::Vector3d imaginary_zmp_;       //!< Imaginary ZMP（IZMP）
  bool            enable_flag = false;  //!< IMUのデータが存在するか判定するフラグ
  const double    g = 9.81;             //!< 重力加速度

  /*** util関連のクラスの初期化 ***/
  Utils::Utils util;
  Filter       filter[LEG_NUM];
};