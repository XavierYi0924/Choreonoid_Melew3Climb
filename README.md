# Legged_GYM_Melew3Climb 

本仓库包含了 **MELEW-3** 四轮足机器人的核心控制代码与 ROS 工作空间。本项目致力于实现 MELEW-3 机器人在**垂直烟囱状结构中的攀爬任务**，底层核心算法基于**逆运动学（Inverse Kinematics, IK）求解**与传统的开环运动控制策略。

## 核心技术与特性
* **逆运动学 (IK) 核心求解**：通过精确规划机器人足端/轮端在垂直攀爬过程中的空间轨迹，利用逆运动学算法实时反解计算各关节的目标角度与运动姿态。
* **可靠的开环控制架构**：采用稳定且可预测的传统开环步态控制策略，确保在复杂垂直结构中的攀爬动作精准执行。
* **Choreonoid 物理仿真**：集成了 Choreonoid 仿真器，并提供完整的 ROS 接口（`choreonoid_ros`），用于在将代码部署到实物前进行精确的动力学和运动学验证。
* **ZMP 与力控优化**：结合 `zmp_calculator` 模块计算零矩点以维持攀爬姿态平衡，并使用 `qpOASES` 二次规划求解器处理复杂的运动学约束。

## 系统与环境依赖
* 操作系统：Ubuntu 20.04
* ROS 版本：ROS 1 Noetic
* 仿真环境：[Choreonoid](https://choreonoid.org/)
* 编程语言：C++ 

## 仓库结构
* `MELEW-3/` : 机器人的 URDF 模型文件及网格（Mesh）资产。
* `choreonoid/` & `choreonoid_ros/` : Choreonoid 仿真环境配置及 ROS 通信节点。
* `zmp_calculator/` : 机器人的 ZMP 计算及姿态评估算法包。
* `qpOASES/` : 用于处理约束优化和底层控制的 QP 求解器。

## 编译与安装
```bash
# 1. 克隆仓库到本地的 ROS 工作空间 (例如 catkin_ws/src)
git clone [https://github.com/XavierYi0924/Legged_GYM_Melew3Climb.git](https://github.com/XavierYi0924/Legged_GYM_Melew3Climb.git)

# 2. 返回工作空间根目录并编译
cd ~/catkin_ws
catkin_make

# 3. 刷新环境变量
source devel/setup.bash
