/**
 * @file    jumping.cpp
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
#include <MELEW3_control/Calc_Matrix.hpp>
#include <MELEW3_control/timer.hpp>
#include <MELEW3_control/param.hpp>
#include <MELEW3_control/utils.hpp>

using namespace std;

namespace MELEW3_control {

class jumping : public BaseController {
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

  Eigen::Vector3d FL_foot_tilted_position;
  Eigen::Vector3d FR_foot_tilted_position;
  

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
  const double z_init = 0.2 * sqrt(2) + 0.136 / 2;            // y軸初期位置[m]
  const double psi_init = 0.0;                                // psi初期位置[rad]
  
  const double leg_down = 0.06;                                // leg down
  const double x_ch = 0.10;                                    // make sure L stay in [L_min,L_max]

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

  Eigen::Vector3d left_p_init;   // 動作開始姿勢
  Eigen::Vector3d right_p_init;  // 動作開始姿勢

public:
  double Get_FreeFall_z(double time, Utils::Five_Spline::point z);
  double Get_FreeFall_dz(double time, Utils::Five_Spline::point z);
  double Get_FreeFall_ddz(double time);

  void ZTG();   // Z direction Trajectory Generayor
  void FTG();   // Foot Trajectory Generator
  void TILT();

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

  jumping(void);
  virtual void control_loop(void) override;

};

/**
 * @brief Construct a new melew 2l object
 *
 */
jumping::jumping(void) {
  start_controller();
}


/**
 * @brief
 *
 */
void jumping::control_loop(void) {
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

      ref.z_s = 0.35; // 0.35
      ref.z_f = 0.40;
      ref.z_l = ref.z_s + 0.1;
      ref.z_e = ref.z_s + 0.1;
      // ref.z_ref = 0.45 + 0.136 / 2;
      ref.z_ref = 0.57;
      
      // Time Relationship
      timer.t_s = 0.0;  // start time
      timer.t_rs = timer.t_s + 3.0; // running start time
      timer.t_js = timer.t_rs + 1.1;//jump start time 0.7
      timer.t_f = timer.t_js + 0.4; // flying time 0.4
      timer.t_l = timer.t_f + sqrt(2 * (ref.z_ref - ref.z_f) / param.g) + sqrt(2 * (ref.z_ref - ref.z_l) / param.g); // landing time
      timer.t_je = timer.t_l + 0.2; // jump end time
      timer.t_re = timer.t_je + 0.8; // running end time 0.6
      timer.t_e = timer.t_re + 2.0;  // void XTG();   // X direction Trajectory Generayor  / end time
    
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
    
      ZTG();
      ROS_ERROR("Z Trajectory set");
      timer.current_count = 0;
      
      FTG();
      ROS_ERROR("Foot Trajectory set");

      TILT();
      ROS_ERROR("Tilt set");

      ROS_INFO("phase0 end");
      timer.current_count = 0;

      initialize_flag = false;
      phase = 1;
    }
  }

  // Transition to start pose + 抬腿动作
  if (phase == 1) {
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase1 end");
            // count
      timer.current_time = 0.0;
      timer.current_count = 0;

      ROS_INFO("Phase 1 complete, lowering left legs");

      ROS_INFO("Enter key to start jumping");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }

  // 完成跳跃动作 （只跳跃不移动，忽略zmp的计算）
  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      initialize_flag = true;
    }
  std_msgs::Float64 hi;
  double time = get_time();

  bool isLeftLegBent = true;  // 这里假设左腿弯曲

  /*** 脚先軌道と重心軌道を設定 ***/
  if(timer.current_count < timer.c_e){
    
    leg_pos_ref[FL] = Eigen::Vector3d(ref.FL_foot[timer.current_count].x(), ref.FL_foot[timer.current_count].y(), ref.FL_foot[timer.current_count].z());
    leg_pos_ref[FR] = Eigen::Vector3d(ref.FR_foot[timer.current_count].x(), ref.FR_foot[timer.current_count].y(), ref.FR_foot[timer.current_count].z());
    leg_pos_ref[BL] = Eigen::Vector3d(ref.BL_foot[timer.current_count].x(), ref.BL_foot[timer.current_count].y(), ref.BL_foot[timer.current_count].z());
    leg_pos_ref[BR] = Eigen::Vector3d(ref.BR_foot[timer.current_count].x(), ref.BR_foot[timer.current_count].y(), ref.BR_foot[timer.current_count].z());
    leg_yaw_ref = init_leg_yaw;

    COM_pos_ref = Eigen::Vector3d(ref.CoM[timer.current_count].x(), 0.0, ref.CoM[timer.current_count].z());
    COM_vel_ref = Eigen::Vector3d(ref.dCoM[timer.current_count].x(), 0.0, ref.dCoM[timer.current_count].z());
    COM_acl_ref = Eigen::Vector3d(ref.ddCoM[timer.current_count].x(), 0.0, ref.ddCoM[timer.current_count].z());
    COM_yaw_ref = init_COM_yaw;


    Leg_length = COM_pos_ref - leg_pos_ref[FL];
    timer.current_count ++;
  }
  else {

    FL_leg_pos_ref = Eigen::Vector3d(ref.FL_foot[timer.c_e].x(), ref.FL_foot[timer.c_e].y(), ref.FL_foot[timer.c_e].z());
    FR_leg_pos_ref = Eigen::Vector3d(ref.FR_foot[timer.c_e].x(), ref.FR_foot[timer.c_e].y(), ref.FR_foot[timer.c_e].z());
    BL_leg_pos_ref = Eigen::Vector3d(ref.BL_foot[timer.c_e].x(), ref.BL_foot[timer.c_e].y(), ref.BL_foot[timer.c_e].z());
    BR_leg_pos_ref = Eigen::Vector3d(ref.BR_foot[timer.c_e].x(), ref.BR_foot[timer.c_e].y(), ref.BR_foot[timer.c_e].z());
    leg_yaw_ref = init_leg_yaw;

    COM_pos_ref = Eigen::Vector3d(ref.CoM[timer.l_e].x(), 0.0, ref.CoM[timer.c_e].z());
    COM_vel_ref = Eigen::Vector3d(ref.dCoM[timer.l_e].x(), 0.0, ref.dCoM[timer.c_e].z());
    COM_acl_ref = Eigen::Vector3d(ref.ddCoM[timer.l_e].x(), 0.0, ref.ddCoM[timer.c_e].z());
    COM_yaw_ref = init_COM_yaw;
    Leg_length = COM_pos_ref - leg_pos_ref[FL];
  


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
    ROS_INFO("Phase 3 complete, raised legs back");

    ROS_INFO("jumping complete!");
    stop_controller();
  }
}

// Z方向运动轨迹生成
double jumping::Get_FreeFall_z(double time, Utils::Five_Spline::point z){
    double CT = time;
    double t_takeoff = z.time;
    double z_takeoff = z.x;
    double dz_takeoff = z.dx;
    double z_current = z_takeoff + dz_takeoff * (CT - t_takeoff) - 0.5 * param.g * pow(CT - t_takeoff, 2);
    
    return z_current;
}

// Z方向速度函数生成
double jumping::Get_FreeFall_dz(double time, Utils::Five_Spline::point z){
    double CT = time;
    double t_takeoff = z.time;
    double dz_takeoff = z.dx;
    double dz_current = dz_takeoff - param.g * (CT - t_takeoff);
    
    return dz_current;
}

// 重力加速度函数生成
double jumping::Get_FreeFall_ddz(double time){
    double ddz_current = - param.g;
    
    return ddz_current;
}


//* 重心轨迹生成 */
void jumping::ZTG(){
  //** ZTG Start **//////////////////////////////////////////////////////////////////////////////
  //*********** *************//
  // 1点目の時刻，位置，速度，加速度を指定
  z1 = {timer.t_js, 
        ref.z_s, 
        0.0, 
        0.0 };

  // 2点目の時刻，位置，速度，加速度を指定
  z2 = {timer.t_f,   
        ref.z_f, 
        ref.dz_f, 
        param.g };

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
    // double current_time = period_count * timer.dt;
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
//* 腿部轨迹生成 */
// 腿部轨迹生成函数
void jumping::FTG() {

    Utils::Five_Spline::point FL_f1 = {
        timer.t_f,
        FL_leg_offset_z_ - FL_foot_tilted_position.z(),  
        0.0,
        param.g
    };

    Utils::Five_Spline::point FR_f1 = {
        timer.t_f,
        FR_leg_offset_z_ - FR_foot_tilted_position.z(),
        0.0,
        param.g
    };

    Utils::Five_Spline::point BL_f1 = {
        timer.t_f,
        BL_leg_offset_z_,
        0.0,
        param.g
    };

    Utils::Five_Spline::point BR_f1 = {
        timer.t_f,
        BR_leg_offset_z_,
        0.0,
        param.g
    };

    Utils::Five_Spline::point f2 = {
        timer.t_f + sqrt(2 * param.g * (ref.z_ref - ref.z_f)) / param.g,
        Get_FreeFall_z(z2.time + sqrt(2 * (ref.z_ref - ref.z_f) / param.g), zt) - ref.z_s,
        Get_FreeFall_dz(z2.time + sqrt(2 * (ref.z_ref - ref.z_f) / param.g), zt),
        Get_FreeFall_ddz(z2.time + sqrt(2 * (ref.z_ref - ref.z_f) / param.g))
    };

    timer.c_lift = f2.time / timer.dt;

  
    std::vector<Utils::Five_Spline::point> FL_points = {FL_f1, f2};
    std::vector<Utils::Five_Spline::point> FR_points = {FR_f1, f2};
    std::vector<Utils::Five_Spline::point> BL_points = {BL_f1, f2};
    std::vector<Utils::Five_Spline::point> BR_points = {BR_f1, f2};

    Utils::Five_Spline FL_spline, FR_spline, BL_spline, BR_spline;
    FL_spline.Calc_Spline(FL_points);
    FR_spline.Calc_Spline(FR_points);
    BL_spline.Calc_Spline(BL_points);
    BR_spline.Calc_Spline(BR_points);

    // 生成每条腿的轨迹
    for (int period_count = timer.c_ini; period_count < timer.c_e; period_count++) {
        double current_time = period_count * timer.dt;

        ref.FL_foot[period_count].x() = FL_leg_offset_x_ + FL_foot_tilted_position.x();
        ref.FR_foot[period_count].x() = FR_leg_offset_x_ + FR_foot_tilted_position.x();
        ref.BL_foot[period_count].x() = BL_leg_offset_x_;
        ref.BR_foot[period_count].x() = BR_leg_offset_x_;

        ref.FL_foot[period_count].y() = FL_leg_offset_y_;  
        ref.FR_foot[period_count].y() = FR_leg_offset_y_;
        ref.BL_foot[period_count].y() = BL_leg_offset_y_;
        ref.BR_foot[period_count].y() = BR_leg_offset_y_;

        if (period_count < timer.c_f) {
            ref.FL_foot[period_count].z() = FL_leg_offset_z_ - FL_foot_tilted_position.z();
            ref.FR_foot[period_count].z() = FR_leg_offset_z_ - FR_foot_tilted_position.z();
            ref.BL_foot[period_count].z() = BL_leg_offset_z_;
            ref.BR_foot[period_count].z() = BR_leg_offset_z_;
        } 
        else if (period_count < timer.c_lift) {
            ref.FL_foot[period_count].z() = FL_spline.Get_Spline_x(current_time) + FL_leg_offset_z_;
            ref.FR_foot[period_count].z() = FR_spline.Get_Spline_x(current_time) + FR_leg_offset_z_;
            ref.BL_foot[period_count].z() = BL_spline.Get_Spline_x(current_time) + BL_leg_offset_z_;
            ref.BR_foot[period_count].z() = BR_spline.Get_Spline_x(current_time) + BR_leg_offset_z_;
        } 
        else if (period_count < timer.c_l) {
            ref.FL_foot[period_count].z() = Get_FreeFall_z(current_time, zt) - ref.z_s + FL_leg_offset_z_;
            ref.FR_foot[period_count].z() = Get_FreeFall_z(current_time, zt) - ref.z_s + FR_leg_offset_z_;
            ref.BL_foot[period_count].z() = Get_FreeFall_z(current_time, zt) - ref.z_s + BL_leg_offset_z_;
            ref.BR_foot[period_count].z() = Get_FreeFall_z(current_time, zt) - ref.z_s + BR_leg_offset_z_;
        } 
        else {
            ref.FL_foot[period_count].z() = param.obs_h + FL_leg_offset_z_;
            ref.FR_foot[period_count].z() = param.obs_h + FR_leg_offset_z_;
            ref.BL_foot[period_count].z() = param.obs_h + BL_leg_offset_z_;
            ref.BR_foot[period_count].z() = param.obs_h + BR_leg_offset_z_;
        }
    }
}

  // Defining front legs tilting function
void jumping::TILT(){
  double tilt_duration = 1.0; // 倾斜持续时间（在起跳之前）
  double t_start_tilt = timer.t_js - tilt_duration;  // 倾斜开始时间
  double t_end_tilt = timer.t_js;     // 倾斜结束时间

  double init_x_ch = 0.0;
  double end_x_ch = x_ch;          
  double init_leg_down = 0;
  double end_leg_down = - leg_down + init_leg_down;  

  double accumulated_delta_x = 0.0;
  double accumulated_delta_z = 0.0;

  Utils::Five_Spline::point x_tilt_start = {
    t_start_tilt,
    init_x_ch,
    0,
    0
  };

  Utils::Five_Spline::point x_tilt_end = {
    t_end_tilt,
    end_x_ch,
    0,
    0
  };

  Utils::Five_Spline::point z_tilt_start = {
    t_start_tilt,
    init_leg_down,
    0,
    0
  };

  Utils::Five_Spline::point z_tilt_end = {
    t_end_tilt,
    end_leg_down,
    0,
    0
  };

  std::vector<Utils::Five_Spline::point> points_x_tilt = {x_tilt_start, x_tilt_end};
  Utils::Five_Spline five_spline_x_tilt;
  five_spline_x_tilt.Calc_Spline(points_x_tilt);

  std::vector<Utils::Five_Spline::point> points_z_tilt = {z_tilt_start, z_tilt_end};
  Utils::Five_Spline five_spline_z_tilt;
  five_spline_z_tilt.Calc_Spline(points_z_tilt);

  int c_tilt_start = static_cast<int>(t_start_tilt / timer.dt);
  int c_tilt_end = static_cast<int>(t_end_tilt / timer.dt);

  // 在倾斜期间调整前腿的位置
  for (int period_count = c_tilt_start; period_count <= c_tilt_end; period_count++) {
      double current_time = period_count * timer.dt;

      double delta_x = five_spline_x_tilt.Get_Spline_x(current_time);
      double delta_z = five_spline_z_tilt.Get_Spline_x(current_time);

      accumulated_delta_x = delta_x;  
      accumulated_delta_z = delta_z;

      // 调整x位置
      ref.FL_foot[period_count].x() += delta_x;
      ref.FR_foot[period_count].x() += delta_x;

      // 调整z位置
      ref.FL_foot[period_count].z() -= delta_z;
      ref.FR_foot[period_count].z() -= delta_z;
  }

  // 在倾斜结束后保持前腿的位移
  for (int period_count = c_tilt_end + 1; period_count < timer.c_e; period_count++) {
      // 调整x位置
      ref.FL_foot[period_count].x() += accumulated_delta_x;
      ref.FR_foot[period_count].x() += accumulated_delta_x;

      // 调整z位置
      ref.FL_foot[period_count].z() -= accumulated_delta_z;
      ref.FR_foot[period_count].z() -= accumulated_delta_z;
  }

  // 保存倾斜结束后的前腿位置
  FL_foot_tilted_position.x() = accumulated_delta_x;
  FL_foot_tilted_position.z() = accumulated_delta_z;
  FR_foot_tilted_position.x() = accumulated_delta_x;
  FR_foot_tilted_position.z() = accumulated_delta_z;
}

}  // namespace MELEW3_control

int main(int argc, char* argv[]){
  ros::init(argc, argv, "jumping");
  MELEW3_control::BaseController* controller = new MELEW3_control::jumping;
  ros::waitForShutdown();
  return 0;
}