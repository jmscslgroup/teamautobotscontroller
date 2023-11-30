#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "teamautobotscontroller_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block teamautobotscontroller/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_teamautobotscontroller_std_msgs_Float64> Sub_teamautobotscontroller_36;

// For Block teamautobotscontroller/Subscribe1
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_teamautobotscontroller_std_msgs_Float64> Sub_teamautobotscontroller_48;

// For Block teamautobotscontroller/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_teamautobotscontroller_std_msgs_Float64> Pub_teamautobotscontroller_37;

void slros_node_init(int argc, char** argv);

#endif
