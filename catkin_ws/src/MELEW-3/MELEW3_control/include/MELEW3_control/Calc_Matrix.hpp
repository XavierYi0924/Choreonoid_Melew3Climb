#include "math.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <stdlib.h>
#include <iostream>

namespace MELEW3_control {

Eigen::MatrixXd PowMat(Eigen::MatrixXd A, int i);
Eigen::Matrix3d Alternative(Eigen::Vector3d a);
Eigen::Matrix3d Dyadic(Eigen::Vector3d a);
Eigen::MatrixXd Generalized_Inverse(Eigen::MatrixXd A);
Eigen::Vector3d Rot_to_w(Eigen::Matrix3d R);
void PrintMat(const char *str, double a);
void PrintMat(const char *str, Eigen::MatrixXd A);

}