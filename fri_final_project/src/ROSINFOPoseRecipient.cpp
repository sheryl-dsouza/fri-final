#include "ROSINFOPoseRecipient.h"
#include "ros/ros.h"

void ROSINFOPoseRecipient::receivePose(geometry_msgs::Pose &pose) {
    ROS_INFO("POS:  %f %f %f"
    , pose.position.x
    , pose.position.y
    , pose.position.z);
    ROS_INFO("ORIENTATION:  %f %f %f %f"
    , pose.orientation.x
    , pose.orientation.y
    , pose.orientation.z
    , pose.orientation.w);
}
