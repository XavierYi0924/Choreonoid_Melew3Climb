/**
 * @file    pi_jumping.cpp
 * @author  Takatoshi Nakahara
 * @brief   Move z sine wave
 * @version 1.0
 * @date    2022-11-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <MELEW3_control/BaseController.h>
#include <Eigen/Core>
#include <iostream>
#include <vector> 
#include <MELEW3_control/timer.hpp>
#include <MELEW3_control/param.hpp>
#include <MELEW3_control/utils.hpp>

using namespace std;

namespace MELEW3_control {

class pi_jumping : public BaseController {
private:
  double    lo; // landing offset
  int total_count_num;           // シミュレーションの全カウント数
  void COMCallback();
  ros::Publisher FL_leg_pos_ref_pub_;   //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;   //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;   //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;   //!< 右後脚の目標脚先位置用パブリッシャー
  ros::Publisher gene_zmp_pub_;         //!< Generated ZMP 位置用パブリッシャー
  ros::Publisher ZMP_pos_ref_pub_;      //!< 目標ZMP位置用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;      //!< 目標重心位置用パブリッシャー
  ros::Publisher COM_vel_ref_pub_;      //!< 目標重心速度用パブリッシャー
  ros::Publisher COM_acl_ref_pub_;      //!< 目標重心加速度用パブリッシャー
  ros::Publisher Leg_Length_pub_;      //!< 目標重心加速度用パブリッシャー
  ros::Subscriber com_sub_;

  /*** メッセージ関連 ***/
  Eigen::Vector3d FL_leg_pos_ref;  //!< 左前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d FR_leg_pos_ref;  //!< 右前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d BL_leg_pos_ref;  //!< 左前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d BR_leg_pos_ref;  //!< 右前脚の目標脚先位置を一時保存する変数
  Eigen::Vector3d gene_zmp;
  Eigen::Vector3d ZMP_pos_ref;
  Eigen::Vector3d COM_vel_ref;     //!< 目標重心位置を一時保存する変数
  Eigen::Vector3d COM_acl_ref;     //!< 目標重心位置を一時保存する変数

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
  Utils::Five_Spline five_spline_z_init;
  Utils::Five_Spline five_spline_z;
  Utils::Five_Spline five_spline_f;
  Utils::Five_Spline five_spline_fx;
  Utils::Five_Spline five_spline_zmp;
  Utils::Five_Spline five_spline_x;

  /*** 経由点情報 ***/
  Utils::Five_Spline::point x1;
  Utils::Five_Spline::point x2;
  Utils::Five_Spline::point x3;
  Utils::Five_Spline::point x4;

  Utils::Five_Spline::point z1_;  
  Utils::Five_Spline::point z2_;
  Utils::Five_Spline::point z1;
  Utils::Five_Spline::point z2;
  Utils::Five_Spline::point z3;
  Utils::Five_Spline::point z4;
  Utils::Five_Spline::point z5;
  Utils::Five_Spline::point zt;

  Utils::Five_Spline::point f1;
  Utils::Five_Spline::point f2;
  Utils::Five_Spline::point f3;
  Utils::Five_Spline::point f4;
  Utils::Five_Spline::point f5;

  Utils::Five_Spline::point fx1;
  Utils::Five_Spline::point fx2;
  Utils::Five_Spline::point fx3;
  Utils::Five_Spline::point fx4;
  Utils::Five_Spline::point fx5;

  Utils::Five_Spline::point zmp1;
  Utils::Five_Spline::point zmp2;
  Utils::Five_Spline::point zmp3;
  Utils::Five_Spline::point zmp4;

  const double settingTime = 2.0;                             // 動作開始姿勢への遷移時間[s]
  const double movingTime = 20.0;                             // 動作時間[s]
  const double x_init = 0.0;                                  // x軸初期位置[m]
  const double y_init = 0.0;  
  const double z_init = 0.2 * sqrt(2) + 0.136 / 2;                                // y軸初期位置[m]
  const double psi_init = 0.0;                                // psi初期位置[rad]

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

  Eigen::Vector3d left_p_init;   // 動作開始姿勢
  Eigen::Vector3d right_p_init;  // 動作開始姿勢

public:
  double Get_FreeFall_z(double time, Utils::Five_Spline::point z);
  double Get_FreeFall_dz(double time, Utils::Five_Spline::point z);
  double Get_FreeFall_ddz(double time);
  double JumpPointer(Param param_, Reference ref_);

  void ZMPTG(); // ZMP Trajectory Generayor
  void ZTG();   // Z direction Trajectory Generayor
  void FTG();   // Foot Trajectory Generator
  void XTG();   // X direction Trajectory Generayor  

  Timer timer;
  Param param;
  Reference ref;

  std::vector<Eigen::Vector3d> init_leg_pos{
    Eigen::Vector3d(FL_leg_offset_x_,FL_leg_offset_y_,FL_leg_offset_z_),
    Eigen::Vector3d(FR_leg_offset_x_,FR_leg_offset_y_,FR_leg_offset_z_),
    Eigen::Vector3d(BL_leg_offset_x_,BL_leg_offset_y_,BL_leg_offset_z_),
    Eigen::Vector3d(BR_leg_offset_x_,BR_leg_offset_y_,BR_leg_offset_z_)
  };
  std::vector<double> init_leg_yaw = {0.0, 0.0, 0.0, 0.0};
  Eigen::Vector3d init_COM_pos{0.0, 0.0, z_init};
  double init_COM_yaw = 0.0;

  pi_jumping(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
pi_jumping::pi_jumping(void) {
  start_controller();
}

/**
 * @brief
 *
 */
void pi_jumping::control_loop(void) {
  double current_time = get_time();
  // Transition to initial pose
  if (phase == 0) {
    if (pose_transition()) {
      FL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FL_leg_pos_ref", 1);
      FR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FR_leg_pos_ref", 1);
      BL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BL_leg_pos_ref", 1);
      BR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BR_leg_pos_ref", 1);
      gene_zmp_pub_ = nh.advertise<melew3_msgs::leg_pose>("/gene_zmp_test", 1);
      ZMP_pos_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/ZMP_pos_ref_test", 1);
      COM_pos_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_pos_ref", 1);
      COM_vel_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_vel_ref", 1);
      COM_acl_ref_pub_ =nh.advertise<melew3_msgs::leg_pose>("/COM_acl_ref", 1);
      Leg_Length_pub_ =nh.advertise<melew3_msgs::leg_pose>("/Leg_Length", 1);

      // com_sub_ = nh.subscribe("MELEW3/com", 1, &pi_jumping::COMCallback, this);

      ref.z_s = 0.35; // 0.35
      ref.z_f = 0.42;
      ref.z_l = ref.z_s + 0.1;
      ref.z_e = ref.z_s + 0.1;
      // ref.z_ref = 0.45 + 0.136 / 2;
      ref.z_ref = 0.57;
      
      // Time Relationship
      timer.t_s = 0.0;  // start time
      timer.t_rs = timer.t_s + 3.0; // running start time
      timer.t_js = timer.t_rs + 0.7; // jump start time
      timer.t_f = timer.t_js + 0.3; // flying time
      timer.t_l = timer.t_f + sqrt(2 * (ref.z_ref - ref.z_f) / param.g) + sqrt(2 * (ref.z_ref - ref.z_l) / param.g); // landing time
      timer.t_je = timer.t_l + 0.2; // jump end time
      timer.t_re = timer.t_je + 0.6; // running end time
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
    
      // Environmental 
      param.obs_h = 0.1;
      param.s_dist = 3.0;
      param.stature = 0.25;
    
      // Reference Speed
      ref.dx_f = 2.7;
      ref.dz_f = sqrt((2 * param.g * (ref.z_ref - ref.z_f) * (param.mb + param.mw) / param.mb));
      ref.dz_ft = sqrt(2 * param.g * (ref.z_ref - ref.z_f));
      ROS_ERROR("dz:%f",ref.dz_f);
      // X Reference Point
      ref.x_s = 0.0;
      ref.x_f = JumpPointer(param, ref);
      ref.x_l = ref.x_f + ref.dx_f * (timer.t_l - timer.t_f);
      ref.x_e = ref.x_l + 1.5;
    
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
      ref.zmp_pgref = Eigen::VectorXd::Zero(mem);
      zmp_ref_tra = Eigen::VectorXd::Zero(mem);
      com_z_tra = Eigen::VectorXd::Zero(mem);
      com_dz_tra = Eigen::VectorXd::Zero(mem);
      com_ddz_tra = Eigen::VectorXd::Zero(mem);
    
      ROS_ERROR("Reference Point set");
    
      ZMPTG();
      ROS_ERROR("ZMP set");
    
      ZTG();
      ROS_ERROR("Z Trajectory set");
      timer.current_count = 0;
      
      FTG();
      ROS_ERROR("Foot Trajectory set");
    
      XTG();
      ROS_ERROR("X Trajectory set");
      ROS_INFO("phase0 end");
      timer.current_count = 0;

      initialize_flag = false;
      phase = 1;
    }
  }

  // Transition to start pose
  if (phase == 1) {
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase1 end");
            // count
      timer.current_time = 0.0;
      timer.current_count = 0;
      ROS_INFO("Enter key to start pi_jumping");
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
  std_msgs::Float64 hi;
  double time = get_time();

  /*** 脚先軌道と重心軌道を設定 ***/
  if(timer.current_count < timer.c_e){
    
    leg_pos_ref[FL] = Eigen::Vector3d(ref.FL_foot[timer.current_count].x(), ref.FL_foot[timer.current_count].y(), ref.FL_foot[timer.current_count].z());
    leg_pos_ref[FR] = Eigen::Vector3d(ref.FR_foot[timer.current_count].x(), ref.FR_foot[timer.current_count].y(), ref.FR_foot[timer.current_count].z());
    leg_pos_ref[BL] = Eigen::Vector3d(ref.BL_foot[timer.current_count].x(), ref.BL_foot[timer.current_count].y(), ref.BL_foot[timer.current_count].z());
    leg_pos_ref[BR] = Eigen::Vector3d(ref.BR_foot[timer.current_count].x(), ref.BR_foot[timer.current_count].y(), ref.BR_foot[timer.current_count].z());
    leg_yaw_ref = init_leg_yaw;

    gene_zmp = Eigen::Vector3d(ref.gene_zmp[timer.current_count].x(), 0.0, 0.0);
    ZMP_pos_ref = Eigen::Vector3d(ref.ZMP[timer.current_count].x(), 0.0, 0.0);
    COM_pos_ref = Eigen::Vector3d(ref.CoM[timer.current_count].x(), 0.0, ref.CoM[timer.current_count].z());
    COM_vel_ref = Eigen::Vector3d(ref.dCoM[timer.current_count].x(), 0.0, ref.dCoM[timer.current_count].z());
    COM_acl_ref = Eigen::Vector3d(ref.ddCoM[timer.current_count].x(), 0.0, ref.ddCoM[timer.current_count].z());
    COM_yaw_ref = init_COM_yaw;
    Leg_length = COM_pos_ref - leg_pos_ref[FL];
    // std::cout << "FL_leg_pos_ref.x : " << leg_pos_ref[FL].x() << std::endl;
    // std::cout << "COM_pos_ref.z : " << COM_pos_ref.z() << std::endl;
    // std::cout << "current_count : " << timer.current_count << std::endl;
    timer.current_count ++;
    // if(timer.current_count%5 == 0) timer.current_count ++;
  }
  else {

    FL_leg_pos_ref = Eigen::Vector3d(ref.FL_foot[timer.c_e].x(), ref.FL_foot[timer.c_e].y(), ref.FL_foot[timer.c_e].z());
    FR_leg_pos_ref = Eigen::Vector3d(ref.FR_foot[timer.c_e].x(), ref.FR_foot[timer.c_e].y(), ref.FR_foot[timer.c_e].z());
    BL_leg_pos_ref = Eigen::Vector3d(ref.BL_foot[timer.c_e].x(), ref.BL_foot[timer.c_e].y(), ref.BL_foot[timer.c_e].z());
    BR_leg_pos_ref = Eigen::Vector3d(ref.BR_foot[timer.c_e].x(), ref.BR_foot[timer.c_e].y(), ref.BR_foot[timer.c_e].z());
    leg_yaw_ref = init_leg_yaw;

    gene_zmp = Eigen::Vector3d(ref.gene_zmp[timer.c_e].x(), 0.0, 0.0);
    ZMP_pos_ref = Eigen::Vector3d(ref.ZMP[timer.l_e].x(), 0.0, 0.0);
    COM_pos_ref = Eigen::Vector3d(ref.CoM[timer.l_e].x(), 0.0, ref.CoM[timer.c_e].z());
    COM_vel_ref = Eigen::Vector3d(ref.dCoM[timer.l_e].x(), 0.0, ref.dCoM[timer.c_e].z());
    COM_acl_ref = Eigen::Vector3d(ref.ddCoM[timer.l_e].x(), 0.0, ref.ddCoM[timer.c_e].z());
    COM_yaw_ref = init_COM_yaw;
    Leg_length = COM_pos_ref - leg_pos_ref[FL];
    // std::cout << "Usso_leg_pos_ref.x : " << leg_pos_ref[FL].x() << std::endl;
    // std::cout << "UssoCOM_pos_ref.z : " << COM_pos_ref.z() << std::endl;
    // std::cout << "Usso_current_count : " << timer.current_count << std::endl;
    timer.current_count ++;
  }
      /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
    melew3_msgs::leg_pose  pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
                            pub_COM_pos_ref, pub_COM_vel_ref, pub_COM_acl_ref, pub_gene_zmp, pub_ZMP_pos_ref, pub_Leg_Length;

    util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
    util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);

    util.Vector3dToLegpose(gene_zmp, COM_yaw_ref, pub_gene_zmp);
    util.Vector3dToLegpose(ZMP_pos_ref, COM_yaw_ref, pub_ZMP_pos_ref);
    util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
    util.Vector3dToLegpose(COM_vel_ref, COM_yaw_ref, pub_COM_vel_ref);
    util.Vector3dToLegpose(COM_acl_ref, COM_yaw_ref, pub_COM_acl_ref);
    util.Vector3dToLegpose(Leg_length, COM_yaw_ref, pub_Leg_Length);

    FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
    BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
    FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
    BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
    gene_zmp_pub_.publish(pub_gene_zmp);
    ZMP_pos_ref_pub_.publish(pub_ZMP_pos_ref);
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
    ROS_INFO("pi_Jumping complete!");
    stop_controller();
  }
}

// 浮遊期中のCoM_z軌道を生成する関数
double pi_jumping::Get_FreeFall_z(double time, Utils::Five_Spline::point z){
    double CT = time;
    double t_takeoff = z.time;
    double z_takeoff = z.x;
    double dz_takeoff = z.dx;
    double z_current = z_takeoff + dz_takeoff * (CT - t_takeoff) - 0.5 * param.g * pow(CT - t_takeoff, 2);
    
    return z_current;
}

// 浮遊期中のCoM_dz軌道を生成する関数
double pi_jumping::Get_FreeFall_dz(double time, Utils::Five_Spline::point z){
    double CT = time;
    double t_takeoff = z.time;
    double dz_takeoff = z.dx;
    double dz_current = dz_takeoff - param.g * (CT - t_takeoff);
    
    return dz_current;
}

// 浮遊期中のCoM_ddz軌道を生成する関数
double pi_jumping::Get_FreeFall_ddz(double time){
    double ddz_current = - param.g;
    
    return ddz_current;
}

double pi_jumping::JumpPointer(Param param_, Reference ref_) {
  param = param_;
  ref = ref_;
  
  double disc = ref.dx_f * sqrt(ref.dz_f * ref.dz_f - 2 * param.g * param.obs_h);
  double x_ref;

  if(param.stature * param.g < disc){
    double x_ref_min = -(ref.dx_f * ref.dz_f + disc) / param.g + param.stature + param.s_dist;
    double x_ref_max = -(ref.dx_f * ref.dz_f - disc) / param.g - param.stature + param.s_dist;
    x_ref = (x_ref_max + x_ref_min) / 2;

  }else{
    ROS_ERROR("Can't find jump point");
    x_ref = 0;
  }
  
  return x_ref;
}

void pi_jumping::ZMPTG(){
  //** ZMPTG Start **//////////////////////////////////////////////////////////////////////////////
  zmp_ref_tra = Eigen::VectorXd::Zero(2*timer.c_e);

  // 1点目の時刻，位置，速度，加速度を指定
  zmp1 = {timer.t_rs, 
          0.0, 
          0.0, 
          0.0 };

  // 2点目の時刻，位置，速度，加速度を指定
  zmp2 = {timer.t_f,   
          ref.x_f, 
          ref.dx_f, 
          0.0 };
    
  // 3点目の時刻，位置，速度，加速度を指定
  zmp3 = {timer.t_l, 
          ref.x_l, 
          ref.dx_f, 
          0.0 };

  // 4点目の時刻，位置，速度，加速度を指定
  zmp4 = {timer.t_re,   
          ref.x_e, 
          0.0, 
          0.0 };  
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_zmp_1 = {zmp1, zmp2, zmp3, zmp4};
  // std::vector<Utils::Five_Spline::point> points_zmp_1 = {zmp1, zmp2};

  // 5次多項式補間の係数を計算
  five_spline_zmp.Calc_Spline(points_zmp_1);

  for(int period_count = 0; period_count < timer.c_e; period_count++){
    if(period_count < timer.c_rs){
      zmp_ref_tra(period_count) = 0.0;
      ref.gene_zmp[period_count].x() = zmp_ref_tra(period_count);
    }
    else if(period_count < timer.c_f){
      zmp_ref_tra(period_count) = five_spline_zmp.Get_Spline_x(period_count*timer.dt);
      ref.gene_zmp[period_count].x() = zmp_ref_tra(period_count);
    }
    else if(period_count < timer.c_l){
      zmp_ref_tra(period_count) = ref.x_f + ref.dx_f * (period_count*timer.dt - timer.t_f);
      ref.gene_zmp[period_count].x() = zmp_ref_tra(period_count);
    }
    else if(period_count < timer.c_re){
      zmp_ref_tra(period_count) = five_spline_zmp.Get_Spline_x(period_count*timer.dt);
      ref.gene_zmp[period_count].x() = zmp_ref_tra(period_count);
    }
    else{
      zmp_ref_tra(period_count) = ref.x_e;
      ref.gene_zmp[period_count].x() = zmp_ref_tra(period_count);
    }
  }
}

void pi_jumping::ZTG(){
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

    // (For Trajectory)の時刻，位置，速度，加速度を指定
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
  }
  //** ZTG End **//////////////////////////////////////////////////////////////////////////////
}

void pi_jumping::FTG(){
  //** FTG Start **//////////////////////////////////////////////////////////////////////////////
  // 1点目の時刻，位置，速度，加速度を指定
  f1 = {timer.t_f, 
        0.0, 
        0.0, 
        param.g };

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

void pi_jumping::XTG(){
//** XTG Start **//////////////////////////////////////////////////////////////////////////////
  // 1点目の時刻，位置，速度，加速度を指定
  x1 = {timer.t_rs, 
          0.0, 
          0.0, 
          0.0 };

  // 2点目の時刻，位置，速度，加速度を指定
  x2 = {timer.t_f,   
          ref.x_f, 
          ref.dx_f, 
          0.0 };
    
  // 3点目の時刻，位置，速度，加速度を指定
  x3 = {timer.t_l, 
          ref.x_l, 
          ref.dx_f, 
          0.0 };

  // 4点目の時刻，位置，速度，加速度を指定
  x4 = {timer.t_re,   
          ref.x_e, 
          0.0, 
          0.0 };  
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_x_1 = {x1, x2, x3, x4};
  // std::vector<Utils::Five_Spline::point> points_zmp_1 = {zmp1, zmp2};

  // 5次多項式補間の係数を計算
  five_spline_x.Calc_Spline(points_x_1);

  for(int period_count = 0; period_count < timer.c_e; period_count++){
    if(period_count < timer.c_rs){
      ref.CoM[period_count].x() = x1.x;
      ref.dCoM[period_count].x() = x1.dx;
      ref.ddCoM[period_count].x() = x1.ddx;
      ref.ZMP[period_count].x() = ref.CoM[period_count].x() - (ref.CoM[period_count].z() * ref.ddCoM[period_count].x()) / (ref.ddCoM[period_count].z() + param.g);
    }
    else if(period_count < timer.c_f){
      ref.CoM[period_count].x() = five_spline_x.Get_Spline_x(period_count*timer.dt);
      ref.dCoM[period_count].x() = five_spline_x.Get_Spline_dx(period_count*timer.dt);
      ref.ddCoM[period_count].x() =  five_spline_x.Get_Spline_ddx(period_count*timer.dt);
      ref.ZMP[period_count].x() = ref.CoM[period_count].x() - (ref.CoM[period_count].z() * ref.ddCoM[period_count].x()) / (ref.ddCoM[period_count].z() + param.g);
    }
    else if(period_count < timer.c_l){
      ref.CoM[period_count].x() = ref.x_f + ref.dx_f * (period_count*timer.dt - timer.t_f);
      ref.dCoM[period_count].x() = ref.dx_f;
      ref.ddCoM[period_count].x() = 0.0;
      ref.ZMP[period_count].x() = 0.0;
    }
    else if(period_count < timer.c_re){
      ref.CoM[period_count].x() = five_spline_x.Get_Spline_x(period_count*timer.dt);
      ref.dCoM[period_count].x() = five_spline_x.Get_Spline_dx(period_count*timer.dt);
      ref.ddCoM[period_count].x() =  five_spline_x.Get_Spline_ddx(period_count*timer.dt);
      ref.ZMP[period_count].x() = ref.CoM[period_count].x() - (ref.CoM[period_count].z() * ref.ddCoM[period_count].x()) / (ref.ddCoM[period_count].z() + param.g);
    }
    else{
      ref.CoM[period_count].x() = x4.x;
      ref.dCoM[period_count].x() = x4.dx;
      ref.ddCoM[period_count].x() = x4.ddx;
      ref.ZMP[period_count].x() = ref.CoM[period_count].x() - (ref.CoM[period_count].z() * ref.ddCoM[period_count].x()) / (ref.ddCoM[period_count].z() + param.g);
    }
  }
}

}  // namespace MELEW3_control

int main(int argc, char* argv[]){
  ros::init(argc, argv, "pi_jumping");
  MELEW3_control::BaseController* controller = new MELEW3_control::pi_jumping;
  ros::waitForShutdown();
  return 0;
}