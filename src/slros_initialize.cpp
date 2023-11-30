#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "teamautobotscontroller";

// For Block teamautobotscontroller/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_teamautobotscontroller_std_msgs_Float64> Sub_teamautobotscontroller_36;

// For Block teamautobotscontroller/Subscribe1
SimulinkSubscriber<std_msgs::Float64, SL_Bus_teamautobotscontroller_std_msgs_Float64> Sub_teamautobotscontroller_48;

// For Block teamautobotscontroller/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_teamautobotscontroller_std_msgs_Float64> Pub_teamautobotscontroller_37;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

