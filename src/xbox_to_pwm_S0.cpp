/*
 *  Base Servo(S0) : GPIO 18
 *
 *
*/

#include<ros/ros.h>   // Include ROS Library
#include <wiringPi.h> // Include wiringPi Library
#include <iostream>
#include <std_msgs/UInt16.h>

#define S0_GPIO 18

using namespace std;

int pos = 0;
double eq_pos = 0;

void myCallback(const std_msgs::UInt16& message_holder)
{
  pos = message_holder.data;
}

int main(int argc, char **argv)
{
  cout << "Servo 0 Node\n";

  ros::init(argc,argv,"xbox_to_pwm_S0"); //name this node
  // when this compiled code is run, ROS will recognize it as a node called "minimal_wiringPi"

  ros::NodeHandle n; // need this to establish communications with our new node
  ros::Subscriber my_subscriber_object= n.subscribe("Servo_POS_S0",1,myCallback);

  wiringPiSetupGpio(); // Initalize Pi

  pinMode (S0_GPIO, PWM_OUTPUT);

  pwmSetMode (PWM_MODE_MS);

  // pwmFrequency in Hz = (19.2e6 Hz / pwmClock) / pwmRange.
  // 50Hz ---> 20ms per cycle. 20ms / 2000 units = 0.01ms per unit
   pwmSetRange (2000);
   pwmSetClock (192);

   ros::Rate r(30); // 30 hz for spin

   while(ros::ok())
   {
     eq_pos = (0.963*pos) + 74.9;
     pwmWrite(S0_GPIO,eq_pos);
     ros::spinOnce();
     r.sleep();
   }
   pwmWrite(S0_GPIO,0);
   return 0;
}




