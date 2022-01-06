
message(STATUS "if cmake_minimum_req fails, use: 
sudo apt-get update -y; sudo apt-get purge cmake; 
pip3 install cmake, sudo apt-get install -y ninja-build;
and also write : in .profile : export PATH="/home/pi/.local/bin:$PATH"
")


cmake_minimum_required(VERSION 3.18.4 )


#[[
Every project must have a call to the "project()" function
in order to set the project name, language(s) and other parameters
]]
project(RPI_TARGET
	VERSION 1.0
	DESCRIPTION "Project to target a raspberry pi"
	LANGUAGES C CXX)


# set the default c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#include CPM.cmake module for package handling
include(cmake/CPM.cmake)


# Include packaging module
include(cmake/Packaging.cmake)

# in order to specify that the library should be running in rpi mode, we need to add the
# follwoing definitions:
# @attention this should probably be handled in a better way, now that we do not use a .hpp file to switch from one domain to another
# ToDo fix it
add_compile_definitions(	
    __RPI__=1
	__WITH_OPENCV__=1  # access to image analysis
	__WITH_DATABASE__=1   # access to database
    __EMBEDDED_LINUX__=1 # RPI/NANO
    LOGGER_STDOUT=1 # define logger interface LOGGER_STDOUT | LOGGER_MQTT
 )

####################################################################################
include(cmake/installDependencies.cmake)
installDependecies()
####################################################################################


###############################################################################################################
#						CUSTUM COMMAND FOR INSTALLING LIBRARY
###############################################################################################################
# User input: Path to library
set(PATH_TO_LIBRARY "/home/$ENV{USER}/Projects/SiP_Embedded/Library")
# User input: Library name and version
set(LIB_NAME "LibraryModule-1.0-Source")
set(INSTALL_PATH "${CMAKE_CURRENT_LIST_DIR}/")

set(TOOLS_PATH "${CMAKE_CURRENT_LIST_DIR}/tools")
add_custom_target(install_sip_lib 
COMMAND sh ${TOOLS_PATH}/installLibrary.sh ${PATH_TO_LIBRARY}/build/${LIB_NAME} ${INSTALL_PATH}
)

###############################################################################################################
#						add library to project
###############################################################################################################

if(EXISTS "${INSTALL_PATH}${LIB_NAME}")
message(STATUS "We found a library, lets include it...")
add_subdirectory(${LIB_NAME})
endif()

###############################################################################################################
#						add IntegrationTest to project
###############################################################################################################

add_subdirectory(IntegrationTest)

###############################################################################################################
#						add Release to project
###############################################################################################################

add_subdirectory(Release)