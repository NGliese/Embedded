
#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]
message(STATUS "if cmake_minimum_req fails, use: sudo apt-get update -y; sudo apt-get purge cmake; pip3 install cmake, sudo apt-get install -y ninja-build;")
cmake_minimum_required(VERSION 3.18.4)

#[[
Every project must have a call to the "project()" function
in order to set the project name, language(s) and other parameters
]]
project(LibraryModule
	VERSION 1.0
	DESCRIPTION "A CMakeScript to handle the modules in the library"
	LANGUAGES C CXX)

# compile definitions : 
 #include target compiler warnings
 # we want to have the variable stored as a global one, in the CACHE space, where every subproject can reach it.
 # we want to FORCE override so that we always are sure how the flags are set
 set(global_compiler_warning -Wall -Wextra -Wpedantic  CACHE STRING "default compiler warning flags" FORCE )

#include CPM.cmake module for package handling
include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(BuildOptions.cmake)

# Include packaging module
include(cmake/Packaging.cmake)


message("CMAKE PROJECT NAME IN LIBRARY IS : ${CMAKE_PROJECT_NAME}")
# only use testing if we're not somebody's subproject!
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
message(WARNING "We are build with testing")
# CMake's test module
include(CTest)

# if we are testing, lets remove optimiziation
add_compile_options("-O0")

add_custom_target(simple_test
DEPENDS  ${COSTUM_TEST_FILES} # does this mean, that every test has been compiled?    
COMMAND ctest --output-on-failure 
)

# in order to specify that the library should be running in unit test mode, we need to add the
# follwoing definitions:
# @attention this should probably be handled in a better way, now that we do not use a .hpp file to switch from one domain to another
# ToDo fix it
add_compile_definitions(	
	UNIT_TEST_MODE=1 
	__UNITTEST__=1
	__WITH_OPENCV__=1 
	GLOBAL_MQTT_SERVER="mqtt://192.168.1.157:1883"
 )

 ####################################################################################
#@Note: we do not want to apply this earlier than this, 
#       to make sure we dont use static-analysis tools on cpputest
include(cmake/applyBuildTooling.cmake)
applyBuildTooling()
####################################################################################


####################################################################################
include(cmake/installDependencies.cmake)
installDependecies()
####################################################################################

endif()





####################################################################################
set(COSTUM_SRC_FILES "" CACHE STRING "avaliable build src" FORCE)
set(COSTUM_INC_FILES "" CACHE STRING "avaliable build inc" FORCE)
set(COSTUM_TEST_FILES "" CACHE STRING "avaliable build tests" FORCE)

add_compile_options(${global_compiler_warning})

#Create a static library
add_library(LibraryModule STATIC)

## add the source folder to the cmake list:
add_subdirectory(Components)

target_sources(LibraryModule PRIVATE ${COSTUM_SRC_FILES} )

target_include_directories(LibraryModule PRIVATE  ${COSTUM_INC_FILES} )


####################################################################################

# only use testing if we're not somebody's subproject!
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
applyCodeCoverageTools()
endif()


