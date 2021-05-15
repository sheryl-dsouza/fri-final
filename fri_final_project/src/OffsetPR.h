#ifndef OFFSET_PR_H
#define OFFSET_PR_H

#include "PoseRecipient.h"
#include <Eigen/Dense>
#include <iostream> 
using namespace std;


class OffsetPR : public PoseRecipient {
public:
  
  Eigen::MatrixXd _offset;
  PoseRecipient &_pr;
  OffsetPR(double x, double y, double z, PoseRecipient &pr);
  void receivePose(geometry_msgs::Pose &pose);
  
};



#endif
