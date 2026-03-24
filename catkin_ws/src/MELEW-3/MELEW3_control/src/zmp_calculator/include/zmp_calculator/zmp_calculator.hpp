#pragma once

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/WrenchStamped.h>
#include <melew3_msgs/LinkInfoArray.h>
#include <ros/ros.h>

#include <Eigen/Core>
#include <MELEW3_control/utils.hpp>
#include <zmp_calculator/filter.hpp>

#define LEG_NUM 4  //!< 脚の本数

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
  void ZmpCalculatorCallback(const geometry_msgs::WrenchStamped FL_ft_sensor,
                             const geometry_msgs::WrenchStamped FR_ft_sensor,
                             const geometry_msgs::WrenchStamped BL_ft_sensor,
                             const geometry_msgs::WrenchStamped BR_ft_sensor);

private:
  void FLFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& FL_ft_sensor);
  void FRFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& FR_ft_sensor);
  void BLFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& BL_ft_sensor);
  void BRFtSensorCallback(const geometry_msgs::WrenchStamped::ConstPtr& BR_ft_sensor);
  void LinkInfoCallback(const melew3_msgs::LinkInfoArray::ConstPtr& link_info);

  ros::NodeHandle nh_;                //!< NodeHandle
  ros::Rate       rate_;              //!< 制御周期
  ros::Publisher  actual_zmp_pub_;    //!< 実ZMP用パブリッシャー
  ros::Subscriber FL_ft_sensor_sub_;  //!< 左前脚の力覚センサ用サブスクライバ
  ros::Subscriber FR_ft_sensor_sub_;  //!< 右前脚の力覚センサ用サブスクライバ
  ros::Subscriber BL_ft_sensor_sub_;  //!< 左後脚の力覚センサ用サブスクライバ
  ros::Subscriber BR_ft_sensor_sub_;  //!< 右後脚の力覚センサ用サブスクライバ
  ros::Subscriber link_info_sub_;  //!< 絶対座標系から見た全リンクの位置・速度用サブスクライバ

  geometry_msgs::WrenchStamped FL_ft_sensor_data_;  //!< 左前脚の力覚センサのデータを一時保存する変数
  geometry_msgs::WrenchStamped FR_ft_sensor_data_;  //!< 右後脚の力覚センサのデータを一時保存する変数
  geometry_msgs::WrenchStamped BL_ft_sensor_data_;  //!< 左前脚の力覚センサのデータを一時保存する変数
  geometry_msgs::WrenchStamped BR_ft_sensor_data_;  //!< 右後脚の力覚センサのデータを一時保存する変数
  melew3_msgs::LinkInfoArray link_info_;  //!< 絶対座標系から見た全リンクの位置・速度を一時保存する変数

  double                       dt_;                 //!< 制御周期
  double                       min_contact_force_;  //!< 接地を判定する閾値
  std::vector<bool>            leg_is_contact_;     //!< 脚の接地状態
  std::vector<double>          ft_sensor_;          //!< 各脚の力センサの値
  std::vector<Eigen::Vector3d> leg_zmp_;            //!< 各脚でのZMP
  std::vector<double>          zmp_balance_;        //!< ZMPの分配バランス
  Eigen::Vector3d              actual_zmp_;         //!< 実ZMP
  bool enable_flag = false;                         //!< 力センサのデータが存在するか判定するフラグ

  enum leg_num_2 { L, R };                                    //!< 脚の番号（2脚用）
  enum leg_num_4 { FL, FR, BL, BR };                          //!< 脚の番号（4脚用）
  std::vector<Eigen::Vector3d> ft_sensor_link_pos_;           //!< 絶対座標系から見たFTセンサの位置
  std::vector<Eigen::Matrix3d> ft_sensor_link_ori_;           //!< 絶対座標系から見たFTセンサの姿勢
  int                          ft_sensor_link_num_[LEG_NUM];  //!< FTセンサのあるリンクのID
  Eigen::Vector2d              support_area_min_;             //!< 1脚での支持領域における下限
  Eigen::Vector2d              support_area_max_;             //!< 1脚での支持領域における上限

  /*** util関連のクラスの初期化 ***/
  Utils::Utils util;
  Filter       filter[LEG_NUM * 2];
};