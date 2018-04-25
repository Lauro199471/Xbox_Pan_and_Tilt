/*
 *  A Button Led : GPIO 5 (Pin 29)
 *  B Button Led : GPIO 6 (Pin 31)
 *  Y Button Led : GPIO 19 (Pin 35)
 *  X Button Led : GPIO 26 (Pin 37)
*/

#include<ros/ros.h>   // Include ROS Library
#include <wiringPi.h> // Include wiringPi Library
#include <iostream>
#include <sensor_msgs/Joy.h>

#define A_GPIO 5
#define B_GPIO 6
#define Y_GPIO 19
#define X_GPIO 26

#define OFF 0

using namespace std;

bool a_button = FALSE ,
     b_button = FALSE ,
     x_button = FALSE ,
     y_button = FALSE;

void myCallback(const sensor_msgs::Joy& message_holder)
{
  a_button = message_holder.buttons[0];
  b_button = message_holder.buttons[1];
  x_button = message_holder.buttons[2];
  y_button = message_holder.buttons[3];
}

int main(int argc, char **argv)
{
  cout << "LED Node\n";

  ros::init(argc,argv,"xbox_button_led"); //name this node
  // when this compiled code is run, ROS will recognize it as a node called "minimal_wiringPi"

  ros::NodeHandle n; // need this to establish communications with our new node
  ros::Subscriber my_subscriber_object= n.subscribe("joy",1,myCallback);

  wiringPiSetupGpio(); // Initalize Pi

  pinMode(A_GPIO, OUTPUT);
  pinMode(B_GPIO, OUTPUT);
  pinMode(Y_GPIO, OUTPUT);
  pinMode(X_GPIO, OUTPUT);

  ros::Rate r(1000); // 1 khz for spin (Industry Standard)

  while(ros::ok())
  {
    digitalWrite(A_GPIO , a_button);
    digitalWrite(B_GPIO , b_button);
    digitalWrite(Y_GPIO , y_button);
    digitalWrite(X_GPIO , x_button);
    ros::spinOnce();
    r.sleep();
  }

  digitalWrite(A_GPIO , OFF);
  digitalWrite(B_GPIO , OFF);
  digitalWrite(Y_GPIO , OFF);
  digitalWrite(X_GPIO , OFF);

  return 0;
}




