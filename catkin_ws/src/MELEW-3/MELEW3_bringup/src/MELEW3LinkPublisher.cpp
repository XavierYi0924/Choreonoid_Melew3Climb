#include <melew3_msgs/LinkInfoArray.h>
#include <ros/node_handle.h>

#include <cnoid/SimpleController>

using namespace std;
using namespace cnoid;

class MELEW3LinkPublisher : public SimpleController {
  std::unique_ptr<ros::NodeHandle> node;
  BodyPtr                          ioBody;
  ros::Publisher                   LinkPublisher;     //!< リンク情報のPublisher
  melew3_msgs::LinkInfoArray       link_info;         //!< リンク情報を格納する変数
  std::vector<std::string>         link_name;         //!< リンク名
  std::vector<Eigen::Vector3d>     link_position;     //!< リンク位置
  std::vector<Eigen::Matrix3d>     link_orientation;  //!< リンク姿勢
  std::vector<Eigen::Vector3d>     link_linear;       //!< リンク速度
  std::vector<Eigen::Vector3d>     link_angular;      //!< リンク角速度
  int                              link_num;          //!< リンク数

  void VectorToLinkInfoArray(const std::vector<std::string> name_data, const std::vector<Eigen::Vector3d> position_data,
                             const std::vector<Eigen::Matrix3d> orientation_data,
                             const std::vector<Eigen::Vector3d> linear_data,
                             const std::vector<Eigen::Vector3d> angular_data,
                             melew3_msgs::LinkInfoArray&        link_info_array_data);

public:
  virtual bool configure(SimpleControllerConfig* config) override {
    node.reset(new ros::NodeHandle(config->body()->name()));
    LinkPublisher = node->advertise<melew3_msgs::LinkInfoArray>("/MELEW3/link_info", 1);
    return true;
  }

  virtual bool initialize(SimpleControllerIO* io) override {
    /*** 変数の初期化 ***/
    ioBody = io->body();
    link_num = ioBody->numLinks();
    link_info.name.resize(link_num);
    link_info.position.resize(link_num);
    link_info.velocity.resize(link_num);
    link_name.resize(link_num);
    link_position.resize(link_num);
    link_orientation.resize(link_num);
    link_linear.resize(link_num);
    link_angular.resize(link_num);

    /*** リンク位置とリンク速度の取得の有効化 ***/
    for (int i = 0; i < link_num; i++) {
      io->enableInput(ioBody->links()[i], LinkPosition | LinkTwist);
    }

    return true;
  }

  virtual bool control() override {
    /*** データの取得 ***/
    for (int i = 0; i < link_num; i++) {
      link_name[i] = ioBody->links()[i]->name();
      link_position[i] = ioBody->links()[i]->p();
      link_orientation[i] = ioBody->links()[i]->R();
      link_linear[i] = ioBody->links()[i]->v();
      link_angular[i] = ioBody->links()[i]->w();
    }

    /*** データのPublish ***/
    link_info.header.stamp = ros::Time::now();
    link_info.header.frame_id = "link_info";
    VectorToLinkInfoArray(link_name, link_position, link_orientation, link_linear, link_angular, link_info);
    LinkPublisher.publish(link_info);

    return true;
  }
};

void MELEW3LinkPublisher::VectorToLinkInfoArray(const std::vector<std::string>     name_data,
                                                const std::vector<Eigen::Vector3d> position_data,
                                                const std::vector<Eigen::Matrix3d> orientation_data,
                                                const std::vector<Eigen::Vector3d> linear_data,
                                                const std::vector<Eigen::Vector3d> angular_data,
                                                melew3_msgs::LinkInfoArray&        link_info_array_data) {
  for (int i = 0; i < link_info_array_data.position.size(); i++) {
    /*** リンク名の格納 ***/
    link_info_array_data.name[i] = name_data[i];

    /*** リンク位置の格納 ***/
    link_info_array_data.position[i].position.x = position_data[i].x();
    link_info_array_data.position[i].position.y = position_data[i].y();
    link_info_array_data.position[i].position.z = position_data[i].z();

    /*** リンク姿勢の格納 ***/
    Eigen::Quaterniond q;
    q = orientation_data[i];
    link_info_array_data.position[i].orientation.w = q.w();
    link_info_array_data.position[i].orientation.x = q.x();
    link_info_array_data.position[i].orientation.y = q.y();
    link_info_array_data.position[i].orientation.z = q.z();

    /*** リンク速度の格納 ***/
    link_info_array_data.velocity[i].linear.x = linear_data[i].x();
    link_info_array_data.velocity[i].linear.y = linear_data[i].y();
    link_info_array_data.velocity[i].linear.z = linear_data[i].z();

    /*** リンク角速度の格納 ***/
    link_info_array_data.velocity[i].angular.x = angular_data[i].x();
    link_info_array_data.velocity[i].angular.y = angular_data[i].y();
    link_info_array_data.velocity[i].angular.z = angular_data[i].z();
  }
}

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(MELEW3LinkPublisher)