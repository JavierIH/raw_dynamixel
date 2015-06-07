#include "ros/ros.h"
#include "raw_dynamixel/dxl_word.h"
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "dxl_example");
    ros::NodeHandle nodo;
    ROS_INFO("Dynamixel servos handling example");
    ros::Publisher publicador = nodo.advertise<raw_dynamixel::dxl_word>("dxl_topic", 0);

    while(ros::ok())
    {
        raw_dynamixel::dxl_word mensaje;

        int i;

        ROS_INFO("Enter ID: ");
        scanf ("%d",&i);


        mensaje.id=i;
        mensaje.address=0;
        mensaje.value=0;

        publicador.publish(mensaje);

        ROS_INFO("Done!");
        ros::spinOnce();
    }
}
