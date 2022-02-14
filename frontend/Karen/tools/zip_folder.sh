#!/bin/bash

echo "zipping folder"


PROJECT_NAME=$1

zip -q -r zip/$PROJECT_NAME ../$PROJECT_NAME


