#!/bin/bash

echo "beginning upload of code to target : rpi ..."


SERVER_IP=$1

echo "Make sure the follwing command has been executed : ssh-copy-id pi@"$SERVER_IP

SERVER_Work_Folder=/home/server/Project/ # Destination of project content
Work_Folder=zip/

echo "-> Work_Folder :: "$Work_Folder ", RPI_Work_Folder :: "$SERVER_Work_Folder
# copy the code to the rpi:
scp -r  $Work_Folder/* server@$SERVER_IP:$SERVER_Work_Folder # copy all

