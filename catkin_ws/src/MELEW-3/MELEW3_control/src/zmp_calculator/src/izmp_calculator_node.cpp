#include <zmp_calculator/izmp_calculator.hpp>

int main(int argc, char** argv) {
  ros::init(argc, argv, "IzmpCalculatorNode");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");
  IzmpCalculator  izmpCalc(nh, pnh);
  izmpCalc.Run();

  return 0;
}