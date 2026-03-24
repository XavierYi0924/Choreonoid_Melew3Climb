/**
 * @file    MELEW3_fk_calculator.hpp
 * @author  Taisei Suzuki
 * @brief   潤運動学計算を行うプログラムファイルのヘッダ
 * @version 0.1
 * @date    2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <melew3_msgs/LinkInfoArray.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

#include <Eigen/Core>
#include <MELEW3_control/param.hpp>
#include <MELEW3_control/utils.hpp>

#include "../src/MELEW3_kinematics/MELEW3_Kinematics.h"

#define LINK_NUM_PARALLEL 14
#define LINK_NUM_SERIAL 6

/**
 * @brief リンクの情報を格納する構造体
 *
 */
struct uLINK {
  // リンク情報を格納
public:
  std::string     name;     //!< 名前
  int             mother;   //!< 親リンクID
  double          mass;     //!< 質量
  double          q;        //!< 関節角度
  double          dq;       //!< 関節角速度
  double          alpha;    //!< 球面リンクの角度
  Eigen::Vector3d p;        //!< ワールド座標系から見た自リンク原点位置
  Eigen::Matrix3d R;        //!< ワールド座標系から見た姿勢
  Eigen::Vector3d v;        //!< ワールド座標系から見た速度
  Eigen::Vector3d omega;    //!< ワールド座標系から見た角速度ベクトル
  Eigen::Vector3d com;      //!< 自リンクの重心位置
  Eigen::Vector3d a_link;   //!< 親リンクから見た球面リンクの軸ベクトル
  Eigen::Vector3d a_joint;  //!< 親リンク先端から見た関節軸ベクトル
  Eigen::Vector3d b;        //!< 親リンクから見た自リンクの原点位置
};

/**
 * @brief 各リンクの位置・姿勢・速度・角速度の計算を行うクラス
 *
 */
class MSPARCFKCalculator {
public:
  MSPARCFKCalculator(ros::NodeHandle nh, ros::NodeHandle pnh);
  void CalcMSPARCFKCalculator(const Eigen::VectorXd joint_angle_value, const Eigen::VectorXd joint_angular_value);
  void CalcComCalculator();
  void MSPARCFKCalculatorCallback(const sensor_msgs::JointState joint_state);
  void Run();

  /*** 計算した値を取得する関数 ***/
  std::vector<std::vector<Eigen::Vector3d>>
                               GetLinkPosition();  // resize(LEG_NUM, std::vector<Eigen::Vector3d>(LINK_NUM))
  std::vector<Eigen::Vector3d> GetLinkPosition(const double leg_num);  // resize(LINK_NUM)
  std::vector<std::vector<Eigen::Matrix3d>>
                               GetLinkOrientation();  // resize(LEG_NUM, std::vector<Eigen::Matrix3d>(LINK_NUM))
  std::vector<Eigen::Matrix3d> GetLinkOrientation(const double leg_num);  // resize(LINK_NUM)
  std::vector<std::vector<Eigen::Vector3d>> GetLinkLinear();  // resize(LEG_NUM, std::vector<Eigen::Vector3d>(LINK_NUM))
  std::vector<Eigen::Vector3d>              GetLinkLinear(const double leg_num);  // resize(LINK_NUM)
  std::vector<std::vector<Eigen::Vector3d>>
                               GetLinkAngular();  // resize(LEG_NUM, std::vector<Eigen::Vector3d>(LINK_NUM))
  std::vector<Eigen::Vector3d> GetLinkAngular(const double leg_num);  // resize(LINK_NUM)
  std::vector<Eigen::Vector3d> GetFootPosition();                     // resize(LEG_NUM)
  Eigen::Vector3d              GetFootPosition(const double leg_num);
  std::vector<Eigen::Matrix3d> GetFootOrientation();  // resize(LEG_NUM)
  Eigen::Matrix3d              GetFootOrientation(const double leg_num);
  Eigen::Vector3d              GetCOM();

private:
  void Setlink(const int leg_num, const int _ID, const std::string _name, const int _mother, const double _alpha,
               const Eigen::Vector3d _a_link, const Eigen::Vector3d _a_joint, const Eigen::Vector3d _b);
  void SetAllLink();
  Eigen::Matrix3d Rodrigues(const Eigen::Vector3d omega, const double angle);
  void            _JointStateToVector(const sensor_msgs::JointState joint_state_data, Eigen::VectorXd& position_data,
                                      Eigen::VectorXd& velocity_data);
  void            _VectorToPoseArray(const std::vector<Eigen::Vector3d> position_data,
                                     const std::vector<Eigen::Matrix3d> orientation_data,
                                     geometry_msgs::PoseArray&          pose_array_data);
  void            _VectorToLinkInfoArray(const std::vector<Eigen::Vector3d> position_data,
                                         const std::vector<Eigen::Matrix3d> orientation_data,
                                         const std::vector<Eigen::Vector3d> linear_data,
                                         const std::vector<Eigen::Vector3d> angular_data,
                                         melew3_msgs::LinkInfoArray&       link_info_array_data);
  void            _JointStateRefCallback(const sensor_msgs::JointState::ConstPtr& joint_state);

  /*** ROS関連 ***/
  ros::NodeHandle nh_;               //!< NodeHandle
  ros::Rate       rate_;             //!< 制御周期
  ros::Subscriber joint_state_sub_;  //!< モータ角度用サブスクライバ
  // ros::Publisher  link_info_pub_;    //!< リンク位置・姿勢・角度・角速度用パブリッシャ
  // ros::Publisher  link_com_pub_;     //!< ベースリンクから見た重心位置用パブリッシャ

  /*** メッセージ関連 ***/
  sensor_msgs::JointState      joint_state_;  //!< joint_stateを一時保存する変数
  std::vector<Eigen::VectorXd> q_link_pre;    //!< リンク角度

  std::vector<std::vector<Eigen::Vector3d>> link_position_value;     //!< リンク位置
  std::vector<std::vector<Eigen::Matrix3d>> link_orientation_value;  //!< リンク姿勢
  std::vector<std::vector<Eigen::Vector3d>> link_linear_value;       //!< リンク角度
  std::vector<std::vector<Eigen::Vector3d>> link_angular_value;      //!< リンク角速度
  std::vector<Eigen::Vector3d>              foot_position_value;     //!< 脚先位置
  std::vector<Eigen::Matrix3d>              foot_orientation_value;  //!< 脚先姿勢
  Eigen::Vector3d                           link_com;                //!< ベースリンクから見た重心位置

  /*** 変数関連 ***/
  double                           control_period_;  //!< 制御周期[s]
  double                           time;             //!< 1ループあたりの経過時間[s]
  ros::Time                        t_start;          //!< 脚のタイマー
  std::vector<XmlRpc::XmlRpcValue> link_params;      //!< リンク情報を格納する変数

  bool   sim_flag_;                         //!< シミュレーションか否か
  int    LINK_NUM;                          //!< 1脚あたりのリンク数
  double wheel_diameter_;                   //!< 車輪径[m]
  double FL_leg_offset_x_;                  //!< ベースリンク→左前股関節のx軸オフセット距離[m]
  double FL_leg_offset_y_;                  //!< ベースリンク→左前股関節のy軸オフセット距離[m]
  double FL_leg_offset_z_;                  //!< ベースリンク→左前股関節のz軸オフセット距離[m]
  double FR_leg_offset_x_;                  //!< ベースリンク→右前股関節のx軸オフセット距離[m]
  double FR_leg_offset_y_;                  //!< ベースリンク→右前股関節のy軸オフセット距離[m]
  double FR_leg_offset_z_;                  //!< ベースリンク→右後股関節のz軸オフセット距離[m]
  double BL_leg_offset_x_;                  //!< ベースリンク→左後股関節のx軸オフセット距離[m]
  double BL_leg_offset_y_;                  //!< ベースリンク→左後股関節のy軸オフセット距離[m]
  double BL_leg_offset_z_;                  //!< ベースリンク→左後股関節のz軸オフセット距離[m]
  double BR_leg_offset_x_;                  //!< ベースリンク→右後股関節のx軸オフセット距離[m]
  double BR_leg_offset_y_;                  //!< ベースリンク→右後股関節のy軸オフセット距離[m]
  double BR_leg_offset_z_;                  //!< ベースリンク→右後股関節のz軸オフセット距離[m]
  std::vector<Eigen::Vector3d> leg_offset;  //!< ベースリンク→股関節のオフセット距離[m]

  const double l_sim = 0.20;  //!< シミュレーションの脚長[m]
  const double l1 = 0.12;     //!< 点D1の原点Oからの長さ[m]
  const double l2 = 0.20;     //!< 点D2の原点Oからの長さ[m]
  const double l_A1 = 0.109;  //!< 点A1，点A4の原点Oからの長さ[m]
  const double l_A2 = 0.049;  //!< 点A2，点A3の原点Oからの長さ[m]
  const double l_B1 = 0.097;  //!< 点B1，点B4の原点Oからの長さ[m]
  const double l_B2 = 0.083;  //!< 点B2，点B3の原点Oからの長さ[m]
  const double l_C = 0.0975;  //!< 点C1，点C2の原点Oからの長さ[m]

  const Eigen::Vector3d ux = Eigen::Vector3d::UnitX();  //!< (1.0, 0.0, 0.0)
  const Eigen::Vector3d uy = Eigen::Vector3d::UnitY();  //!< (0.0, 1.0, 0.0)
  const Eigen::Vector3d uz = Eigen::Vector3d::UnitZ();  //!< (0.0, 0.0, 1.0)
  const Eigen::Vector3d u0 = Eigen::Vector3d::Zero();   //!< (0.0, 0.0, 0.0)
  Eigen::Matrix3d       rotate_C;                       //!< 点C1，点C2の回転行列

  /*** クラス・構造体 ***/
  uLINK                                  ulink[LEG_NUM][LINK_NUM_PARALLEL + 1];  //!< リンク情報構造体
  melew3_kinematics::MELEW3_Kinematics MsparcKinematics[LEG_NUM];              //!< 順運動学計算クラス
  Utils::Utils                           util;                                   //!< Utilsクラス
};