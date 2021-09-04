cmake_minimum_required(VERSION 3.13)

project(UNIT)


add_compile_options(-g -std=c++14 -Wall -w -Wextra)

set(APP_NAME unit)

# (1) Look for installed version of CppUTest
if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()






set(SRC_DIR ../../..)

file(GLOB_RECURSE LIB_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${SRC_DIR}/DIR_NAME/include/*.hpp" "../src/*.cpp") # CHANGE DIR_NAME

file(GLOB_RECURSE LIB_FILES1 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${SRC_DIR}/Protocols/MQTT/include/*.hpp" "${SRC_DIR}/Protocols/MQTT/src/*.cpp") # CHANGE DIR_NAME
file(GLOB_RECURSE LIB_FILES2 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${SRC_DIR}/Objects/Timeservice/include/*.hpp" "${SRC_DIR}/Objects/Timeservice/src/*.cpp") # CHANGE DIR_NAME
file(GLOB_RECURSE LIB_FILES3 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${SRC_DIR}/Objects/ErrorHandler/include/*.hpp" "${SRC_DIR}/Objects/ErrorHandler/src/*.cpp") # CHANGE DIR_NAME
file(GLOB_RECURSE LIB_FILES4 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${SRC_DIR}/RTOS/FreeRTOS/include/*.hpp" "${SRC_DIR}/RTOS/FreeRTOS/src/*.cpp") # CHANGE DIR_NAME

################################### STANDARD INCLUDES #############################

file(GLOB_RECURSE COMP_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "../include/*.hpp" "../src/*.cpp")

################################### TEST INCLUDES #############################

set(TEST_DIR test/)

file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${TEST_DIR}/*.hpp" "${TEST_DIR}/*.cpp")

################################### MOCK INCLUDES #############################

set(MOCK_DIR mock/)

file(GLOB_RECURSE MOCK_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${MOCK_DIR}/*.hpp" "${MOCK_DIR}/*.cpp")


set(GLOB_INC /media/espenv/Extra_Disk/Opgaver/Opgaver/Nikolaj/00 settings/Global_Include )
file(GLOB_RECURSE GLOBAL_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${GLOB_INC}/*.hpp" )

# (2) Our unit tests sources

## APPEND new tests @gliese
set(TEST_APP_NAME ${APP_NAME}_tests)
set(TEST_SOURCES
    test_main.cpp
)

# (3) Take care of include directories
include_directories(${CPPUTEST_INCLUDE_DIRS} ../src/)
link_directories(${CPPUTEST_LIBRARIES})


# (4) Build the unit tests objects and link then with the app library
add_executable(${TEST_APP_NAME} ${TEST_SOURCES} ${TEST_FILES} ${COMP_FILES} ${MOCK_FILES} ${GLOBAL_FILES} ${LIB_FILES} 
${LIB_FILES1} ${LIB_FILES2} ${LIB_FILES3} ${LIB_FILES4}  )


#target_include_directories(${TEST_APP_NAME} PUBLIC ${INTERNAL_INCLUDES})
target_link_libraries(${TEST_APP_NAME} ${APP_LIB_NAME} ${CPPUTEST_LDFLAGS})

