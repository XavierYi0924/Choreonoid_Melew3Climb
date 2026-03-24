/**
 * @file    trans.cpp
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

using namespace std;

namespace MELEW3_control {

class wheel_running : public BaseController {
private:
  double start_time = 1.0;
  double end_time = 14.0;
  double bug_start = 5.0;
  double bug_end = 5.3;
  double adj_end = 6.5;
  double turn_end = 6.5;
  const double settingTime = 3.0;     // 動作開始姿勢への遷移時間[s]
  const double movingTime = 14.1;     // 動作時間[s]
  const double turning_rate = M_PI / 3.0; 
  const double z_frequency = 2.0;                            // 周波数[Hz]
  const double z_amplitude = 0.005;                            // 振幅[m]

  std::vector<double>  leg_yaw_ref_temp = init_leg_yaw;
  double COM_yaw_ref_temp = init_COM_yaw;

  int c_init = 0;
  int c_s = start_time * controller_frequency;
  int c_e = end_time * controller_frequency;
  int c_bs = bug_start * controller_frequency;
  int c_be = bug_end * controller_frequency;
  int c_ad = adj_end * controller_frequency;
  int c_t = turn_end * controller_frequency;
  int c_mt = movingTime * controller_frequency;
  int OFFFL = 0;
  int OFFFR = 0;
  int OFFBL = 0;
  int OFFBR = 0;
  
  const double x_init = 0.0;          // x軸ベースリンク初期位置[m]
  const double y_init = 0.0;          // y軸ベースリンク初期位置[m]
  const double z_init = 0.4;         // z軸ベースリンク初期位置[m]
  const double psi_init = 0.0;        // psi初期位置[rad]

  double loop_time;  // phase内の時間[s]
  double tmp_time;   // 時間のオフセット記録[s]
  double pos_temp = 0;
  double step_time;

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
  Utils::Five_Spline::point a1;
  Utils::Five_Spline::point a2;
  Utils::Five_Spline::point a3;
  Utils::Five_Spline::point b1;
  Utils::Five_Spline::point b2;
  Utils::Five_Spline::point y1;
  Utils::Five_Spline::point y2;
  Utils::Five_Spline five_spline_x1;
  Utils::Five_Spline five_spline_z1;
  Utils::Five_Spline five_spline_a1;
  Utils::Five_Spline five_spline_a2;
  Utils::Five_Spline five_spline_b1;
  Utils::Five_Spline five_spline_y1;
  Eigen::VectorXd x_trajectory;
  Eigen::VectorXd z_trajectory;
  Eigen::VectorXd a_trajectory;
  Eigen::VectorXd b_trajectory;
  Eigen::VectorXd y_trajectory;
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
  void ATrajectoryGenerator();
  void BugTrajectoryGenerator();
  void YTrajectoryGenerator();
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

      a_trajectory.resize(c_mt*2);
      ATrajectoryGenerator();

      b_trajectory.resize(c_mt*2);
      BugTrajectoryGenerator();

      y_trajectory.resize(c_mt*2);
      YTrajectoryGenerator();

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
    step_time = loop_time - bug_start;
    /*
        ここで以下を決定する
        ・足先位置            ：leg_pos_ref
        ・足先YAW角度         ：leg_yaw_ref
        ・ベースリンク位置    ：COM_pos_ref
        ・ベースリンクYAW角度 ：COM_yaw_ref
        （World座標系）
    */

    //moving version

    if(loop_time < movingTime){
      if(OFFFL){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_), 
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
            };
        }
        else if(loop_time < adj_end){
          if(step_time < 1 / (2 * z_frequency)){
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_+0.04), 
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time)))
            };
          }
          else{
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_+0.04), 
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time)))
            };
          }
        }
        else{
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_+0.04), 
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
          };
        }
        leg_yaw_ref = {0.0,a_trajectory(loop_time*controller_frequency),0.0,0.0};
      }
      else if(OFFFR){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_), 
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
            };
        }
        else if(loop_time < adj_end){
          if(step_time < 1 / (2 * z_frequency)){
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_+0.04), 
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
            };
          }
          else{
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_+0.04), 
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI)))
            };
          }
        }
        else{
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_+0.04), 
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
          };
        }
        leg_yaw_ref = {-a_trajectory(loop_time*controller_frequency),0.0,0.0,0.0};
      }
      else if(OFFBL){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_), 
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency))
            };
        }
        else if(loop_time < adj_end){
          if(step_time < 1 / (2 * z_frequency)){
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_+0.04), 
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency))
            };
          }
          else{
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_+0.04), 
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI)))
            };
          }
        }
        else{
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_, BL_leg_offset_z_+0.04), 
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency))
            };
        }
        leg_yaw_ref = {0.0,0.0,0.0,a_trajectory(loop_time*controller_frequency)};
      }
      else if(OFFBR){
        if(loop_time < bug_start){
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_)
            };
        }
        else if(loop_time < adj_end){
          if(step_time < 1 / (2 * z_frequency)){
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_+0.04)
            };
          }
          else{
            leg_pos_ref = {
              Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
              Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
              Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
              Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_+0.04)
            };
          }
        }
        else{
          leg_pos_ref = {
            Eigen::Vector3d(FL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(FR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BL_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
            Eigen::Vector3d(BR_leg_offset_x_ + x_trajectory(loop_time*controller_frequency), BR_leg_offset_y_, BR_leg_offset_z_+0.04)
            };
        }
        leg_yaw_ref = {0.0,0.0,-a_trajectory(loop_time*controller_frequency),0.0};
      }

      COM_pos_ref = Eigen::Vector3d(x_init + x_trajectory(loop_time*controller_frequency), y_init, z_init);
    //stand version

    // if(loop_time < movingTime){
    //   if(OFFFL){
    //     if(loop_time < bug_start){
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_), 
    //         Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
    //         };
    //     }
    //     else if(loop_time < adj_end){
    //       if(step_time < 1 / (2 * z_frequency)){
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_+0.04), 
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time)))
    //         };
    //       }
    //       else{
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_+0.04), 
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time)))
    //         };
    //       }
    //     }
    //     else{
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_+0.04), 
    //         Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
    //       };
    //     }
    //     leg_yaw_ref = {0.0,a_trajectory(loop_time*controller_frequency),0.0,0.0};
    //   }
    //   else if(OFFFR){
    //     if(loop_time < bug_start){
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_), 
    //         Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
    //         };
    //     }
    //     else if(loop_time < adj_end){
    //       if(step_time < 1 / (2 * z_frequency)){
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_+0.04), 
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
    //         };
    //       }
    //       else{
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_+0.04), 
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI)))
    //         };
    //       }
    //     }
    //     else{
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_+0.04), 
    //         Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency))
    //       };
    //     }
    //     leg_yaw_ref = {-a_trajectory(loop_time*controller_frequency),0.0,0.0,0.0};
    //   }
    //   else if(OFFBL){
    //     if(loop_time < bug_start){
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_), 
    //         Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency))
    //         };
    //     }
    //     else if(loop_time < adj_end){
    //       if(step_time < 1 / (2 * z_frequency)){
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_+0.04), 
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency))
    //         };
    //       }
    //       else{
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_+0.04), 
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI)))
    //         };
    //       }
    //     }
    //     else{
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_, BL_leg_offset_z_+0.04), 
    //         Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_+ y_trajectory(loop_time*controller_frequency), BR_leg_offset_z_- z_trajectory(loop_time*controller_frequency))
    //         };
    //     }
    //     leg_yaw_ref = {0.0,0.0,0.0,a_trajectory(loop_time*controller_frequency)};
    //   }
    //   else if(OFFBR){
    //     if(loop_time < bug_start){
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_)
    //         };
    //     }
    //     else if(loop_time < adj_end){
    //       if(step_time < 1 / (2 * z_frequency)){
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_+0.04)
    //         };
    //       }
    //       else{
    //         leg_pos_ref = {
    //           Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
    //           Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time))),
    //           Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+ z_amplitude * (1 - cos(2 * M_PI * z_frequency * step_time - M_PI))),
    //           Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_+0.04)
    //         };
    //       }
    //     }
    //     else{
    //       leg_pos_ref = {
    //         Eigen::Vector3d(FL_leg_offset_x_ , FL_leg_offset_y_, FL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(FR_leg_offset_x_ , FR_leg_offset_y_, FR_leg_offset_z_- z_trajectory(loop_time*controller_frequency)+b_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BL_leg_offset_x_ , BL_leg_offset_y_- y_trajectory(loop_time*controller_frequency), BL_leg_offset_z_- z_trajectory(loop_time*controller_frequency)),
    //         Eigen::Vector3d(BR_leg_offset_x_ , BR_leg_offset_y_, BR_leg_offset_z_+0.04)
    //         };
    //     }
    //     leg_yaw_ref = {0.0,0.0,-a_trajectory(loop_time*controller_frequency),0.0};
    //   }
    //   COM_pos_ref = Eigen::Vector3d(x_init , y_init, z_init);

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
          Eigen::Vector3d(FL_leg_offset_x_ + x2.x, FL_leg_offset_y_, FL_leg_offset_z_),
          Eigen::Vector3d(FR_leg_offset_x_ + x2.x, FR_leg_offset_y_+y2.x, FR_leg_offset_z_- z2.x),
          Eigen::Vector3d(BL_leg_offset_x_ + x2.x, BL_leg_offset_y_, BL_leg_offset_z_+ 0.02),
          Eigen::Vector3d(BR_leg_offset_x_ + x2.x, BR_leg_offset_y_, BR_leg_offset_z_+ 0.02)
          };
      }
      else if(OFFFR){
        leg_pos_ref = {
          Eigen::Vector3d(FL_leg_offset_x_ + x2.x, FL_leg_offset_y_-y2.x, FL_leg_offset_z_- z2.x),
          Eigen::Vector3d(FR_leg_offset_x_ + x2.x, FR_leg_offset_y_, FR_leg_offset_z_),
          Eigen::Vector3d(BL_leg_offset_x_ + x2.x, BL_leg_offset_y_, BL_leg_offset_z_+ 0.02),
          Eigen::Vector3d(BR_leg_offset_x_ + x2.x, BR_leg_offset_y_, BR_leg_offset_z_+ 0.02)
          };
      }
      else if(OFFBL){
        leg_pos_ref = {
          Eigen::Vector3d(FL_leg_offset_x_ + x2.x, FL_leg_offset_y_, FL_leg_offset_z_+ 0.02),
          Eigen::Vector3d(FR_leg_offset_x_ + x2.x, FR_leg_offset_y_, FR_leg_offset_z_+ 0.02),
          Eigen::Vector3d(BL_leg_offset_x_ + x2.x, BL_leg_offset_y_, BL_leg_offset_z_),
          Eigen::Vector3d(BR_leg_offset_x_ + x2.x, BR_leg_offset_y_+y2.x, BR_leg_offset_z_- z2.x)
          };
      }
      else if(OFFBR){
        leg_pos_ref = {
          Eigen::Vector3d(FL_leg_offset_x_ + x2.x, FL_leg_offset_y_, FL_leg_offset_z_+ 0.02),
          Eigen::Vector3d(FR_leg_offset_x_ + x2.x, FR_leg_offset_y_, FR_leg_offset_z_+ 0.02),
          Eigen::Vector3d(BL_leg_offset_x_ + x2.x, BL_leg_offset_y_-y2.x, BL_leg_offset_z_- z2.x),
          Eigen::Vector3d(BR_leg_offset_x_ + x2.x, BR_leg_offset_y_, BR_leg_offset_z_)
          };
      }
      leg_yaw_ref = init_leg_yaw;
      COM_pos_ref = Eigen::Vector3d(x2.x, y_init, z_init);
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
  
      FL_leg_pos_ref_pub_.publish(pub_FL_leg_pos_ref);
      BL_leg_pos_ref_pub_.publish(pub_BL_leg_pos_ref);
      FR_leg_pos_ref_pub_.publish(pub_FR_leg_pos_ref);
      BR_leg_pos_ref_pub_.publish(pub_BR_leg_pos_ref);
      COM_pos_ref_pub_.publish(pub_COM_pos_ref);
    }
    if (current_time >= tmp_time + movingTime) {
      phase = 3; 
      initialize_flag = false; 
    }
  }

  // Finalize
  else if (phase == 3) {
    ROS_INFO("Moving x sine wave complete!");
    stop_controller();
  }
}

void wheel_running::XTrajectoryGenerator(){
    x1 = {
        start_time,
        0.0,
        0.0,
        0.0
    };
    x2 = {
        end_time,
        5.0,
        0.0,
        0.0,
    };
    std::vector<Utils::Five_Spline::point> points_x1 = {x1, x2};
    five_spline_x1.Calc_Spline(points_x1);
    for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_s){
        x_trajectory(period_count) = 0.0;
    }
    else if(period_count < c_e){
      x_trajectory(period_count) = five_spline_x1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
       x_trajectory(period_count) = x2.x;
    }
}
}
void wheel_running::ZTrajectoryGenerator(){
    z1 = {
        bug_start,
        0.0,
        0.0,
        0.0
    };
    z2 = {
        bug_end,
        0.03,
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
void wheel_running::ATrajectoryGenerator(){
    a1 = {
        bug_start,
        0.0,
        0.0,
        0.0
    };
    a2 = {
        bug_end,
        15.0 * (M_PI / 180.0),
        0.0,
        0.0,
    };
    a3 = {
        turn_end,
        -0.0 * (M_PI / 180.0),
        0.0,
        0.0
    };
    std::vector<Utils::Five_Spline::point> points_a1 = {a1, a2};
    std::vector<Utils::Five_Spline::point> points_a2 = {a2, a3};
    five_spline_a1.Calc_Spline(points_a1);
    five_spline_a2.Calc_Spline(points_a2);
    for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_bs){
      a_trajectory(period_count) = a1.x;
    }
    else if(period_count < c_be){
      a_trajectory(period_count) = five_spline_a1.Get_Spline_x(period_count/controller_frequency);
    }
    else if(period_count < c_t){
      a_trajectory(period_count) = five_spline_a2.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      a_trajectory(period_count) = a3.x;
    }

}
}
void wheel_running::BugTrajectoryGenerator(){
    b1 = {
        bug_end,
        0.0,
        0.0,
        0.0
    };
    b2 = {
        adj_end,
        0.07,
        0.0,
        0.0,
    };
    std::vector<Utils::Five_Spline::point> points_b1 = {b1, b2};
    five_spline_b1.Calc_Spline(points_b1);
    for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_be){
      b_trajectory(period_count) = b1.x;
    }
    else if(period_count < c_ad){
      b_trajectory(period_count) = five_spline_b1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      b_trajectory(period_count) = b2.x;
    }
}
}
void wheel_running::YTrajectoryGenerator(){
    y1 = {
        bug_end,
        0.0,
        0.0,
        0.0
    };
    y2 = {
        adj_end,
        0.12,
        0.0,
        0.0,
    };
    std::vector<Utils::Five_Spline::point> points_y1 = {y1, y2};
    five_spline_y1.Calc_Spline(points_y1);
    for(int period_count = 0; period_count < c_mt; period_count++){
    if(period_count < c_be){
      y_trajectory(period_count) = y1.x;
    }
    else if(period_count < c_ad){
      y_trajectory(period_count) = five_spline_y1.Get_Spline_x(period_count/controller_frequency);
    }
    else{
      y_trajectory(period_count) = y2.x;
    }
}
}
void wheel_running::RandomOffline(){
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  int index = std::rand() % 4;
  switch (index) {
        case 0:
            OFFFL = 1; 
            printf("FL is offline.\n.");
            break;
        case 1:
            OFFFR = 1; 
            printf("FR is offline.\n");
            break;
        case 2:
            OFFBL = 1; 
            printf("BL is offline.\n");
            break;
        case 3:
            OFFBR = 1; 
            printf("BR is offline.\n");
            break;
    }
}

}  // namespace MELEW3_control


int main(int argc, char** argv) {
  ros::init(argc, argv, "wheel_running");
  // ROS_WARN("wheel running");
  MELEW3_control::BaseController* controller = new MELEW3_control::wheel_running;
  ros::waitForShutdown();
  return 0;
}