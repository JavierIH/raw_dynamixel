#include "ros/ros.h"
#include "raw_dynamixel/dxl_command.h"
#include "raw_dynamixel/dxl_state.h"
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "dxl_example");
	ros::NodeHandle nodo;

	int id=22;
	
	ros::Publisher publicador = nodo.advertise<raw_dynamixel::dxl_command>("dxl_command_controller", 0);
	raw_dynamixel::dxl_command command;
	command.id=id;

	ros::ServiceClient state_client = nodo.serviceClient<raw_dynamixel::dxl_state>("dxl_state_controller");
	raw_dynamixel::dxl_state moving;
	moving.request.id=id;
	moving.request.address=46;

	ros::Duration(1).sleep();

	int speed=400;
	int sense=1;
	command.address=32;
	command.value=200;
	publicador.publish(command);

	while(ros::ok()){
		
		command.address=30;
		command.value=500;
		publicador.publish(command);

		ros::Duration(100/(float)speed).sleep();

		command.address=30;
		command.value=650;
		publicador.publish(command);

		ros::Duration(75/(float)speed).sleep();
	
		speed+=sense*30;
		if (speed>=500 || speed<=100) sense=-sense;

		command.address=32;
		command.value=speed;
		publicador.publish(command);

	}
}
