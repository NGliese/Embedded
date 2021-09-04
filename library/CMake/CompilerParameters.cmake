## Make script to standardize the compiler settings for cross-compiled projects
## This makes sure that we are using the same standard for utest as for production code
## Version 1.0, date : 2021-07-22


cmake_minimum_required(VERSION 3.13)


set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_C_EXTENSIONS OFF)
SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)


add_compile_options(
-Wall
-Wextra
-Wno-unused-variable   # usually unused due to unit test env
-Wno-unused-parameter  # usually unused due to unit test env
#-Wconversion
#-Weffc++ # effectice c++ ( scott mayer ) # no fucking way
-g
-O0 ## debugging level optimizing
)


