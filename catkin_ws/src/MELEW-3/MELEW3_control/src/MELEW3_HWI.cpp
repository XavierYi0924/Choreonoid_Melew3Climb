/**
 * @file    MELEW3_HWI.cpp
 * @author  Taisei Suzuki
 * @brief   MELEW3の実機用ハードウェアインターフェース
 * @version 1.0
 * @date    2023-08-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MELEW3_control/MELEW3_HWI.h>

namespace MELEW3_control {

/**
 * @brief 新しい MELEW3_HWI::MELEW3_HWI オブジェクトを作成
 *
 * @param nh_ ノードハンドラ
 */
MELEW3_HWI::MELEW3_HWI(ros::NodeHandle& nh_) : nh(nh_), pnh("~"), config_client("~") {
  /*** 利用モータやrosparamのロード ***/
  load();

  ROS_INFO("LOAD SUCCESS!");
  /*** MELEW3の初期化処理 ***/
  init();
}

/**
 * @brief MELEW3_HWI::MELEW3_HWI オブジェクトを破棄する
 *
 */
MELEW3_HWI::~MELEW3_HWI() {}

/**
 * @brief MELEW3の各種設定を行うためのパラメータをrosparamからロード
 *
 */
void MELEW3_HWI::load(void) {
  XmlRpc::XmlRpcValue params;

  /*** rosparamをロード ***/
  nh.getParam(nh.getNamespace(), params);

  /*** 利用モータの読み込み ***/
  available_motors.insert(available_motors::AK10_9::model_name);
  available_motors.insert(available_motors::AK80_6::model_name);
  available_motors.insert(available_motors::AK80_9::model_name);
  available_motors.insert(available_motors::AK10_9_OLD::model_name);
  available_motors.insert(available_motors::AK80_6_OLD::model_name);

  /*** rosparam と preserveからモータの設定を読み込む ***/
  for (auto params_itr = params.begin(); params_itr != params.end(); ++params_itr) {
    if (params_itr->second["config"].valid()) {
      motor_status m;
      m.name = static_cast<std::string>(params_itr->second["joint"]);
      m.model = static_cast<std::string>(params_itr->second["config"]["model"]);
      m.can_id = static_cast<uint16_t>(static_cast<int>(params_itr->second["config"]["can_id"]));

      /*** モータが利用可能か確認 ***/
      if (available_motors.find(m.model) == available_motors.end()) {
        ROS_ERROR("Invalid motor model has detected at %s in rosparam !", m.name.c_str());
      } else {
        using namespace available_motors;
        if (m.model == AK10_9::model_name) {
          m.P_MAX = AK10_9::P_MAX;
          m.P_MIN = AK10_9::P_MIN;
          m.V_MAX = AK10_9::V_MAX;
          m.V_MIN = AK10_9::V_MIN;
          m.T_MAX = AK10_9::T_MAX;
          m.T_MIN = AK10_9::T_MIN;
        } else if (m.model == AK80_9::model_name) {
          m.P_MAX = AK80_9::P_MAX;
          m.P_MIN = AK80_9::P_MIN;
          m.V_MAX = AK80_9::V_MAX;
          m.V_MIN = AK80_9::V_MIN;
          m.T_MAX = AK80_9::T_MAX;
          m.T_MIN = AK80_9::T_MIN;
        } else if (m.model == AK80_6::model_name) {
          m.P_MAX = AK80_6::P_MAX;
          m.P_MIN = AK80_6::P_MIN;
          m.V_MAX = AK80_6::V_MAX;
          m.V_MIN = AK80_6::V_MIN;
          m.T_MAX = AK80_6::T_MAX;
          m.T_MIN = AK80_6::T_MIN;
        } else if (m.model == AK10_9_OLD::model_name) {
          m.P_MAX = AK10_9_OLD::P_MAX;
          m.P_MIN = AK10_9_OLD::P_MIN;
          m.V_MAX = AK10_9_OLD::V_MAX;
          m.V_MIN = AK10_9_OLD::V_MIN;
          m.T_MAX = AK10_9_OLD::T_MAX;
          m.T_MIN = AK10_9_OLD::T_MIN;
        } else if (m.model == AK80_6_OLD::model_name) {
          m.P_MAX = AK80_6_OLD::P_MAX;
          m.P_MIN = AK80_6_OLD::P_MIN;
          m.V_MAX = AK80_6_OLD::V_MAX;
          m.V_MIN = AK80_6_OLD::V_MIN;
          m.T_MAX = AK80_6_OLD::T_MAX;
          m.T_MIN = AK80_6_OLD::T_MIN;
        }
      }

      /*** モータ出力の方向を反転させるかどうかをロードする ***/
      if (params_itr->second["config"]["inverseDirection"].valid()) {
        m.inverseDirection = static_cast<bool>(params_itr->second["config"]["inverseDirection"]);
      } else {
        ROS_ERROR("'inverseDirection' is not defined in %s", m.name.c_str());
      }

      /*** オフセット角度をロードする ***/
      if (params_itr->second["config"]["offset"].valid()) {
        m.offset = deg2rad(static_cast<double>(params_itr->second["config"]["offset"]));
      } else {
        ROS_ERROR("'offset' is not defined in %s", m.name.c_str());
      }

      /*** joint_limit ***/
      if (params_itr->second["config"]["joint_limit"].valid()) {
        m.P_MIN = angles::from_degrees(static_cast<double>(params_itr->second["config"]["joint_limit"][0]));
        m.P_MAX = angles::from_degrees(static_cast<double>(params_itr->second["config"]["joint_limit"][1]));
      } else {
        ROS_WARN("%s has no limit !", m.name.c_str());
      }

      /*** max_output ***/
      if (params_itr->second["config"]["max_output"].valid()) {
        m.max_output = static_cast<double>(params_itr->second["config"]["max_output"]);
      } else {
        ROS_WARN("%s has no max_output !", m.name.c_str());
      }

      /*** モータのcan_idとmotor_status構造体の対応付け ***/
      can_id_map[m.name] = m.can_id;
      motor_map[m.can_id] = m;
    }
  }

  /*** 各マイコンへ送信するcmdのリサイズ ***/
  FL_leg_impedance_cmd.drive_ids.resize(leg_motor_num + 1);
  FR_leg_impedance_cmd.drive_ids.resize(leg_motor_num + 1);
  BL_leg_impedance_cmd.drive_ids.resize(leg_motor_num + 1);
  BR_leg_impedance_cmd.drive_ids.resize(leg_motor_num + 1);
  FL_leg_impedance_cmd.kp.resize(leg_motor_num + 1);
  FR_leg_impedance_cmd.kp.resize(leg_motor_num + 1);
  BL_leg_impedance_cmd.kp.resize(leg_motor_num + 1);
  BR_leg_impedance_cmd.kp.resize(leg_motor_num + 1);
  FL_leg_impedance_cmd.kd.resize(leg_motor_num + 1);
  FR_leg_impedance_cmd.kd.resize(leg_motor_num + 1);
  BL_leg_impedance_cmd.kd.resize(leg_motor_num + 1);
  BR_leg_impedance_cmd.kd.resize(leg_motor_num + 1);
  FL_leg_impedance_cmd.max_output.resize(leg_motor_num + 1);
  FR_leg_impedance_cmd.max_output.resize(leg_motor_num + 1);
  BL_leg_impedance_cmd.max_output.resize(leg_motor_num + 1);
  BR_leg_impedance_cmd.max_output.resize(leg_motor_num + 1);
}

/**
 * @brief MELEW3の初期化処理を実行
 *
 */
void MELEW3_HWI::init(void) {
  /*** pub/subの初期化 ***/
  FL_leg_impedance_cmd_pub = nh.advertise<melew3_msgs::ImpedanceCommand>(
      pnh.param<std::string>("/md80_FL/impedance_command_topic_name", "/md80_FL/impedance_command"), 1);
  FR_leg_impedance_cmd_pub = nh.advertise<melew3_msgs::ImpedanceCommand>(
      pnh.param<std::string>("/md80_FR/impedance_command_topic_name", "/md80_FR/impedance_command"), 1);
  BL_leg_impedance_cmd_pub = nh.advertise<melew3_msgs::ImpedanceCommand>(
      pnh.param<std::string>("/md80_BL/impedance_command_topic_name", "/md80_BL/impedance_command"), 1);
  BR_leg_impedance_cmd_pub = nh.advertise<melew3_msgs::ImpedanceCommand>(
      pnh.param<std::string>("/md80_BR/impedance_command_topic_name", "/md80_BR/impedance_command"), 1);

  /*** server / clientの初期化 ***/
  set_ZP_server = nh.advertiseService("set_position_to_zero", &MELEW3_HWI::set_ZP_Cb, this);
  servo_setting_server = nh.advertiseService("servo_setting", &MELEW3_HWI::servo_setting_Cb, this);
  FL_zero_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/zero_md80s_FL_service_name", "/zero_md80s_FL"));
  FR_zero_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/zero_md80s_FR_service_name", "/zero_md80s_FR"));
  BL_zero_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/zero_md80s_BL_service_name", "/zero_md80s_BL"));
  BR_zero_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/zero_md80s_BR_service_name", "/zero_md80s_BR"));
  FL_enable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/enable_md80s_FL_service_name", "/enable_md80s_FL"));
  FR_enable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/enable_md80s_FR_service_name", "/enable_md80s_FR"));
  BL_enable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/enable_md80s_BL_service_name", "/enable_md80s_BL"));
  BR_enable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/enable_md80s_BR_service_name", "/enable_md80s_BR"));
  FL_disable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/disable_md80s_FL_service_name", "/disable_md80s_FL"));
  FR_disable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/disable_md80s_FR_service_name", "/disable_md80s_FR"));
  BL_disable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/disable_md80s_BL_service_name", "/disable_md80s_BL"));
  BR_disable_md80_client = nh.serviceClient<melew3_msgs::GenericMd80Msg>(
      pnh.param<std::string>("/disable_md80s_BR_service_name", "/disable_md80s_BR"));

  /*** dynamic reconfigureの設定 ***/
  configure_f = boost::bind(&MELEW3_HWI::dynamic_reconfigure_callback, this, _1, _2);
  config_server.setCallback(configure_f);

  enable_flag.resize(LEG_NUM);
  for (int i = 0; i < LEG_NUM; i++) enable_flag[i] = false;
}

/**
 * @brief dynamic_reconfigurationのパラメータが変更されたときに呼び出されるコールバック関数
 *
 * @param config ジョイントのPD情報
 * @param level
 */
void MELEW3_HWI::dynamic_reconfigure_callback(MELEW3_control::joint_pd_gainConfig& config, uint32_t level) {
  for (auto& e : motor_map) {
    if (e.second.name == "FL1_motor") {
      e.second.Kp = config.FL1_motor_Kp;
      e.second.Kd = config.FL1_motor_Kd;
    } else if (e.second.name == "FL2_motor") {
      e.second.Kp = config.FL2_motor_Kp;
      e.second.Kd = config.FL2_motor_Kd;
    } else if (e.second.name == "FL3_motor") {
      e.second.Kp = config.FL3_motor_Kp;
      e.second.Kd = config.FL3_motor_Kd;
    } else if (e.second.name == "FL4_motor") {
      e.second.Kp = config.FL4_motor_Kp;
      e.second.Kd = config.FL4_motor_Kd;
    } else if (e.second.name == "FR1_motor") {
      e.second.Kp = config.FR1_motor_Kp;
      e.second.Kd = config.FR1_motor_Kd;
    } else if (e.second.name == "FR2_motor") {
      e.second.Kp = config.FR2_motor_Kp;
      e.second.Kd = config.FR2_motor_Kd;
    } else if (e.second.name == "FR3_motor") {
      e.second.Kp = config.FR3_motor_Kp;
      e.second.Kd = config.FR3_motor_Kd;
    } else if (e.second.name == "FR4_motor") {
      e.second.Kp = config.FR4_motor_Kp;
      e.second.Kd = config.FR4_motor_Kd;
    } else if (e.second.name == "BL1_motor") {
      e.second.Kp = config.BL1_motor_Kp;
      e.second.Kd = config.BL1_motor_Kd;
    } else if (e.second.name == "BL2_motor") {
      e.second.Kp = config.BL2_motor_Kp;
      e.second.Kd = config.BL2_motor_Kd;
    } else if (e.second.name == "BL3_motor") {
      e.second.Kp = config.BL3_motor_Kp;
      e.second.Kd = config.BL3_motor_Kd;
    } else if (e.second.name == "BL4_motor") {
      e.second.Kp = config.BL4_motor_Kp;
      e.second.Kd = config.BL4_motor_Kd;
    } else if (e.second.name == "BR1_motor") {
      e.second.Kp = config.BR1_motor_Kp;
      e.second.Kd = config.BR1_motor_Kd;
    } else if (e.second.name == "BR2_motor") {
      e.second.Kp = config.BR2_motor_Kp;
      e.second.Kd = config.BR2_motor_Kd;
    } else if (e.second.name == "BR3_motor") {
      e.second.Kp = config.BR3_motor_Kp;
      e.second.Kd = config.BR3_motor_Kd;
    } else if (e.second.name == "BR4_motor") {
      e.second.Kp = config.BR4_motor_Kp;
      e.second.Kd = config.BR4_motor_Kd;
    } else if (e.second.name == "wheel_FL_motor") {
      e.second.Kp = config.wheel_FL_motor_Kp;
      e.second.Kd = config.wheel_FL_motor_Kd;
    } else if (e.second.name == "wheel_FR_motor") {
      e.second.Kp = config.wheel_FR_motor_Kp;
      e.second.Kd = config.wheel_FR_motor_Kd;
    } else if (e.second.name == "wheel_BL_motor") {
      e.second.Kp = config.wheel_BL_motor_Kp;
      e.second.Kd = config.wheel_BL_motor_Kd;
    } else if (e.second.name == "wheel_BR_motor") {
      e.second.Kp = config.wheel_BR_motor_Kp;
      e.second.Kd = config.wheel_BR_motor_Kd;
    }
  }
  if (config.Send) {
    /*** モータ設定用のcmdを送信 ***/
    writeImpedanceCommand(getTime(), getPeriod());
    config.Send = false;
  }
}

/**
 * @brief set_zero_positionサービスのコールバック関数で、関節のゼロ位置をリセット
 *
 * @param req ゼロ点の位置を変えたいCAN_ID
 * @param res succeeded or not
 * @return    true
 * @return    false
 */
bool MELEW3_HWI::set_ZP_Cb(melew3_msgs::set_position_zero::Request&  req,
                           melew3_msgs::set_position_zero::Response& res) {
  ROS_INFO("set_zero_position");
  try {
    /*** すべてのモータを設定 ***/
    if (req.name == "ALL") {
      melew3_msgs::GenericMd80Msg FL_srv, FR_srv, BL_srv, BR_srv;
      FL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FL_srv.request.drive_ids[0] = set_CAN_ID(FL1);
      FL_srv.request.drive_ids[1] = set_CAN_ID(FL2);
      FL_srv.request.drive_ids[2] = set_CAN_ID(FL3);
      FL_srv.request.drive_ids[3] = set_CAN_ID(FL4);
      FL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FL);
      FR_srv.request.drive_ids[0] = set_CAN_ID(FR1);
      FR_srv.request.drive_ids[1] = set_CAN_ID(FR2);
      FR_srv.request.drive_ids[2] = set_CAN_ID(FR3);
      FR_srv.request.drive_ids[3] = set_CAN_ID(FR4);
      FR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FR);
      BL_srv.request.drive_ids[0] = set_CAN_ID(BL1);
      BL_srv.request.drive_ids[1] = set_CAN_ID(BL2);
      BL_srv.request.drive_ids[2] = set_CAN_ID(BL3);
      BL_srv.request.drive_ids[3] = set_CAN_ID(BL4);
      BL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BL);
      BR_srv.request.drive_ids[0] = set_CAN_ID(BR1);
      BR_srv.request.drive_ids[1] = set_CAN_ID(BR2);
      BR_srv.request.drive_ids[2] = set_CAN_ID(BR3);
      BR_srv.request.drive_ids[3] = set_CAN_ID(BR4);
      BR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BR);

      /*** ゼロ点の位置を変えたいモータのCAN_IDをMD80に送信 ***/
      if (!((FL_zero_md80_client.call(FL_srv)) & (FR_zero_md80_client.call(FR_srv)) &
            (BL_zero_md80_client.call(BL_srv)) & (BR_zero_md80_client.call(BR_srv)))) {
        ROS_ERROR("Failed to connect with MD80s !");
        res.success = false;
        return false;
      }
      ROS_INFO("Set zero position of all motors !");
    }

    /*** 左前脚のモータを設定 ***/
    else if (req.name == "FL") {
      melew3_msgs::GenericMd80Msg FL_srv;
      FL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FL_srv.request.drive_ids[0] = set_CAN_ID(FL1);
      FL_srv.request.drive_ids[1] = set_CAN_ID(FL2);
      FL_srv.request.drive_ids[2] = set_CAN_ID(FL3);
      FL_srv.request.drive_ids[3] = set_CAN_ID(FL4);
      FL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FL);

      /*** ゼロ点の位置を変えたいモータのCAN_IDをMD80に送信 ***/
      if (!FL_zero_md80_client.call(FL_srv)) {
        ROS_ERROR("Failed to connect with MD80s !");
        res.success = false;
        return false;
      }
      ROS_INFO("Set zero position of FL_leg motors !");
    }

    /*** 右前脚のモータを設定 ***/
    else if (req.name == "FR") {
      melew3_msgs::GenericMd80Msg FR_srv;
      FR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FR_srv.request.drive_ids[0] = set_CAN_ID(FR1);
      FR_srv.request.drive_ids[1] = set_CAN_ID(FR2);
      FR_srv.request.drive_ids[2] = set_CAN_ID(FR3);
      FR_srv.request.drive_ids[3] = set_CAN_ID(FR4);
      FR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FR);

      /*** ゼロ点の位置を変えたいモータのCAN_IDをMD80に送信 ***/
      if (!FR_zero_md80_client.call(FR_srv)) {
        ROS_ERROR("Failed to connect with MD80s !");
        res.success = false;
        return false;
      }
      ROS_INFO("Set zero position of FR_leg motors !");
    }

    /*** 左後脚のモータを設定 ***/
    else if (req.name == "BL") {
      melew3_msgs::GenericMd80Msg BL_srv;
      BL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BL_srv.request.drive_ids[0] = set_CAN_ID(BL1);
      BL_srv.request.drive_ids[1] = set_CAN_ID(BL2);
      BL_srv.request.drive_ids[2] = set_CAN_ID(BL3);
      BL_srv.request.drive_ids[3] = set_CAN_ID(BL4);
      BL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BL);

      /*** ゼロ点の位置を変えたいモータのCAN_IDをMD80に送信 ***/
      if (!BL_zero_md80_client.call(BL_srv)) {
        ROS_ERROR("Failed to connect with MD80s !");
        res.success = false;
        return false;
      }
      ROS_INFO("Set zero position of BL_leg motors !");
    }

    /*** 右後脚のモータを設定 ***/
    else if (req.name == "BR") {
      melew3_msgs::GenericMd80Msg BR_srv;
      BR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BR_srv.request.drive_ids[0] = set_CAN_ID(BR1);
      BR_srv.request.drive_ids[1] = set_CAN_ID(BR2);
      BR_srv.request.drive_ids[2] = set_CAN_ID(BR3);
      BR_srv.request.drive_ids[3] = set_CAN_ID(BR4);
      BR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BR);

      /*** ゼロ点の位置を変えたいモータのCAN_IDをMD80に送信 ***/
      if (!BR_zero_md80_client.call(BR_srv)) {
        ROS_ERROR("Failed to connect with MD80s !");
        res.success = false;
        return false;
      }
      ROS_INFO("Set zero position of BR_leg motors !");
    }

    /*** 車輪のモータを設定 ***/
    else if (req.name == "WHEEL") {
      melew3_msgs::GenericMd80Msg FL_srv, FR_srv, BL_srv, BR_srv;
      FL_srv.request.drive_ids = {set_CAN_ID(WHEEL_FL)};
      FR_srv.request.drive_ids = {set_CAN_ID(WHEEL_FR)};
      BL_srv.request.drive_ids = {set_CAN_ID(WHEEL_BL)};
      BR_srv.request.drive_ids = {set_CAN_ID(WHEEL_BR)};

      /*** ゼロ点の位置を変えたいモータのCAN_IDをMD80に送信 ***/
      if (!((FL_zero_md80_client.call(FL_srv)) & (FR_zero_md80_client.call(FR_srv)) &
            (BL_zero_md80_client.call(BL_srv)) & (BR_zero_md80_client.call(BR_srv)))) {
        ROS_ERROR("Failed to connect with MD80s !");
        res.success = false;
        return false;
      }
      ROS_INFO("Set zero position of wheel motors !");
    }

    /*** 個々のモータを設定 ***/
    else {
      melew3_msgs::GenericMd80Msg srv;
      uint16_t                    id = can_id_map.at(req.name);
      srv.request.drive_ids = {id};

      /*** ゼロ点の位置を変えたいモータのCAN_IDをMD80に送信 ***/
      if (id == set_CAN_ID(FL1) || id == set_CAN_ID(FL2) || id == set_CAN_ID(FL3) || id == set_CAN_ID(FL4) ||
          id == set_CAN_ID(WHEEL_FL)) {
        if (!FL_zero_md80_client.call(srv)) {
          ROS_ERROR("Failed to connect with the MD80 !");
          res.success = false;
          return false;
        }

      } else if (id == set_CAN_ID(FR1) || id == set_CAN_ID(FR2) || id == set_CAN_ID(FR3) || id == set_CAN_ID(FR4) ||
                 id == set_CAN_ID(WHEEL_FR)) {
        if (!FR_zero_md80_client.call(srv)) {
          ROS_ERROR("Failed to connect with the MD80 !");
          res.success = false;
          return false;
        }

      } else if (id == set_CAN_ID(BL1) || id == set_CAN_ID(BL2) || id == set_CAN_ID(BL3) || id == set_CAN_ID(BL4) ||
                 id == set_CAN_ID(WHEEL_BL)) {
        if (!BL_zero_md80_client.call(srv)) {
          ROS_ERROR("Failed to connect with the MD80 !");
          res.success = false;
          return false;
        }

      } else if (id == set_CAN_ID(BR1) || id == set_CAN_ID(BR2) || id == set_CAN_ID(BR3) || id == set_CAN_ID(BR4) ||
                 id == set_CAN_ID(WHEEL_BR)) {
        if (!BR_zero_md80_client.call(srv)) {
          ROS_ERROR("Failed to connect with the MD80 !");
          res.success = false;
          return false;
        }
      }
      ROS_INFO("Set zero position of %s !", req.name.c_str());
    }

    res.success = true;
    return true;

  } catch (std::out_of_range&) {
    /*** 例外処理 ***/
    ROS_ERROR("Failed to search the motor !");
    res.success = false;
    return false;
  }
}

/**
 * @brief ロボット関節のONとOFFを設定するコールバック関数
 *        dynamic reconfigureによりPDゲインを変更できる
 *
 * @param req
 * @param res
 * @return true
 * @return false
 */
bool MELEW3_HWI::servo_setting_Cb(melew3_msgs::servo_setting::Request& req, melew3_msgs::servo_setting::Response& res) {
  ROS_INFO("Servo setting");
  MELEW3_control::joint_pd_gainConfig gain_config;
  config_client.getCurrentConfiguration(gain_config, ros::Duration(0.1));
  std::string Kp_param, Kd_param;
  double      Kp_tmp, Kd_tmp;

  try {
    /*** すべてのモータを設定 ***/
    if (req.name == "ALL") {
      melew3_msgs::GenericMd80Msg FL_srv, FR_srv, BL_srv, BR_srv;
      FL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FL_srv.request.drive_ids[0] = set_CAN_ID(FL1);
      FL_srv.request.drive_ids[1] = set_CAN_ID(FL2);
      FL_srv.request.drive_ids[2] = set_CAN_ID(FL3);
      FL_srv.request.drive_ids[3] = set_CAN_ID(FL4);
      FL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FL);
      FR_srv.request.drive_ids[0] = set_CAN_ID(FR1);
      FR_srv.request.drive_ids[1] = set_CAN_ID(FR2);
      FR_srv.request.drive_ids[2] = set_CAN_ID(FR3);
      FR_srv.request.drive_ids[3] = set_CAN_ID(FR4);
      FR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FR);
      BL_srv.request.drive_ids[0] = set_CAN_ID(BL1);
      BL_srv.request.drive_ids[1] = set_CAN_ID(BL2);
      BL_srv.request.drive_ids[2] = set_CAN_ID(BL3);
      BL_srv.request.drive_ids[3] = set_CAN_ID(BL4);
      BL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BL);
      BR_srv.request.drive_ids[0] = set_CAN_ID(BR1);
      BR_srv.request.drive_ids[1] = set_CAN_ID(BR2);
      BR_srv.request.drive_ids[2] = set_CAN_ID(BR3);
      BR_srv.request.drive_ids[3] = set_CAN_ID(BR4);
      BR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BR);

      /*** ロボット関節のONとOFFを切り替えたいモータのCAN_IDをMD80に送信 ***/
      if (req.servo == true) {
        if (!((FL_enable_md80_client.call(FL_srv)) & (FR_enable_md80_client.call(FR_srv)) &
              (BL_enable_md80_client.call(BL_srv)) & (BR_enable_md80_client.call(BR_srv))))
          throw "Failed to connect with MD80s !";
        for (int i = 0; i < LEG_NUM; i++) enable_flag[i] = true;
      } else {
        if (!((FL_disable_md80_client.call(FL_srv)) & (FR_disable_md80_client.call(FR_srv)) &
              (BL_disable_md80_client.call(BL_srv)) & (BR_disable_md80_client.call(BR_srv))))
          throw "Failed to connect with MD80s !";
        for (int i = 0; i < LEG_NUM; i++) enable_flag[i] = false;
      }

      for (auto& m : motor_map) {
        /*** ON-OFFが変化した場合 ***/
        if (!(m.second.servo_mode == req.servo)) {
          /*** サーボをOFFからONに切り替える場合 ***/
          if (req.servo == true) {
            /*** KpとKdをロードし更新 ***/
            Kp_param = nh.getNamespace() + "/" + m.second.name + "_position_controller/config/Kp";
            Kd_param = nh.getNamespace() + "/" + m.second.name + "_position_controller/config/Kd";

            /*** 例外処理 ***/
            if (!nh.getParam(Kp_param, Kp_tmp)) throw "Failed to get" + m.second.name + "P gain !";
            if (!nh.getParam(Kd_param, Kd_tmp)) throw "Failed to get" + m.second.name + "D gain !";
          }

          /*** ON -> OFFの場合 ***/
          else {
            /*** PDゲインを全て0にする ***/
            Kp_tmp = 0.0;
            Kd_tmp = 0.0;
          }

          /*** PDゲインの値を格納 ***/
          if (m.second.name == "FL1_motor") {
            gain_config.FL1_motor_Kp = Kp_tmp;
            gain_config.FL1_motor_Kd = Kd_tmp;
          } else if (m.second.name == "FL2_motor") {
            gain_config.FL2_motor_Kp = Kp_tmp;
            gain_config.FL2_motor_Kd = Kd_tmp;
          } else if (m.second.name == "FL3_motor") {
            gain_config.FL3_motor_Kp = Kp_tmp;
            gain_config.FL3_motor_Kd = Kd_tmp;
          } else if (m.second.name == "FL4_motor") {
            gain_config.FL4_motor_Kp = Kp_tmp;
            gain_config.FL4_motor_Kd = Kd_tmp;
          } else if (m.second.name == "FR1_motor") {
            gain_config.FR1_motor_Kp = Kp_tmp;
            gain_config.FR1_motor_Kd = Kd_tmp;
          } else if (m.second.name == "FR2_motor") {
            gain_config.FR2_motor_Kp = Kp_tmp;
            gain_config.FR2_motor_Kd = Kd_tmp;
          } else if (m.second.name == "FR3_motor") {
            gain_config.FR3_motor_Kp = Kp_tmp;
            gain_config.FR3_motor_Kd = Kd_tmp;
          } else if (m.second.name == "FR4_motor") {
            gain_config.FR4_motor_Kp = Kp_tmp;
            gain_config.FR4_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BL1_motor") {
            gain_config.BL1_motor_Kp = Kp_tmp;
            gain_config.BL1_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BL2_motor") {
            gain_config.BL2_motor_Kp = Kp_tmp;
            gain_config.BL2_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BL3_motor") {
            gain_config.BL3_motor_Kp = Kp_tmp;
            gain_config.BL3_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BL4_motor") {
            gain_config.BL4_motor_Kp = Kp_tmp;
            gain_config.BL4_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BR1_motor") {
            gain_config.BR1_motor_Kp = Kp_tmp;
            gain_config.BR1_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BR2_motor") {
            gain_config.BR2_motor_Kp = Kp_tmp;
            gain_config.BR2_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BR3_motor") {
            gain_config.BR3_motor_Kp = Kp_tmp;
            gain_config.BR3_motor_Kd = Kd_tmp;
          } else if (m.second.name == "BR4_motor") {
            gain_config.BR4_motor_Kp = Kp_tmp;
            gain_config.BR4_motor_Kd = Kd_tmp;
          } else if (m.second.name == "wheel_FL_motor") {
            gain_config.wheel_FL_motor_Kp = Kp_tmp;
            gain_config.wheel_FL_motor_Kd = Kd_tmp;
          } else if (m.second.name == "wheel_FR_motor") {
            gain_config.wheel_FR_motor_Kp = Kp_tmp;
            gain_config.wheel_FR_motor_Kd = Kd_tmp;
          } else if (m.second.name == "wheel_BL_motor") {
            gain_config.wheel_BL_motor_Kp = Kp_tmp;
            gain_config.wheel_BL_motor_Kd = Kd_tmp;
          } else if (m.second.name == "wheel_BR_motor") {
            gain_config.wheel_BR_motor_Kp = Kp_tmp;
            gain_config.wheel_BR_motor_Kd = Kd_tmp;
          }
          m.second.Kp = Kp_tmp;
          m.second.Kd = Kd_tmp;
        }
        m.second.servo_mode = req.servo;  // サーボモードを更新
      }
      config_client.setConfiguration(gain_config);  // dynamic reconfigureでKpとKdの値を変更
    }

    /*** 左前脚のモータを設定 ***/
    else if (req.name == "FL") {
      melew3_msgs::GenericMd80Msg FL_srv;
      FL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FL_srv.request.drive_ids[0] = set_CAN_ID(FL1);
      FL_srv.request.drive_ids[1] = set_CAN_ID(FL2);
      FL_srv.request.drive_ids[2] = set_CAN_ID(FL3);
      FL_srv.request.drive_ids[3] = set_CAN_ID(FL4);
      FL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FL);

      /*** ロボット関節のONとOFFを切り替えたいモータのCAN_IDをMD80に送信 ***/
      if (req.servo == true) {
        if (!FL_enable_md80_client.call(FL_srv)) throw "Failed to connect with MD80s !";
        enable_flag[FL] = true;
      } else {
        if (!FL_disable_md80_client.call(FL_srv)) throw "Failed to connect with MD80s !";
        enable_flag[FL] = false;
      }

      for (int i = 0; i < SINGLE_LEG_JOINT_NUM + 1; i++) {
        motor_status& m = motor_map.at(FL_srv.request.drive_ids[i]);
        /*** ON-OFFが変化した場合 ***/
        if (!(m.servo_mode == req.servo)) {
          /*** サーボをOFFからONに切り替える場合 ***/
          if (req.servo == true) {
            /*** KpとKdをロードし更新 ***/
            Kp_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kp";
            Kd_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kd";

            /*** 例外処理 ***/
            if (!nh.getParam(Kp_param, Kp_tmp)) throw "Failed to get" + m.name + "P gain !";
            if (!nh.getParam(Kd_param, Kd_tmp)) throw "Failed to get" + m.name + "D gain !";
          }

          /*** ON -> OFFの場合 ***/
          /*** PDゲインを全て0にする ***/
          else {
            Kp_tmp = 0.0;
            Kd_tmp = 0.0;
          }

          /*** PDゲインの値を格納 ***/
          if (m.name == "FL1_motor") {
            gain_config.FL1_motor_Kp = Kp_tmp;
            gain_config.FL1_motor_Kd = Kd_tmp;
          } else if (m.name == "FL2_motor") {
            gain_config.FL2_motor_Kp = Kp_tmp;
            gain_config.FL2_motor_Kd = Kd_tmp;
          } else if (m.name == "FL3_motor") {
            gain_config.FL3_motor_Kp = Kp_tmp;
            gain_config.FL3_motor_Kd = Kd_tmp;
          } else if (m.name == "FL4_motor") {
            gain_config.FL4_motor_Kp = Kp_tmp;
            gain_config.FL4_motor_Kd = Kd_tmp;
          } else if (m.name == "wheel_FL_motor") {
            gain_config.wheel_FL_motor_Kp = Kp_tmp;
            gain_config.wheel_FL_motor_Kd = Kd_tmp;
          }
          m.Kp = Kp_tmp;
          m.Kd = Kd_tmp;
        }
        m.servo_mode = req.servo;  // サーボモードを更新
      }
      config_client.setConfiguration(gain_config);
    }

    // 右前脚のモータを設定
    else if (req.name == "FR") {
      melew3_msgs::GenericMd80Msg FR_srv;
      FR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      FR_srv.request.drive_ids[0] = set_CAN_ID(FR1);
      FR_srv.request.drive_ids[1] = set_CAN_ID(FR2);
      FR_srv.request.drive_ids[2] = set_CAN_ID(FR3);
      FR_srv.request.drive_ids[3] = set_CAN_ID(FR4);
      FR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_FR);

      /*** ロボット関節のONとOFFを切り替えたいモータのCAN_IDをMD80に送信 ***/
      if (req.servo == true) {
        if (!FR_enable_md80_client.call(FR_srv)) throw "Failed to connect with MD80s !";
        enable_flag[FR] = true;
      } else {
        if (!FR_disable_md80_client.call(FR_srv)) throw "Failed to connect with MD80s !";
        enable_flag[FR] = false;
      }

      for (int i = 0; i < SINGLE_LEG_JOINT_NUM + 1; i++) {
        motor_status& m = motor_map.at(FR_srv.request.drive_ids[i]);
        /*** ON-OFFが変化した場合 ***/
        if (!(m.servo_mode == req.servo)) {
          /*** サーボをOFFからONに切り替える場合 ***/
          if (req.servo == true) {
            /*** KpとKdをロードし更新 ***/
            Kp_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kp";
            Kd_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kd";

            /*** 例外処理 ***/
            if (!nh.getParam(Kp_param, Kp_tmp)) throw "Failed to get" + m.name + "P gain !";
            if (!nh.getParam(Kd_param, Kd_tmp)) throw "Failed to get" + m.name + "D gain !";
          }

          /*** ON -> OFFの場合 ***/
          /*** PDゲインを全て0にする ***/
          else {
            Kp_tmp = 0.0;
            Kd_tmp = 0.0;
          }

          /*** PDゲインの値を格納 ***/
          if (m.name == "FR1_motor") {
            gain_config.FR1_motor_Kp = Kp_tmp;
            gain_config.FR1_motor_Kd = Kd_tmp;
          } else if (m.name == "FR2_motor") {
            gain_config.FR2_motor_Kp = Kp_tmp;
            gain_config.FR2_motor_Kd = Kd_tmp;
          } else if (m.name == "FR3_motor") {
            gain_config.FR3_motor_Kp = Kp_tmp;
            gain_config.FR3_motor_Kd = Kd_tmp;
          } else if (m.name == "FR4_motor") {
            gain_config.FR4_motor_Kp = Kp_tmp;
            gain_config.FR4_motor_Kd = Kd_tmp;
          } else if (m.name == "wheel_FR_motor") {
            gain_config.wheel_FR_motor_Kp = Kp_tmp;
            gain_config.wheel_FR_motor_Kd = Kd_tmp;
          }
          m.Kp = Kp_tmp;
          m.Kd = Kd_tmp;
        }
        m.servo_mode = req.servo;  // サーボモードを更新
      }
      config_client.setConfiguration(gain_config);
    }

    /*** 左後脚のモータを設定 ***/
    else if (req.name == "BL") {
      melew3_msgs::GenericMd80Msg BL_srv;
      BL_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BL_srv.request.drive_ids[0] = set_CAN_ID(BL1);
      BL_srv.request.drive_ids[1] = set_CAN_ID(BL2);
      BL_srv.request.drive_ids[2] = set_CAN_ID(BL3);
      BL_srv.request.drive_ids[3] = set_CAN_ID(BL4);
      BL_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BL);

      /*** ロボット関節のONとOFFを切り替えたいモータのCAN_IDをMD80に送信 ***/
      if (req.servo == true) {
        if (!BL_enable_md80_client.call(BL_srv)) throw "Failed to connect with MD80s !";
        enable_flag[BL] = true;
      } else {
        if (!BL_disable_md80_client.call(BL_srv)) throw "Failed to connect with MD80s !";
        enable_flag[BL] = false;
      }

      for (int i = 0; i < SINGLE_LEG_JOINT_NUM + 1; i++) {
        motor_status& m = motor_map.at(BL_srv.request.drive_ids[i]);
        /*** ON-OFFが変化した場合 ***/
        if (!(m.servo_mode == req.servo)) {
          /*** サーボをOFFからONに切り替える場合 ***/
          if (req.servo == true) {
            /*** KpとKdをロードし更新 ***/
            std::string Kp_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kp";
            std::string Kd_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kd";

            /*** 例外処理 ***/
            if (!nh.getParam(Kp_param, Kp_tmp)) throw "Failed to get" + m.name + "P gain !";
            if (!nh.getParam(Kd_param, Kd_tmp)) throw "Failed to get" + m.name + "D gain !";
          }

          /*** ON -> OFFの場合 ***/
          /*** PDゲインを全て0にする ***/
          else {
            Kp_tmp = 0.0;
            Kd_tmp = 0.0;
          }

          /*** PDゲインの値を格納 ***/
          if (m.name == "BL1_motor") {
            gain_config.BL1_motor_Kp = Kp_tmp;
            gain_config.BL1_motor_Kd = Kd_tmp;
          } else if (m.name == "BL2_motor") {
            gain_config.BL2_motor_Kp = Kp_tmp;
            gain_config.BL2_motor_Kd = Kd_tmp;
          } else if (m.name == "BL3_motor") {
            gain_config.BL3_motor_Kp = Kp_tmp;
            gain_config.BL3_motor_Kd = Kd_tmp;
          } else if (m.name == "BL4_motor") {
            gain_config.BL4_motor_Kp = Kp_tmp;
            gain_config.BL4_motor_Kd = Kd_tmp;
          } else if (m.name == "wheel_BL_motor") {
            gain_config.wheel_BL_motor_Kp = Kp_tmp;
            gain_config.wheel_BL_motor_Kd = Kd_tmp;
          }
          m.Kp = Kp_tmp;
          m.Kd = Kd_tmp;
        }
        m.servo_mode = req.servo;  // サーボモードを更新
      }
      config_client.setConfiguration(gain_config);
    }

    // 右後脚のモータを設定
    else if (req.name == "BR") {
      melew3_msgs::GenericMd80Msg BR_srv;
      BR_srv.request.drive_ids.resize(SINGLE_LEG_JOINT_NUM + 1);
      BR_srv.request.drive_ids[0] = set_CAN_ID(BR1);
      BR_srv.request.drive_ids[1] = set_CAN_ID(BR2);
      BR_srv.request.drive_ids[2] = set_CAN_ID(BR3);
      BR_srv.request.drive_ids[3] = set_CAN_ID(BR4);
      BR_srv.request.drive_ids[4] = set_CAN_ID(WHEEL_BR);

      /*** ロボット関節のONとOFFを切り替えたいモータのCAN_IDをMD80に送信 ***/
      if (req.servo == true) {
        if (!BR_enable_md80_client.call(BR_srv)) throw "Failed to connect with MD80s !";
        enable_flag[BR] = true;
      } else {
        if (!BR_disable_md80_client.call(BR_srv)) throw "Failed to connect with MD80s !";
        enable_flag[BR] = false;
      }

      for (int i = 0; i < SINGLE_LEG_JOINT_NUM + 1; i++) {
        motor_status& m = motor_map.at(BR_srv.request.drive_ids[i]);
        /*** ON-OFFが変化した場合 ***/
        if (!(m.servo_mode == req.servo)) {
          /*** サーボをOFFからONに切り替える場合 ***/
          if (req.servo == true) {
            /*** KpとKdをロードし更新 ***/
            std::string Kp_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kp";
            std::string Kd_param = nh.getNamespace() + "/" + m.name + "_position_controller/config/Kd";

            /*** 例外処理 ***/
            if (!nh.getParam(Kp_param, Kp_tmp)) throw "Failed to get" + m.name + "P gain !";
            if (!nh.getParam(Kd_param, Kd_tmp)) throw "Failed to get" + m.name + "D gain !";
          }

          /*** ON -> OFFの場合 ***/
          /*** PDゲインを全て0にする ***/
          else {
            Kp_tmp = 0.0;
            Kd_tmp = 0.0;
          }

          /*** PDゲインの値を格納 ***/
          if (m.name == "BR1_motor") {
            gain_config.BR1_motor_Kp = Kp_tmp;
            gain_config.BR1_motor_Kd = Kd_tmp;
          } else if (m.name == "BR2_motor") {
            gain_config.BR2_motor_Kp = Kp_tmp;
            gain_config.BR2_motor_Kd = Kd_tmp;
          } else if (m.name == "BR3_motor") {
            gain_config.BR3_motor_Kp = Kp_tmp;
            gain_config.BR3_motor_Kd = Kd_tmp;
          } else if (m.name == "BR4_motor") {
            gain_config.BR4_motor_Kp = Kp_tmp;
            gain_config.BR4_motor_Kd = Kd_tmp;
          } else if (m.name == "wheel_BR_motor") {
            gain_config.wheel_BR_motor_Kp = Kp_tmp;
            gain_config.wheel_BR_motor_Kd = Kd_tmp;
          }

          m.Kp = Kp_tmp;
          m.Kd = Kd_tmp;
        }
        m.servo_mode = req.servo;  // サーボモードを更新
      }
      config_client.setConfiguration(gain_config);
    }

    res.success = true;

    /*** モータ設定用のcmdを送信 ***/
    writeImpedanceCommand(getTime(), getPeriod());

    /*** モータ角度が範囲外の場合のエラー処理 ***/
    for (auto& m : motor_map)
      if (m.second.servo_mode)
        if ((m.second.position < m.second.P_MIN) || (m.second.position > m.second.P_MAX))
          ROS_ERROR("Angle of [%s] is %f rad, out of range! Turn off servo mode!", m.second.name.c_str(), m.second.position);

    return true;
  } catch (std::out_of_range&) {
    /*** 例外処理 ***/
    throw "Failed to search the motor !";
  } catch (const char* str) {
    /*** 例外処理 ***/
    ROS_ERROR("%s", str);
    res.success = false;
    return false;
  }
}

/**
 * @brief MELEW3にCANコマンドを送信し、制御する
 *
 */
void MELEW3_HWI::writeImpedanceCommand(ros::Time time, ros::Duration period) {
  int FL_leg_index = 0;
  int FR_leg_index = 0;
  int BL_leg_index = 0;
  int BR_leg_index = 0;
  for (auto& m : motor_map) {
    if (m.first == set_CAN_ID(FL1) || m.first == set_CAN_ID(FL2) || m.first == set_CAN_ID(FL3) ||
        m.first == set_CAN_ID(FL4) || m.first == set_CAN_ID(WHEEL_FL)) {
      {
        /*** 左前脚 ***/
        /*** CAN_IDをパック ***/
        FL_leg_impedance_cmd.drive_ids[FL_leg_index] = m.first;

        /*** サーボモードに応じたKpとKdの値をパック ***/
        FL_leg_impedance_cmd.kp[FL_leg_index] = std::min(std::max(KP_MIN, m.second.Kp), KP_MAX);
        FL_leg_impedance_cmd.kd[FL_leg_index] = std::min(std::max(KD_MIN, m.second.Kd), KD_MAX);

        /*** max_outputをパック ***/
        FL_leg_impedance_cmd.max_output[FL_leg_index] = m.second.max_output;

        ROS_INFO("[%14s] Kp: %3.0f, Kd: %2.1f", m.second.name.c_str(), FL_leg_impedance_cmd.kp[FL_leg_index],
                 FL_leg_impedance_cmd.kd[FL_leg_index]);

        FL_leg_index++;
      }
    } else if (m.first == set_CAN_ID(FR1) || m.first == set_CAN_ID(FR2) || m.first == set_CAN_ID(FR3) ||
               m.first == set_CAN_ID(FR4) || m.first == set_CAN_ID(WHEEL_FR)) {
      {
        /*** 右前脚 ***/
        /*** CAN_IDをパック ***/
        FR_leg_impedance_cmd.drive_ids[FR_leg_index] = m.first;

        /*** サーボモードに応じたKpとKdの値をパック ***/
        FR_leg_impedance_cmd.kp[FR_leg_index] = std::min(std::max(KP_MIN, m.second.Kp), KP_MAX);
        FR_leg_impedance_cmd.kd[FR_leg_index] = std::min(std::max(KD_MIN, m.second.Kd), KD_MAX);

        /*** max_outputをパック ***/
        FR_leg_impedance_cmd.max_output[FR_leg_index] = m.second.max_output;

        ROS_INFO("[%14s] Kp: %3.0f, Kd: %2.1f", m.second.name.c_str(), FR_leg_impedance_cmd.kp[FR_leg_index],
                 FR_leg_impedance_cmd.kd[FR_leg_index]);

        FR_leg_index++;
      }
    } else if (m.first == set_CAN_ID(BL1) || m.first == set_CAN_ID(BL2) || m.first == set_CAN_ID(BL3) ||
               m.first == set_CAN_ID(BL4) || m.first == set_CAN_ID(WHEEL_BL)) {
      {
        /*** 左後脚 ***/
        /* CAN_IDをパック */
        BL_leg_impedance_cmd.drive_ids[BL_leg_index] = m.first;

        /*** サーボモードに応じたKpとKdの値をパック ***/
        BL_leg_impedance_cmd.kp[BL_leg_index] = std::min(std::max(KP_MIN, m.second.Kp), KP_MAX);
        BL_leg_impedance_cmd.kd[BL_leg_index] = std::min(std::max(KD_MIN, m.second.Kd), KD_MAX);

        /*** max_outputをパック ***/
        BL_leg_impedance_cmd.max_output[BL_leg_index] = m.second.max_output;

        ROS_INFO("[%14s] Kp: %3.0f, Kd: %2.1f", m.second.name.c_str(), BL_leg_impedance_cmd.kp[BL_leg_index],
                 BL_leg_impedance_cmd.kd[BL_leg_index]);

        BL_leg_index++;
      }
    } else if (m.first == set_CAN_ID(BR1) || m.first == set_CAN_ID(BR2) || m.first == set_CAN_ID(BR3) ||
               m.first == set_CAN_ID(BR4) || m.first == set_CAN_ID(WHEEL_BR)) {
      {
        /*** 右後脚 ***/
        /*** CAN_IDをパック ***/
        BR_leg_impedance_cmd.drive_ids[BR_leg_index] = m.first;

        /*** サーボモードに応じたKpとKdの値をパック ***/
        BR_leg_impedance_cmd.kp[BR_leg_index] = std::min(std::max(KP_MIN, m.second.Kp), KP_MAX);
        BR_leg_impedance_cmd.kd[BR_leg_index] = std::min(std::max(KD_MIN, m.second.Kd), KD_MAX);

        /*** max_outputをパック ***/
        BR_leg_impedance_cmd.max_output[BR_leg_index] = m.second.max_output;

        ROS_INFO("[%14s] Kp: %3.0f, Kd: %2.1f", m.second.name.c_str(), BR_leg_impedance_cmd.kp[BR_leg_index],
                 BR_leg_impedance_cmd.kd[BR_leg_index]);

        BR_leg_index++;
      }
    }
  }

  /*** 各マイコンごとににパブリッシュ ***/
  if(enable_flag[FL]){
    FL_leg_impedance_cmd.header.stamp = ros::Time::now();
    FL_leg_impedance_cmd_pub.publish(FL_leg_impedance_cmd);
  }
  if(enable_flag[FR]){
    FR_leg_impedance_cmd.header.stamp = ros::Time::now();
    FR_leg_impedance_cmd_pub.publish(FR_leg_impedance_cmd);
  }
  if(enable_flag[BL]){
    BL_leg_impedance_cmd.header.stamp = ros::Time::now();
    BL_leg_impedance_cmd_pub.publish(BL_leg_impedance_cmd);
  }
  if(enable_flag[BR]){
    BR_leg_impedance_cmd.header.stamp = ros::Time::now();
    BR_leg_impedance_cmd_pub.publish(BR_leg_impedance_cmd);
  }
}
}  // namespace MELEW3_control