#!/usr/bin/env bash
source /opt/ros/foxy/setup.bash
source /home/aaryanred/Desktop/ws2/install/setup.bash

echo "Launching!"
ros2 run more_interfaces publish_address_book
# echo "Hello Worldddd"
# echo $USER
