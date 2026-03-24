#include <MELEW3_control/BaseController.h>

namespace MELEW3_control {

/**
 * @brief Construct a new Base Controller:: Base Controller object
 *
 */
BaseController::BaseController(void) : nh("/MELEW3"), pnh("~"), spinner(1), gain_client("/MELEW3/MELEW3_control") {
  init();
  ros::Duration(2).sleep();  // 遅延を入れないと指令値の最初のほうが欠落する！
  load();
}

/**
 * @brief Destroy the Base Controller:: Base Controller object
 *
 */
BaseController::~BaseController() { spinner.stop(); }

/**
 * @brief Execute initializations of MELEW3
 *
 */
void BaseController::init(void) {
  // sim_flagを確認してtrueの場合はcommandの送り先をchoreonoid_ros基準に設定
  // if (nh.param<bool>("/MELEW3/sim_flag", false)) {
  /*** 運動学クラスの初期化 ***/
  melew3Kinematics.init(0.20, 0.20, 0.20, 0.20);
  pnh.getParam("/sim_flag", sim_flag);
//------------------
  wheel_velocity_ref.resize(LEG_NUM, 0.0);
//--------------------
  if (sim_flag) {
    ROS_WARN("in sim true");

    leg_FL_position_controller_pub_ =
        nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/leg_FL_position_controller/command", 1);
    leg_FR_position_controller_pub_ =
        nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/leg_FR_position_controller/command", 1);
    leg_BL_position_controller_pub_ =
        nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/leg_BL_position_controller/command", 1);
    leg_BR_position_controller_pub_ =
        nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/leg_BR_position_controller/command", 1);
    wheel_controller_pub_ = nh.advertise<std_msgs::Float64MultiArray>("/MELEW3/wheel_controller/command", 1);
    joint_state_sub = nh.subscribe("joint_states", 2, &BaseController::read_state, this);
  } else {
    ROS_WARN("in sim false");

    FL_leg_motion_cmd_pub_ =
        nh.advertise<melew3_msgs::MotionCommand>("/md80_FL/motion_command", 1);
    FR_leg_motion_cmd_pub_ =
        nh.advertise<melew3_msgs::MotionCommand>("/md80_FR/motion_command", 1);
    BL_leg_motion_cmd_pub_ =
        nh.advertise<melew3_msgs::MotionCommand>("/md80_BL/motion_command", 1);
    BR_leg_motion_cmd_pub_ =
        nh.advertise<melew3_msgs::MotionCommand>("/md80_BR/motion_command", 1);
    
    FL_joint_state_sub = nh.subscribe("/md80_FL/joint_states", 2, &BaseController::FL_read_state, this);
    FR_joint_state_sub = nh.subscribe("/md80_FR/joint_states", 2, &BaseController::FR_read_state, this);
    BL_joint_state_sub = nh.subscribe("/md80_BL/joint_states", 2, &BaseController::BL_read_state, this);
    BR_joint_state_sub = nh.subscribe("/md80_BR/joint_states", 2, &BaseController::BR_read_state, this);

    joint_numf = Eigen::VectorXf::Zero(4);
    leg_motor_torque.resize(LEG_NUM, joint_numf);
    leg_motor_vel.resize(LEG_NUM, joint_numf);
    wheel_motor_torque = Eigen::VectorXf::Zero(4);
    wheel_motor_vel = Eigen::VectorXf::Zero(4);
  }
  joint_num = Eigen::VectorXd::Zero(4);
  leg_yaw_cmd.resize(LEG_NUM);
  migration_length_cmd.resize(LEG_NUM);
  wheel_pos_cmd.resize(LEG_NUM);
  leg_angle_cmd.resize(LEG_NUM, joint_num);
  leg_angle_cmd_pre.resize(LEG_NUM, joint_num);
  leg_angle_cmd_pre = {Eigen::VectorXd::Zero(LEG_JOINT_NUM), Eigen::VectorXd::Zero(LEG_JOINT_NUM),
                       Eigen::VectorXd::Zero(LEG_JOINT_NUM), Eigen::VectorXd::Zero(LEG_JOINT_NUM)};
  wheel_pos_cmd_pre.resize(LEG_NUM);
  std::fill(wheel_pos_cmd_pre.begin(), wheel_pos_cmd_pre.end(), 0.0);
  leg_pos_cmd.resize(LEG_NUM);
  leg_pos_ref.resize(LEG_NUM);
  leg_pos_ref_pre.resize(LEG_NUM);
  migration_length_cmd_pre.resize(LEG_NUM);
  leg_offset.resize(LEG_NUM);
  move_direction.resize(LEG_NUM);
  leg_offset[FL] = Eigen::Vector3d(FL_leg_offset_x_, FL_leg_offset_y_, FL_leg_offset_z_);
  leg_offset[FR] = Eigen::Vector3d(FR_leg_offset_x_, FR_leg_offset_y_, FR_leg_offset_z_);
  leg_offset[BL] = Eigen::Vector3d(BL_leg_offset_x_, BL_leg_offset_y_, BL_leg_offset_z_);
  leg_offset[BR] = Eigen::Vector3d(BR_leg_offset_x_, BR_leg_offset_y_, BR_leg_offset_z_);
  leg_pos_ref_pre = leg_offset;
  
  imu_data_sub = nh.subscribe("/imu/data", 2, &BaseController::read_imu, this);

  spinner.start();

  /* resize vectors of Eigen library */
  qref.resize(JOINT_NUM);
  q_init.resize(JOINT_NUM);
  q_current.resize(JOINT_NUM);
  leg_pos_ref_data.leg.resize(LEG_NUM);
  leg_pos_data.leg.resize(LEG_NUM);
  c = Eigen::VectorXd::Zero(6);
  pD = Eigen::MatrixXd::Zero(2, 3);
  initialize_flag = false;
  l << 0.12, 0.20;
}

/**
 * @brief Read settings to prepare
 *
 */
void BaseController::load(void) {
  std::lock_guard<std::mutex> lock(joint_states_mutex);
  q_init = q_current;  // Read angle when controller starts
  qref = q_init;       // Set target angle to current angle
}

void BaseController::send_command_sim(void) {
  std_msgs::Float64MultiArray pub_FL_leg_pos_ref, pub_FR_leg_pos_ref, pub_BL_leg_pos_ref, pub_BR_leg_pos_ref,
      pub_wheel_pos_cmd;
  pub_FL_leg_pos_ref.data.resize(LEG_JOINT_NUM);
  pub_FR_leg_pos_ref.data.resize(LEG_JOINT_NUM);
  pub_BL_leg_pos_ref.data.resize(LEG_JOINT_NUM);
  pub_BR_leg_pos_ref.data.resize(LEG_JOINT_NUM);
  pub_wheel_pos_cmd.data.resize(LEG_JOINT_NUM);

   if(!fl_leg_disabled_) {
    for (int i = 0; i < LEG_JOINT_NUM; i++) {
      pub_FL_leg_pos_ref.data[i] = leg_angle_cmd[FL][i];
    }
    leg_FL_position_controller_pub_.publish(pub_FL_leg_pos_ref);
  } else {
    ROS_WARN_THROTTLE(1.0, "FL leg disabled in sim: no position command published for FL!");
  }

  for (int i = 0; i < LEG_JOINT_NUM; i++) {
    // pub_FL_leg_pos_ref.data[i] = leg_angle_cmd[FL][i];
    pub_FR_leg_pos_ref.data[i] = leg_angle_cmd[FR][i];
    pub_BL_leg_pos_ref.data[i] = leg_angle_cmd[BL][i];
    pub_BR_leg_pos_ref.data[i] = leg_angle_cmd[BR][i];
    pub_wheel_pos_cmd.data[i] = wheel_pos_cmd[i];
  }
  // leg_FL_position_controller_pub_.publish(pub_FL_leg_pos_ref);
  leg_FR_position_controller_pub_.publish(pub_FR_leg_pos_ref);
  leg_BL_position_controller_pub_.publish(pub_BL_leg_pos_ref);
  leg_BR_position_controller_pub_.publish(pub_BR_leg_pos_ref);
  wheel_controller_pub_.publish(pub_wheel_pos_cmd);
}

void BaseController::send_command_real(void) {
  melew3_msgs::MotionCommand pub_FL_motion_cmd, pub_FR_motion_cmd, pub_BL_motion_cmd, pub_BR_motion_cmd;
  // ROS_WARN("command real in");
  pub_FL_motion_cmd.drive_ids.resize(ONE_LEG_JOINT_NUM );
  pub_FL_motion_cmd.target_position.resize(ONE_LEG_JOINT_NUM );
  pub_FL_motion_cmd.target_velocity.resize(ONE_LEG_JOINT_NUM );
  pub_FL_motion_cmd.target_torque.resize(ONE_LEG_JOINT_NUM );

  pub_FR_motion_cmd.drive_ids.resize(ONE_LEG_JOINT_NUM );
  pub_FR_motion_cmd.target_position.resize(ONE_LEG_JOINT_NUM );
  pub_FR_motion_cmd.target_velocity.resize(ONE_LEG_JOINT_NUM );
  pub_FR_motion_cmd.target_torque.resize(ONE_LEG_JOINT_NUM );

  pub_BL_motion_cmd.drive_ids.resize(ONE_LEG_JOINT_NUM );
  pub_BL_motion_cmd.target_position.resize(ONE_LEG_JOINT_NUM );
  pub_BL_motion_cmd.target_velocity.resize(ONE_LEG_JOINT_NUM );
  pub_BL_motion_cmd.target_torque.resize(ONE_LEG_JOINT_NUM );

  pub_BR_motion_cmd.drive_ids.resize(ONE_LEG_JOINT_NUM );
  pub_BR_motion_cmd.target_position.resize(ONE_LEG_JOINT_NUM);
  pub_BR_motion_cmd.target_velocity.resize(ONE_LEG_JOINT_NUM );
  pub_BR_motion_cmd.target_torque.resize(ONE_LEG_JOINT_NUM );
  
  calc_vel(leg_angle_cmd, leg_angle_cmd_pre, wheel_pos_cmd, wheel_pos_cmd_pre);
  
  for (int i = 0; i < LEG_JOINT_NUM; i++) {
    pub_FL_motion_cmd.drive_ids[i] = FL1_MOTOR + i + 11;
    pub_FL_motion_cmd.target_position[i] = (float)leg_angle_cmd[FL][i];
    pub_FL_motion_cmd.target_velocity[i] = leg_motor_vel[FL][i];
    pub_FL_motion_cmd.target_torque[i] = leg_motor_torque[FL][i];

    pub_FR_motion_cmd.drive_ids[i] = FR1_MOTOR + i + 11;
    pub_FR_motion_cmd.target_position[i] = (float)leg_angle_cmd[FR][i];
    pub_FR_motion_cmd.target_velocity[i] = leg_motor_vel[FR][i];
    pub_FR_motion_cmd.target_torque[i] = leg_motor_torque[FR][i];

    pub_BL_motion_cmd.drive_ids[i] = BL1_MOTOR + i + 11;
    pub_BL_motion_cmd.target_position[i] = (float)leg_angle_cmd[BL][i];
    pub_BL_motion_cmd.target_velocity[i] = leg_motor_vel[BL][i];
    pub_BL_motion_cmd.target_torque[i] = leg_motor_torque[BL][i];

    pub_BR_motion_cmd.drive_ids[i] = BR1_MOTOR + i + 11;
    pub_BR_motion_cmd.target_position[i] = (float)leg_angle_cmd[BR][i];
    pub_BR_motion_cmd.target_velocity[i] = leg_motor_vel[BR][i];
    pub_BR_motion_cmd.target_torque[i] = leg_motor_torque[BR][i];
  }

  pub_FL_motion_cmd.drive_ids[WHEEL_JOINT] = WHEEL_FL_MOTOR + 11;
  pub_FL_motion_cmd.target_position[WHEEL_JOINT] = (float)wheel_pos_cmd[FL_LEG];
  pub_FL_motion_cmd.target_velocity[WHEEL_JOINT] = wheel_motor_vel[FL_LEG];
  pub_FL_motion_cmd.target_torque[WHEEL_JOINT] = wheel_motor_torque[FL_LEG];

  pub_FR_motion_cmd.drive_ids[WHEEL_JOINT] = WHEEL_FR_MOTOR + 11;
  pub_FR_motion_cmd.target_position[WHEEL_JOINT] = (float)wheel_pos_cmd[FR_LEG];
  pub_FR_motion_cmd.target_velocity[WHEEL_JOINT] = wheel_motor_vel[FR_LEG];
  pub_FR_motion_cmd.target_torque[WHEEL_JOINT] = wheel_motor_torque[FR_LEG];

  pub_BL_motion_cmd.drive_ids[WHEEL_JOINT] = WHEEL_BL_MOTOR + 11;
  pub_BL_motion_cmd.target_position[WHEEL_JOINT] = (float)wheel_pos_cmd[BL_LEG];
  pub_BL_motion_cmd.target_velocity[WHEEL_JOINT] = wheel_motor_vel[BL_LEG];
  pub_BL_motion_cmd.target_torque[WHEEL_JOINT] = wheel_motor_torque[BL_LEG];

  pub_BR_motion_cmd.drive_ids[WHEEL_JOINT] = WHEEL_BR_MOTOR + 11;
  pub_BR_motion_cmd.target_position[WHEEL_JOINT] = (float)wheel_pos_cmd[BR_LEG];
  pub_BR_motion_cmd.target_velocity[WHEEL_JOINT] = wheel_motor_vel[BR_LEG];
  pub_BR_motion_cmd.target_torque[WHEEL_JOINT] = wheel_motor_torque[BR_LEG];

  FL_leg_motion_cmd_pub_.publish(pub_FL_motion_cmd);
  FR_leg_motion_cmd_pub_.publish(pub_FR_motion_cmd);
  BL_leg_motion_cmd_pub_.publish(pub_BL_motion_cmd);
  BR_leg_motion_cmd_pub_.publish(pub_BR_motion_cmd);

  for (int i = 0; i < LEG_JOINT_NUM; i++) {
    leg_angle_cmd_pre[FL][i] = leg_angle_cmd[FL][i];
    leg_angle_cmd_pre[FR][i] = leg_angle_cmd[FR][i];
    leg_angle_cmd_pre[BL][i] = leg_angle_cmd[BL][i];
    leg_angle_cmd_pre[BR][i] = leg_angle_cmd[BR][i];
    wheel_pos_cmd_pre[i] = wheel_pos_cmd[i];
  }
}

void BaseController::calc_vel(const std::vector<Eigen::VectorXd>& angle_cmd,
                              const std::vector<Eigen::VectorXd>& angle_cmd_pre, const std::vector<double>& wheel_cmd,
                              const std::vector<double>& wheel_cmd_pre) {
  for (int i = 0; i < LEG_JOINT_NUM; i++) {
    leg_motor_vel[FL][i] = (float)((angle_cmd[FL][i] - angle_cmd_pre[FL][i]) * controller_frequency);
    leg_motor_vel[FR][i] = (float)((angle_cmd[FR][i] - angle_cmd_pre[FR][i]) * controller_frequency);
    leg_motor_vel[BL][i] = (float)((angle_cmd[BL][i] - angle_cmd_pre[BL][i]) * controller_frequency);
    leg_motor_vel[BR][i] = (float)((angle_cmd[BR][i] - angle_cmd_pre[BR][i]) * controller_frequency);
    wheel_motor_vel[i] = (float)((wheel_cmd[i] - wheel_cmd_pre[i]) * controller_frequency);
    //std::cout << angle_cmd[0] << std::endl;
    //std::cout << leg_angle_cmd_pre[0] << std::endl;
    // std::cout <<leg_motor_vel[FL][i] << std::endl;
  }
}

/**
 * @brief Read current joint position when controller starts.
 *
 * @return true
 * @return false
 */
void BaseController::read_state(const sensor_msgs::JointState::ConstPtr& msg) {
  std::lock_guard<std::mutex> lock(joint_states_mutex);
  for (int i = 0; i < JOINT_NUM; i++) {
    q_current[i] = msg->position[i];
  }
}

void BaseController::FL_read_state(const sensor_msgs::JointState::ConstPtr& msg) {
  std::lock_guard<std::mutex> lock(joint_states_mutex);
  
  q_current[FL1_MOTOR] = msg->position[0];
  q_current[FL2_MOTOR] = msg->position[1];
  q_current[FL3_MOTOR] = msg->position[2];
  q_current[FL4_MOTOR] = msg->position[3];
  q_current[WHEEL_FL_MOTOR] = msg->position[4];
}

void BaseController::FR_read_state(const sensor_msgs::JointState::ConstPtr& msg) {
  std::lock_guard<std::mutex> lock(joint_states_mutex);
  
  q_current[FR1_MOTOR] = msg->position[0];
  q_current[FR2_MOTOR] = msg->position[1];
  q_current[FR3_MOTOR] = msg->position[2];
  q_current[FR4_MOTOR] = msg->position[3];
  q_current[WHEEL_FR_MOTOR] = msg->position[4];
  
}

void BaseController::BL_read_state(const sensor_msgs::JointState::ConstPtr& msg) {
  std::lock_guard<std::mutex> lock(joint_states_mutex);

  q_current[BL1_MOTOR] = msg->position[0];
  q_current[BL2_MOTOR] = msg->position[1];
  q_current[BL3_MOTOR] = msg->position[2];
  q_current[BL4_MOTOR] = msg->position[3];
  q_current[WHEEL_BL_MOTOR] = msg->position[4];
}

void BaseController::BR_read_state(const sensor_msgs::JointState::ConstPtr& msg) {
  std::lock_guard<std::mutex> lock(joint_states_mutex);

  q_current[BR1_MOTOR] = msg->position[0];
  q_current[BR2_MOTOR] = msg->position[1];
  q_current[BR3_MOTOR] = msg->position[2];
  q_current[BR4_MOTOR] = msg->position[3];
  q_current[WHEEL_BR_MOTOR] = msg->position[4];
}

void BaseController::read_imu(const sensor_msgs::Imu::ConstPtr& msg) {
  imu_quaternion.x() = msg->orientation.x;
  imu_quaternion.y() = msg->orientation.y;
  imu_quaternion.z() = msg->orientation.z;
  imu_quaternion.w() = msg->orientation.w;

  // クォータニオン→オイラー角
  double q0q0 = imu_quaternion.x() * imu_quaternion.x();
  double q0q1 = imu_quaternion.x() * imu_quaternion.y();
  double q0q2 = imu_quaternion.x() * imu_quaternion.z();
  double q0q3 = imu_quaternion.x() * imu_quaternion.w();
  double q1q1 = imu_quaternion.y() * imu_quaternion.y();
  double q1q2 = imu_quaternion.y() * imu_quaternion.z();
  double q1q3 = imu_quaternion.y() * imu_quaternion.w();
  double q2q2 = imu_quaternion.z() * imu_quaternion.z();
  double q2q3 = imu_quaternion.z() * imu_quaternion.w();
  double q3q3 = imu_quaternion.w() * imu_quaternion.w();

  imu_euler.x() = -atan2(2.0 * (q2q3 + q0q1), q0q0 - q1q1 - q2q2 + q3q3);
  imu_euler.y() = -asin(2.0 * (q0q2 - q1q3));
  imu_euler.z() = -atan2(2.0 * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3);
}

/**
 * @brief Measure the time when this function is called
 *
 */
void BaseController::start_timer(void) { t_start = ros::Time::now(); }

/**
 * @brief
 *
 */
void BaseController::stop_timer(void) {}

/**
 * @brief return current time measured since start_timer() function was called
 *
 * @return double : current time
 */
double BaseController::get_time(void) { return (ros::Time::now() - t_start).toSec(); }

/**
 * @brief Start Controller
 *        Please call this function in constructor of derived controller class
 *
 */
void BaseController::start_controller(void) {
  start_timer();
  timer = nh.createTimer(ros::Duration(1.0 / controller_frequency), &BaseController::loop, this);
}

/**
 * @brief Start Controller
 *        Please call this function when you want to kill controller node
 *
 */
void BaseController::stop_controller(void) {
  timer.stop();
  ros::shutdown();
}

/**
 * @brief Transition to default pose
 *
 * @param moving_time : Time to complete the transition (default value is 1.0[s])
 * @return true       : Returns when transition has been finished
 * @return false      : Returns while doing transition
 */
bool BaseController::pose_transition(void) {
  if (sim_flag) {
    //  ROS_INFO("in sim true");

    double t = get_time();
    if (!initialize_flag) {
      angle_mode = true;
      leg_pos_ref[FL] << 0.0, 0.0, default_z;
      leg_pos_ref[FR] << 0.0, 0.0, default_z;
      leg_pos_ref[BL] << 0.0, 0.0, default_z;
      leg_pos_ref[BR] << 0.0, 0.0, default_z;
      leg_yaw_cmd[FL] = default_psi;
      leg_yaw_cmd[FR] = default_psi;
      leg_yaw_cmd[BL] = default_psi;
      leg_yaw_cmd[BR] = default_psi;
      for (int i = 0; i < LEG_JOINT_NUM; i++) {
        leg_angle_cmd_pre[FL][i] = q_current[i];
        leg_angle_cmd_pre[FR][i] = q_current[i + 4];
        leg_angle_cmd_pre[BL][i] = q_current[i + 8];
        leg_angle_cmd_pre[BR][i] = q_current[i + 12];
        wheel_pos_cmd_pre[i] = q_current[i + 16];
      }
      initialize_flag = true;
    }

    qref = q_current;
    for (int i = 0; i < LEG_JOINT_NUM; i++) {
      leg_angle_cmd[FL][i] = qref[i];
      leg_angle_cmd[FR][i] = qref[i + 4];
      leg_angle_cmd[BL][i] = qref[i + 8];
      leg_angle_cmd[BR][i] = qref[i + 12];
      wheel_pos_cmd[i] = qref[i + 16];
    }
    if (t >= joint_Interpolator.domainUpper()) {
      initialize_flag = false;
      angle_mode = true;
      return true;
    } else {
      return false;
    }
  } else {
    //  ROS_INFO("in sim false");
    double t = get_time();
    if (!initialize_flag) {
      angle_mode = true;
      leg_pos_ref[FL] << 0.0, 0.0, default_z;
      leg_pos_ref[FR] << 0.0, 0.0, default_z;
      leg_pos_ref[BL] << 0.0, 0.0, default_z;
      leg_pos_ref[BR] << 0.0, 0.0, default_z;
      leg_yaw_cmd[FL] = default_psi;
      leg_yaw_cmd[FR] = default_psi;
      leg_yaw_cmd[BL] = default_psi;
      leg_yaw_cmd[BR] = default_psi;
      for (int i = 0; i < LEG_JOINT_NUM; i++) {
        leg_angle_cmd_pre[FL][i] = q_current[i];
        leg_angle_cmd_pre[FR][i] = q_current[i + 4];
        leg_angle_cmd_pre[BL][i] = q_current[i + 8];
        leg_angle_cmd_pre[BR][i] = q_current[i + 12];
        wheel_pos_cmd_pre[i] = q_current[i + 16];
      }
      initialize_flag = true;
    }

    qref = q_current;
    for (int i = 0; i < LEG_JOINT_NUM; i++) {
      leg_angle_cmd[FL][i] = qref[i];
      leg_angle_cmd[FR][i] = qref[i + 4];
      leg_angle_cmd[BL][i] = qref[i + 8];
      leg_angle_cmd[BR][i] = qref[i + 12];
      wheel_pos_cmd[i] = qref[i + 16];
      leg_motor_torque[FL][i] = 0.0f;
      leg_motor_torque[FR][i] = 0.0f;
      leg_motor_torque[BL][i] = 0.0f;
      leg_motor_torque[BR][i] = 0.0f;

      wheel_motor_torque[i] = 0.0f;
    }
    if (t >= joint_Interpolator.domainUpper()) {
      initialize_flag = false;
      angle_mode = true;
      return true;
    } else {
      return false;
    }
  }
}

/**
 * @brief
 *
 * @param p         : Target foot position
 * @param psi       : Target yaw angle
 * @return true     : Returns when transition has been finished
 * @return false    : Returns while doing transition
 */
bool BaseController::pose_transition(const std::vector<Eigen::Vector3d>& leg_pos, const std::vector<double>& leg_yaw,
                                     Eigen::Vector3d& COM_pos, const double& COM_yaw, const double& move_time) {
  if (sim_flag) {
    //  ROS_INFO("in sim true");
    double t = get_time();
    if (!initialize_flag) {
      angle_mode = true;
      // Calculate Inverse Kinematics

      Eigen::VectorXd q_tmp = Eigen::VectorXd::Zero(JOINT_NUM);
      q_tmp[WHEEL_FL_MOTOR] = q_current[WHEEL_FL_MOTOR];
      q_tmp[WHEEL_FR_MOTOR] = q_current[WHEEL_FR_MOTOR];
      q_tmp[WHEEL_BL_MOTOR] = q_current[WHEEL_BL_MOTOR];
      q_tmp[WHEEL_BR_MOTOR] = q_current[WHEEL_BR_MOTOR];

    //----------
    double COM_pitch=0.0;
    //----------

      // Calculate IK Here !!
      solve_IK_serial(leg_pos, leg_yaw, COM_pos, COM_yaw, COM_pitch);//add

      for (int i = 0; i < LEG_JOINT_NUM; i++) {
        q_tmp[i] = leg_angle_cmd[FL][i];
        q_tmp[i + 4] = leg_angle_cmd[FR][i];
        q_tmp[i + 8] = leg_angle_cmd[BL][i];
        q_tmp[i + 12] = leg_angle_cmd[BR][i];
        q_tmp[i + 16] = wheel_pos_cmd[i];
      }

      joint_Interpolator.clear();
      joint_Interpolator.appendSample(t, q_current);
      joint_Interpolator.appendSample(t + move_time, q_tmp);
      joint_Interpolator.update();
      initialize_flag = true;
    }

    qref = joint_Interpolator.interpolate(t);

    for (int i = 0; i < LEG_JOINT_NUM; i++) {
      leg_angle_cmd[FL][i] = qref[i];
      leg_angle_cmd[FR][i] = qref[i + 4];
      leg_angle_cmd[BL][i] = qref[i + 8];
      leg_angle_cmd[BR][i] = qref[i + 12];
      wheel_pos_cmd[i] = qref[i + 16];
    }

    if (t >= joint_Interpolator.domainUpper()) {  // nazo
      initialize_flag = false;
      angle_mode = false;
      return true;
    } else {
      return false;
    }
  } else {
    //  ROS_INFO("in sim false");
    double t = get_time();
    if (!initialize_flag) {
      angle_mode = true;
      // Calculate Inverse Kinematics

      Eigen::VectorXd q_tmp = Eigen::VectorXd::Zero(JOINT_NUM);
      q_tmp[WHEEL_FL_MOTOR] = q_current[WHEEL_FL_MOTOR];
      q_tmp[WHEEL_FR_MOTOR] = q_current[WHEEL_FR_MOTOR];
      q_tmp[WHEEL_BL_MOTOR] = q_current[WHEEL_BL_MOTOR];
      q_tmp[WHEEL_BR_MOTOR] = q_current[WHEEL_BR_MOTOR];

    //----------
    double COM_pitch=0.0;
    //----------

      // Calculate IK Here !!
      solve_IK_parallel(leg_pos, leg_yaw, COM_pos, COM_yaw, COM_pitch);//add

      for (int i = 0; i < LEG_JOINT_NUM; i++) {
        q_tmp[i] = leg_angle_cmd[FL][i];
        q_tmp[i + 4] = leg_angle_cmd[FR][i];
        q_tmp[i + 8] = leg_angle_cmd[BL][i];
        q_tmp[i + 12] = leg_angle_cmd[BR][i];
        q_tmp[i + 16] = wheel_pos_cmd[i];
      }

      joint_Interpolator.clear();
      joint_Interpolator.appendSample(t, q_current);
      joint_Interpolator.appendSample(t + move_time, q_tmp);
      joint_Interpolator.update();
      initialize_flag = true;
    }

    qref = joint_Interpolator.interpolate(t);

    for (int i = 0; i < LEG_JOINT_NUM; i++) {
      leg_angle_cmd[FL][i] = qref[i];
      leg_angle_cmd[FR][i] = qref[i + 4];
      leg_angle_cmd[BL][i] = qref[i + 8];
      leg_angle_cmd[BR][i] = qref[i + 12];
      wheel_pos_cmd[i] = qref[i + 16];
      leg_motor_torque[FL][i] = 0.0f;
      leg_motor_torque[FR][i] = 0.0f;
      leg_motor_torque[BL][i] = 0.0f;
      leg_motor_torque[BR][i] = 0.0f;

      wheel_motor_torque[i] = 0.0f;
    }

    if (t >= joint_Interpolator.domainUpper()) {  // nazo
      initialize_flag = false;
      angle_mode = false;
      return true;
    } else {
      return false;
    }
  }
}

/**
 * @brief 速度制限用関数
 *
 * @param velocity
 * @param velocity_pre
 */
// void BaseController::wheel_vel_limit(const double& velocity, const double& velocity_pre, double&
// migration_length_ref) {
//   if (-wheel_max_change > (velocity + velocity_pre) * dt / (2.0 * (wheel_diameter / 2))) {
//     migration_length_ref -= wheel_max_change * (wheel_diameter / 2);
//     ROS_ERROR("speed over");
//   } else if (wheel_max_change < (velocity + velocity_pre) * dt / (2.0 * (wheel_diameter / 2))) {
//     migration_length_ref += wheel_max_change * (wheel_diameter / 2);
//     ROS_ERROR("speed over");
//   } else
//     migration_length_ref += (velocity + velocity_pre) * dt / 2.0;
// }

/**
 * @brief
 *
 * @param joint_id  : Where to change PD gain (HIP or KNEE or WHEEL)
 * @param kp        : Desired P gain
 * @param kd        : Desired D gain
 */
// void BaseController::change_PD_gain(uint8_t joint, double kp, double kd) {
//   gain_client.getCurrentConfiguration(gain_config, ros::Duration(0.01));

//   switch (joint) {
//     case L1_MOTOR:
//       gain_config.L1_motor_Kp = kp;
//       gain_config.L1_motor_Kd = kd;
//       break;
//     case L2_MOTOR:
//       gain_config.L2_motor_Kp = kp;
//       gain_config.L2_motor_Kd = kd;
//       break;
//     case L3_MOTOR:
//       gain_config.L3_motor_Kp = kp;
//       gain_config.L3_motor_Kd = kd;
//       break;
//     case L4_MOTOR:
//       gain_config.L4_motor_Kp = kp;
//       gain_config.L4_motor_Kd = kd;
//       break;
//     case R1_MOTOR:
//       gain_config.R1_motor_Kp = kp;
//       gain_config.R1_motor_Kd = kd;
//       break;
//     case R2_MOTOR:
//       gain_config.R2_motor_Kp = kp;
//       gain_config.R2_motor_Kd = kd;
//       break;
//     case R3_MOTOR:
//       gain_config.R3_motor_Kp = kp;
//       gain_config.R3_motor_Kd = kd;
//       break;
//     case R4_MOTOR:
//       gain_config.R4_motor_Kp = kp;
//       gain_config.R4_motor_Kd = kd;
//       break;
//     case WHEEL_L_MOTOR:
//       gain_config.wheel_L_motor_Kp = kp;
//       gain_config.wheel_L_motor_Kd = kd;
//       break;
//     case WHEEL_R_MOTOR:
//       gain_config.wheel_R_motor_Kp = kp;
//       gain_config.wheel_R_motor_Kd = kd;
//       break;
//     default:
//       break;
//   }
//   gain_client.setConfiguration(gain_config);
// }

/**
 * @brief Calculate forward kinematics for current joint position
 *
 * @param q     : Joint position vector
 * @param p     : Answer of forward kinematics
 * @param psi   : Target yaw angle
 * @return true :
 * @return false:
 */

bool BaseController::solve_FK(const Eigen::VectorXd& q, Eigen::Vector3d& left_leg_pos, Eigen::Vector3d& right_leg_pos,
                              double& left_psi, double& right_psi) {
  return true;
}

/**
 * @brief Calculate inverse kinematics from target foot position and yaw angle
 *
 * @param p     : Target foot position
 * @param psi   : Target yaw angle
 * @param q     : Answer of inverse kinematics
 * @return true
 * @return false
 */
bool BaseController::solve_IK_serial(const std::vector<Eigen::Vector3d>& leg_pos, const std::vector<double>& leg_yaw,
                                     Eigen::Vector3d& COM_pos, const double& COM_yaw, const double& COM_pitch) {
  if (leg_pos[FL].x() || leg_pos[FR].x() || leg_pos[BL].x() || leg_pos[BR].x()) {
    ik_flag = true;
    if (loop_time > climb_time && loop_time < climb_end)
    {
      for (int i = 0; i < LEG_NUM; i++) {
      /*** 脚先の相対位置を計算 ***/
      //-------------
        leg_pos_cmd[i] = (leg_pos[i] - COM_pos) + melew3Kinematics.RotZ(COM_yaw) * melew3Kinematics.RotY(COM_pitch) *
                                                      (-leg_offset[i] + Eigen::Vector3d(0.0, 0.0, wheel_diameter_ / 2.0));
        //-------------

        leg_yaw_cmd[i] = leg_yaw[i] - COM_yaw;

        // move_direction[i] = ((leg_pos[i] - leg_pos_ref_pre[i]).x() > 0.0) -
        //                     ((leg_pos[i] - leg_pos_ref_pre[i]).x() < 0.0);  // 車輪の進行方向を設定

        /*** 逆運動学計算（実機の場合はserialをparallelに変更するのを忘れずに） ***/
        ik_flag *= melew3Kinematics.solve_IK_serial(i, leg_pos_cmd[i], leg_yaw_cmd[i], leg_angle_cmd[i]);

    }
      if (ik_flag) {
        // for (int i = 0; i < LEG_NUM; i++) {
        //   /*** 車輪走行距離の計算（後で変更するかも）***/
        //   migration_length_cmd[i] =
        //       (double)move_direction[i] * (leg_pos[i] - leg_pos_ref_pre[i]).norm() + migration_length_cmd_pre[i];

        //   /*** 車輪の目標関節角の計算（後で変更するかも）***/
        //   wheel_pos_cmd[i] =
        //       migration_length_cmd[i] / (wheel_diameter_ / 2.0) - (leg_angle_cmd[i][HIP_PITCH] + leg_angle_cmd[i][KNEE]);
        // }

        /*** 1個前の目標脚先位置と目標車輪位置の保存 ***/
        leg_pos_ref_pre = leg_pos;
        // migration_length_cmd_pre = migration_length_cmd;

        return true;
      } else {
        return false;
      }
    }
    else{
      for (int i = 0; i < LEG_NUM; i++) {
        /*** 脚先の相対位置を計算 ***/
        //-------------
          leg_pos_cmd[i] = (leg_pos[i] - COM_pos) + melew3Kinematics.RotZ(COM_yaw) * melew3Kinematics.RotY(COM_pitch) *
                                                        (-leg_offset[i] + Eigen::Vector3d(0.0, 0.0, wheel_diameter_ / 2.0));
          //-------------
  
          leg_yaw_cmd[i] = leg_yaw[i] - COM_yaw;
  
          move_direction[i] = ((leg_pos[i] - leg_pos_ref_pre[i]).x() > 0.0) -
                              ((leg_pos[i] - leg_pos_ref_pre[i]).x() < 0.0);  // 車輪の進行方向を設定
  
          /*** 逆運動学計算（実機の場合はserialをparallelに変更するのを忘れずに） ***/
          ik_flag *= melew3Kinematics.solve_IK_serial(i, leg_pos_cmd[i], leg_yaw_cmd[i], leg_angle_cmd[i]);
  
      }
        if (ik_flag) {
          for (int i = 0; i < LEG_NUM; i++) {
          //   /*** 車輪走行距離の計算（後で変更するかも）***/
            migration_length_cmd[i] =
                (double)move_direction[i] * (leg_pos[i] - leg_pos_ref_pre[i]).norm() + migration_length_cmd_pre[i];
  
          //   /*** 車輪の目標関節角の計算（後で変更するかも）***/
            wheel_pos_cmd[i] =
                migration_length_cmd[i] / (wheel_diameter_ / 2.0) - (leg_angle_cmd[i][HIP_PITCH] + leg_angle_cmd[i][KNEE]);
          }
  
          /*** 1個前の目標脚先位置と目標車輪位置の保存 ***/
          leg_pos_ref_pre = leg_pos;
          migration_length_cmd_pre = migration_length_cmd;
  
          return true;
        } else {
          return false;
        }
    }
  } else {
    return false;
  }
}

/**
 * @brief Calculate inverse kinematics from target foot position and yaw angle
 *
 * @param p     : Target foot position
 * @param psi   : Target yaw angle
 * @param q     : Answer of inverse kinematics
 * @return true
 * @return false
 */
bool BaseController::solve_IK_parallel(const std::vector<Eigen::Vector3d>& leg_pos, const std::vector<double>& leg_yaw,
                                       Eigen::Vector3d& COM_pos, const double& COM_yaw, const double& COM_pitch) {
  if (leg_pos[FL].x() || leg_pos[FR].x() || leg_pos[BL].x() || leg_pos[BR].x()) {
    ik_flag = true;
    if (loop_time > climb_time && loop_time < climb_end)
    {
      for (int i = 0; i < LEG_NUM; i++) {
      /*** 脚先の相対位置を計算 ***/
      //-------------
        leg_pos_cmd[i] = (leg_pos[i] - COM_pos) + melew3Kinematics.RotZ(COM_yaw) * melew3Kinematics.RotY(COM_pitch) *
                                                      (-leg_offset[i] + Eigen::Vector3d(0.0, 0.0, wheel_diameter_ / 2.0));
        //-------------

        leg_yaw_cmd[i] = leg_yaw[i] - COM_yaw;

        // move_direction[i] = ((leg_pos[i] - leg_pos_ref_pre[i]).x() > 0.0) -
        //                     ((leg_pos[i] - leg_pos_ref_pre[i]).x() < 0.0);  // 車輪の進行方向を設定

        /*** 逆運動学計算（実機の場合はserialをparallelに変更するのを忘れずに） ***/
        ik_flag *= melew3Kinematics.solve_IK_parallel(i, leg_pos_cmd[i], leg_yaw_cmd[i], leg_angle_cmd[i]);

    }
      if (ik_flag) {
        // for (int i = 0; i < LEG_NUM; i++) {
        //   /*** 車輪走行距離の計算（後で変更するかも）***/
        //   migration_length_cmd[i] =
        //       (double)move_direction[i] * (leg_pos[i] - leg_pos_ref_pre[i]).norm() + migration_length_cmd_pre[i];

        //   /*** 車輪の目標関節角の計算（後で変更するかも）***/
        //   wheel_pos_cmd[i] =
        //       migration_length_cmd[i] / (wheel_diameter_ / 2.0) - (leg_angle_cmd[i][HIP_PITCH] + leg_angle_cmd[i][KNEE]);
        // }

        /*** 1個前の目標脚先位置と目標車輪位置の保存 ***/
        leg_pos_ref_pre = leg_pos;
        // migration_length_cmd_pre = migration_length_cmd;

        return true;
      } else {
        return false;
      }
    }
    else{
      for (int i = 0; i < LEG_NUM; i++) {
        /*** 脚先の相対位置を計算 ***/
        //-------------
          leg_pos_cmd[i] = (leg_pos[i] - COM_pos) + melew3Kinematics.RotZ(COM_yaw) * melew3Kinematics.RotY(COM_pitch) *
                                                        (-leg_offset[i] + Eigen::Vector3d(0.0, 0.0, wheel_diameter_ / 2.0));
          //-------------
  
          leg_yaw_cmd[i] = leg_yaw[i] - COM_yaw;
  
          move_direction[i] = ((leg_pos[i] - leg_pos_ref_pre[i]).x() > 0.0) -
                              ((leg_pos[i] - leg_pos_ref_pre[i]).x() < 0.0);  // 車輪の進行方向を設定
  
          /*** 逆運動学計算（実機の場合はserialをparallelに変更するのを忘れずに） ***/
          ik_flag *= melew3Kinematics.solve_IK_parallel(i, leg_pos_cmd[i], leg_yaw_cmd[i], leg_angle_cmd[i]);
  
      }
        if (ik_flag) {
          for (int i = 0; i < LEG_NUM; i++) {
          //   /*** 車輪走行距離の計算（後で変更するかも）***/
            migration_length_cmd[i] =
                (double)move_direction[i] * (leg_pos[i] - leg_pos_ref_pre[i]).norm() + migration_length_cmd_pre[i];
  
          //   /*** 車輪の目標関節角の計算（後で変更するかも）***/
            Eigen::VectorXd leg_angle_cmd_serial(4);
            melew3Kinematics.solve_IK_serial(i, leg_pos_cmd[i], leg_yaw_cmd[i], leg_angle_cmd_serial);
            wheel_pos_cmd[i] = migration_length_cmd[i] / (wheel_diameter_ / 2.0) -
                               (leg_angle_cmd_serial[HIP_PITCH] + leg_angle_cmd_serial[KNEE]);
          }
  
          /*** 1個前の目標脚先位置と目標車輪位置の保存 ***/
          leg_pos_ref_pre = leg_pos;
          migration_length_cmd_pre = migration_length_cmd;
  
          return true;
        } else {
          return false;
        }
    }
  } else {
    return false;
  }
}

/**
 * @brief The function called every timer event.
 *        Read the "qref" vector and publish at each joint.
 *
 * @param e
 */
void BaseController::loop(const ros::TimerEvent& e) {
  if (sim_flag) {
    //  ROS_INFO("in sim true");
    control_loop();
    if (!angle_mode) {
      // std::cout << "FL_leg_pos_ref.x : " << leg_pos_ref[FL].x() << std::endl;
      // std::cout << "COM_pos_ref.z : " << COM_pos_ref.z() << std::endl;
      solve_IK_serial(leg_pos_ref, leg_yaw_ref, COM_pos_ref, COM_yaw_ref, COM_pitch_ref);
    }
//----------------------
    if (loop_time > climb_time && loop_time < climb_end)
    {
      double dt = 1.0;
      for (int i = 0; i < LEG_NUM; i++){
        wheel_pos_cmd[i] += wheel_velocity_ref[i] * dt;
      }
      // std::cout << "wheel mode active" << std::endl;
    }
//-------------------------
    send_command_sim();
  } else {
    //  ROS_INFO("in sim false");
    control_loop();
    if (!angle_mode) {
      solve_IK_parallel(leg_pos_ref, leg_yaw_ref, COM_pos_ref, COM_yaw_ref, COM_pitch_ref);
    }
    send_command_real();
  }
}
}  // namespace MELEW3_control
   // namespace MELEW3_control