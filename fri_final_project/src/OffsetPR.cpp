
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include "ros/ros.h"
#include "OffsetPR.h"

using namespace std;
  OffsetPR::OffsetPR(double x, double y, double z, PoseRecipient &pr) : _offset(3,1), _pr(pr) {
    _offset(0,0) = x;
    _offset(1,0) = y;
    _offset(2,0) = z;
  }
void OffsetPR :: receivePose(geometry_msgs::Pose &pose) {
    Eigen::Quaterniond r(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
    std::cout << "line 18" << std::endl;
    Eigen::MatrixXd rotatedP = r.toRotationMatrix();
    std::cout << "line 22" << std::endl;
    Eigen::MatrixXd t(4,4);
    t(0,0) = rotatedP(0,0);    
    t(1,0) = rotatedP(1,0); 
    t(2,0) = rotatedP(2,0); 
    t(3,0) = 0;
    t(0,1) = rotatedP(0,1); 
    t(1,1) = rotatedP(1,1); 
    t(2,1) = rotatedP(2,1); 
    t(3,1) = 0; 
    t(0,2) = rotatedP(0,2); 
    t(1,2) = rotatedP(1,2); 
    t(2,2) = rotatedP(2,2); 
    t(3,2) = 0; 
    t(0,3) = pose.position.x;
    t(1,3) = pose.position.y;
    t(2,3) = pose.position.z;
    t(3,3) = 1;

std::cout << "line 42" << std::endl;
    Eigen::MatrixXd pos(4,1);
    pos(0,0) = _offset(0, 0);
    pos(1,0) = _offset(1, 0);
    pos(2,0) = _offset(2, 0);
    pos(3,0) = 1;
std::cout << "line 48" << std::endl;
    Eigen::MatrixXd translated(4,1);
    translated = t * pos;
    geometry_msgs::Pose newPose;
    newPose.position.x = translated(0,0);
    newPose.position.y = translated(1,0);
    newPose.position.z = translated(2,0);
    newPose.orientation.x = pose.orientation.x;
    newPose.orientation.y = pose.orientation.y;
    newPose.orientation.z = pose.orientation.z;
    newPose.orientation.w = pose.orientation.w;
    _pr.receivePose(newPose);

    std::cout << "line 51" << std::endl;
}