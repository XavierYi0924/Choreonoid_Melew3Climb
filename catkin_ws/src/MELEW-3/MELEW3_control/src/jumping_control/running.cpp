/**
 * @file    running.cpp
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

class running : public BaseController {
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
  Utils::Five_Spline five_spline_zmp;
  Utils::Five_Spline five_spline_x;

  /*** 経由点情報 ***/
  Utils::Five_Spline::point x1;
  Utils::Five_Spline::point x2;
  Utils::Five_Spline::point zmp1;
  Utils::Five_Spline::point zmp2;

  const double settingTime = 2.0;                             // 動作開始姿勢への遷移時間[s]
  const double x_init = 0.0;                                  // x軸初期位置[m]
  const double y_init = 0.0;  
  const double z_init = 0.2 * sqrt(2) + 0.136 / 2;                                // y軸初期位置[m]
  const double psi_init = 0.0;                                // psi初期位置[rad]

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]

public:
  void ZMPTG(); // ZMP Trajectory Generayor
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
  Eigen::Vector3d init_COM_pos{x_init, y_init, z_init};
  double init_COM_yaw = psi_init;

  running(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
running::running(void) {
  start_controller();
}

/**
 * @brief
 *
 */
void running::control_loop(void) {
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

      // com_sub_ = nh.subscribe("MELEW3/com", 1, &running::COMCallback, this);

      ref.z_s = 0.35; // 0.35
      
      // Time Relationship
      timer.t_s = 0.0;  // start time
      timer.t_rs = timer.t_s + 3.0; // running start time
      timer.t_re = timer.t_rs + 3.0; // running end time
      timer.t_e = timer.t_re + 2.0; // end time
    
      // count
      timer.current_time = 0.0;
      timer.current_count = 0;
      
      timer.c_ini = 0;
      timer.c_s = timer.t_s / timer.dt; // 800
      timer.c_rs = timer.t_rs / timer.dt; // 1000
      timer.c_re = timer.t_re / timer.dt; //1408
      timer.c_e = timer.t_e / timer.dt; //1608 

      int mem = 2*timer.c_e;
    
      // Environmental 
      param.obs_h = 0.1;
      param.s_dist = 3.0;
      param.stature = 0.25;
    
      // Reference Speed
      ref.dx_f = 2.7;

      // X Reference Point
      ref.x_s = 0.0;
      ref.x_e = 5.0;
    
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

    
      ROS_ERROR("Reference Point set");
    
      ZMPTG();
      ROS_ERROR("ZMP set");

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
      ROS_INFO("Enter key to start running");
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

    COM_pos_ref = Eigen::Vector3d(ref.CoM[timer.current_count].x(), 0.0, ref.z_s);
    COM_vel_ref = Eigen::Vector3d(ref.dCoM[timer.current_count].x(), 0.0, 0.0);
    COM_acl_ref = Eigen::Vector3d(ref.ddCoM[timer.current_count].x(), 0.0, 0.0);
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

    COM_pos_ref = Eigen::Vector3d(ref.CoM[timer.l_e].x(), 0.0, ref.z_s);
    COM_vel_ref = Eigen::Vector3d(ref.dCoM[timer.l_e].x(), 0.0, 0.0);
    COM_acl_ref = Eigen::Vector3d(ref.ddCoM[timer.l_e].x(), 0.0, 0.0);
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
    ROS_INFO("running complete!");
    stop_controller();
  }
}

void running::ZMPTG(){
  //** ZMPTG Start **//////////////////////////////////////////////////////////////////////////////
  zmp_ref_tra = Eigen::VectorXd::Zero(2*timer.c_e);

  // 1点目の時刻，位置，速度，加速度を指定
  zmp1 = {timer.t_rs, 
          0.0, 
          0.0, 
          0.0 };

  // 2点目の時刻，位置，速度，加速度を指定
  zmp2 = {timer.t_re,   
          ref.x_e, 
          0.0, 
          0.0 };  
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_zmp_1 = {zmp1, zmp2};

  // 5次多項式補間の係数を計算
  five_spline_zmp.Calc_Spline(points_zmp_1);

  for(int period_count = 0; period_count < timer.c_e; period_count++){
    if(period_count < timer.c_rs){
      zmp_ref_tra(period_count) = 0.0;
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

void running::FTG(){
  //** FTG Start **//////////////////////////////////////////////////////////////////////////////

  for(int period_count = timer.c_ini; period_count < timer.c_e; period_count++){
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
  //** FTG End **//////////////////////////////////////////////////////////////////////////////
}

void running::XTG(){
//** XTG Start **//////////////////////////////////////////////////////////////////////////////
  // 1点目の時刻，位置，速度，加速度を指定
  x1 = {timer.t_rs, 
          0.0, 
          0.0, 
          0.0 };

  // 2点目の時刻，位置，速度，加速度を指定
  x2 = {timer.t_re,   
          ref.x_e, 
          0.0, 
          0.0 }; 
  
  // 経由点の情報をまとめたベクトルを定義
  std::vector<Utils::Five_Spline::point> points_x_1 = {x1, x2};

  // 5次多項式補間の係数を計算
  five_spline_x.Calc_Spline(points_x_1);

  for(int period_count = 0; period_count < timer.c_e; period_count++){
    if(period_count < timer.c_rs){
      ref.CoM[period_count].x() = x1.x;
      ref.dCoM[period_count].x() = x1.dx;
      ref.ddCoM[period_count].x() = x1.ddx;
    }
    else if(period_count < timer.c_re){
      ref.CoM[period_count].x() = five_spline_x.Get_Spline_x(period_count*timer.dt);
      ref.dCoM[period_count].x() = five_spline_x.Get_Spline_dx(period_count*timer.dt);
      ref.ddCoM[period_count].x() =  five_spline_x.Get_Spline_ddx(period_count*timer.dt);
    }
    else{
      ref.CoM[period_count].x() = x2.x;
      ref.dCoM[period_count].x() = x2.dx;
      ref.ddCoM[period_count].x() = x2.ddx;
    }
  }
}
}  // namespace MELEW3_control

int main(int argc, char* argv[]){
  ros::init(argc, argv, "running");
  MELEW3_control::BaseController* controller = new MELEW3_control::running;
  ros::waitForShutdown();
  return 0;
}