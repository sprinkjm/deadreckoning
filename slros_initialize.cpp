#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "deadreckoning";

// For Block deadreckoning/Subscribe
SimulinkSubscriber<geometry_msgs::Twist, SL_Bus_deadreckoning_geometry_msgs_Twist> Sub_deadreckoning_1;

// For Block deadreckoning/Subscribe3
SimulinkSubscriber<geometry_msgs::Wrench, SL_Bus_deadreckoning_geometry_msgs_Wrench> Sub_deadreckoning_121;

// For Block deadreckoning/Subscribe4
SimulinkSubscriber<rosgraph_msgs::Clock, SL_Bus_deadreckoning_rosgraph_msgs_Clock> Sub_deadreckoning_127;

// For Block deadreckoning/Publish
SimulinkPublisher<nav_msgs::Odometry, SL_Bus_deadreckoning_nav_msgs_Odometry> Pub_deadreckoning_79;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

