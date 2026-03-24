#include <zmp_calculator/zmp_calculator.hpp>

int main(int argc, char** argv) {
  ros::init(argc, argv, "ZmpCalculatorNode");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  ZmpCalculator   zmpCalc(nh, pnh);
  zmpCalc.Run();

  return 0;
}