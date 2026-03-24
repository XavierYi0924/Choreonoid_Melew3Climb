#include "../MELEW3_kinematics/MELEW3_Kinematics.h"

int main(int argc, char* argv[]) {
  melew3_kinematics::MELEW3_Kinematics melew3Kinematics(0.12, 0.20, 0.20, 0.20);
  Eigen::Vector3d                        p = Eigen::Vector3d::Zero();
  double                                 psi = 0.0;

  if (argc > 2) {
    if (argc == 4) {
      p.x() = std::atof(argv[1]);
      p.y() = std::atof(argv[2]);
      p.z() = std::atof(argv[3]);
    } else if (argc == 5) {
      p.x() = std::atof(argv[1]);
      p.y() = std::atof(argv[2]);
      p.z() = std::atof(argv[3]);
      psi = std::atof(argv[4]);
    } else {
      ROS_ERROR("Argument are too few or too many for this program");
    }
  } else {
    ROS_ERROR("Please enter the target position and Yaw angle");
  }

  Eigen::VectorXd q = Eigen::VectorXd::Zero(4);

  if (melew3Kinematics.solve_IK_parallel(1, p, psi, q)) {
    std::cout << "q= \n" << q << std::endl;

    p = Eigen::Vector3d::Zero();
    psi = 0.0;

    if (melew3Kinematics.solve_FK_parallel(1, q, p, psi)) {
      std::cout << "p= \n" << p << std::endl;
      std::cout << "psi= \n" << psi << std::endl;
    }
  }
}
