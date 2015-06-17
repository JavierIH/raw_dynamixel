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

	ros::ServiceClient state = nodo.serviceClient<raw_dynamixel::dxl_state>("dxl_state_controller");
	raw_dynamixel::dxl_state present_speed;
	present_speed.request.address=38;

	raw_dynamixel::dxl_state present_position;
	present_position.request.address=36;

	int id=22;

	//Turn off torque
	command.id=id;
	command.address=24;
	command.value=0;
	publicador.publish(command);

	//Setting ID
	present_speed.request.id=id;
	present_position.request.id=id;

	while(ros::ok()){
    		state.call(present_position);
		state.call(present_speed);
		
		cout<<"Position "<<present_position.response.value<<endl;

		int value;
		if(present_speed.response.value>=1024)
			value=(1024-present_speed.response.value)/4;
		else
			value=present_speed.response.value/4;

		cout<<"Speed "<<value<<endl;
		ros::Duration(0.1).sleep();
		cout << "\033[2J\033[1;1H";
	}	
}
