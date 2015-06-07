#include "ros/ros.h"
#include "raw_dynamixel/dxl_word.h"
#include "dynamixel.h"
#include <iostream>

using namespace std;

raw_dynamixel::dxl_word mensaje;

ros::Subscriber subscriptor;


void funcionCallback(const raw_dynamixel::dxl_word::ConstPtr& msg)
{
    ROS_INFO("Mensaje PU recibido\n");
    cout << "   id: " << (int)msg->id << endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "dxl_manager");
    ros::NodeHandle nodo;
    ROS_INFO("Dynamixel servos handling node");

    if(dxl_initialize(0,1)) cout<<"bien"; else cout<<"mal";

    subscriptor = nodo.subscribe("dxl_topic", 0, funcionCallback);


    
    ros::Duration seconds_sleep(3);


    while(ros::ok())
    {
        ros::spinOnce();
        seconds_sleep.sleep();
    }
}
