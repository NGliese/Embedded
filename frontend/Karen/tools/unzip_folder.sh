#!/bin/bash

echo "un-zipping folder"


PROJECT_NAME=$1
SERVER_Work_Folder=/home/server/Project/ # Destination of project content
unzip -o -q $SERVER_Work_Folder$PROJECT_NAME -d $SERVER_Work_Folder



