#include "ros/ros.h"

#include "raw_dynamixel/dxl_state.h"
#include "raw_dynamixel/dxl_command.h"
#include "dynamixel.h"
#include <iostream>

bool dxl_st(raw_dynamixel::dxl_state::Request &req, raw_dynamixel::dxl_state::Response &res){
	
	dxl_read_word(req.id, req.address);	

	ROS_INFO("Dynamixel motor state:");
	ROS_INFO("ID: ", (int)req.id);
	ROS_INFO("Address: ", (int)req.address);
	ROS_INFO("Value: ", (int)res.value);

	return 1;
}

void dxl_cmd(const raw_dynamixel::dxl_command::ConstPtr& msg)
{
	ROS_INFO("Dynamixel motor command");
	ROS_INFO("ID: %d", (int)msg->id);
	ROS_INFO("Address: %d", (int)msg->address);
	ROS_INFO("Value: %d", (int)msg->value);
    	
	dxl_write_word((int)msg->id, (int)msg->address, (int)msg->value);
}

int main(int argc, char **argv){

	ros::init(argc, argv, "dynamixel_controller");
	ros::NodeHandle node;

	if(dxl_initialize(0,1)) ROS_INFO("Dynamixel bus connected :)");
	else ROS_INFO("Dynamixel bus connection failed :(");

	ros::ServiceServer service = node.advertiseService("dxl_state_controller",dxl_st);
	ros::Subscriber subscriber = node.subscribe("dxl_command_controller", 0, dxl_cmd);    
	
	while(ros::ok()) ros::spinOnce();

	return 0;
}
