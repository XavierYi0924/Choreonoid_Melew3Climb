/**
 * @file    zmp_preview_controller.cpp
 * @author  Yuta Ishizawa
 * @brief   予見制御を行うプログラムファイル
 * @version 0.1
 * @date    2022-12-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <zmp_generator/zmp_generator.hpp>
#include <zmp_preview_controller/zmp_preview_controller.hpp>

/**
 * @brief Construct a new Preview Control:: Preview Control object
 *
 * @param nh  ノードハンドル
 * @param pnh プライベートノードハンドル
 */
PreviewControl::PreviewControl(ros::NodeHandle nh, ros::NodeHandle pnh)
    : nh_(nh),
      rate_(pnh.param<double>("/loop_rate", 100)),
      pg(pnh.param<double>("/pr/com_height", 0.41441016151), pnh.param<double>("/pr/sampling_time", 0.001),
         pnh.param<double>("/pr/preview_time", 1.0)),
      zg(nh, pnh) {
  /*** パブリッシャ，サブスクライバの初期化 ***/
  zmp_pos_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("zmp_pos_ref_topic_name", "/zmp_pos_ref"), 1);
  zmp_vel_ref_pub_ =
      nh_.advertise<geometry_msgs::PointStamped>(pnh.param<std::string>("zmp_vel_ref_topic_name", "/zmp_vel_ref"), 1);
  zmp_acc_ref_pub_ =
      nh_.advertise<geometry_msgs::PointStamped>(pnh.param<std::string>("zmp_acc_ref_topic_name", "/zmp_acc_ref"), 1);
  com_pos_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("com_pos_ref_topic_name", "/COM_pos_ref"), 1);
  com_vel_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("com_vel_ref_topic_name", "/COM_vel_ref"), 1);
  com_acc_ref_pub_ =
      nh_.advertise<melew3_msgs::leg_pose>(pnh.param<std::string>("com_acc_ref_topic_name", "/COM_acc_ref"), 1);

  /*** メンバ変数の初期化 ***/
  pnh.param<double>("/loop_rate", loop_rate_, 100);
  pnh.param<double>("/pr/sampling_time", sampling_time_, 0.001);
  pnh.param<double>("/pr/leg_rotate_time", leg_rotate_time_, 0.5);
  pnh.param<double>("/pr/start_control_time", start_control_time_, 5.0);
  pnh.param<double>("/pr/com_height", com_height_, 0.41441016151);
  pnh.param<double>("/pr/Qe", Qe_, 1.0);
  pnh.param<double>("/pr/Ru", Ru_, 3.0);
  control_period_ = 1.0 / loop_rate_;

  Init();  // 初期設定
}

/**
 * @brief 最初の処理を行う関数
 *
 */
void PreviewControl::Init() {
  /*** 経由点を追加 ***/
  waypoint_position.push_back({0.0, {0.0, 0.0, com_height_}, Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero()});
  waypoint_position.push_back({start_control_time_ - leg_rotate_time_,
                               {0.0, 0.0, com_height_},
                               Eigen::Vector3d::Zero(),
                               Eigen::Vector3d::Zero()});
  waypoint_position.push_back(
      {start_control_time_, {0.0, 0.0, com_height_}, Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero()});
  waypoint_yaw.push_back({0.0, 0.0, 0.0, 0.0});
  waypoint_yaw.push_back({start_control_time_ - leg_rotate_time_, 0.0, 0.0, 0.0});
  waypoint_yaw.push_back({start_control_time_, 0.0, 0.0, 0.0});
  waypoint_time.insert(waypoint_time.end(), {0.0, start_control_time_ - leg_rotate_time_, start_control_time_});

  CalcZmpTrajectory(waypoint_position, waypoint_yaw);  // 目標ZMP軌道を生成
  CalcPreviewControl(false);                           // 目標重心軌道を生成
}

/**
 * @brief 微分を計算する関数
 *
 * @param control_period 制御周期[s]
 * @param pos            位置
 * @param vel            速度
 * @param acc            加速度
 */
void PreviewControl::CalcDifferential(const double control_period, const std::vector<Eigen::Vector3d> pos,
                                      std::vector<Eigen::Vector3d>& vel, std::vector<Eigen::Vector3d>& acc) {
  for (int i = vel.size(); i < pos.size(); i++) {
    /*** 数値微分で目標com速度と加速度を算出 ***/
    if (i) {
      vel.emplace_back((pos[i] - pos[i - 1]) / control_period);
      acc.emplace_back((vel[i] - vel[i - 1]) / control_period);
    } else {
      vel.emplace_back(Eigen::Vector3d::Zero());
      acc.emplace_back(Eigen::Vector3d::Zero());
    }
  }
}

/**
 * @brief 目標ZMP軌道を計算する関数
 *
 * @param zmp_point_data     位置に関する経由点データ
 * @param zmp_yaw_point_data 操舵角に関する経由点データ
 */
void PreviewControl::CalcZmpTrajectory(std::vector<Utils::Five_Spline::point3> zmp_point_data,
                                       std::vector<Utils::Five_Spline::point>  zmp_yaw_point_data) {
  /*** 5次多項式補間の係数を計算 ***/
  five_spline_zmp.Calc_Spline3(zmp_point_data);
  five_spline_zmp.Calc_Spline(zmp_yaw_point_data);

  stop_control_time_ = zmp_point_data.back().time;  // 終了時刻の設定

  /*** 現在時刻におけるZMPと重心操舵角の位置・速度・加速度を取得 ***/
  for (int i = zmp_pos_traj_.size(); i < (int)(stop_control_time_ / sampling_time_); i++) {
    zmp_pos_traj_.push_back({five_spline_zmp.Get_Spline3_x((double)i * sampling_time_)});
    zmp_vel_traj_.push_back({five_spline_zmp.Get_Spline3_dx((double)i * sampling_time_)});
    zmp_acc_traj_.push_back({five_spline_zmp.Get_Spline3_ddx((double)i * sampling_time_)});
    com_yaw_pos_traj_.push_back({five_spline_zmp.Get_Spline_x((double)i * sampling_time_)});
    com_yaw_vel_traj_.push_back({five_spline_zmp.Get_Spline_dx((double)i * sampling_time_)});
    com_yaw_acc_traj_.push_back({five_spline_zmp.Get_Spline_ddx((double)i * sampling_time_)});
  }
}

/**
 * @brief 予見制御を用いて目標重心軌道を計算する関数
 *
 * @param last_flag 終了時の処理かどうかを判定するフラグ
 */
void PreviewControl::CalcPreviewControl(const bool last_flag) {
  /*** 重心軌道生成 ***/
  pg.generate(zmp_pos_traj_, com_pos_traj_, Qe_, Ru_, last_flag);
  // pg.notgenerate(zmp_pos_traj_, com_pos_traj_, last_flag);

  CalcDifferential(sampling_time_, com_pos_traj_, com_vel_traj_, com_acc_traj_);  //数値微分で目標com速度と加速度を算出
}

/**
 * @brief 目標経由点から目標ZMP軌道と目標重心軌道を生成する関数
 *
 * @param waypoint_ref 目標経由点
 */
bool PreviewControl::PreviewControlCallback(const double control_time) {
  how_many_times_ = (int)(control_time / sampling_time_);  // 制御回数を設定
  if (control_time <= stop_control_time_) {
    zg.ZmpGeneratorCallback(control_time);  // 目標経由点を取得

    /*** 変数の定義 ***/
    Utils::Five_Spline::point3 waypoint_position_data;
    Utils::Five_Spline::point  waypoint_yaw_data;
    /*** 目標経由点のデータの時刻が変化したときの処理 ***/
    if (zg.zmp_ref.size() && zg.zmp_ref.back().time > stop_control_time_) {
      /*** 目標経由点を追加 ***/
      if (!(zg.zmp_ref.back().dx.x() || zg.zmp_ref.back().dx.y())) {
        waypoint_position_data = {zg.zmp_ref.back().time - leg_rotate_time_, zg.zmp_ref.back().x, zg.zmp_ref.back().dx,
                                  zg.zmp_ref.back().ddx};
        waypoint_yaw_data = {zg.com_yaw_ref.back().time - leg_rotate_time_, zg.com_yaw_ref.back().x,
                             zg.com_yaw_ref.back().dx, zg.com_yaw_ref.back().ddx};
        waypoint_time.emplace_back(zg.zmp_ref.back().time - leg_rotate_time_);
        waypoint_position.push_back(waypoint_position_data);
        waypoint_yaw.push_back(waypoint_yaw_data);

        CalcZmpTrajectory({waypoint_position_data}, {waypoint_yaw_data});  // 目標ZMP軌道を生成
        CalcPreviewControl(false);                                         // 目標重心軌道を生成
      }

      waypoint_position_data = {zg.zmp_ref.back().time, zg.zmp_ref.back().x, zg.zmp_ref.back().dx,
                                zg.zmp_ref.back().ddx};
      waypoint_yaw_data = {zg.com_yaw_ref.back().time, zg.com_yaw_ref.back().x, zg.com_yaw_ref.back().dx,
                           zg.com_yaw_ref.back().ddx};

      waypoint_position.push_back(waypoint_position_data);
      waypoint_yaw.push_back(waypoint_yaw_data);
      waypoint_time.emplace_back(zg.zmp_ref.back().time);
      CalcZmpTrajectory({waypoint_position_data}, {waypoint_yaw_data});  // 目標ZMP軌道を生成
      CalcPreviewControl(false);                                         // 目標重心軌道を生成
    }

    /*** 制御時間内 ***/
    if (!(how_many_times_ < com_pos_traj_.size()))
      CalcPreviewControl(true);  // 重心軌道がまだ生成されていない場合，目標重心軌道を生成

    PreviewControlPublisher(control_time);  // 目標ZMP軌道と目標重心軌道をパブリッシュ

    return true;
  } else {
    return false;
  }
}

/**
 * @brief 目標ZMP軌道と目標重心軌道をパブリッシュする関数
 *
 */
void PreviewControl::PreviewControlPublisher(const double control_time) {
  /*** ZMPと重心の目標位置・速度・加速度をパブリッシュ ***/
  util.Vector3dToLegpose(zmp_pos_traj_[how_many_times_], 0.0, pub_zmp_pos_ref_data_);
  util.Vector3dToPoint(zmp_vel_traj_[how_many_times_], pub_zmp_vel_ref_data_.point);
  util.Vector3dToPoint(zmp_acc_traj_[how_many_times_], pub_zmp_acc_ref_data_.point);
  util.Vector3dToLegpose(com_pos_traj_[how_many_times_], com_yaw_pos_traj_[how_many_times_], pub_com_pos_ref_data_);
  util.Vector3dToLegpose(com_vel_traj_[how_many_times_], com_yaw_vel_traj_[how_many_times_], pub_com_vel_ref_data_);
  util.Vector3dToLegpose(com_acc_traj_[how_many_times_], com_yaw_acc_traj_[how_many_times_], pub_com_acc_ref_data_);

  pub_zmp_pos_ref_data_.header.stamp = ros::Time::now();
  pub_zmp_vel_ref_data_.header.stamp = ros::Time::now();
  pub_zmp_acc_ref_data_.header.stamp = ros::Time::now();
  pub_com_pos_ref_data_.header.stamp = ros::Time::now();
  pub_com_vel_ref_data_.header.stamp = ros::Time::now();
  pub_com_acc_ref_data_.header.stamp = ros::Time::now();

  pub_zmp_pos_ref_data_.header.frame_id = "zmp_ref";
  pub_zmp_vel_ref_data_.header.frame_id = "zmp_velocity_ref";
  pub_zmp_acc_ref_data_.header.frame_id = "zmp_acceleration_ref";
  pub_com_pos_ref_data_.header.frame_id = "com_pos_ref";
  pub_com_vel_ref_data_.header.frame_id = "com_vel_ref";
  pub_com_acc_ref_data_.header.frame_id = "com_acc_ref";

  zmp_pos_ref_pub_.publish(pub_zmp_pos_ref_data_);
  zmp_vel_ref_pub_.publish(pub_zmp_vel_ref_data_);
  zmp_acc_ref_pub_.publish(pub_zmp_acc_ref_data_);
  com_pos_ref_pub_.publish(pub_com_pos_ref_data_);
  com_vel_ref_pub_.publish(pub_com_vel_ref_data_);
  com_acc_ref_pub_.publish(pub_com_acc_ref_data_);
}

/**
 * @brief 予見制御を回す関数
 *
 */
void PreviewControl::Run() {
  initial_time_ = ros::Time::now().toSec();
  while (nh_.ok()) {
    control_time_ = ros::Time::now().toSec() - initial_time_;  // 制御時刻を設定

    /*** 目標経由点から目標ZMP軌道と目標重心軌道を生成 ***/
    if (!PreviewControlCallback(control_time_)) ros::shutdown();

    ros::spinOnce();
    rate_.sleep();
  }
}