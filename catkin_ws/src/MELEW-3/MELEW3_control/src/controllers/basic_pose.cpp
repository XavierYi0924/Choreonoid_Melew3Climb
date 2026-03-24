/**
 * @file basic_pose.cpp
 * @author Hayato Ota
 * @brief Transition to basical pose
 * @version 1.0
 * @date 2022-04-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <MELEW3_control/BaseController.h>

namespace MELEW3_control {

class basic_pose : public BaseController {
private:
public:
  basic_pose(void);
  virtual void control_loop(void) override;
};

/**
 * @brief Construct a new melew 2l object
 *
 */
basic_pose::basic_pose(void) {
  start_controller();

  // -- You can change PD gain whenever like this --
  // change_PD_gain(LO_MOTOR, 10.0, 3.0);   // kp，kdの変更
  // change_PD_gain(LI_MOTOR, 10.0, 3.0);  // kp，kdの変更
  // change_PD_gain(RI_MOTOR, 10.0, 3.0);   // kp，kdの変更
  // change_PD_gain(RO_MOTOR, 10.0, 3.0);   // kp，kdの変更
}

/**
 * @brief
 *
 */
void basic_pose::control_loop(void) {
  double current_time = get_time();

  // Transition to initial pose
  if (phase == 0) {
    if (pose_transition()) {
      phase = 1;
      stop_controller();
    }
  }

  /** -- You can code like this below if you want to move leg --
  // Move leg
  else if(phase == 1){
      if(!initialize_flag){
          Eigen::Vector3d p_init, p_after;
          p_init << 0.0, 0.0, -0.3266;
          p_after << 0.0, 0.0, -0.2;

          leg_Interpolator.clear();
          leg_Interpolator.appendSample(current_time, p_init);
          leg_Interpolator.appendSample(current_time+1.0, p_after);
          leg_Interpolator.update();
          initialize_flag = true;
      }

      leg_pos_ref = leg_Interpolator.interpolate(current_time);

      if(current_time >= leg_Interpolator.domainUpper()){
          phase = 2;
          initialize_flag = false;
      }
  }

  // Finalize
  else if(phase == 2){
     stop_controller();
  }
  -- */
}

}  // namespace MELEW3_control

int main(int argc, char** argv) {
  ros::init(argc, argv, "basic_pose");
  MELEW3_control::BaseController* controller = new MELEW3_control::basic_pose;
  ros::waitForShutdown();
  return 0;
}
