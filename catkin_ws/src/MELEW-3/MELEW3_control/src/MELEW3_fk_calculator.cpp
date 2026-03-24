/**
 * @file    MELEW3_fk_value_calculator.cpp
 * @author  Taisei Suzuki
 * @brief   各リンクの位置・姿勢・速度・角速度の計算を行うプログラムファイル
 * @version 0.1
 * @date    2023-06-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MELEW3_control/MELEW3_fk_calculator.hpp>

/**
 * @brief コンストラクタ
 *
 * @param nh  ノードハンドル
 * @param pnh プライベートノードハンドル
 */
MSPARCFKCalculator::MSPARCFKCalculator(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param("loop_rate", 1000)) {
  /*** パブリッシャ，サブスクライバの初期化 ***/
  joint_state_sub_ = nh_.subscribe(pnh.param<std::string>("joint_state_topic_name", "/MELEW3/joint_states"), 1000,
                                   &MSPARCFKCalculator::_JointStateRefCallback, this,
                                   ros::TransportHints().reliable().tcpNoDelay(true));
  // link_info_pub_ =
  //     nh_.advertise<melew3_msgs::LinkInfoArray>(pnh.param<std::string>("link_info_topic_name", "/link_info_array"),
  //     1);
  // link_com_pub_ =
  //     nh_.advertise<geometry_msgs::PointStamped>(pnh.param<std::string>("link_com_topic_name", "/link_com"), 1);

  /*** 運動学クラスの初期化 ***/
  for (int i = 0; i < LEG_NUM; i++) MsparcKinematics[i].init(l1, l2, l_sim, l_sim);

  /*** メンバ変数の初期化 ***/
  pnh.param<double>("control_period", control_period_, 0.001);
  pnh.param<bool>("sim_flag", sim_flag_, true);
  pnh.param<double>("FL_leg_offset_x", FL_leg_offset_x_, 0.25);
  pnh.param<double>("FL_leg_offset_y", FL_leg_offset_y_, 0.20);
  pnh.param<double>("FL_leg_offset_z", FL_leg_offset_z_, 0.0);
  pnh.param<double>("FR_leg_offset_x", FR_leg_offset_x_, 0.25);
  pnh.param<double>("FR_leg_offset_y", FR_leg_offset_y_, -0.20);
  pnh.param<double>("FR_leg_offset_z", FR_leg_offset_z_, 0.0);
  pnh.param<double>("BL_leg_offset_x", BL_leg_offset_x_, -0.25);
  pnh.param<double>("BL_leg_offset_y", BL_leg_offset_y_, 0.20);
  pnh.param<double>("BL_leg_offset_z", BL_leg_offset_z_, 0.0);
  pnh.param<double>("BR_leg_offset_x", BR_leg_offset_x_, -0.25);
  pnh.param<double>("BR_leg_offset_y", BR_leg_offset_y_, -0.20);
  pnh.param<double>("BR_leg_offset_z", BR_leg_offset_z_, 0.0);
  leg_offset.resize(LEG_NUM);
  leg_offset[FL] = Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
  leg_offset[FR] = Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
  leg_offset[BL] = Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
  leg_offset[BR] = Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);

  link_params.resize(LEG_NUM);
  if (sim_flag_) {
    LINK_NUM = LINK_NUM_SERIAL;
    pnh.getParam("MELEW3_sim/link_info_FL", link_params[FL]);
    pnh.getParam("MELEW3_sim/link_info_FR", link_params[FR]);
    pnh.getParam("MELEW3_sim/link_info_BL", link_params[BL]);
    pnh.getParam("MELEW3_sim/link_info_BR", link_params[BR]);
  } else {
    LINK_NUM = LINK_NUM_PARALLEL;
    pnh.getParam("MELEW3/link_info_FL", link_params[FL]);
    pnh.getParam("MELEW3/link_info_FR", link_params[FR]);
    pnh.getParam("MELEW3/link_info_BL", link_params[BL]);
    pnh.getParam("MELEW3/link_info_BR", link_params[BR]);
    rotate_C << -1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -1.0, 0.0;
  }

  q_link_pre.resize(LEG_NUM, Eigen::VectorXd(LINK_NUM));
  link_position_value.resize(LEG_NUM, std::vector<Eigen::Vector3d>(LINK_NUM));
  link_orientation_value.resize(LEG_NUM, std::vector<Eigen::Matrix3d>(LINK_NUM));
  link_linear_value.resize(LEG_NUM, std::vector<Eigen::Vector3d>(LINK_NUM));
  link_angular_value.resize(LEG_NUM, std::vector<Eigen::Vector3d>(LINK_NUM));
  foot_position_value.resize(LEG_NUM);
  foot_orientation_value.resize(LEG_NUM);

  SetAllLink();  // リンクの設定

  // タイマーの開始
  time = 0.0;
  ros::Time t_start = ros::Time::now();
}

/**
 * @brief 各リンクの位置・姿勢・速度・角速度の計算を行う関数
 *
 * @param joint_angle_value       モータの角度
 * @param joint_angular_value     モータの角速度
 */
void MSPARCFKCalculator::CalcMSPARCFKCalculator(const Eigen::VectorXd joint_angle_value,
                                                const Eigen::VectorXd joint_angular_value) {
  /*** 変数の初期設定 ***/
  Eigen::Vector3d              p;                  //!< 脚先位置
  double                       psi;                //!< 脚先のYaw角
  std::vector<double>          q_link(LINK_NUM);   //!< 関節角
  std::vector<double>          dq_link(LINK_NUM);  //!< 関節角速度
  std::vector<Eigen::VectorXd> joint_angle_data(LEG_NUM, Eigen::VectorXd((int)SINGLE_LEG_JOINT_NUM));  //!< モータの角度
  std::vector<Eigen::Vector3d> link_position_data(LINK_NUM);  //!< リンク位置
  int                          mom;                           //!< 親リンクID

  /*** 関節角のデータを格納（4脚用）***/
  for (int i = 0; i < LEG_NUM; i++) {
    for (int j = 0; j < SINGLE_LEG_JOINT_NUM; j++)
      joint_angle_data[i][j] = joint_angle_value[i * SINGLE_LEG_JOINT_NUM + j];
  }

  if (sim_flag_) {
    for (int i = 0; i < LEG_NUM; i++) {
      /*** 順運動学計算 ***/
      if (MsparcKinematics[i].solve_link_position_serial(joint_angle_data[i], p, psi, link_position_data, q_link)) {
        for (int j = 0; j < LINK_NUM; j++) {
          /*** 脚の各関節の角速度の計算 ***/
          dq_link[j] = (q_link[j] - q_link_pre[i][j]) / time;
          q_link_pre[i][j] = q_link[j];

          /*** 各関節の角度と角速度を格納 ***/
          ulink[i][j + 1].q = q_link[j];
          ulink[i][j + 1].dq = dq_link[j];

          /*** 各リンクの原点位置の更新(p63, 2.58) ***/
          // ulink[i][j+1].p = ulink[i][mom].R * ulink[i][j+1].b + ulink[i][mom].p;
          ulink[i][j + 1].p = link_position_data[j];

          /*** 各リンクの姿勢の更新(p63, 2.59) ***/
          mom = ulink[i][j + 1].mother;
          ulink[i][j + 1].R = ulink[i][mom].R * Rodrigues(ulink[i][j + 1].a_link, ulink[i][j + 1].alpha) *
                              Rodrigues(ulink[i][j + 1].a_joint, ulink[i][j + 1].q);

          /*** 各リンクの速度の更新(p51, 2.40) ***/
          ulink[i][j + 1].v = ulink[i][mom].v + ulink[i][mom].omega.cross(ulink[i][mom].R * ulink[i][j + 1].b);

          /*** 各リンクの角速度の更新(p53, 2.50) ***/
          ulink[i][j + 1].omega = ulink[i][mom].omega + ulink[i][mom].R *
                                                            Rodrigues(ulink[i][j + 1].a_link, ulink[i][j + 1].alpha) *
                                                            (ulink[i][j + 1].a_joint * ulink[i][j + 1].dq);

          /*** 計算した値の格納 ***/
          link_position_value[i][j] = link_position_data[j];
          link_orientation_value[i][j] = ulink[i][j + 1].R;
          link_linear_value[i][j] = ulink[i][j + 1].v;
          link_angular_value[i][j] = ulink[i][j + 1].omega;
        }
        foot_position_value[i] = p;
        foot_orientation_value[i] = ulink[i][LINK_NUM].R;
      }
    }
  } else {
    for (int i = 0; i < LEG_NUM; i++) {
      /*** 順運動学計算 ***/
      if (MsparcKinematics[i].solve_link_position_parallel(i, joint_angle_data[i], p, psi, link_position_data,
                                                           q_link)) {
        for (int j = 0; j < LINK_NUM; j++) {
          /*** 脚の各関節の角速度の計算 ***/
          dq_link[j] = (q_link[j] - q_link_pre[i][j]) / time;
          q_link_pre[i][j] = q_link[j];

          /*** 各関節の角度と角速度を格納 ***/
          ulink[i][j + 1].q = q_link[j];
          ulink[i][j + 1].dq = dq_link[j];

          /*** 各リンクの原点位置の更新(p63, 2.58) ***/
          // ulink[i][j+1].p = ulink[i][mom].R * ulink[i][j+1].b + ulink[i][mom].p;
          ulink[i][j + 1].p = link_position_data[j];

          /*** 各リンクの姿勢の更新(p63, 2.59) ***/
          mom = ulink[i][j + 1].mother;
          ulink[i][j + 1].R = ulink[i][mom].R * Rodrigues(ulink[i][j + 1].a_link, ulink[i][j + 1].alpha) *
                              Rodrigues(ulink[i][j + 1].a_joint, ulink[i][j + 1].q);
          if (j == C1_PARALLEL - 1 || j == C2_PARALLEL - 1) ulink[i][j + 1].R = ulink[i][j + 1].R * rotate_C;

          /*** 各リンクの速度の更新(p51, 2.40) ***/
          ulink[i][j + 1].v = ulink[i][mom].v + ulink[i][mom].omega.cross(ulink[i][mom].R * ulink[i][j + 1].b);

          /*** 各リンクの角速度の更新(p53, 2.50) ***/
          ulink[i][j + 1].omega = ulink[i][mom].omega + ulink[i][mom].R *
                                                            Rodrigues(ulink[i][j + 1].a_link, ulink[i][j + 1].alpha) *
                                                            (ulink[i][j + 1].a_joint * ulink[i][j + 1].dq);
          if (j == C1_PARALLEL - 1 || j == C2_PARALLEL - 1) ulink[i][mom].omega = rotate_C * ulink[i][mom].omega;

          /*** 計算した値の格納 ***/
          link_position_value[i][j] = link_position_data[j];
          link_orientation_value[i][j] = ulink[i][j + 1].R;
          link_linear_value[i][j] = ulink[i][j + 1].v;
          link_angular_value[i][j] = ulink[i][j + 1].omega;
        }
        foot_position_value[i] = p;
        foot_orientation_value[i] = ulink[i][LINK_NUM].R;
      }
    }
  }
}

/**
 * @brief 重心位置を計算する関数
 *
 * @param joint_state       関節の角度と角速度
 */
void MSPARCFKCalculator::CalcComCalculator() {
  /*** 変数の初期設定 ***/
  Eigen::Vector3d com = Eigen::Vector3d::Zero();  //!< 重心位置
  double          total_mass = 0.0;               //!< 総質量

  /*** 重心位置の計算 ***/
  for (int i = 0; i < LEG_NUM; i++) {
    for (int j = 0; j < LINK_NUM; j++) {
      com += ulink[i][j + 1].mass * (leg_offset[i] + ulink[i][j + 1].p + ulink[i][j + 1].R * ulink[i][j + 1].com);
      total_mass += ulink[i][j + 1].mass;
    }
  }
  link_com = com / total_mass;
}

/**
 * @brief 各リンクの位置・姿勢・速度・角速度をpublishする関数
 *
 * @param joint_state       モータ角度・角速度
 */
void MSPARCFKCalculator::MSPARCFKCalculatorCallback(const sensor_msgs::JointState joint_state) {
  /*** 位置・姿勢・速度・角速度を計算する変数の初期化 ***/
  Eigen::VectorXd joint_angle_value(LEG_NUM * JOINT_NUM);    //!< モータ角度
  Eigen::VectorXd joint_angular_value(LEG_NUM * JOINT_NUM);  //!< モータ角速度

  if (joint_state.position.size() != LEG_NUM * JOINT_NUM) return;  // subscribeの失敗判定
  _JointStateToVector(joint_state, joint_angle_value,
                      joint_angular_value);  // JointState型をVector型に変換

  /*** 時刻の設定 ***/
  time = (ros::Time::now() - t_start).toSec();
  t_start = ros::Time::now();

  if (time) CalcMSPARCFKCalculator(joint_angle_value, joint_angular_value);  // 各リンクの位置・姿勢・速度・角速度の計算
  CalcComCalculator();                                                       // 重心位置の計算

  ROS_INFO("[COM] x : %9.6f, y : %9.6f, z : %9.6f", GetCOM().x(), GetCOM().y(), GetCOM().z());

  // /*** publishするデータの初期化 ***/
  // std::vector<Eigen::Vector3d> pub_link_position_value(LINK_NUM * LEG_NUM);     //!< リンク位置
  // std::vector<Eigen::Matrix3d> pub_link_orientation_value(LINK_NUM * LEG_NUM);  //!< リンク姿勢
  // std::vector<Eigen::Vector3d> pub_link_linear_value(LINK_NUM * LEG_NUM);       //!< リンク速度
  // std::vector<Eigen::Vector3d> pub_link_angular_value(LINK_NUM * LEG_NUM);      //!< リンク角速度
  // melew3_msgs::LinkInfoArray  pub_link_info_data;  //!< リンク位置・姿勢・速度・角速度用メッセージ
  // geometry_msgs::PointStamped  pub_link_com_data;   //!< ベースリンクから見た重心位置用メッセージ
  // pub_link_info_data.position.resize(LEG_NUM * LINK_NUM);
  // pub_link_info_data.velocity.resize(LEG_NUM * LINK_NUM);

  // /*** Publishする値の格納 ***/
  // for (int i = 0; i < LEG_NUM; i++) {
  //   for (int j = 0; j < LINK_NUM; j++) {
  //     pub_link_position_value[i * LEG_NUM + j] = link_position_value[i][j];
  //     pub_link_orientation_value[i * LEG_NUM + j] = link_orientation_value[i][j];
  //     pub_link_linear_value[i * LEG_NUM + j] = link_linear_value[i][j];
  //     pub_link_angular_value[i * LEG_NUM + j] = link_angular_value[i][j];
  //   }
  // }

  // /*** Vector型をPublishする型に変換 ***/
  // util.VectorToLinkInfoArray(pub_link_position_value, pub_link_orientation_value, pub_link_linear_value,
  //                            pub_link_angular_value, pub_link_info_data);
  // util.Vector3dToPoint(link_com, pub_link_com_data.point);

  // /*** 各リンクの位置・姿勢・速度・角速度のpublish ***/
  // pub_link_info_data.header.stamp = ros::Time::now();
  // pub_link_com_data.header.stamp = ros::Time::now();
  // pub_link_info_data.header.frame_id = "link_info";
  // pub_link_com_data.header.frame_id = "link_com";
  // link_info_pub_.publish(pub_link_info_data);
  // link_com_pub_.publish(pub_link_com_data);
}

/**
 * @brief msparc_fk_calculatorの制御を回す関数
 *
 */
void MSPARCFKCalculator::Run() {
  while (nh_.ok()) {
    MSPARCFKCalculatorCallback(joint_state_);
    ros::spinOnce();
    rate_.sleep();
  }
}

/**
 * @brief リンク位置を取得する関数（4脚まとめて取得）
 *
 */
std::vector<std::vector<Eigen::Vector3d>> MSPARCFKCalculator::GetLinkPosition() { return link_position_value; }

/**
 * @brief リンク位置を取得する関数（脚番号を指定して取得）
 *
 * @param leg_num 脚番号 (FL:0, FR:1, BL:2, BR:3)
 */
std::vector<Eigen::Vector3d> MSPARCFKCalculator::GetLinkPosition(const double leg_num) {
  return link_position_value[leg_num];
}

/**
 * @brief リンク姿勢を取得する関数（4脚まとめて取得）
 *
 */
std::vector<std::vector<Eigen::Matrix3d>> MSPARCFKCalculator::GetLinkOrientation() { return link_orientation_value; }

/**
 * @brief リンク位置を取得する関数（脚番号を指定して取得）
 *
 * @param leg_num 脚番号 (FL:0, FR:1, BL:2, BR:3)
 */
std::vector<Eigen::Matrix3d> MSPARCFKCalculator::GetLinkOrientation(const double leg_num) {
  return link_orientation_value[leg_num];
}

/**
 * @brief リンク速度を取得する関数（4脚まとめて取得）
 *
 */
std::vector<std::vector<Eigen::Vector3d>> MSPARCFKCalculator::GetLinkLinear() { return link_linear_value; }

/**
 * @brief リンク速度を取得する関数（脚番号を指定して取得）
 *
 * @param leg_num 脚番号 (FL:0, FR:1, BL:2, BR:3)
 */
std::vector<Eigen::Vector3d> MSPARCFKCalculator::GetLinkLinear(const double leg_num) {
  return link_linear_value[leg_num];
}

/**
 * @brief リンク角速度を取得する関数（4脚まとめて取得）
 *
 */
std::vector<std::vector<Eigen::Vector3d>> MSPARCFKCalculator::GetLinkAngular() { return link_angular_value; }

/**
 * @brief リンク角速度を取得する関数（脚番号を指定して取得）
 *
 * @param leg_num 脚番号 (FL:0, FR:1, BL:2, BR:3)
 */
std::vector<Eigen::Vector3d> MSPARCFKCalculator::GetLinkAngular(const double leg_num) {
  return link_angular_value[leg_num];
}

/**
 * @brief ベースリンクから見た脚先位置を取得する関数（4脚まとめて取得）
 *
 */
std::vector<Eigen::Vector3d> MSPARCFKCalculator::GetFootPosition() { return foot_position_value; }

/**
 * @brief ベースリンクから見た脚先位置を取得する関数（脚番号を指定して取得）
 *
 * @param leg_num 脚番号 (FL:0, FR:1, BL:2, BR:3)
 */
Eigen::Vector3d MSPARCFKCalculator::GetFootPosition(const double leg_num) { return foot_position_value[leg_num]; }

/**
 * @brief ベースリンクから見た脚先姿勢を取得する関数（4脚まとめて取得）
 *
 */
std::vector<Eigen::Matrix3d> MSPARCFKCalculator::GetFootOrientation() { return foot_orientation_value; }

/**
 * @brief ベースリンクから見た脚先姿勢を取得する関数（脚番号を指定して取得）
 *
 * @param leg_num 脚番号 (FL:0, FR:1, BL:2, BR:3)
 */
Eigen::Matrix3d MSPARCFKCalculator::GetFootOrientation(const double leg_num) { return foot_orientation_value[leg_num]; }

/**
 * @brief ベースリンクから見た重心位置を取得する関数
 *
 */
Eigen::Vector3d MSPARCFKCalculator::GetCOM() { return link_com; }

/**
 * @brief 各リンク情報の設定を行う関数
 *
 * @param leg_num  脚の番号
 * @param _ID      ID
 * @param _name    名前
 * @param _mother  親リンクID
 * @param _alpha   球面リンクの角度
 * @param _a_link  親リンクから見た球面リンクの軸ベクトル
 * @param _a_joint 親リンク先端から見た関節軸ベクトル
 * @param _b       親リンクから見た自リンクの原点位置
 */
void MSPARCFKCalculator::Setlink(const int leg_num, const int _ID, const std::string _name, const int _mother,
                                 const double _alpha, const Eigen::Vector3d _a_link, const Eigen::Vector3d _a_joint,
                                 const Eigen::Vector3d _b) {
  // j番目リンクの情報を格納
  ulink[leg_num][_ID].name = _name;        // 名前
  ulink[leg_num][_ID].mother = _mother;    // 親リンクID
  ulink[leg_num][_ID].alpha = _alpha;      // 球面リンクの角度
  ulink[leg_num][_ID].a_link = _a_link;    // 親リンクから見た球面リンクの軸ベクトル
  ulink[leg_num][_ID].a_joint = _a_joint;  // 親リンク先端から見た関節軸ベクトル
  ulink[leg_num][_ID].b = _b;              // 親リンクから見た自リンクの原点位置
}

/**
 * @brief リンク情報の設定を行う関数
 *
 */
void MSPARCFKCalculator::SetAllLink() {
  std::string LEG_NAME[LEG_NUM] = {"FL", "FR", "BL", "BR"};  //!< リンクの名前

  /*** 全情報を初期化 ***/
  for (int i = 0; i < LEG_NUM; i++) {
    for (int j = 0; j <= LINK_NUM; j++) {
      ulink[i][j].mother = 0;
      ulink[i][j].mass = 0.0;
      ulink[i][j].q = 0.0;
      ulink[i][j].dq = 0.0;
      ulink[i][j].alpha = 0.0;
      ulink[i][j].p = Eigen::Vector3d::Zero();
      ulink[i][j].R = Eigen::Matrix3d::Identity(3, 3);
      ulink[i][j].v = Eigen::Vector3d::Zero();
      ulink[i][j].omega = Eigen::Vector3d::Zero();
      ulink[i][j].com = Eigen::Vector3d::Zero();
      ulink[i][j].a_link = Eigen::Vector3d::Zero();
      ulink[i][j].a_joint = Eigen::Vector3d::Zero();
      ulink[i][j].b = Eigen::Vector3d::Zero();
    }
  }

  // exmple robot py『Humanoid Robot』p.60
  // Setlink(ID，名前，母ID，妹ID, 子ID，
  // 球面リンクの角度，親リンクから見た球面リンクの軸ベクトル，
  // 親リンク先端から見た関節軸ベクトル，親リンクから見た自リンクの原点位置); ボディ

  /*** 各リンクの質量と重心位置を格納 ***/
  for (int i = 0; i < LEG_NUM; i++) {
    for (int j = 0; j < LINK_NUM; j++) {
      ulink[i][j + 1].mass = static_cast<double>(link_params[i][j]["mass"]);
      ulink[i][j + 1].com << static_cast<double>(link_params[i][j]["com"][0]),
          static_cast<double>(link_params[i][j]["com"][1]), static_cast<double>(link_params[i][j]["com"][2]);
    }
  }

  /*** 各リンクの情報を格納 ***/
  if (sim_flag_) {
    /*** シミュレーション用 ***/
    for (int i = 0; i < LEG_NUM; i++) {
      Setlink(i, BODY_SERIAL, "BODY_" + LEG_NAME[i], BASE_SERIAL, 0.0, u0, uz, u0);                // ID : 1
      Setlink(i, HIP_YAW_SERIAL, "HIP_YAW_" + LEG_NAME[i], BODY_SERIAL, 0.0, u0, uz, u0);          // ID : 2
      Setlink(i, HIP_ROLL_SERIAL, "HIP_ROLL_" + LEG_NAME[i], HIP_YAW_SERIAL, 0.0, u0, ux, u0);     // ID : 3
      Setlink(i, HIP_PITCH_SERIAL, "HIP_PITCH_" + LEG_NAME[i], HIP_ROLL_SERIAL, 0.0, u0, uy, u0);  // ID : 4
      Setlink(i, KNEE_SERIAL, "KNEE_" + LEG_NAME[i], HIP_PITCH_SERIAL, 0.0, u0, uy, -l_sim * uz);  // ID : 5
      Setlink(i, WHEEL_SERIAL, "WHEEL_" + LEG_NAME[i], KNEE_SERIAL, 0.0, u0, uy, -l_sim * uz);     // ID : 6
    }
  } else {
    /*** 実機用 ***/
    for (int i = 0; i < LEG_NUM; i++) {
      Setlink(i, BODY_PARALLEL, "BODY_" + LEG_NAME[i], BASE_PARALLEL, 0.0, u0, uz, u0);      // ID : 1
      Setlink(i, A1_PARALLEL, LEG_NAME[i] + "_A1", BODY_PARALLEL, 0.0, u0, uy, l_A1 * uy);   // ID : 2
      Setlink(i, A2_PARALLEL, LEG_NAME[i] + "_A2", BODY_PARALLEL, 0.0, u0, uy, l_A2 * uy);   // ID : 3
      Setlink(i, A3_PARALLEL, LEG_NAME[i] + "_A3", BODY_PARALLEL, 0.0, u0, uy, -l_A2 * uy);  // ID : 4
      Setlink(i, A4_PARALLEL, LEG_NAME[i] + "_A4", BODY_PARALLEL, 0.0, u0, uy, -l_A1 * uy);  // ID : 5
      Setlink(i, B1_PARALLEL, LEG_NAME[i] + "_B1", A1_PARALLEL, -M_PI / 3.0, uz, uy,
              Eigen::Vector3d(sqrt(3.0) * 0.5 * l_B1, -l_A1 + 0.5 * l_B1, 0.0));  // ID : 6
      Setlink(i, B2_PARALLEL, LEG_NAME[i] + "_B2", A2_PARALLEL, M_PI / 3.0, uz, uy,
              Eigen::Vector3d(-sqrt(3.0) * 0.5 * l_B2, -l_A2 + 0.5 * l_B2, 0.0));  // ID : 7
      Setlink(i, B3_PARALLEL, LEG_NAME[i] + "_B3", A3_PARALLEL, -M_PI / 3.0, uz, uy,
              Eigen::Vector3d(-sqrt(3.0) * 0.5 * l_B2, l_A2 - 0.5 * l_B2, 0.0));  // ID : 8
      Setlink(i, B4_PARALLEL, LEG_NAME[i] + "_B4", A4_PARALLEL, M_PI / 3.0, uz, uy,
              Eigen::Vector3d(sqrt(3.0) * 0.5 * l_B1, l_A1 - 0.5 * l_B1, 0.0));  // ID : 9
    }

    /*** 前脚用 ***/
    for (int i = 0; i < LEG_NUM / 2; i++) {
      Setlink(i, C1_PARALLEL, LEG_NAME[i] + "_C1", B1_PARALLEL, -M_PI / 3.0, uz, uy,
              Eigen::Vector3d(sqrt(3.0) * 0.5 * l_C, -l_B1 + 0.5 * l_C, 0.0));  // ID : 10
      Setlink(i, C2_PARALLEL, LEG_NAME[i] + "_C2", B2_PARALLEL, M_PI / 3.0, uz, uy,
              Eigen::Vector3d(-sqrt(3.0) * 0.5 * l_C, -l_B2 + 0.5 * l_C, 0.0));  // ID : 11
    }

    /*** 後脚用 ***/
    for (int i = LEG_NUM / 2; i < LEG_NUM; i++) {
      Setlink(i, C1_PARALLEL, LEG_NAME[i] + "_C1", B2_PARALLEL, M_PI / 3.0, uz, uy,
              Eigen::Vector3d(-sqrt(3.0) * 0.5 * l_C, -l_B2 + 0.5 * l_C, 0.0));  // ID : 10
      Setlink(i, C2_PARALLEL, LEG_NAME[i] + "_C2", B1_PARALLEL, -M_PI / 3.0, uz, uy,
              Eigen::Vector3d(sqrt(3.0) * 0.5 * l_C, -l_B1 + 0.5 * l_C, 0.0));  // ID : 11
    }

    for (int i = 0; i < LEG_NUM; i++) {
      Setlink(i, D1_PARALLEL, LEG_NAME[i] + "_D1", C1_PARALLEL, 0.0, u0, uy, (l_C - l1) * uz);  // ID : 12
      Setlink(i, D2_PARALLEL, LEG_NAME[i] + "_D2", C2_PARALLEL, 0.0, u0, uy, (l_C - l2) * uz);  // ID : 13
      Setlink(i, WHEEL_PARALLEL, "WHEEL_" + LEG_NAME[i], D2_PARALLEL, 0.0, u0, uz, -l2 * uz);   // ID : 14
    }
  }
}

/**
 * @brief 回転行列を単位行列と関節角度から計算する関数
 *
 * @param omega  回転軸のベクトル
 * @param angle     回転角
 */
Eigen::Matrix3d MSPARCFKCalculator::Rodrigues(const Eigen::Vector3d omega, const double angle) {
  Eigen::Matrix3d _R, omega_wedge;

  double norm_omega = omega.norm();
  if (norm_omega < 1e-10) {
    _R << Eigen::MatrixXd::Identity(3, 3);
  } else {
    Eigen::Vector3d omega_n = omega / norm_omega;
    double          theta = norm_omega * angle;
    omega_wedge << 0.0, -omega_n.z(), omega_n.y(), omega_n.z(), 0.0, -omega_n.x(), -omega_n.y(), omega_n.x(), 0.0;
    _R = Eigen::MatrixXd::Identity(3, 3) + omega_wedge * sin(theta) + omega_wedge * omega_wedge * (1 - cos(theta));
  }
  return _R;
}

/**
 * @brief Jointstate型からVector型へ変換
 *
 * @param joint_state_data Jointstate型のデータ
 * @param position_data    Vector型の位置
 * @param velocity_data    Vector型の速度
 */
void MSPARCFKCalculator::_JointStateToVector(const sensor_msgs::JointState joint_state_data,
                                             Eigen::VectorXd& position_data, Eigen::VectorXd& velocity_data) {
  for (int i = 0; i < LEG_NUM * JOINT_NUM; i++) {
    position_data[i] = joint_state_data.position[i];
    velocity_data[i] = joint_state_data.velocity[i];
  }
}

/**
 * @brief モータの角度と角速度を一時保存するコールバック関数
 *
 * @param joint_state  モータの角度と角速度
 */
void MSPARCFKCalculator::_JointStateRefCallback(const sensor_msgs::JointState::ConstPtr& joint_state) {
  joint_state_.header = joint_state->header;
  joint_state_.position = joint_state->position;
  joint_state_.velocity = joint_state->velocity;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "MSPARCFKCalculatorNode");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  MSPARCFKCalculator MSPARCFKCalculator(nh, pnh);
  MSPARCFKCalculator.Run();

  return 0;
}