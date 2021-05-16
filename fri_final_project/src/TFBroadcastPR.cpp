#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#include "TFBroadcastPR.h"
#include "ros/ros.h"

TFBroadcastPR::TFBroadcastPR(
    std::string parent, std::string child,
    double pX, double pY, double pZ,
    double oX, double oY, double oZ, double oW) :
    _parent(parent), _child(child),
    _pX(pX), _pY(pY), _pZ(pZ),
    _oX(oX), _oY(oY), _oZ(oZ), _oW(oW)
    {}

void TFBroadcastPR::send() {
    geometry_msgs::TransformStamped ts;
    ts.header.stamp = ros::Time::now();
    ts.header.frame_id = _parent;
    ts.child_frame_id = _child;
    ts.transform.translation.x = _pX;
    ts.transform.translation.y = _pY;
    ts.transform.translation.z = _pZ;

    ts.transform.rotation.x = _oX;
    ts.transform.rotation.y = _oY;
    ts.transform.rotation.z = _oZ;
    ts.transform.rotation.w = _oW;

    _br.sendTransform(ts);
}  

