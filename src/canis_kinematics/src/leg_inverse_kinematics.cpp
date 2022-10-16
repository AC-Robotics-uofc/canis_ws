#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Point.h"
#include <math.h>

std_msgs::Float64 superior_right_shoulder_msg;
std_msgs::Float64 superior_left_shoulder_msg;
std_msgs::Float64 inferior_right_shoulder_msg;
std_msgs::Float64 inferior_left_shoulder_msg;

std_msgs::Float64 superior_right_arm_msg;
std_msgs::Float64 superior_left_arm_msg;
std_msgs::Float64 inferior_right_arm_msg;
std_msgs::Float64 inferior_left_arm_msg;

std_msgs::Float64 superior_right_forearm_msg;
std_msgs::Float64 superior_left_forearm_msg;
std_msgs::Float64 inferior_right_forearm_msg;
std_msgs::Float64 inferior_left_forearm_msg;

ros::Publisher superior_right_shoulder_pub = n.advertise<std_msgs::Float64>("/actuation/leg/shoulder/superior/right", 1000);
ros::Publisher superior_left_shoulder_pub = n.advertise<std_msgs::Float64>("/actuation/leg/shoulder/superior/left", 1000);
ros::Publisher inferior_right_shoulder_pub = n.advertise<std_msgs::Float64>("/actuation/leg/shoulder/inferior/right", 1000);
ros::Publisher inferior_left_shoulder_pub = n.advertise<std_msgs::Float64>("/actuation/leg/shoulder/inferior/left", 1000);

ros::Publisher superior_right_arm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/arm/superior/right", 1000);
ros::Publisher superior_left_arm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/arm/superior/left", 1000);
ros::Publisher inferior_right_arm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/arm/inferior/right", 1000);
ros::Publisher inferior_left_arm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/arm/inferior/left", 1000);

ros::Publisher superior_right_forearm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/forearm/superior/right", 1000);
ros::Publisher superior_left_forearm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/forearm/superior/left", 1000);
ros::Publisher inferior_right_forearm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/forearm/inferior/right", 1000);
ros::Publisher inferior_left_forearm_pub = n.advertise<std_msgs::Float64>("/actuation/leg/forearm/inferior/left", 1000);

double shoulder_length = 0.055;
double arm_length = 0.105;
double forearm_length = 0.136;

void Superior_Right_Leg_Pos_CB(const geometry_msgs::Point::ConstPtr& msg) {

    // ######### Calculation Process Vars ############
    // From this repo: https://github.com/Technician13/QuadrupedInverseKinematic
    // Example Desmos Graph: https://www.desmos.com/calculator/m8do1lkiop
    // Motor positions are stored in extern vars at bottom

    double superior_right_x = msg.x.data;
    double superior_right_y = msg.y.data;
    double superior_right_z = msg.z.data;

    double dyz = sqrt(superior_right_y * superior_right_y + superior_right_z * superior_right_z);

    double lyz = sqrt(dyz * dyz - shoulder_length * shoulder_length);

    double g1 = atan2(superior_right_y, superior_right_z);

    double g2 = atan2(shoulder_length, lyz);

    double lxz = sqrt(lyz * lyz - superior_right_x * superior_right_x);

    double n = (lxz * lxz - forearm_length * forearm_length - arm_length * arm_length) * 1 / (2 * arm_length);

    double a1 = atan2(superior_right_x, lyz);

    double a2 = -acos((arm_length + n) / lxz);

    double forearm_extensor_pos = acos(n / forearm_length);

    double arm_extensor_pos = -(a1 + a2);

    double shoulder_abductor_pos = (-(g1 + g2)) + M_PI;

    superior_right_shoulder_msg.data = shoulder_abductor_pos;
    superior_right_arm_msg.data = arm_extensor_pos;
    superior_right_forearm_msg.data = forearm_extensor_pos;

    superior_right_shoulder_pub.publish(superior_right_shoulder_msg);
    superior_right_arm_pub.publish(superior_right_arm_msg);
    superior_right_forearm_pub.publish(superior_right_forearm_msg);
}

void Superior_Left_Leg_Pos_CB(const geometry_msgs::Point::ConstPtr& msg) {

    double superior_left_x = msg.x.data;
    double superior_left_y = msg.y.data;
    double superior_left_z = msg.z.data;

    double dyz = sqrt(superior_left_y * superior_left_y + superior_left_z * superior_left_z);

    double lyz = sqrt(dyz * dyz - shoulder_length * shoulder_length);

    double g1 = atan2(superior_left_y, superior_left_z);

    double g2 = atan2(shoulder_length, lyz);

    double lxz = sqrt(lyz * lyz - superior_left_x * superior_left_x);

    double n = (lxz * lxz - forearm_length * forearm_length - arm_length * arm_length) * 1 / (2 * arm_length);

    double a1 = atan2(superior_left_x, lyz);

    double a2 = -acos((arm_length + n) / lxz);

    double forearm_extensor_pos = acos(n / forearm_length);

    double arm_extensor_pos = -(a1 + a2);

    double shoulder_abductor_pos = (-(g1 + g2)) + M_PI;

    superior_left_shoulder_msg.data = shoulder_abductor_pos;
    superior_left_arm_msg.data = arm_extensor_pos;
    superior_left_forearm_msg.data = forearm_extensor_pos;

    superior_left_shoulder_pub.publish(superior_left_shoulder_msg);
    superior_left_arm_pub.publish(superior_left_arm_msg);
    superior_left_forearm_pub.publish(superior_left_forearm_msg);
}

void Inferior_Right_Leg_Pos_CB(const geometry_msgs::Point::ConstPtr& msg) {

    double inferior_right_x = msg.x.data;
    double inferior_right_y = msg.y.data;
    double inferior_right_z = msg.z.data;

    double dyz = sqrt(inferior_right_y * inferior_right_y + inferior_right_z * inferior_right_z);

    double lyz = sqrt(dyz * dyz - shoulder_length * shoulder_length);

    double g1 = atan2(inferior_right_y, inferior_right_z);

    double g2 = atan2(shoulder_length, lyz);

    double lxz = sqrt(lyz * lyz - inferior_right_x * inferior_right_x);

    double n = (lxz * lxz - forearm_length * forearm_length - arm_length * arm_length) * 1 / (2 * arm_length);

    double a1 = atan2(inferior_right_x, lyz);

    double a2 = -acos((arm_length + n) / lxz);

    double forearm_extensor_pos = acos(n / forearm_length);

    double arm_extensor_pos = -(a1 + a2);

    double shoulder_abductor_pos = (-(g1 + g2)) + M_PI;

    inferior_right_shoulder_msg.data = shoulder_abductor_pos;
    inferior_right_arm_msg.data = arm_extensor_pos;
    inferior_right_forearm_msg.data = forearm_extensor_pos;

    inferior_right_shoulder_pub.publish(inferior_right_shoulder_msg);
    inferior_right_arm_pub.publish(inferior_right_arm_msg);
    inferior_right_forearm_pub.publish(inferior_right_forearm_msg);
}

void Inferior_Left_Leg_Pos_CB(const geometry_msgs::Point::ConstPtr& msg) {

    double inferior_left_x = msg.x.data;
    double inferior_left_y = msg.y.data;
    double inferior_left_z = msg.z.data;

    double dyz = sqrt(inferior_left_y * inferior_left_y + inferior_left_z * inferior_left_z);

    double lyz = sqrt(dyz * dyz - shoulder_length * shoulder_length);

    double g1 = atan2(inferior_left_y, inferior_left_z);

    double g2 = atan2(shoulder_length, lyz);

    double lxz = sqrt(lyz * lyz - inferior_left_x * inferior_left_x);

    double n = (lxz * lxz - forearm_length * forearm_length - arm_length * arm_length) * 1 / (2 * arm_length);

    double a1 = atan2(inferior_left_x, lyz);

    double a2 = -acos((arm_length + n) / lxz);

    double forearm_extensor_pos = acos(n / forearm_length);

    double arm_extensor_pos = -(a1 + a2);

    double shoulder_abductor_pos = (-(g1 + g2)) + M_PI;

    inferior_left_shoulder_msg.data = shoulder_abductor_pos;
    inferior_left_arm_msg.data = arm_extensor_pos;
    inferior_left_forearm_msg.data = forearm_extensor_pos;

    inferior_left_shoulder_pub.publish(inferior_left_shoulder_msg);
    inferior_left_arm_pub.publish(inferior_left_arm_msg);
    inferior_left_forearm_pub.publish(inferior_left_forearm_msg);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "Robot_Leg_IK_Node");

  ros::NodeHandle n;

  ros::Subscriber SuperiorRightSub = n.subscribe("/desired_pos/superior/right", 1000, Superior_Right_Leg_Pos_CB);
  ros::Subscriber SuperiorLeftSub = n.subscribe("/desired_pos/superior/left", 1000, Superior_Left_Leg_Pos_CB);
  ros::Subscriber InferiorRightSub = n.subscribe("/desired_pos/inferior/right", 1000, Inferior_Right_Leg_Pos_CB);
  ros::Subscriber InferiorLeftSub = n.subscribe("/desired_pos/inferior/left", 1000, Inferior_Left_Leg_Pos_CB);

  ros::spin();

  return 0;
}
