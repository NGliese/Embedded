#!/bin/bash

SERVER_Work_Folder=/home/server/Project/ # Destination of project content
PROJECT_NAME=$1
echo "-> building project  :: "$PROJECT_NAME" in "$SERVER_Work_Folder " with -j"$(nproc) 

## go to work folder
cd $SERVER_Work_Folder$PROJECT_NAME/;
rm -r build;
rm -r node_modules;
npm install;
npm run build;
## TODO : RESTART SERVICE 
# serve -s build -l 4000
