#ifndef DRIVE_ROBOT_PR_H
#define DRIVE_ROBOT_PR_H
 
#include "PoseRecipient.h"
#include <Eigen/Dense>
#include <iostream>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "TFBroadcastPR.h"
 
using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 
class DriveRobotPR : public PoseRecipient {
public:
  MoveBaseClient _ac;
  TFBroadcastPR &_tf;
  DriveRobotPR(TFBroadcastPR &tf);
  void receivePose(geometry_msgs::Pose &pose);
 };
#endif
