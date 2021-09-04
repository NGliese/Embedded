# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

add_compile_options(-g -std=c++14 -Wall -w -Wextra)
set(CMAKE_CXX_STANDARD 14)

set(LIB_DIR "~/github/Embedded/library")
include(${LIB_DIR}/CMake/secrets.cmake)

add_compile_options(-DLOGGER_MQTT=1)
add_compile_options(-DPROJECT_NAME="DogFeeder")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(DogFeeder)
