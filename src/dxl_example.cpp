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
	raw_dynamixel::dxl_state moving;
		moving.request.id=1;
		moving.request.address=46;

	raw_dynamixel::dxl_state present_position;
		present_position.request.id=1;
		present_position.request.address=36;


	if (argc==4){
	        command.id=atoi(argv[1]);
	        command.address=atoi(argv[2]);
	        command.value=atoi(argv[3]);
	
	        publicador.publish(command);
	}
	else{
	        ROS_INFO("Note: You can execute this example with the usage ./dxl_example <ID> <ADDRESS> <VALUE> ");
	}

	while(ros::ok()){
	        ROS_INFO("Enter ID / Address / Value: ");
        	cin>>command.id;
       		cin>>command.address;
		cin>>command.value;

	        publicador.publish(command);
    		if (state_client.call(moving)){
			while((int)moving.response.value){
				if(state_client.call(present_position)) ROS_INFO("Present position: %d", (int)present_position.response.value);					
				else ROS_INFO("Call to -present_position- failed");
				state_client.call(moving);
				break;////////
			}			
		}
		else ROS_INFO("Call to -moving- failed");
	        ROS_INFO("Done!");
	}
}
