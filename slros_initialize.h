#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block deadreckoning/Subscribe
extern SimulinkSubscriber<geometry_msgs::Twist, SL_Bus_deadreckoning_geometry_msgs_Twist> Sub_deadreckoning_1;

// For Block deadreckoning/Subscribe3
extern SimulinkSubscriber<geometry_msgs::Wrench, SL_Bus_deadreckoning_geometry_msgs_Wrench> Sub_deadreckoning_121;

// For Block deadreckoning/Subscribe4
extern SimulinkSubscriber<sensor_msgs::LaserScan, SL_Bus_deadreckoning_sensor_msgs_LaserScan> Sub_deadreckoning_127;

// For Block deadreckoning/Publish
extern SimulinkPublisher<nav_msgs::Odometry, SL_Bus_deadreckoning_nav_msgs_Odometry> Pub_deadreckoning_79;

void slros_node_init(int argc, char** argv);

#endif
