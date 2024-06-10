#!/bin/bash
source /opt/ros/foxy/setup.bash
export ROS_LOCALHOST_ONLY=1
export TURTLEBOT3_MODEL=burger
ros2 bag play rosbag2_2023_09_13-16_40_42
