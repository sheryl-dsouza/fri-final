#include "ros/ros.h"
#include "AlvarMarker.h"
#include "ROSINFOPoseRecipient.h"
#include "SplitterPR.h"
#include "TFBroadcastPR.h"
#include "OffsetPR.h"
#include "OffsetFlipPR.h"
#include "DriveRobotPR.h"
 
//I have removed code from this file. This is for illustration only. You will need to modify it to make your code work.
 
int main(int argc, char **argv) {
 ros::init(argc, argv, "hw5_node");
 ros::NodeHandle n;
 
 tf::TransformListener tf_l;
 ROSINFOPoseRecipient rosInfoPR;
 TFBroadcastPR tfBroadcastPR1("camera_rgb_optical_frame", "marker_frame");
 TFBroadcastPR tfBroadcastPR2("camera_rgb_optical_frame", "offset_frame");
 TFBroadcastPR tfBroadcastPR3("camera_rgb_optical_frame", "offsetFlip_frame");
  
OffsetPR offsetPR(0,0,1,tfBroadcastPR2);
OffsetFlipPR offsetFlip(0,0,1,tfBroadcastPR3);
  
 SplitterPR splitterPR1(rosInfoPR, tfBroadcastPR1);
 SplitterPR splitterPR2(splitterPR1, offsetPR);
 SplitterPR splitterPR3(splitterPR2, offsetFlip); 
 
 AlvarMarker am(n, tf_l, splitterPR3, "camera_rgb_optical_frame");
 
 ros::AsyncSpinner spinner(1);
 spinner.start();
 ros::waitForShutdown();
 
 return 0;
}
