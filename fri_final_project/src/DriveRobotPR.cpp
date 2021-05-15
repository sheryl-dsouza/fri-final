#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "DriveRobotPR.h"
 
DriveRobotPR::DriveRobotPR (TFBroadcastPR &tf) : _tf(tf) , _ac("/bav_kinect/base_link", true){
      while(!_ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
  }
}
  
void DriveRobotPR :: receivePose(geometry_msgs::Pose &pose) {
 
   move_base_msgs::MoveBaseGoal goal;
 

   goal.target_pose.header.frame_id = "nav_kinect/base_link";
   goal.target_pose.header.stamp = ros::Time::now();

   goal.target_pose.pose.position.x = pose.position.x;
   goal.target_pose.pose.position.y = pose.position.y;
   goal.target_pose.pose.position.z = pose.position.z;
 
   goal.target_pose.pose.orientation.w = pose.orientation.x;
   goal.target_pose.pose.orientation.x = pose.orientation.y;
   goal.target_pose.pose.orientation.y = pose.orientation.z;
   goal.target_pose.pose.orientation.z = pose.orientation.w;
 
   // _tf.receivePose(goal.target_pose.pose);

    ROS_INFO("Sending goal");
 
   _ac.sendGoal(goal);
 
   _ac.waitForResult();
 
   if (_ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
       ROS_INFO("Hooray, the base moved 1 meter forward");
   }
   else {
       ROS_INFO("The base failed to move forward 1 meter for some reason");
   }
    
};


