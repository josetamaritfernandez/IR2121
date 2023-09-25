#!/bin/bash
export TURTLEBOT3_MODEL=burger
export ROS_LOCALHOST_ONLY=1
source /opt/ros/foxy/setup.bash
ros2 launch turtlebot3_bringup robot.launch.py

