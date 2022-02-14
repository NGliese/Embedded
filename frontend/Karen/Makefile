# you can set this to 1 to see all commands that are being run
VERBOSE ?= 1

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

INSTALL_PATH="./"
PROJECT_NAME="Karen"
SERVER_IP="192.168.1.157"

# make all : format the code using clang-tiny, document by doxygen, apply unittest coverage and zip everythin up

all:  zip_project upload_to_rpi unzip_project build_remote

build: build_remote

# zip project
.PHONY: zip_project
zip_project:
	$(Q) sh tools/zip_folder.sh $(PROJECT_NAME) ; 

# upload to target
.PHONY: upload_to_server
upload_to_rpi:
	$(Q) sh tools/to_server.sh $(SERVER_IP) ; 

# unzip project
.PHONY: unzip_project
unzip_project:
	$(Q) ssh server@$(SERVER_IP) 'bash -s' < tools/unzip_folder.sh $(PROJECT_NAME) ; 

# build remote target
.PHONY: build_remote
build_remote:
	$(Q) ssh server@$(SERVER_IP) 'bash -s' < tools/build_server.sh $(PROJECT_NAME); 


