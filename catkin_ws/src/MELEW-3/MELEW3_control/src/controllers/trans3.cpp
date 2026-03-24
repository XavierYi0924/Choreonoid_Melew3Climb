/**
 * @file    trans3.cpp
 * @author  
 * @brief   Using from 4 legs to 3 legs while running
 * @version 1.1
 * @date    
 *
 * @copyright 
 *
 */
#include <MELEW3_control/BaseController.h>

#include <MELEW3_control/utils.hpp>

// #include <sensor_msgs/Imu.h>

using namespace std;

namespace MELEW3_control {

class wheel_running : public BaseController {
private:
  double start_time = 1.0;
  double bug_start = 4.0;
  double bug_end = 4.5;
  double adj_end = 5.0;
  double adj2_end = 6.0;
  const double settingTime = 2.0;     // 動作開始姿勢への遷移時間[s]
  const double movingTime = 8.0;     // 動作時間[s]
  const double turning_rate = M_PI / 3.0; 
  
  std::vector<double>  leg_yaw_ref_temp = init_leg_yaw;
  double COM_yaw_ref_temp = init_COM_yaw;

  int c_init = 0;
  int c_s = start_time * controller_frequency;
  int c_bs = bug_start * controller_frequency;
  int c_be = bug_end * controller_frequency;
  int c_ad = adj_end * controller_frequency;
  int c_ad2 = adj2_end * controller_frequency;
  int c_mt = movingTime * controller_frequency;
  int OFFFL = 0;
  int OFFFR = 0;
  int OFFBL = 0;
  int OFFBR = 0;
  int OFF = 0;

  const double bug_h = 0.046;

  const double x_init = 0.0;          // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;          // y軸ベースリンク初期位置[m]
  const double z_init = 0.43;         // z軸ベースリンク初期位置[m]
  const double psi_init = 0.0;        // psi初期位置[rad]

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]
  double pos_temp = 0;

  // ros::Subscriber imu_sub_;
  // sensor_msgs::Imu::ConstPtr imu_data_;

public:
  ros::Publisher FL_leg_pos_ref_pub_;  //!< 左前脚の目標脚先位置用パブリッシャー
  ros::Publisher FR_leg_pos_ref_pub_;  //!< 右前脚の目標脚先位置用パブリッシャー
  ros::Publisher BL_leg_pos_ref_pub_;  //!< 左後脚の目標脚先位置用パブリッシャー
  ros::Publisher BR_leg_pos_ref_pub_;  //!< 右後脚の目標(loop_time*controller_frequency)用パブリッシャー
  ros::Publisher COM_pos_ref_pub_;     //!< 目標重心位置用パブリッシャー
  ros::Publisher COM_vel_ref_pub_;     //!< 目標重心速度用パブリッシャー
  ros::Publisher COM_acl_ref_pub_;     //!< 目標重心加速度用パブリッシャー

  Utils::Utils util;
  Utils::Five_Spline::point x1;
  Utils::Five_Spline::point x2;
  Utils::Five_Spline::point z1;
  Utils::Five_Spline::point z2;
  Utils::Five_Spline::point r1;
  Utils::Five_Spline::point r2;
  Utils::Five_Spline::point b1;
  Utils::Five_Spline::point b2;
  Utils::Five_Spline five_spline_x1;
  Utils::Five_Spline five_spline_z1;
  Utils::Five_Spline five_spline_r1;
  Utils::Five_Spline five_spline_b1;
  Eigen::VectorXd x_trajectory;
  Eigen::VectorXd z_trajectory;
  Eigen::VectorXd r_trajectory;
  Eigen::VectorXd b_trajectory;
  Eigen::Vector3d gene_zmp{0.0, 0.0, 0.0};     //!< ５次補完ZMP位置を一時保存する変数
  Eigen::Vector3d ZMP_pos_ref{0.0, 0.0, 0.0};  //!< 目標ZMP位置を一時保存する変数
  Eigen::Vector3d COM_vel_ref{0.0, 0.0, 0.0};  //!< 目標重心速度を一時保存する変数
  Eigen::Vector3d COM_acl_ref{0.0, 0.0, 0.0};  //!< 目標重心加速度を一時保存する変数
  std::vector<Eigen::Vector3d> init_leg_pos{            // 初期足部位置
                                            Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_),
                                            Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_),
                                            Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_),
                                            Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_)};
  std::vector<double>          init_leg_yaw = {0.0, 0.0, 0.0, 0.0};  // 初期足部YAW角度
  std::vector<Eigen::VectorXf> init_torque{Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4), Eigen::VectorXf::Zero(4),
                                           Eigen::VectorXf::Zero(4)};
  Eigen::Vector3d              init_COM_pos{x_init, y_init, z_init};  // 初期ベースリンク位置
  double                       init_COM_yaw = 0.0;                    // 初期ベースリンクYAW角度

  void XTrajectoryGenerator();   // X direction Trajectory Generayor  
  void ZTrajectoryGenerator();
  // void ATrajectoryGenerator();
  void RTrajectoryGenerator();
  void BTrajectoryGenerator();
  void RandomOffline();

  wheel_running(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *.hpp>
 */
wheel_running::wheel_running(void) {
  // ROS_WARN("start ready");
  start_controller();
  // ROS_WARN("start");
}

/**
 * @brief
 *
 */
void wheel_running::control_loop(void) {
  double current_time = get_time();
  if (phase == 0) {
    if (pose_transition()) {
      // ROS_WARN("potra haitta");
      /*** パブリッシャ，サブスクライバの初期化 ***/
      FL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FL_leg_pos_ref", 1);
      FR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/FR_leg_pos_ref", 1);
      BL_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BL_leg_pos_ref", 1);
      BR_leg_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/BR_leg_pos_ref", 1);
      COM_pos_ref_pub_ = nh.advertise<melew3_msgs::leg_pose>("/COM_pos_ref", 1);

      x_trajectory.resize(c_mt*2);
      XTrajectoryGenerator();

      z_trajectory.resize(c_mt*2);
      ZTrajectoryGenerator();

      // a_trajectory.resize(c_mt*2);
      // ATrajectoryGenerator();

      r_trajectory.resize(c_mt*2);
      RTrajectoryGenerator();

      b_trajectory.resize(c_mt*2);
      BTrajectoryGenerator();

      RandomOffline();

      ROS_INFO("phase0 end");
      initialize_flag = false;
      phase = 1;
    }
    // ROS_WARN("Through");
  }

  if (phase == 1) {
    // ROS_WARN("phase1 in");
    if (pose_transition(init_leg_pos, init_leg_yaw, init_COM_pos, init_COM_yaw, settingTime)) {
      ROS_INFO("phase1 end");
      ROS_INFO("Enter key to start moving wheel running");
      char buf;
      std::cin >> buf;
      phase = 2;
      initialize_flag = false;
    }
  }

  else if (phase == 2) {
    if (!initialize_flag) {
      tmp_time = get_time();
      XTrajectoryGenerator();
      initialize_flag = true;
    }
    current_time = get_time();
    loop_time = current_time - tmp_time;
    /*
        ここで以下を決定する
        ・足先位置            ：leg_pos_ref
        ・足先YAW角度         ：leg_yaw_ref
        ・ベースリンク位置    ：COM_pos_ref
        ・ベースリンクYAW角度 ：COM_yaw_ref
        （World座標系）
    */

    if(loop_time < movingTime){
      if(OFFFL){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time) , FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(FR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(BL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(BR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_)
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time), y_init, z_init);
        }
        else{
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time) + b_trajectory(controller_frequency * loop_time), FL_leg_offset_y_, FL_leg_offset_z_ + bug_h),
            Eigen::Vector3d(FR_leg_offset_x_  + x_trajectory(controller_frequency * loop_time) + r_trajectory(controller_frequency * loop_time) + b_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_ + 0.1 * z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(BL_leg_offset_x_  + x_trajectory(controller_frequency * loop_time) + r_trajectory(controller_frequency * loop_time) + b_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_ - z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(BR_leg_offset_x_  - x_trajectory(controller_frequency * loop_time) + r_trajectory(controller_frequency * loop_time) + b_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_ - 1.1 * z_trajectory(controller_frequency * loop_time))
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time) + b_trajectory(controller_frequency * loop_time), y_init, z_init);
          // leg_yaw_ref = {0.0,-a_trajectory(controller_frequency * loop_time),-a_trajectory(controller_frequency * loop_time),-a_trajectory(controller_frequency * loop_time)};
          // COM_yaw_ref = -a_trajectory(controller_frequency * loop_time);
        }
      }
      else if(OFFFR){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(FR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(BL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(BR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_)
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time), y_init, z_init);
        }
        else{
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_  + x_trajectory(controller_frequency * loop_time) + r_trajectory(controller_frequency * loop_time)+ b_trajectory(controller_frequency * loop_time), FL_leg_offset_y_, FL_leg_offset_z_ + 0.1 * z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(FR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time)+ b_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_ + bug_h),
            Eigen::Vector3d(BL_leg_offset_x_  - x_trajectory(controller_frequency * loop_time) + r_trajectory(controller_frequency * loop_time)+ b_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_ - 1.1 * z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(BR_leg_offset_x_  + x_trajectory(controller_frequency * loop_time) + r_trajectory(controller_frequency * loop_time)+ b_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_ - z_trajectory(controller_frequency * loop_time))
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time)+ b_trajectory(controller_frequency * loop_time), y_init, z_init);
          // leg_yaw_ref = {a_trajectory(controller_frequency * loop_time),0.0,a_trajectory(controller_frequency * loop_time),a_trajectory(controller_frequency * loop_time)};
          // COM_yaw_ref = a_trajectory(controller_frequency * loop_time);
        }
      }
      else if(OFFBL){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(FR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(BL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(BR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_)
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time), y_init, z_init);
        }
        else{
          leg_pos_ref ={
            Eigen::Vector3d(FL_leg_offset_x_  - x_trajectory(controller_frequency * loop_time)+ r_trajectory(controller_frequency * loop_time) - b_trajectory(controller_frequency * loop_time), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(FR_leg_offset_x_  + x_trajectory(controller_frequency * loop_time)+  r_trajectory(controller_frequency * loop_time) - b_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_- 1.1 * z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(BL_leg_offset_x_ +  r_trajectory(controller_frequency * loop_time) - b_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_ + bug_h),
            Eigen::Vector3d(BR_leg_offset_x_  - x_trajectory(controller_frequency * loop_time)+  r_trajectory(controller_frequency * loop_time) - b_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_ + 0.1 * z_trajectory(controller_frequency * loop_time))
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time) - b_trajectory(controller_frequency * loop_time), y_init, z_init);
        }
      }
      else if(OFFBR){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), FL_leg_offset_y_, FL_leg_offset_z_),
            Eigen::Vector3d(FR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_),
            Eigen::Vector3d(BL_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_),
            Eigen::Vector3d(BR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_)
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time), y_init, z_init);
        }
        else{
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(controller_frequency * loop_time)+ r_trajectory(controller_frequency * loop_time) - b_trajectory(controller_frequency * loop_time), FL_leg_offset_y_, FL_leg_offset_z_- 1.1 * z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(FR_leg_offset_x_ - x_trajectory(controller_frequency * loop_time)+ r_trajectory(controller_frequency * loop_time)- b_trajectory(controller_frequency * loop_time), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(BL_leg_offset_x_ - x_trajectory(controller_frequency * loop_time)+ r_trajectory(controller_frequency * loop_time)- b_trajectory(controller_frequency * loop_time), BL_leg_offset_y_, BL_leg_offset_z_ + 0.1 * z_trajectory(controller_frequency * loop_time)),
            Eigen::Vector3d(BR_leg_offset_x_ + r_trajectory(controller_frequency * loop_time)- b_trajectory(controller_frequency * loop_time), BR_leg_offset_y_, BR_leg_offset_z_ + bug_h)
            };
            COM_pos_ref = Eigen::Vector3d(x_init+ r_trajectory(controller_frequency * loop_time)- b_trajectory(controller_frequency * loop_time), y_init, z_init);
        }
      }
      leg_yaw_ref = {0.0,0.0,0.0,0.0};
      COM_yaw_ref = init_COM_yaw;
      leg_motor_torque = init_torque;
      /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
      melew3_msgs::leg_pose pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
          pub_COM_pos_ref;
      if (loop_time < bug_start){

        // fl_leg_disabled_ = false;

        util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);
        util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
    
        FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
        BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
        FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
        BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
        COM_pos_ref_pub_.publish(pub_COM_pos_ref);
      }
      else{
        
        // fl_leg_disabled_ = true;

        util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
        util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);
        util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
    
        FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
        BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
        FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
        BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
        COM_pos_ref_pub_.publish(pub_COM_pos_ref);
      }
    }
    else {
      if(OFFFL){
        leg_pos_ref = {
          Eigen::Vector3d(FL_leg_offset_x_+r2.x+b2.x, FL_leg_offset_y_, FL_leg_offset_z_ + bug_h),
          Eigen::Vector3d(FR_leg_offset_x_+x2.x+r2.x+b2.x, FR_leg_offset_y_, FR_leg_offset_z_),
          Eigen::Vector3d(BL_leg_offset_x_+x2.x+r2.x+b2.x, BL_leg_offset_y_, BL_leg_offset_z_ - z2.x),
          Eigen::Vector3d(BR_leg_offset_x_-x2.x+r2.x+b2.x, BR_leg_offset_y_, BR_leg_offset_z_ - 1.1 * z2.x)
          };
        COM_pos_ref = Eigen::Vector3d(x_init+r2.x+b2.x, y_init, z_init);
      }
      else if(OFFFR){
        leg_pos_ref = {
          Eigen::Vector3d(FL_leg_offset_x_+x2.x+r2.x+b2.x, FL_leg_offset_y_, FL_leg_offset_z_),
          Eigen::Vector3d(FR_leg_offset_x_+r2.x+b2.x, FR_leg_offset_y_, FR_leg_offset_z_ + bug_h),
          Eigen::Vector3d(BL_leg_offset_x_-x2.x+r2.x+b2.x, BL_leg_offset_y_, BL_leg_offset_z_- 1.1 * z2.x),
          Eigen::Vector3d(BR_leg_offset_x_+x2.x+r2.x+b2.x, BR_leg_offset_y_, BR_leg_offset_z_- z2.x)
          };
        COM_pos_ref = Eigen::Vector3d(x_init+r2.x+b2.x, y_init, z_init);
      }
      else if(OFFBL){
        leg_pos_ref = {
          Eigen::Vector3d(FL_leg_offset_x_-x2.x+r2.x-b2.x, FL_leg_offset_y_, FL_leg_offset_z_- z2.x),
          Eigen::Vector3d(FR_leg_offset_x_+x2.x+r2.x-b2.x, FR_leg_offset_y_, FR_leg_offset_z_- 1.1 * z2.x),
          Eigen::Vector3d(BL_leg_offset_x_+r2.x-b2.x, BL_leg_offset_y_, BL_leg_offset_z_ + bug_h),
          Eigen::Vector3d(BR_leg_offset_x_-x2.x+r2.x-b2.x, BR_leg_offset_y_, BR_leg_offset_z_)
          };
        COM_pos_ref = Eigen::Vector3d(x_init+r2.x-b2.x, y_init, z_init);
      }
      else if(OFFBR){
        leg_pos_ref = {
          Eigen::Vector3d(FL_leg_offset_x_+x2.x+r2.x-b2.x, FL_leg_offset_y_, FL_leg_offset_z_- 1.1 * z2.x),
          Eigen::Vector3d(FR_leg_offset_x_-x2.x+r2.x-b2.x, FR_leg_offset_y_, FR_leg_offset_z_- z2.x),
          Eigen::Vector3d(BL_leg_offset_x_-x2.x+r2.x-b2.x, BL_leg_offset_y_, BL_leg_offset_z_),
          Eigen::Vector3d(BR_leg_offset_x_+r2.x-b2.x, BR_leg_offset_y_, BR_leg_offset_z_ + bug_h)
          };
        COM_pos_ref = Eigen::Vector3d(x_init+r2.x-b2.x, y_init, z_init);
      }
      leg_yaw_ref = init_leg_yaw;
      COM_yaw_ref = init_COM_yaw;
      leg_motor_torque = init_torque;

      /*** 4脚車輪ロボットの軌道をパブリッシュ ***/
      melew3_msgs::leg_pose pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
          pub_COM_pos_ref;

      util.Vector3dToLegpose(leg_pos_ref[FL], leg_yaw_ref[FL], pub_FL_leg_pos_ref);
      util.Vector3dToLegpose(leg_pos_ref[FR], leg_yaw_ref[FR], pub_FR_leg_pos_ref);
      util.Vector3dToLegpose(leg_pos_ref[BL], leg_yaw_ref[BL], pub_BL_leg_pos_ref);
      util.Vector3dToLegpose(leg_pos_ref[BR], leg_yaw_ref[BR], pub_BR_leg_pos_ref);
      util.Vector3dToLegpose(COM_pos_ref, COM_yaw_ref, pub_COM_pos_ref);
      // leg_yaw_ref = {0.0,a_trajectory(controller_frequency * loop_time),a_trajectory(controller_frequency * loop_time),a_trajectory(controller_frequency * loop_time)};
      // COM_yaw_ref = a_trajectory(controller_frequency * loop_time);
      leg_yaw_ref = {0.0,0.0,0.0,0.0};
      COM_yaw_ref = init_COM_yaw;
      
      if(OFF){
        if(current_time >= tmp_time + adj2_end){
          phase = 3;
          initialize_flag = false;
        }
      }
      else if (current_time >= tmp_time + movingTime) {
      phase = 3; 
      initialize_flag = false; 
    }
  }
  }
  // Finalize
  else if (phase == 3) {
    ROS_INFO("Moving x sine wave complete!");
    stop_controller();
  }
}

//Legs position adjustment
void wheel_running::XTrajectoryGenerator(){
  x1 = {
    bug_start,
    0.0,
    0.0,
    0.0
  };
  x2 = {
    adj_end,
    0.05,
    0.0,
    0.0
  };
  std::vector<Utils::Five_Spline::point> points_x1 = {x1, x2};
  five_spline_x1.Calc_Spline(points_x1);
  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_bs){
        x_trajectory(period_count) = 0.0;
    }
    else if(period_count < c_ad){
      x_trajectory(period_count) = five_spline_x1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
        x_trajectory(period_count) = x2.x;
    }
  }
}

//Height adjustment
void wheel_running::ZTrajectoryGenerator(){
  z1 = {
      bug_start,
      0.0,
      0.0,
      0.0
  };
  z2 = {
      bug_end,
      -0.04,
      0.0,
      0.0,
  };
  std::vector<Utils::Five_Spline::point> points_z1 = {z1, z2};
  five_spline_z1.Calc_Spline(points_z1);
  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_bs){
      z_trajectory(period_count) = z1.x;
    }
    else if(period_count < c_be){
      z_trajectory(period_count) = five_spline_z1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      z_trajectory(period_count) = z2.x;
    }
  }
}

//Forward route
void wheel_running::RTrajectoryGenerator(){
  r1 = {
      start_time,
      0.0,
      0.0,
      0.0
  };
  r2 = {
      movingTime,
      3.5,
      0.0,
      0.0,
  };
  std::vector<Utils::Five_Spline::point> points_r1 = {r1, r2};
  five_spline_r1.Calc_Spline(points_r1);
  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_s){
      r_trajectory(period_count) = r1.x;
    }
    else if(period_count < c_mt){
      r_trajectory(period_count) = five_spline_r1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      r_trajectory(period_count) = r2.x;
    }
  }
}

//Speed adjustment
void wheel_running::BTrajectoryGenerator(){
  b1 = {
      bug_start,
      0.0,
      0.3,
      0.3,
  };
  b2 = {
      movingTime,
      0.5,
      0.0,
      0.0,
  };
  std::vector<Utils::Five_Spline::point> points_b1 = {b1, b2};
  five_spline_b1.Calc_Spline(points_b1);
  for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_bs){
      b_trajectory(period_count) = b1.x;
    }
    else if(period_count < c_mt){
      b_trajectory(period_count) = five_spline_b1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      b_trajectory(period_count) = b2.x;
    }
  }
}

void wheel_running::RandomOffline(){
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  int index = std::rand() % 4;
  switch (index) {
        case 0:
            OFFFL = 1; 
            OFF = 1;
            printf("FL is offline.\n.");
            break;
        case 1:
            OFFFR = 1; 
            OFF = 1;
            printf("FR is offline.\n");
            break;
        case 2:
            OFFBL = 1; 
            OFF = 1;
            printf("BL is offline.\n");
            break;
        case 3:
            OFFBR = 1; 
            OFF = 1;
            printf("BR is offline.\n");
            break;
    }
  //For one leg test
  // OFFFL = 1;
  // OFF = 1;
  // printf("FL is offline.\n");
  // printf("OFF is %d \n",OFF);
}

// Turning control
// void wheel_running::ATrajectoryGenerator(){
//   a1 = {
//       bug_start,
//       0.0,
//       0.0,
//       0.0
//   };
//   a2 = {
//       adj2_end,
//       15.0 * (M_PI / 180.0),
//       0.0,
//       0.0,
//   };
//   std::vector<Utils::Five_Spline::point> points_a1 = {a1, a2};
//   five_spline_a1.Calc_Spline(points_a1);
//   for(int period_count = 0; period_count < c_mt; period_count++){
//     if(period_count < c_bs){
//       a_trajectory(period_count) = a1.x;
//     }
//     else if(period_count < c_ad2){
//       a_trajectory(period_count) = five_spline_a1.Get_Spline_x(period_count/controller_frequency);
//     }
//     else{
//       a_trajectory(period_count) = a2.x;
//     }
//   }
// }

}  // namespace MELEW3_control


int main(int argc, char** argv) {
  ros::init(argc, argv, "wheel_running");
  // ROS_WARN("wheel running");
  MELEW3_control::BaseController* controller = new MELEW3_control::wheel_running;
  ros::waitForShutdown();
  return 0;
}