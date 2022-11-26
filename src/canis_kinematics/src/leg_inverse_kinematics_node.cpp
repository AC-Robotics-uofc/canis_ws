
#include <ros/ros.h>
#include "../include/leg_inverse_kinematics.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "leg_innverse_kinematics_node");

    ros::NodeHandle nh_("~");
    LegInverseKinematicsProcessor IK = LegInverseKinematicsProcessor(nh_);
    
    ros::spin();
    return 0;
}