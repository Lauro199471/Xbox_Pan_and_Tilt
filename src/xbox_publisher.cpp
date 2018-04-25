#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/Joy.h>
#include <iostream>
using namespace std;

double servo0_pos = 0 , servo1_pos= 0;

void myCallback(const sensor_msgs::Joy& message_holder)
{
  servo0_pos = (message_holder.axes[2] - 1.0) * -90; // fit -2~0 to 0~180 not 0-2 to 180 ~ 0
  servo1_pos = (message_holder.axes[5] - 1.0) * -90; // fit -2~0 to 0~180 not 0-2 to 180 ~ 0
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "xbox_publisher"); // name of this node will be "minimal_publisher"
    ros::NodeHandle n; // two lines to create a publisher object that can talk to ROS
    ros::Publisher my_publisher_object_S0 = n.advertise<std_msgs::UInt16>("Servo_POS_S0", 100);
    ros::Publisher my_publisher_object_S1 = n.advertise<std_msgs::UInt16>("Servo_POS_S1", 100);

    ros::Subscriber my_subscriber_object= n.subscribe("joy",1,myCallback);


    ros::Rate r(100); // 100 hz for spin
    while (ros::ok()) 
    {
      std_msgs::UInt16 msgS0;
      msgS0.data = servo0_pos;
      my_publisher_object_S0.publish(msgS0);

      std_msgs::UInt16 msgS1;
      msgS1.data = servo1_pos;
      my_publisher_object_S1.publish(msgS1);


      ros::spinOnce();
      r.sleep();
    }
    exit(0);
}

