/**
 * @file    sne_controller.cpp
 * @author  Taisei Suzuki
 * @brief   SNEを用いて目標脚先軌道を生成するプログラムファイル
 * @version 0.1
 * @date    2023-05-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <sne_controller/sne_controller.hpp>

/**
 * @brief Construct a new SneController::SneController object
 *
 * @param nh  ノードハンドル
 * @param pnh プライベートノードハンドル
 */
SneController::SneController(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh), rate_(pnh.param("/loop_rate", 100)), pc(nh, pnh) {
  /*** パブリッシャ，サブスクライバの初期化 ***/
  FL_leg_pos_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("FL_leg_pos_ref_topic_name", "/FL_leg_pos_ref"), 1);
  FR_leg_pos_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("FR_leg_pos_ref_topic_name", "/FR_leg_pos_ref"), 1);
  BL_leg_pos_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("BL_leg_pos_ref_topic_name", "/BL_leg_pos_ref"), 1);
  BR_leg_pos_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("BR_leg_pos_ref_topic_name", "/BR_leg_pos_ref"), 1);

  // ベクトルの初期化
  SNE_threshold.resize(judge_num);
  foot.resize(LEG_NUM);
  x_p.resize(judge_num);
  x_p1.resize(judge_num);
  SNE_flag.resize(judge_num);
  move_distance.resize(judge_num);
  move_distance_pre.resize(judge_num);
  for (int i = 0; i < judge_num; i++) move_distance[i] = 0.0;
  for (int i = 0; i < judge_num; i++) move_distance_pre[i] = 0.0;
  leg_pos.resize(LEG_NUM);
  leg_yaw.resize(LEG_NUM);
  leg_pos_pre.resize(LEG_NUM);
  leg_yaw_pre.resize(LEG_NUM);
  for (int i = 0; i < LEG_NUM; i++) leg_yaw_pre[i] = 0.0;

  // 変数の初期化
  pnh.param<double>("/loop_rate", loop_rate_, 100);
  pnh.param<double>("/pr/sampling_time", sampling_time_, 0.001);
  SNE_threshold[0] = pnh.param("/sn/SNE_threshold/x", 0.10);
  SNE_threshold[1] = pnh.param("/sn/SNE_threshold/y", 0.10);
  phi = pnh.param("/sn/phi", 0.0) * (M_PI / 180.0);
  xi = pnh.param("/sn/xi", 0.0) * (M_PI / 180.0);
  d_leg = pnh.param("/sn/d_leg", 0.50);
  b_leg = pnh.param("/sn/b_leg", 0.40);
  l_limit = pnh.param("/sn/l_limit", 0.44);
  pnh.param<double>("/pr/start_control_time", start_control_time_, 5.0);
  pnh.param<double>("/pr/com_height", com_height_, 0.41441016151);
  pnh.param<double>("/FL_leg_offset/x", FL_leg_offset_x_, 0.25);
  pnh.param<double>("/FL_leg_offset/y", FL_leg_offset_y_, 0.20);
  pnh.param<double>("/FL_leg_offset/z", FL_leg_offset_z_, 0.0);
  pnh.param<double>("/FR_leg_offset/x", FR_leg_offset_x_, 0.25);
  pnh.param<double>("/FR_leg_offset/y", FR_leg_offset_y_, -0.20);
  pnh.param<double>("/FR_leg_offset/z", FR_leg_offset_z_, 0.0);
  pnh.param<double>("/BL_leg_offset/x", BL_leg_offset_x_, -0.25);
  pnh.param<double>("/BL_leg_offset/y", BL_leg_offset_y_, 0.20);
  pnh.param<double>("/BL_leg_offset/z", BL_leg_offset_z_, 0.0);
  pnh.param<double>("/BR_leg_offset/x", BR_leg_offset_x_, -0.25);
  pnh.param<double>("/BR_leg_offset/y", BR_leg_offset_y_, -0.20);
  pnh.param<double>("/BR_leg_offset/z", BR_leg_offset_z_, 0.0);
  leg_offset.resize(LEG_NUM);
  leg_pos[FL] = Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
  leg_pos[FR] = Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
  leg_pos[BL] = Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
  leg_pos[BR] = Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);
  leg_offset[FL] = Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
  leg_offset[FR] = Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
  leg_offset[BL] = Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
  leg_offset[BR] = Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);
}

/**
 * @brief 最初の処理を行う関数
 *
 */
void SneController::Init() {}

/**
 * @brief SNE等高線の(x, y)座標を設定する関数
 *
 * @param SNE   SNE [m]
 * @param theta 媒介変数θ [rad]
 * @param x     SNE等高線のx座標 [m]
 * @param y     SNE等高線のy座標 [m]
 *
 */
void SneController::CalcSneContour(const double SNE, const double theta, double& x, double& y) {
  //!< d(θ)の計算式
  const double d = (-(SNE + h * cos(phi)) * sin(phi) * cos(theta) +
                    sqrt(SNE * (SNE + 2.0 * h * cos(phi)) * (1.0 - sin(phi) * sin(phi) * sin(theta) * sin(theta)))) /
                   (cos(phi) * cos(phi));
  // (x, y)を計算
  x = d * cos(theta + xi);
  y = d * sin(theta + xi);
}

/**
 * @brief 目標脚先位置と支持多角形の方向ベクトルを計算する関数
 *
 */
void SneController::CalcSupportPolygon() {
  std::vector<Eigen::Vector3d> p_foot(LEG_NUM);  //!< ZMPに対する脚先の相対位置 [m]

  // ZMPに対する脚先の相対位置を計算
  p_foot[FL] = Eigen::Vector3d(d_leg / 2.0, b_leg / 2.0, 0.0);
  p_foot[FR] = Eigen::Vector3d(d_leg / 2.0, -b_leg / 2.0, 0.0);
  p_foot[BL] = Eigen::Vector3d(-d_leg / 2.0, b_leg / 2.0, 0.0);
  p_foot[BR] = Eigen::Vector3d(-d_leg / 2.0, -b_leg / 2.0, 0.0);

  for (int i = 0; i < LEG_NUM; i++) foot[i] = p_foot[i] + ZMP;          // 目標脚先位置を計算
  support_porigon_vector = {foot[FL] - foot[FR], foot[FL] - foot[BL]};  // 支持多角形の方向ベクトルを定義
}

/**
 * @brief SNE等高線上の任意の傾きの接点を計算する関数
 *
 * @param num x_pのインデックス
 *
 */
void SneController::CalcPointOfTangency(const int num) {
  double                    a_angle;                             //!< 支持多角形の直線の偏角
  const std::vector<double> theta = {M_PI * 0.75, M_PI * 1.25};  //!< 角度θの初期値
  std::vector<double>       x0;                                  //!< 初期推測値
  double                    x, y;                                //!< 接点の(x, y)座標 [m]
  const double              epsilon = 1e-6;                      //!< ステップ幅
  const int                 max_iterations = 100;                //!< 最大反復回数
  const double              max_step = 0.1;                      //!< 最大ステップ幅

  // 支持多角形の直線の偏角を設定
  a_angle = atan(support_porigon_vector[num].y() / support_porigon_vector[num].x()) - xi;
  while (a_angle > M_PI / 2.0) a_angle -= M_PI;
  while (a_angle < -M_PI / 2.0) a_angle += M_PI;

  // 傾き(dy/dx)が定義可能な場合
  if (std::fabs(cos(a_angle)) > epsilon) {
    SneEquationSolver1 solver1(h, phi, SNE_threshold[num], a_angle);  // ニュートン法で角度θを計算するクラスを生成
    x0 = theta;                                                       // 初期値を設定

    for (int j = 0; j < x0.size(); j++) {
      if (solver1.newton_solve(x0[j], epsilon, max_iterations, max_step)) {  // 角度θを計算
        CalcSneContour(SNE_threshold[num], x0[j], x, y);                     // SNE等高線の(x, y)座標を計算
        x_p[num].push_back(Eigen::Vector3d(x, y, 0.0));                      // 接点座標を保存
      }
    }

    // 傾き(dy/dx)が定義不可能な場合
  } else {
    if (phi) {
      // 斜面の傾斜がある場合の角度θの解析解
      x0 = {acos(sqrt((SNE_threshold[num] * cos(phi)) / (2.0 * h)) / sin(phi)), M_PI,
            (2.0 * M_PI) - acos(sqrt((SNE_threshold[num] * cos(phi)) / (2.0 * h)) / sin(phi))};
    } else {
      x0 = {0.0, M_PI};  // 斜面の傾斜がない場合の角度θの解析解
    }

    for (int j = 0; j < x0.size(); j++) {
      CalcSneContour(SNE_threshold[num], x0[j], x, y);  // SNE等高線の(x, y)座標を計算
      x_p[num].push_back(Eigen::Vector3d(x, y, 0.0));   // 接点座標を保存
    }
  }
}

/**
 * @brief 支持多角形の修正量を計算する関数
 *
 * @param num x_pのインデックス
 *
 */
bool SneController::CalcMovement(const int num) {
  double x1_max, x1_min;  //!< ZMPから支持線に向けて引いた位置ベクトルの，支持線に直交する成分 [m]

  for (int j = 0; j < x_p[num].size(); j++) {
    // ZMPから接点に向けて引いた位置ベクトルの，支持線に直交する成分を抽出
    x_p1[num].push_back(support_porigon_vector[1 - num].dot(x_p[num][j] - ZMP) /
                        support_porigon_vector[1 - num].norm());
  }

  // ZMPから支持線に向けて引いた位置ベクトルの，支持線に直交する成分を抽出（最大値）
  x1_max = support_porigon_vector[1 - num].dot(foot[FL] - ZMP) / support_porigon_vector[1 - num].norm();
  // ZMPから支持線に向けて引いた位置ベクトルの，支持線に直交する成分を抽出（最小値）
  x1_min = support_porigon_vector[1 - num].dot(foot[BR] - ZMP) / support_porigon_vector[1 - num].norm();

  // 支持多角形を移動できないときの処理
  if ((x1_max - x1_min) <
      (*max_element(x_p1[num].begin(), x_p1[num].end()) - *min_element(x_p1[num].begin(), x_p1[num].end()))) {
    ROS_ERROR("Can not move support polygon!");
    SNE_flag[num] = false;
  }

  else {
    // 支持多角形の移動量の計算
    x_p1[num].push_back(x1_max);
    x_p1[num].push_back(x1_min);

    double min_val = move_distance_pre[num] - 0.001;
    double max_val = move_distance_pre[num] + 0.001;

    move_distance[num] = *max_element(x_p1[num].begin(), x_p1[num].end()) - x1_max +
                         *min_element(x_p1[num].begin(), x_p1[num].end()) - x1_min;

    move_distance[num] = std::max(min_val, std::min(move_distance[num], max_val));

    move_distance_pre[num] = move_distance[num];
    SNE_flag[num] = true;

    for (int k = 0; k < LEG_NUM; k++)
      // 支持多角形を移動
      foot[k] += move_distance[num] * (support_porigon_vector[1 - num] / support_porigon_vector[1 - num].norm());
  }

  // x_p，x_p1をリセット
  x_p[num].erase(x_p[num].begin(), x_p[num].end());
  x_p1[num].erase(x_p1[num].begin(), x_p1[num].end());

  return SNE_flag[num];
}

/**
 * @brief 目標脚先軌道を生成する関数
 *
 */
bool SneController::SneControllerCallback(const double control_time) {
  if (pc.PreviewControlCallback(control_time)) {
    zmp_pos = pc.zmp_pos_traj_[pc.how_many_times_];
    com_pos = pc.com_pos_traj_[pc.how_many_times_];
    com_yaw = pc.com_yaw_pos_traj_[pc.how_many_times_];

    ZMP = Eigen::AngleAxisd(-com_yaw, Eigen::Vector3d::UnitZ()) *
          Eigen::Vector3d(zmp_pos.x() - com_pos.x(), zmp_pos.y() - com_pos.y(), 0.0);

    h = com_pos.z();       // 重心高さを設定
    CalcSupportPolygon();  // 目標脚先位置を計算

    if (control_time >= start_control_time_) {
      for (int i = 0; i < judge_num; i++) {
        CalcPointOfTangency(i);       // SNE等高線上の任意の傾きの接点を計算
        while (!CalcMovement(i)) {    // 支持多角形の修正量を計算
          SNE_threshold[i] -= 0.001;  // 支持多角形が移動できない場合，SNEの閾値を小さくする
          CalcPointOfTangency(i);     // SNE等高線上の任意の傾きの接点を計算
        }
      }
    }

    for (int i = 0; i < LEG_NUM; i++) {
      /*** 目標脚先位置を計算 ***/
      if (Eigen::Vector3d(foot[i] - leg_offset[i] - Eigen::Vector3d(0.0, 0.0, h)).norm() > l_limit)
        foot[i] = leg_offset[i] + (foot[i] - leg_offset[i]) /
                                      ((foot[i] - leg_offset[i] - Eigen::Vector3d(0.0, 0.0, h)).norm()) * l_limit;

      leg_pos[i] = Eigen::AngleAxisd(com_yaw, Eigen::Vector3d::UnitZ()) * foot[i] +
                   Eigen::Vector3d(com_pos.x(), com_pos.y(), 0.0);
    }

    if (pc.how_many_times_ == 0) {
      for (int i = 0; i < LEG_NUM; i++) leg_yaw[i] = 0.0;
    } else {
      for (int i = 0; i < LEG_NUM; i++) {
        if (((leg_pos[i] - leg_pos_pre[i]).norm()) > 1e-9) {
          leg_yaw[i] =
              atan2((leg_pos[i] - leg_pos_pre[i]).y(), (leg_pos[i] - leg_pos_pre[i]).x());  // 目標脚先操舵角を計算

          /*** 目標脚先操舵角の変化量が-PI/2以上PI/2以下となるように修正 ***/
          while ((leg_yaw[i] - leg_yaw_pre[i]) < -M_PI / 2.0) leg_yaw[i] += M_PI;
          while ((leg_yaw[i] - leg_yaw_pre[i]) > M_PI / 2.0) leg_yaw[i] -= M_PI;
        } else {
          /*** 次に動き出す瞬間の目標脚先操舵角を計算***/
          int count = 0;
          while ((control_time > pc.waypoint_time[count + 1])) count++;
          std::vector<double> leg_yaw_cmd(LEG_NUM);

          if ((count < pc.waypoint_time.size() - 2)) {
            Eigen::Vector3d leg_pos_before =
                Eigen::AngleAxisd(pc.com_yaw_pos_traj_[(int)(pc.waypoint_time[count + 1] / sampling_time_)],
                                  Eigen::Vector3d::UnitZ()) *
                    leg_offset[i] +
                pc.zmp_pos_traj_[(int)(pc.waypoint_time[count + 1] * sampling_time_)];

            Eigen::Vector3d leg_pos_after =
                Eigen::AngleAxisd(pc.com_yaw_pos_traj_[(int)(pc.waypoint_time[count + 1] / sampling_time_) + 1],
                                  Eigen::Vector3d::UnitZ()) *
                    leg_offset[i] +
                pc.zmp_pos_traj_[(int)(pc.waypoint_time[count + 1] / sampling_time_) + 1];

            leg_yaw_cmd[i] = atan2((leg_pos_after - leg_pos_before).y(), (leg_pos_after - leg_pos_before).x());
          } else
            leg_yaw_cmd[i] = pc.com_yaw_pos_traj_.back();

          /*** 目標脚先操舵角の変化量が-PI/2以上PI/2以下となるように修正 ***/
          while ((leg_yaw_cmd[i] - leg_yaw_pre[i]) < -M_PI / 2.0) leg_yaw_cmd[i] += M_PI;
          while ((leg_yaw_cmd[i] - leg_yaw_pre[i]) > M_PI / 2.0) leg_yaw_cmd[i] -= M_PI;
          // std::cout << i << " " << leg_yaw_cmd[i] << std::endl;

          /*** 脚先操舵角を直線補間 ***/
          leg_yaw[i] = (leg_yaw_cmd[i] - leg_yaw_pre[i]) / (pc.waypoint_time[count + 1] - control_time) / loop_rate_ +
                       leg_yaw_pre[i];
        }
      }
    }

    /*** 1個前の脚先位置と脚先操舵角を保存 ***/
    com_pos_pre = com_pos;
    leg_pos_pre = leg_pos;
    leg_yaw_pre = leg_yaw;

    SneControllerPublisher();
    return true;
  } else
    return false;
}

/**
 * @brief 目標脚先軌道をパブリッシュする関数
 *
 */
void SneController::SneControllerPublisher() {
  /*** 目標脚先軌道をパブリッシュ ***/
  util.Vector3dToLegpose(leg_pos[FL], leg_yaw[FL], pub_FL_leg_pos_ref_data_);
  util.Vector3dToLegpose(leg_pos[FR], leg_yaw[FR], pub_FR_leg_pos_ref_data_);
  util.Vector3dToLegpose(leg_pos[BL], leg_yaw[BL], pub_BL_leg_pos_ref_data_);
  util.Vector3dToLegpose(leg_pos[BR], leg_yaw[BR], pub_BR_leg_pos_ref_data_);

  pub_FL_leg_pos_ref_data_.header.stamp = ros::Time::now();
  pub_FR_leg_pos_ref_data_.header.stamp = ros::Time::now();
  pub_BL_leg_pos_ref_data_.header.stamp = ros::Time::now();
  pub_BR_leg_pos_ref_data_.header.stamp = ros::Time::now();

  pub_FL_leg_pos_ref_data_.header.frame_id = "FL_leg_pos_ref";
  pub_FR_leg_pos_ref_data_.header.frame_id = "FR_leg_pos_ref";
  pub_BL_leg_pos_ref_data_.header.frame_id = "BL_leg_pos_ref";
  pub_BR_leg_pos_ref_data_.header.frame_id = "BR_leg_pos_ref";

  FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref_data_);
  FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref_data_);
  BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref_data_);
  BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref_data_);
}

/**
 * @brief 目標ZMP軌道をパブリッシュする関数
 *
 */
void SneController::Run() {
  const double initial_time = ros::Time::now().toSec();  // 起動時刻を設定
  while (nh_.ok()) {
    const double control_time_ = ros::Time::now().toSec() - initial_time;  // 制御時刻を設定

    if (!SneControllerCallback(control_time_)) ros::shutdown();

    ros::spinOnce();
    rate_.sleep();
  }
}