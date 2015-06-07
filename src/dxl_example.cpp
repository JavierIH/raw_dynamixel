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

    raw_dynamixel::dxl_word mensaje;

    if (argc==4){
        mensaje.id=atoi(argv[1]);
        mensaje.address=atoi(argv[2]);
        mensaje.value=atoi(argv[3]);

        publicador.publish(mensaje);
    }
    else{
        ROS_INFO("Note: You can execute this example with the usage ./dxl_example <ID> <ADDRESS> <VALUE> ");
    }
    while(ros::ok())
    {
        ROS_INFO("Enter ID: ");
        cin>>mensaje.id;
        ROS_INFO("Enter ADDRESS: ");
        cin>>mensaje.address;
        ROS_INFO("Enter VALUE: ");
        cin>>mensaje.value;

        publicador.publish(mensaje);
        ROS_INFO("Done!");
        ros::spinOnce();
    }
}
