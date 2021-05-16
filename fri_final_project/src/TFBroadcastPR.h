#ifndef TF_BROADCAST_PR_H
#define TF_BROADCAST_PR_H
#include <tf2_ros/transform_broadcaster.h>
#include <string>

class TFBroadcastPR  {
protected:
  std::string _parent; 
  std::string _child;
  double _pX;
  double _pY;
  double _pZ;
  double _oX;
  double _oY;
  double _oZ;
  double _oW;
  tf2_ros::TransformBroadcaster _br;

public:
  TFBroadcastPR(std::string a, std::string b, double pX, double pY, double pZ, double oX, double oY, double oZ, double oW);
  void send();
};



#endif
