#include "ros/ros.h"
#include "AlvarMarker.h"
#include "ROSINFOPoseRecipient.h"
#include "SplitterPR.h"
#include "TFBroadcastPR.h"
#include "OffsetPR.h"
#include "OffsetFlipPR.h"
#include "DriveRobotPR.h"
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
//I have removed code from this file. This is for illustration only. You will need to modify it to make your code work.
 
int main(int argc, char **argv) {
 ros::init(argc, argv, "drive_bot");
 ros::NodeHandle n;
 tf::TransformListener listener;


  TFBroadcastPR tfBroadcastPR1(
    "/odom", "/study_room_1",
    15.841, 116.220, -0.000,
    0.000, -0.000, 0.258, 0.966);

  TFBroadcastPR tfBroadcastPR2(
    "/odom", "/study_room_2",
    44.542, 104.611, 0.003,
    -0.004, -0.005, -0.662, 0.749);

 ros::Rate r(10);
 while (ros::ok()){
    tfBroadcastPR1.send();
    tfBroadcastPR2.send();

    /*
    tf::StampedTransform tf;
    listener.lookupTransform("/base_link","/study_room_1",  ros::Time(0), tf);        
    driveR(tfBroadcastPR1);
    driveR.receivePose(tf);

    listener.lookupTransform("/base_link","/study_room_2",  ros::Time(0), tf);
  DriveRobotPR driveR(tfBroadcastPR2);
    driveR.receivePose(tf);
    */

  ros::spinOnce();
  r.sleep();
 }

 
 return 0;
}

