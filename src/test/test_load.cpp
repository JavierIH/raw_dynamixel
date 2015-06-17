#include "ros/ros.h"
#include "raw_dynamixel/dxl_command.h"
#include "raw_dynamixel/dxl_state.h"
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "dxl_example");
	ros::NodeHandle nodo;

	ROS_INFO("Dynamixel servos handling example");
	
	ros::Publisher publicador = nodo.advertise<raw_dynamixel::dxl_command>("dxl_command_controller", 0);
	raw_dynamixel::dxl_command command;

	ros::ServiceClient state_client = nodo.serviceClient<raw_dynamixel::dxl_state>("dxl_state_controller");
	raw_dynamixel::dxl_state load;
	load.request.id=20;
	load.request.address=40;
	
	ros::Duration(2).sleep();

	command.id=24;
	command.address=30;
	command.value=512;
	publicador.publish(command);

	command.id=22;
	publicador.publish(command);

	command.id=20;
	publicador.publish(command);	
	
	ros::Duration(2).sleep();

	while(ros::ok()){
		state_client.call(load);
		ROS_INFO("Load: %d", load.response.value);
		if (load.response.value>100){

			command.id=20;
			command.address=30;
			command.value=480;
			publicador.publish(command);
			ros::Duration(0.2).sleep();
			command.value=530;
			publicador.publish(command);
			ros::Duration(0.2).sleep();
			command.value=480;
			publicador.publish(command);
			ros::Duration(0.2).sleep();
			command.value=530;
			publicador.publish(command);
			ros::Duration(0.2).sleep();
			command.value=480;
			publicador.publish(command);
			ros::Duration(0.2).sleep();
			command.value=512;
			publicador.publish(command);
			ros::Duration(0.2).sleep();

		}
		ros::Duration(0.2).sleep();

	}
}
