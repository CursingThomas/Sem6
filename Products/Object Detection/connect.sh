#!/bin/bash
sleep 15
cd ~/autonomous-exploration-of-a-building-3/tools
source wired-jackal.sh
cd ..
source devel/setup.bash
roslaunch autonomous_exploration startup.launch
