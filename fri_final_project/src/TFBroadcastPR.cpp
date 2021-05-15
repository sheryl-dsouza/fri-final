#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include "TFBroadcastPR.h"
#include "ros/ros.h"

void TFBroadcastPR::receivePose(geometry_msgs::Pose &pose) {

static tf2_ros::TransformBroadcaster br;
geometry_msgs::TransformStamped ts;
ts.header.stamp = ros::Time::now();
ts.header.frame_id = parent;
ts.child_frame_id = child;
ts.transform.translation.x = _pX;
ts.transform.translation.y = _pY;
ts.transform.translation.z = _pZ;

ts.transform.rotation.x = _oX;
ts.transform.rotation.y = _oY;
ts.transform.rotation.z = _oZ;
ts.transform.rotation.w = _oW;

br.sendTransform(ts);
}  

