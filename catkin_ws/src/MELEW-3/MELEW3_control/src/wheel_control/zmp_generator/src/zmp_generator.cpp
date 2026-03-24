/**
 * @file    zmp_generator.cpp
 * @author  Taisei Suzuki
 * @brief   目標経由点を生成するプログラムファイル
 * @version 0.1
 * @date    2023-05-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <zmp_generator/zmp_generator.hpp>

/**
 * @brief Construct a new ZmpGenerator::ZmpGenerator object
 *
 * @param nh  ノードハンドル
 * @param pnh プライベートノードハンドル
 */
ZmpGenerator::ZmpGenerator(ros::NodeHandle nh, ros::NodeHandle pnh) : nh_(nh), rate_(pnh.param("/loop_rate", 100)) {
  /*** パブリッシャの初期化 ***/
  waypoint_ref_pub_ =
      nh_.advertise<melew3_msgs::waypoint>(pnh.param<std::string>("/zg/waypoint_ref_topic_name", "/waypoint_ref"), 1);

  /*** 変数の初期化 ***/
  pnh.getParam("waypoint_ref", params);
  finish_time = 5.0;
}

/*****************************
  zmp := (x_zmp, y_zmp, z_G) (zmpのx座標, zmpのy座標, 重心高さ)
  com_yaw := psi_G (重心のYaw角)

  // 経由点のパラメータ（1次元）
  typedef struct {
    double time;  //!< 時刻
    double x;     //!< 位置
    double dx;    //!< 速度
    double ddx;   //!< 加速度
  } Utils::Five_Spline::point;

  // 経由点のパラメータ（3次元）
  typedef struct {
    double time;  //!< 時刻
    Eigen::Vector3d x;     //!< 位置(x,y,z)
    Eigen::Vector3d dx;    //!< 速度(x,y,z)
    Eigen::Vector3d ddx;   //!< 加速度(x,y,z)
  } Utils::Five_Spline::point3;
*****************************/

/**
 * @brief 目標経由点を生成する関数
 *
 */
void ZmpGenerator::ZmpGeneratorCallback(const double control_time) {
  if (control_time < finish_time) {
    /*** 変数の定義 ***/
    double          time;              //!< 時刻
    Eigen::Vector3d position;          //!< 目標位置
    Eigen::Vector3d velocity;          //!< 目標速度
    Eigen::Vector3d acceleration;      //!< 目標加速度
    double          yaw_position;      //!< 目標Yaw角位置
    double          yaw_velocity;      //!< 目標Yaw角速度
    double          yaw_acceleration;  //!< 目標Yaw角加速度

    if (params.size()) {
      if ((send_count < params.size()) && (static_cast<double>((params[send_count]["send_time"])) <= control_time)) {
        /*** yamlファイルからパラメータを取得 ***/
        send_time.push_back(static_cast<double>(params[send_count]["send_time"]));
        time = static_cast<double>(params[send_count]["time"]);
        position = {static_cast<double>(params[send_count]["position"][0]),
                    static_cast<double>(params[send_count]["position"][1]),
                    static_cast<double>(params[send_count]["position"][2])};
        velocity = {static_cast<double>(params[send_count]["velocity"][0]),
                    static_cast<double>(params[send_count]["velocity"][1]),
                    static_cast<double>(params[send_count]["velocity"][2])};
        acceleration = {static_cast<double>(params[send_count]["acceleration"][0]),
                        static_cast<double>(params[send_count]["acceleration"][1]),
                        static_cast<double>(params[send_count]["acceleration"][2])};
        yaw_position = static_cast<double>(params[send_count]["yaw_position"]);
        yaw_velocity = static_cast<double>(params[send_count]["yaw_velocity"]);
        yaw_acceleration = static_cast<double>(params[send_count]["yaw_acceleration"]);

        /*** 時刻，位置，速度，加速度を設定 ***/
        zmp_ref.push_back({time, position, velocity, acceleration});
        com_yaw_ref.push_back({time, yaw_position, yaw_velocity, yaw_acceleration});
        finish_time = time;  // 終了時刻の設定

        /*** パブリッシュの処理 ***/
        /*** 目標経由点をパブリッシュ ***/
        melew3_msgs::waypoint pub_waypoint_ref_data;
        pub_waypoint_ref_data.position.x = zmp_ref[send_count].x.x();
        pub_waypoint_ref_data.position.y = zmp_ref[send_count].x.y();
        pub_waypoint_ref_data.position.z = zmp_ref[send_count].x.z();
        pub_waypoint_ref_data.velocity.x = zmp_ref[send_count].dx.x();
        pub_waypoint_ref_data.velocity.y = zmp_ref[send_count].dx.y();
        pub_waypoint_ref_data.velocity.z = zmp_ref[send_count].dx.z();
        pub_waypoint_ref_data.acceleration.x = zmp_ref[send_count].ddx.x();
        pub_waypoint_ref_data.acceleration.y = zmp_ref[send_count].ddx.y();
        pub_waypoint_ref_data.acceleration.z = zmp_ref[send_count].ddx.z();
        pub_waypoint_ref_data.time.data = zmp_ref[send_count].time;
        pub_waypoint_ref_data.yaw_position.data = com_yaw_ref[send_count].x;
        pub_waypoint_ref_data.yaw_velocity.data = com_yaw_ref[send_count].dx;
        pub_waypoint_ref_data.yaw_acceleration.data = com_yaw_ref[send_count].ddx;
        pub_waypoint_ref_data.header.stamp = ros::Time::now();
        pub_waypoint_ref_data.header.frame_id = "waypoint_ref";
        waypoint_ref_pub_.publish(pub_waypoint_ref_data);
        send_count++;  // 送信したデータ数を更新
      }
    }
  }
}

/**
 * @brief 目標経由点をパブリッシュする関数
 *
 */
void ZmpGenerator::Run() {
  t_start = ros::Time::now();
  while (nh_.ok()) {
    control_time_ = (ros::Time::now() - t_start).toSec();  // 制御時刻を設定
    ZmpGeneratorCallback(control_time_);
    ros::spinOnce();
    rate_.sleep();
  }
}