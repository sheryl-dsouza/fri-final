
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include "ros/ros.h"
#include "OffsetFlipPR.h"
#include "OffsetPR.h"
#include <math.h>

using namespace std;
  OffsetFlipPR::OffsetFlipPR(double x, double y, double z, PoseRecipient &pr) : _offset(3,1), _pr(pr) {
    _offset(0,0) = x;
    _offset(1,0) = y;
    _offset(2,0) = z;
  }
void OffsetFlipPR :: receivePose(geometry_msgs::Pose &pose) {
   Eigen::Quaterniond r(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);
   Eigen::MatrixXd rotationMatrix = r.toRotationMatrix();
   Eigen::MatrixXd rigidTransform(4,4);
 
   for(int i = 0; i <= 2; i++) {
       for(int j = 0; j <= 2; j++) {
           rigidTransform(i, j) = rotationMatrix(i, j);
       }
   }
   rigidTransform(3,0) = 0;
   rigidTransform(3,1) = 0;
   rigidTransform(3,2) = 0;
   rigidTransform(0,3) = pose.position.x;
   rigidTransform(1,3) = pose.position.y;
   rigidTransform(2,3) = pose.position.z;
   rigidTransform(3,3) = 1;
 
   Eigen::MatrixXd pos(4,1);
   pos(0,0) = 0;
   pos(1,0) = 0;
   pos(2,0) = 1;
   pos(3,0) = 1;
   Eigen::MatrixXd translated(4,1);
   translated = rigidTransform * pos;
 
   Eigen::MatrixXd yAxis(3,1);
   yAxis(0,0) = 0;
   yAxis(1,0) = 1;
   yAxis(2,0) = 0;
   Eigen::AngleAxisd rotAroundY(M_PI, yAxis);
   Eigen::Quaterniond finalRot(r.toRotationMatrix() * rotAroundY.toRotationMatrix());
 
   geometry_msgs::Pose newPose;
   newPose.position.x = translated(0,0);
   newPose.position.y = translated(1,0);
   newPose.position.z = translated(2,0);
   newPose.orientation.x = finalRot.x();
   newPose.orientation.y = finalRot.y();
   newPose.orientation.z = finalRot.z();
   newPose.orientation.w = finalRot.w();
   _pr.receivePose(newPose);
}
