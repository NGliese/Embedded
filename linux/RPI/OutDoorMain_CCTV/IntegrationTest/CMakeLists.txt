#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]
cmake_minimum_required(VERSION 3.18.4)


add_executable(IntegrationTest)

target_include_directories(IntegrationTest PRIVATE components/include )
target_link_libraries(IntegrationTest PRIVATE ${COSTUM_LIBRARIES}  LibraryModule)


###############################################################
#															  #
# 					USER CHANGE START						  #
#															  #
#	In the following the user needs to specify the test files #
#	in the "target_sources(  )" command.					  #
#	example of syntax: 										  #
#       target_sources(${LIBNAME}_tests PRIVATE test_main.cpp #
#       test/time_test.cpp  # <- test file					  #
#       )													  #
#															  #
###############################################################
target_sources(IntegrationTest PRIVATE Integration_Main.cpp
 components/src/Image_Helper_v2.cpp
 components/src/RPICam_Capture.cpp
 components/src/System_Overall.cpp
)