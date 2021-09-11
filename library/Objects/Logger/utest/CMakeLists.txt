cmake_minimum_required(VERSION 3.13)

project(UNIT)


set(APP_NAME unit)


set(LIB_DIR "~/github/Embedded/library")

include(${LIB_DIR}/CMake/CompilerParameters.cmake)
include(${LIB_DIR}/CMake/LibDir.cmake)


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

find_package( OpenCV REQUIRED )


################################### COMP INCLUDES #############################

set(COMP_DIR ../)

file(GLOB_RECURSE COMP_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "../include/*.hpp" "../src/*.cpp")

################################### TEST INCLUDES #############################


set(TEST_DIR test/)

file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${TEST_DIR}/*.hpp" "${TEST_DIR}/*.cpp")

################################### MOCK INCLUDES #############################

set(MOCK_DIR mock/)

file(GLOB_RECURSE MOCK_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${MOCK_DIR}/*.hpp" "${MOCK_DIR}/*.cpp")



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
add_executable(${TEST_APP_NAME} ${TEST_SOURCES} ${TEST_FILES} ${COMP_FILES} ${MOCK_FILES} ${source_list} )


#target_include_directories(${TEST_APP_NAME} PUBLIC ${INTERNAL_INCLUDES})
target_link_libraries(${TEST_APP_NAME} ${APP_LIB_NAME} ${CPPUTEST_LDFLAGS} ${OpenCV_LIBS} )

