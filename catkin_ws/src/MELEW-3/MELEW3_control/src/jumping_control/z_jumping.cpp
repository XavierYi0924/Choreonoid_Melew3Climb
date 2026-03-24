/**
 * @file    z_jumping.cpp
 * @author  Takatoshi Nakahara
 * @brief   Move z jump
 * @version 1.0
 * @date    2023-09-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <MELEW3_control/BaseController.h>
#include <MELEW3_control/utils.hpp>
#include <MELEW3_control/timer.hpp>
#include <MELEW3_control/param.hpp>
#include <vector> 
using namespace std;

namespace MELEW3_control {

class z_jumping : public BaseController {
private:
 double    lo; // landing offset
  int total_count_num;           // シミュレーションの全カウント数
  
  ros::Publisher FL_leg_pos_ref_pub_;   //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;   //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;   //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;   //!< 右後脚の目標脚先位置用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;      //!< 目標重心位置用パブリッシャー
  ros::Publisher COM_vel_ref_pub_;      //!< 目標重心速度用パブリッシャー
  ros::Publisher COM_acl_ref_pub_;      //!< 目標重心加速度用パブリッシャー
  ros::Publisher Leg_Length_pub_;      //!< 目標重心加速度用パブリッシャー
  /*** メッセージ関連 ***/
  Eigen::Vector3d FL_leg_pos_ref;  //!< 左前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d FR_leg_pos_ref;  //!< 右前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d BL_leg_pos_ref;  //!< 左前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d BR_leg_pos_ref;  //!< 右前脚の目標脚先位置を一時保存する変数

  Eigen::Vector3d FL_leg_pos_ref_pre;  //!< 左前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d FR_leg_pos_ref_pre;  //!< 右前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d BL_leg_pos_ref_pre;  //!< 左前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d BR_leg_pos_ref_pre;  //!< 右前脚の1個前の目標脚先位置を一時保存する変数
  Eigen::Vector3d COM_pos_ref_pre;     //!< 1個前の目標重心位置を一時保存する変数
  Eigen::Vector3d COM_vel_ref_pre;     //!< 1個前の目標重心位置を一時保存する変数
  Eigen::Vector3d COM_acl_ref_pre;     //!< 1個前の目標重心位置を一時保存する変数
  Eigen::Vector3d Leg_length;          //!< asinonagasa 

  Eigen::VectorXd com_z_tra;
  Eigen::VectorXd com_dz_tra;
  Eigen::VectorXd com_ddz_tra;
  Eigen::VectorXd zmp_ref_tra;

  double FL_leg_yaw_ref;  //!< 左前脚の目標Yaw角位置を一時保存する変数
  double FR_leg_yaw_ref;  //!< 右前脚の目標Yaw角位置を一時保存する変数
  double BL_leg_yaw_ref;  //!< 左後脚の目標Yaw角位置を一時保存する変数
  double BR_leg_yaw_ref;  //!< 右後脚の目標Yaw角位置を一時保存する変数
  double COM_yaw_ref;     //!< 重心の目標Yaw角位置を一時保存する変数

  /*** util関連 ***/
  Utils::Utils util;
  Utils::Five_Spline five_spline_z;
  Utils::Five_Spline five_spline_f;
    
  /*** 経由点情報 ***/
  Utils::Five_Spline::point z1;
  Utils::Five_Spline::point z2;
  Utils::Five_Spline::point z3;
  Utils::Five_Spline::point z4;
  Utils::Five_Spline::point zt;
  Utils::Five_Spline::point f1;
  Utils::Five_Spline::point f2;

  const double settingTime = 2.0;                             // 動作開始姿勢への遷移時間[s]
  const double x_init = 0.0;                                  // x軸初期位置[m]
  const double y_init = 0.0;  
  const double z_init = 0.35;                                // y軸初期位置[m]
  const double psi_init = 0.0;                                // psi初期位置[rad]

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

public:
  double Get_FreeFall_z(double time, Utils::Five_Spline::point z);
  double Get_FreeFall_dz(double time, Utils::Five_Spline::point z);
  double Get_FreeFall_ddz(double time);

  void ZTG();   // Z direction Trajectory Generayor
  void FTG();   // Foot Trajectory Generator

  Timer timer;
  Param param;
  Reference ref;

  Eigen::Vector3d COM_vel_ref{x_init, y_init, z_init};     //!< 目標重心速度を一時保存する変数
  Eigen::Vector3d COM_acl_ref{x_init, y_init, z_init};     //!< 目標重心加速度を一時保存する変数
  std::vector<Eigen::Vector3d> init_leg_pos{                              // 初期足部位置
    Eigen::Vector3d(FL_leg_offset_x_,FL_leg_offset_y_,FL_leg_offset_z_),
    Eigen::Vector3d(FR_leg_offset_x_,FR_leg_offset_y_,FR_leg_offset_z_),
    Eigen::Vector3d(BL_leg_offset_x_,BL_leg_offset_y_,BL_leg_offset_z_),
    Eigen::Vector3d(BR_leg_offset_x_,BR_leg_offset_y_,BR_leg_offset_z_)
  };
  std::vector<double> init_leg_yaw = {0.0, 0.0, 0.0, 0.0};                // 初期足部YAW角度
  std::vector<Eigen::VectorXf> init_torque{
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4),
    Eigen::VectorXf::Zero(4)
  };
  Eigen::Vector3d init_COM_pos{x_init, y_init, z_init};                   // 初期ベースリンク位置
  double init_COM_yaw = 0.0;                                              // 初期ベースリンクYAW角度

  z_jumping(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
z_jumping::z_jumping(void) {
  start_controller();
}

/**
 * @brief
 *
 */
void z_jumping::control_loop(void) {
  double current_time = get_time();
  // Transition to initial pose
  if (phase == 0) {
    if (pose_transition()) {
        /*** パブリッシャ，サブスクライバの初期化 ***/
      FL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FL_leg_pos_ref", 1);
      FR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FR_leg_pos_ref", 1);
      BL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BL_leg_pos_ref", 1);
      BR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BR_leg_pos_ref", 1);
      COM_pos_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_pos_ref", 1);
      COM_vel_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_vel_ref", 1);
      COM_acl_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_acl_ref", 1);
      Leg_Length_pub_ =nh.advertise<melew3_msgs::leg_pose>("/Leg_Length", 1);

      param.obs_h = 0.0;
      ref.z_s = 0.35; // 0.35
      ref.z_f = 0.42;
      ref.z_l = ref.z_s + param.obs_h;
      ref.z_e = ref.z_s + param.obs_h;
      // ref.z_ref = 0.45 + 0.136 / 2;
      ref.z_ref = 0.57;
      

      // Time Relationship
      timer.t_s = 0.0;  // start time
      timer.t_rs = timer.t_s + 0.0; // running start time
      timer.t_js = timer.t_rs + 1.0; // jump start time
      timer.t_f = timer.t_js + 0.3; // flying time
      timer.t_l = timer.t_f + sqrt(2 * (ref.z_ref - ref.z_f) / param.g) + sqrt(2 * (ref.z_ref - ref.z_l) / param.g); // landing time
      timer.t_je = timer.t_l + 0.2; // jump end time
      timer.t_re = timer.t_je + 0.8; // running end time
      timer.t_e = timer.t_re + 2.0; // end time
    
      // count
      timer.current_time = 0.0;
      timer.current_count = 0;
    
      timer.c_ini = 0;
      timer.c_s = timer.t_s / timer.dt; // 800
      timer.c_rs = timer.t_rs / timer.dt; // 1000
      timer.c_js = timer.t_js / timer.dt; // 1090
      timer.c_f = timer.t_f / timer.dt; //1150
      timer.c_l = timer.t_l / timer.dt; //1188
      timer.c_je = timer.t_je / timer.dt; //1208
      timer.c_re = timer.t_re / timer.dt; //1408
      timer.c_e = timer.t_e / timer.dt; //1608 

      int mem = 2*timer.c_e;
    
      // Reference Speed
      ref.dz_f = sqrt((2 * param.g * (ref.z_ref - ref.z_f) * (param.mb + param.mw) / param.mb));
      ref.dz_ft = sqrt(2 * param.g * (ref.z_ref - ref.z_f));
      ref.gene_zmp.resize(mem);
      ref.ZMP.resize(mem);
      ref.FL_foot.resize(mem);
      ref.FR_foot.resize(mem);
      ref.BL_foot.resize(mem);
      ref.BR_foot.resize(mem);
      ref.CoM.resize(mem);
      ref.dCoM.resize(mem);
      ref.ddCoM.resize(mem);
      ref.dddCoM.resize(mem);
      zmp_ref_tra = Eigen::VectorXd::Zero(mem);
      com_z_tra = Eigen::VectorXd::Zero(mem);
      com_dz_tra = Eigen::VectorXd::Zero(mem);
      com_ddz_tra = Eigen::VectorXd::Zero(mem);
    
      ROS_ERROR("Reference Point set");
    
      ZTG();
      ROS_ERROR("Z Trajectory set");
      timer.current_count = 0;
      
      FTG();
      ROS_ERROR("Foot Trajectory set");

      ROS_INFO("phase0 end");
      initialize_flag = false;
      phase = 1;
    }
  }

  // Transition to start pose
  if (phase == 1) {
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase1 end");
      timer.current_time = 0.0;
      timer.current_count = 0;
      ROS_WARN("z_ref: %f, dz_ref: %f", ref.z_ref, ref.dz_f);
      ROS_INFO("Enter key to start moving z jumping");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }

  // Move z sine wave
  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      initialize_flag = true;
    }

    /*
        ここで以下を決定する
        ・足先位置            ：leg_pos_ref
        ・足先YAW角度         ：leg_yaw_ref
        ・ベースリンク位置    ：COM_pos_ref
        ・ベースリンクYAW角度 ：COM_yaw_ref
        （World座標系）
        ・各モータのトルク（実機のみ）
    */

  /*** 脚先軌道と重心軌道を設定 ***/
  if(timer.current_count < timer.c_e){

    // 足先位置の決定
    leg_pos_ref[FL] = Eigen::Vector3d(ref.FL_foot[timer.current_count].x(), ref.FL_foot[timer.current_count].y(), ref.FL_foot[timer.current_count].z());
    leg_pos_ref[FR] = Eigen::Vector3d(ref.FR_foot[timer.current_count].x(), ref.FR_foot[timer.current_count].y(), ref.FR_foot[timer.current_count].z());
    leg_pos_ref[BL] = Eigen::Vector3d(ref.BL_foot[timer.current_count].x(), ref.BL_foot[timer.current_count].y(), ref.BL_foot[timer.current_count].z());
    leg_pos_ref[BR] = Eigen::Vector3d(ref.BR_foot[timer.current_count].x(), ref.BR_foot[timer.current_count].y(), ref.BR_foot[timer.current_count].z());

    // 足先YAW角度の決定
    leg_yaw_ref = init_leg_yaw;

    // ベースリンク位置の決定
    COM_pos_ref = Eigen::Vector3d(0.0, 0.0, ref.CoM[timer.current_count].z());

    // ベースリンクYAW角度の決定
    COM_yaw_ref = init_COM_yaw;

    // 各モータのトルク（実機のみ）
    leg_motor_torque = init_torque;
    
    // publish用
    COM_vel_ref = Eigen::Vector3d(0.0, 0.0, ref.dCoM[timer.current_count].z());
    COM_acl_ref = Eigen::Vector3d(0.0, 0.0, ref.ddCoM[timer.current_count].z());
    Leg_length = COM_pos_ref - leg_pos_ref[FL];
    
    timer.current_count ++;
  }
  else {

    // 足先位置の決定
    FL_leg_pos_ref = Eigen::Vector3d(ref.FL_foot[timer.c_e].x(), ref.FL_foot[timer.c_e].y(), ref.FL_foot[timer.c_e].z());
    FR_leg_pos_ref = Eigen::Vector3d(ref.FR_foot[timer.c_e].x(), ref.FR_foot[timer.c_e].y(), ref.FR_foot[timer.c_e].z());
    BL_leg_pos_ref = Eigen::Vector3d(ref.BL_foot[timer.c_e].x(), ref.BL_foot[timer.c_e].y(), ref.BL_foot[timer.c_e].z());
    BR_leg_pos_ref = Eigen::Vector3d(ref.BR_foot[timer.c_e].x(), ref.BR_foot[timer.c_e].y(), ref.BR_foot[timer.c_e].z());

    // 足先YAW角度の決定
    leg_yaw_ref = init_leg_yaw;

    // ベースリンク位置の決定
    COM_pos_ref = Eigen::Vector3d(0.0, 0.0, ref.CoM[timer.c_e].z());

    // ベースリンクYAW角度の決定
    COM_yaw_ref = init_COM_yaw;

    // 各モータのトルク（実機のみ）
    leg_motor_torque = init_torque;

    // publish用
    Leg_length = COM_pos_ref - leg_pos_ref[FL];
    COM_vel_ref = Eigen::Vector3d(0.0, 0.0, ref.dCoM[timer.c_e].z());
    COM_acl_ref = Eigen::Vector3d(0.0, 0.0, ref.ddCoM[timer.c_e].z());

    timer.current_count ++;
  }
      /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
    melew3_msgs::leg_pose  pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
                            pub_COM_pos_ref, pub_COM_vel_ref, pub_COM_acl_ref, pub_gene_zmp, pub_ZMP_pos_ref, pub_Leg_Length;

    util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);
    util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
    util.Vector3dToLegpose(COM_vel_ref, COM_yaw_ref, pub_COM_vel_ref);
    util.Vector3dToLegpose(COM_acl_ref, COM_yaw_ref, pub_COM_acl_ref);
    util.Vector3dToLegpose(Leg_length, COM_yaw_ref, pub_Leg_Length);

    FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
    BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
    FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
    BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
    COM_pos_ref_pub_.publish(pub_COM_pos_ref);
    COM_vel_ref_pub_.publish(pub_COM_vel_ref);
    COM_acl_ref_pub_.publish(pub_COM_acl_ref);
    Leg_Length_pub_.publish(pub_Leg_Length);

    if (timer.current_count >= timer.c_e) {
      phase = 3;
      initialize_flag = false;
    }
  }

  // Finalize
  else if (phase == 3) {
    ROS_INFO("Moving z jumping complete!");
    stop_controller();
  }
}

double z_jumping::Get_FreeFall_z(double time, Utils::Five_Spline::point z){
    double CT = time;
    double t_takeoff = z.time;
    double z_takeoff = z.x;
    double dz_takeoff = z.dx;
    double z_current = z_takeoff + dz_takeoff * (CT - t_takeoff) - 0.5 * param.g * pow(CT - t_takeoff, 2);
    
    return z_current;
}

// 浮遊期中のCoM_dz軌道を生成する関数
double z_jumping::Get_FreeFall_dz(double time, Utils::Five_Spline::point z){
    double CT = time;
    double t_takeoff = z.time;
    double dz_takeoff = z.dx;
    double dz_current = dz_takeoff - param.g * (CT - t_takeoff);
    
    return dz_current;
}

// 浮遊期中のCoM_ddz軌道を生成する関数
double z_jumping::Get_FreeFall_ddz(double time){
    double ddz_current = - param.g;
    
    return ddz_current;
}

void z_jumping::ZTG(){
  //** ZTG Start **//////////////////////////////////////////////////////////////////////////////
  // 1点目の時刻，位置，速度，加速度を指定 (For Initialize)

  // 1点目の時刻，位置，速度，加速度を指定
  z1 = {timer.t_js, 
        ref.z_s, 
        0.0, 
        0.0 };

  // 2点目の時刻，位置，速度，加速度を指定
  z2 = {timer.t_f,   
        ref.z_f, 
        ref.dz_f, 
        - param.g };

  // 3点目の時刻，位置，速度，加速度を指定
  z3 = {timer.t_l,
        ref.z_e, 
        - sqrt(2 * param.g * (ref.z_ref - ref.z_f)), 
        0.0 };

  // 4点目の時刻，位置，速度，加速度を指定
  z4 = {timer.t_je, 
        ref.z_e, 
        0.0, 
        0.0 };

  // 2点目(For Trajectory)の時刻，位置，速度，加速度を指定
  zt = {timer.t_f,   
        ref.z_f, 
        ref.dz_ft, 
        param.g };

  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_z_1 = {z1, z2, z3, z4};
  // 5次多項式補間の係数を計算
  five_spline_z.Calc_Spline(points_z_1); 


  for(int period_count = timer.c_ini; period_count < timer.c_e; period_count++){
    if(period_count < timer.c_js){
      com_z_tra(period_count) = z1.x;
      com_dz_tra(period_count) = z1.dx;
      com_ddz_tra(period_count) = z1.ddx;
      ref.CoM[period_count].z() = com_z_tra(period_count);
      ref.dCoM[period_count].z() = com_dz_tra(period_count);
      ref.ddCoM[period_count].z() = com_ddz_tra(period_count);
    }
    else if(period_count < timer.c_f){
      com_z_tra(period_count) = five_spline_z.Get_Spline_x(period_count*timer.dt);
      com_dz_tra(period_count) = five_spline_z.Get_Spline_dx(period_count*timer.dt);
      com_ddz_tra(period_count) = five_spline_z.Get_Spline_ddx(period_count*timer.dt);
      ref.CoM[period_count].z() = com_z_tra(period_count);
      ref.dCoM[period_count].z() = com_dz_tra(period_count);
      ref.ddCoM[period_count].z() = com_ddz_tra(period_count);
    }
    else if(period_count < timer.c_l){
      com_z_tra(period_count) = Get_FreeFall_z(period_count*timer.dt, zt);
      com_dz_tra(period_count) = Get_FreeFall_dz(period_count*timer.dt, zt);
      com_ddz_tra(period_count) = Get_FreeFall_ddz(period_count*timer.dt);
      ref.CoM[period_count].z() = com_z_tra(period_count);
      ref.dCoM[period_count].z() = com_dz_tra(period_count);
      ref.ddCoM[period_count].z() = com_ddz_tra(period_count);
    }
    else{
      com_z_tra(period_count) = z4.x;
      com_dz_tra(period_count) = z4.dx;
      com_ddz_tra(period_count) = z4.ddx;
      ref.CoM[period_count].z() = com_z_tra(period_count);
      ref.dCoM[period_count].z() = com_dz_tra(period_count);
      ref.ddCoM[period_count].z() = com_ddz_tra(period_count);
    }
    // std::cout << "Count " << period_count << "-> ref.CoM[].z() : " << ref.CoM[period_count].z() << std::endl;
  }
  //** ZTG End **//////////////////////////////////////////////////////////////////////////////
}

void z_jumping::FTG(){
  //** FTG Start **//////////////////////////////////////////////////////////////////////////////
  // 1点目の時刻，位置，速度，加速度を指定
  f1 = {timer.t_f, 
        0.0, 
        0.0, 
        param.g};

  // 2点目の時刻，位置，速度，加速度を指定
  f2 = {timer.t_f + sqrt(2 * param.g * (ref.z_ref - ref.z_f)) / param.g,   
        Get_FreeFall_z(z2.time + sqrt(2 * (ref.z_ref - ref.z_f) / param.g), zt) - ref.z_s, 
        Get_FreeFall_dz(z2.time + sqrt(2 * (ref.z_ref - ref.z_f) / param.g), zt), 
        Get_FreeFall_ddz(z2.time + sqrt(2 * (ref.z_ref - ref.z_f) / param.g)) };

  timer.c_lift = f2.time / timer.dt;

  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_foot_1 = {f1, f2};

  // 5次多項式補間の係数を計算
  five_spline_f.Calc_Spline(points_foot_1);


  for(int period_count = timer.c_ini; period_count < timer.c_e; period_count++){
    if(period_count < timer.c_f){
      
      ref.FL_foot[period_count].x() = ref.gene_zmp[period_count].x() + FL_leg_offset_x_;
      ref.FR_foot[period_count].x() = ref.gene_zmp[period_count].x() + FR_leg_offset_x_;
      ref.BL_foot[period_count].x() = ref.gene_zmp[period_count].x() + BL_leg_offset_x_;
      ref.BR_foot[period_count].x() = ref.gene_zmp[period_count].x() + BR_leg_offset_x_;

      ref.FL_foot[period_count].y() = 0.0 + FL_leg_offset_y_;
      ref.FR_foot[period_count].y() = 0.0 + FR_leg_offset_y_;
      ref.BL_foot[period_count].y() = 0.0 + BL_leg_offset_y_;
      ref.BR_foot[period_count].y() = 0.0 + BR_leg_offset_y_;

      ref.FL_foot[period_count].z() = 0.0 + FL_leg_offset_z_;
      ref.FR_foot[period_count].z() = 0.0 + FR_leg_offset_z_;
      ref.BL_foot[period_count].z() = 0.0 + BL_leg_offset_z_;
      ref.BR_foot[period_count].z() = 0.0 + BR_leg_offset_z_;
      
    }
    else if(period_count < timer.c_lift){

      ref.FL_foot[period_count].x() = ref.gene_zmp[period_count].x() + FL_leg_offset_x_;
      ref.FR_foot[period_count].x() = ref.gene_zmp[period_count].x() + FR_leg_offset_x_;
      ref.BL_foot[period_count].x() = ref.gene_zmp[period_count].x() + BL_leg_offset_x_;
      ref.BR_foot[period_count].x() = ref.gene_zmp[period_count].x() + BR_leg_offset_x_;

      ref.FL_foot[period_count].y() = 0.0 + FL_leg_offset_y_;
      ref.FR_foot[period_count].y() = 0.0 + FR_leg_offset_y_;
      ref.BL_foot[period_count].y() = 0.0 + BL_leg_offset_y_;
      ref.BR_foot[period_count].y() = 0.0 + BR_leg_offset_y_;

      ref.FL_foot[period_count].z() = five_spline_f.Get_Spline_x(period_count*timer.dt) + FL_leg_offset_z_;
      ref.FR_foot[period_count].z() = five_spline_f.Get_Spline_x(period_count*timer.dt) + FR_leg_offset_z_;
      ref.BL_foot[period_count].z() = five_spline_f.Get_Spline_x(period_count*timer.dt) + BL_leg_offset_z_;
      ref.BR_foot[period_count].z() = five_spline_f.Get_Spline_x(period_count*timer.dt) + BR_leg_offset_z_;
    }
    else if(period_count < timer.c_l){

      ref.FL_foot[period_count].x() = ref.gene_zmp[period_count].x() + FL_leg_offset_x_;
      ref.FR_foot[period_count].x() = ref.gene_zmp[period_count].x() + FR_leg_offset_x_;
      ref.BL_foot[period_count].x() = ref.gene_zmp[period_count].x() + BL_leg_offset_x_;
      ref.BR_foot[period_count].x() = ref.gene_zmp[period_count].x() + BR_leg_offset_x_;

      ref.FL_foot[period_count].y() = 0.0 + FL_leg_offset_y_;
      ref.FR_foot[period_count].y() = 0.0 + FR_leg_offset_y_;
      ref.BL_foot[period_count].y() = 0.0 + BL_leg_offset_y_;
      ref.BR_foot[period_count].y() = 0.0 + BR_leg_offset_y_;

      ref.FL_foot[period_count].z() = Get_FreeFall_z(period_count*timer.dt, zt) - ref.z_s + FL_leg_offset_z_;
      ref.FR_foot[period_count].z() = Get_FreeFall_z(period_count*timer.dt, zt) - ref.z_s + FR_leg_offset_z_;
      ref.BL_foot[period_count].z() = Get_FreeFall_z(period_count*timer.dt, zt) - ref.z_s + BL_leg_offset_z_;
      ref.BR_foot[period_count].z() = Get_FreeFall_z(period_count*timer.dt, zt) - ref.z_s + BR_leg_offset_z_;
    }
    else {
      ref.FL_foot[period_count].x() = ref.gene_zmp[period_count].x() + FL_leg_offset_x_;
      ref.FR_foot[period_count].x() = ref.gene_zmp[period_count].x() + FR_leg_offset_x_;
      ref.BL_foot[period_count].x() = ref.gene_zmp[period_count].x() + BL_leg_offset_x_;
      ref.BR_foot[period_count].x() = ref.gene_zmp[period_count].x() + BR_leg_offset_x_;

      ref.FL_foot[period_count].y() = 0.0 + FL_leg_offset_y_;
      ref.FR_foot[period_count].y() = 0.0 + FR_leg_offset_y_;
      ref.BL_foot[period_count].y() = 0.0 + BL_leg_offset_y_;
      ref.BR_foot[period_count].y() = 0.0 + BR_leg_offset_y_;

      ref.FL_foot[period_count].z() = param.obs_h + FL_leg_offset_z_;
      ref.FR_foot[period_count].z() = param.obs_h + FR_leg_offset_z_;
      ref.BL_foot[period_count].z() = param.obs_h + BL_leg_offset_z_;
      ref.BR_foot[period_count].z() = param.obs_h + BR_leg_offset_z_;
    }
  }
  //** FTG End **//////////////////////////////////////////////////////////////////////////////
}
}  // namespace MELEW3_control

int main(int argc, char* argv[]){
  ros::init(argc, argv, "z_jumping");
  MELEW3_control::BaseController* controller = new MELEW3_control::z_jumping;
  ros::waitForShutdown();
  return 0;
}

