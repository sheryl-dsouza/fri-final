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

 ROSINFOPoseRecipient rosInfoPR;
// TFBroadcastPR tfBroadcastPR1;
 //TFBroadcastPR tfBroadcastPR2;
 // DriveRobotPR driveR;
 
 while (n.ok()){
       tf::StampedTransform tf;

       try{
         TFBroadcastPR tfBroadcastPR1("/base_link", "/study_room_1", 15, 23, 42, 32, 2, 3,2);
         tfBroadcastPR1.receivePose(NULL);
         listener.lookupTransform("/base_link","/study_room_1",  ros::Time(0), tf);        
          driveR(tfBroadcastPR1);
          driveR.receivePose(tf);

         TFBroadcastPR tfBroadcastPR2("/base_link", "/study_room_2", 35, 12, 12, 9, 3, 2, 1);
         tfBroadcastPR2.receivePose(NULL);
         listener.lookupTransform("/base_link","/study_room_2",  ros::Time(0), tf);
        DriveRobotPR driveR(tfBroadcastPR2);
          driveR.receivePose(tf);
       }
       catch (tf::TransformException ex){
         ROS_ERROR("%s",ex.what());
         ros::Duration(1.0).sleep();
         continue;
       }
       ros::spinOnce();
       
 }

 
 return 0;
}

