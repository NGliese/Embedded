# you can set this to 1 to see all commands that are being run
VERBOSE ?= 0

# Output directory
BUILD_INTEGRATION ?= build

# build options
OPTIONS ?=

INTERNAL_OPTIONS =

# This skeleton is built for CMake's Ninja generator
export CMAKE_GENERATOR=Ninja

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

PATH_TO_LIBRARY="/home/$(USER)/github/Embedded/library"
LIB_NAME="LibraryModule-1.0-Source"
INSTALL_PATH="./"
PROJECT_NAME="OutDoorMain_CCTV"
RPI_IP="192.168.1.241"

# make all : format the code using clang-tiny, document by doxygen, apply unittest coverage and zip everythin up

all: install_sip format zip_project upload_to_rpi unzip_project build_remote

build: build_remote

target : default
# default build target
.PHONY: default
default: | $(BUILD_INTEGRATION)/build.ninja
	$(Q)ninja -C $(BUILD_INTEGRATION) 

# RULE: run cmake .. inside $(BUILD_INTEGRATION) if build is not configured
$(BUILD_INTEGRATION)/build.ninja:
	$(Q) cmake -B ${BUILD_INTEGRATION} 


# install sip lib for release target
.PHONY: install_sip
install_sip:
	$(Q) sh tools/installLibrary.sh $(PATH_TO_LIBRARY)/build/$(LIB_NAME) $(INSTALL_PATH); 

# zip project
.PHONY: zip_project
zip_project:
	$(Q) sh tools/zip_folder.sh $(PROJECT_NAME) ; 

# upload to target
.PHONY: upload_to_rpi
upload_to_rpi:
	$(Q) sh tools/to_rpi.sh $(RPI_IP) ; 

# unzip project
.PHONY: unzip_project
unzip_project:
	$(Q) ssh pi@$(RPI_IP) 'bash -s' < tools/unzip_folder.sh $(PROJECT_NAME) ; 

# build remote target
.PHONY: build_remote
build_remote:
	$(Q) ssh pi@$(RPI_IP) 'bash -s' < tools/build_rpi.sh $(PROJECT_NAME); 


# default build target
.PHONY: package
package: | $(BUILD_INTEGRATION)/build.ninja
	$(Q)ninja -C $(BUILD_INTEGRATION) $(OPTIONS) package_source


# clean the build
.PHONY: clean
clean:
	$(Q) if [ -d "$(BUILD_INTEGRATION)" ]; then ninja -C $(BUILD_INTEGRATION) clean; fi
# remove folder ${BUILD_INTEGRATION}
.PHONY: distclean
distclean:
	$(Q) rm -rf $(BUILD_INTEGRATION)

.PHONY: format
format: |
	$(Q) sh ./tools/format.sh;

