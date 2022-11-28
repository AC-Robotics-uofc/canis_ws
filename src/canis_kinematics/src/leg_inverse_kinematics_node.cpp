
#include <ros/ros.h>
#include "../include/leg_inverse_kinematics.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "leg_inverse_kinematics_node");

    ros::NodeHandle nh_private("~");
    LegInverseKinematicsProcessor IK = LegInverseKinematicsProcessor(nh_private);
    
    ros::spin();
    return 0;
}