#!/bin/bash

# This script aids in setting up the Jackal its network. More on this can be 
# found here:
# https://www.clearpathrobotics.com/assets/guides/noetic/jackal/network.html
#
# The script will change the ROS master of the host machine to the Jackal if the 
# Jackal is connected to the same network, and the current ROS master is not the 
# Jackal.
#
# The script needs to be called the following way:
# source remote-jackal.sh

# get host IP and save URI
#host_ip=$(ip route get 1.1.1.1 | awk -F"src " 'NR==1{split($2,a," ");print a[1]}')
host_ip="192.168.131..50"
host_uri="http://localhost:11311"
echo $host_ip
echo $host_uri
# get Jackal IP and save URI
jackal_ip="192.168.131.1"
jackal_uri="http://cpr-j100:11311"
echo $jackal_ip
echo $jackal_uri
# ping Jackal and save exist status
ping -c1 $jackal_ip 2>/dev/null 1>/dev/null
connected="$?" 

# set ROS master to Jackal if connected to same network
if [[ $connected -ne 0 ]] 
then
    echo "Jackal not connected to the same network as host, host is set as ROS master"
    current_uri=$host_uri
else
    echo "Jackal is set as ROS master"
    current_uri=$jackal_uri
fi

export ROS_IP=$host_ip
export ROS_MASTER_URI=$current_uri
