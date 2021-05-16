#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <ros/ros.h>
#include <std_msgs/Int8.h>

using namespace ros;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int im_in_room = 0;

void driveRobot(
    std::string destination, MoveBaseClient &ac,
    tf2_ros::Buffer &buffer) {
    geometry_msgs::TransformStamped transformStamped;
    
    bool notDone = true;
    while(notDone){
        try{
            ROS_INFO("DOING LOOKUP");
            transformStamped = buffer.lookupTransform("base_link", destination, ros::Time(0));
            ROS_INFO("LOOKUP SUCCEEDED");

            move_base_msgs::MoveBaseGoal goal;

            goal.target_pose.header.frame_id = "base_link";
            goal.target_pose.header.stamp = ros::Time::now();

            goal.target_pose.pose.position.x = transformStamped.transform.translation.x;
            goal.target_pose.pose.position.y = transformStamped.transform.translation.y;
            goal.target_pose.pose.position.z = transformStamped.transform.translation.z;

            goal.target_pose.pose.orientation.w = transformStamped.transform.rotation.w;
            goal.target_pose.pose.orientation.x = transformStamped.transform.rotation.x;
            goal.target_pose.pose.orientation.y = transformStamped.transform.rotation.y;
            goal.target_pose.pose.orientation.z = transformStamped.transform.rotation.z;

            ROS_INFO("Sending goal");

            ac.sendGoal(goal);
            im_in_room = 0;
            ac.waitForResult();
            notDone = false;
        } catch (tf2::TransformException &ex) {
            ROS_WARN("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }
    }

}

void chatterCallback(const std_msgs::Int8::ConstPtr& msg) {
    switch (im_in_room) {
        case 0:
            break;
        case 1:
            ROS_INFO("In room 1");
            ROS_INFO("I heard: [%i]", msg->data);
            break;
        case 2:
            ROS_INFO("In room 2");
            ROS_INFO("I heard: [%i]", msg->data);   
            break;          
    }    
 }

int main(int argc, char **argv) {
    ros::init(argc, argv, "really_drive_robot");
    ros::NodeHandle n;
    
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);

    MoveBaseClient ac("/move_base");

    //SUBSCRIBE
    ros::Subscriber sub = n.subscribe("/darknet_ros/found_object", 1000, chatterCallback);

    ros::AsyncSpinner spinner(4); // Use 4 threads
    spinner.start();

    driveRobot("study_room_1", ac, tfBuffer);
    im_in_room = 1;
    ROS_INFO("SLEEPING 10 seconds");
    ros::Duration(10).sleep();
    ROS_INFO("SLEPT 10 seconds");

    driveRobot("study_room_2", ac, tfBuffer);
    im_in_room = 2;
    ROS_INFO("SLEEPING 10 seconds");
    ros::Duration(10).sleep();
    ROS_INFO("SLEPT 10 seconds");

    driveRobot("study_room_1", ac, tfBuffer);
    im_in_room = 1;
    ROS_INFO("SLEEPING 10 seconds");
    ros::Duration(10).sleep();
    ROS_INFO("SLEPT 10 seconds");

    return 0;
}