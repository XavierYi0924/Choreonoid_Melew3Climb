/**
 * @file    MELEW3_HWI.h
 * @author  Yuta Ishizawa
 * @brief   MELEW3の実機用ハードウェアインターフェースのヘッダ
 * @version 1.0
 * @date    2023-08-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MELEW3_HWI_H_
#define MELEW3_HWI_H_

#define USE_DEBUG 0

#include <MELEW3_control/available_motors.h>
#include <MELEW3_control/basic_op.h>
#include <MELEW3_control/motor_status.h>
#include <angles/angles.h>
#include <dynamic_reconfigure/client.h>
#include <dynamic_reconfigure/server.h>
#include <melew3_control/joint_pd_gainConfig.h>
#include <melew3_msgs/GenericMd80Msg.h>
#include <melew3_msgs/ImpedanceCommand.h>
#include <melew3_msgs/motor_info.h>
#include <melew3_msgs/servo_setting.h>
#include <melew3_msgs/set_position_zero.h>
#include <ros/ros.h>

#include <MELEW3_control/param.hpp>
#include <mutex>

namespace MELEW3_control {

class MELEW3_HWI {
private:
  /*** 制御に利用する変数 ***/
  static constexpr double          loop_hz = 300;  //!< 制御周期[Hz]
  ros::NodeHandle                  nh;             //!< NodeHandle
  ros::NodeHandle                  pnh;
  std::map<std::string, uint16_t>  can_id_map;         //!< CAN_idのマップ
  std::map<uint16_t, motor_status> motor_map;          //!< CAN-IDとmotor_statusのマップ
  std::set<std::string>            available_motors;   //!< 利用可能なモータ

  /*** 初期化等で利用する関数 ***/
  void load(void);  //!< rosparamを読み込んで色々と設定
  void init(void);  //!< topic, serviceの初期化

  /*** Pub/Sub通信関係 ***/
  melew3_msgs::ImpedanceCommand FL_leg_impedance_cmd;      //!< 左前脚のモータ設定用のcmd
  melew3_msgs::ImpedanceCommand FR_leg_impedance_cmd;      //!< 右前脚のモータ設定用のcmd
  melew3_msgs::ImpedanceCommand BL_leg_impedance_cmd;      //!< 左後脚のモータ設定用のcmd
  melew3_msgs::ImpedanceCommand BR_leg_impedance_cmd;      //!< 右後脚のモータ設定用のcmd
  ros::Publisher                FL_leg_impedance_cmd_pub;  //!< 左前脚のモータ設定用のcmd用publisher
  ros::Publisher                FR_leg_impedance_cmd_pub;  //!< 右前脚のモータ設定用のcmd用publisher
  ros::Publisher                BL_leg_impedance_cmd_pub;  //!< 左後脚のモータ設定用のcmd用publisher
  ros::Publisher                BR_leg_impedance_cmd_pub;  //!< 右後脚のモータ設定用のcmd用publisher

  /*** PDゲインを調整するためのdynamic_reconfigure関係 ***/
  dynamic_reconfigure::Server<MELEW3_control::joint_pd_gainConfig> config_server;  //!< configを送信するためのserver
  dynamic_reconfigure::Server<MELEW3_control::joint_pd_gainConfig>::CallbackType configure_f;    //!<
  dynamic_reconfigure::Client<MELEW3_control::joint_pd_gainConfig>               config_client;  //!<
  void dynamic_reconfigure_callback(MELEW3_control::joint_pd_gainConfig&,
                                    uint32_t);  //!< dynamic_reconfigure（ゲイン調整）用のコールバック関数

  /*** サービス通信関係 ***/
  ros::ServiceServer set_ZP_server;           //!< 原点出し用のserver
  ros::ServiceServer servo_setting_server;    //!< サーボを設定するためのserver
  ros::ServiceClient FL_zero_md80_client;     //!< 左前脚のゼロ点合わせを行うためのclient
  ros::ServiceClient FR_zero_md80_client;     //!< 右前脚のゼロ点合わせを行うためのclient
  ros::ServiceClient BL_zero_md80_client;     //!< 左後脚のゼロ点合わせを行うためのclient
  ros::ServiceClient BR_zero_md80_client;     //!< 右後脚のゼロ点合わせを行うためのclient
  ros::ServiceClient FL_enable_md80_client;   //!< 左前脚のサーボをONにするためのclient
  ros::ServiceClient FR_enable_md80_client;   //!< 右前脚のサーボをONにするためのclient
  ros::ServiceClient BL_enable_md80_client;   //!< 左後脚のサーボをONにするためのclient
  ros::ServiceClient BR_enable_md80_client;   //!< 右後脚のサーボをONにするためのclient
  ros::ServiceClient FL_disable_md80_client;  //!< 左前脚のサーボをOFFにするためのclient
  ros::ServiceClient FR_disable_md80_client;  //!< 右前脚のサーボをOFFにするためのclient
  ros::ServiceClient BL_disable_md80_client;  //!< 左後脚のサーボをOFFにするためのclient
  ros::ServiceClient BR_disable_md80_client;  //!< 右後脚のサーボをOFFにするためのclient

  /*** モータを動かすための設定に使う関数 ***/
  bool set_ZP_Cb(melew3_msgs::set_position_zero::Request&,
                 melew3_msgs::set_position_zero::Response&);  //!< 原点出し用のコールバック関数
  bool servo_setting_Cb(melew3_msgs::servo_setting::Request&,
                        melew3_msgs::servo_setting::Response&);  //!< サーボを設定するためのコールバック関数

  /*** CAN ID等 ***/
  uint16_t          set_CAN_ID(const int leg_num) { return leg_num + 11; };  //!<モータのCAN_IDを設定
  static const int  can_FL_leg_start_id = FL1 + 11;                          //!< 左前脚の開始CAN_ID
  static const int  can_FR_leg_start_id = FR1 + 11;                          //!< 右前脚の開始CAN_ID
  static const int  can_BL_leg_start_id = BL1 + 11;                          //!< 左前脚の開始CAN_ID
  static const int  can_BR_leg_start_id = BR1 + 11;                          //!< 右前脚の開始CAN_ID
  static const int  can_wheel_start_id = WHEEL_FL + 11;                      //!< 車輪の開始CAN_ID
  static const int  leg_motor_num = SINGLE_LEG_JOINT_NUM;                    //!< 1脚あたりのモータ数
  static const int  wheel_motor_num = LEG_NUM;                               //!< 車輪モータ数
  std::vector<bool> enable_flag;
  bool              motion_flag = false;

public:
  MELEW3_HWI(ros::NodeHandle&);
  ~MELEW3_HWI();

  /*** 時刻や時間を管理 ***/
  ros::Time     getTime() const { return ros::Time::now(); }                 //!< 現在時刻を取得
  ros::Duration getPeriod() const { return ros::Duration(1.0f / loop_hz); }  //!< 制御周期を取得
  ros::Time     receiveTime;  //!< モータ角度を受信した時刻を格納する変数

  /*** MD80への書き込み・読み取り ***/
  bool start_flag = true;
  void writeImpedanceCommand(ros::Time time, ros::Duration period);  //!< モータ設定用のcmdを送信する
};

}  // namespace MELEW3_control

#endif  // MELEW3_H_