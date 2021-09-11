
# (1) CMake definitions, compiler flags and useful variables
cmake_minimum_required(VERSION 3.13)
#project(DetectorOpenCV)

add_compile_options(-g -std=c++17 -Wall -w -Wextra)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-DLOGGER_STDOUT=1)
#add_compile_options(-DLOGGER_MQTT=1)
add_compile_options(-DPROJECT_NAME="CCTV01")




find_package( OpenCV REQUIRED )

find_package(raspicam REQUIRED)


set(APP_NAME Detector)


# (1) Build a library with my application sources
# first add the directories


# find python
set(Python_ADDITIONAL_VERSIONS 3.5)
find_package(PythonLibs REQUIRED)


# find curl
find_package(CURL REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)


set(SRC_DIR components/)

file(GLOB_RECURSE COMP_FILES RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${SRC_DIR}/*.hpp" "${SRC_DIR}/*.cpp")


file(GLOB_RECURSE LIB_FILES0 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/TYPE/OBJECT/include/*.hpp" "${LIB_DIR}/TYPE/OBJECT/src/*.cpp")

set(LIB_DIR ../../../lib2pi)

file(GLOB_RECURSE LIB_FILES1 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Global_Include/*.hpp" )

file(GLOB_RECURSE LIB_FILES2 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/ErrorHandler/include/*.hpp" "${LIB_DIR}/Objects/ErrorHandler/src/*.cpp")
file(GLOB_RECURSE LIB_FILES3 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Gpio/include/*.hpp" "${LIB_DIR}/Objects/Gpio/src/*.cpp")
file(GLOB_RECURSE LIB_FILES4 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Timeservice/include/*.hpp" "${LIB_DIR}/Objects/Timeservice/src/*.cpp")
file(GLOB_RECURSE LIB_FILES5 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Watchdog/include/*.hpp" "${LIB_DIR}/Objects/Watchdog/src/*.cpp")
file(GLOB_RECURSE LIB_FILES6 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/PerformanceTools/Profiler/include/*.hpp" "${LIB_DIR}/PerformanceTools/Profiler/src/*.cpp")

file(GLOB_RECURSE LIB_FILES7 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Protocols/HTTP/include/*.hpp" "${LIB_DIR}/Protocols/HTTP/src/*.cpp")
file(GLOB_RECURSE LIB_FILES8 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Sensor/RpiCamV2/include/*.hpp" "${LIB_DIR}/Sensor/RpiCamV2/src/*.cpp")
file(GLOB_RECURSE LIB_FILES9 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Utility/utils/include/*.hpp" "${LIB_DIR}/Utility/utils/src/*.cpp")
file(GLOB_RECURSE LIB_FILES10 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Utility/Serialized/include/*.hpp" "${LIB_DIR}/Utility/Serialized/src/*.cpp")
file(GLOB_RECURSE LIB_FILES11 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Interfaces/Camera/include/*.hpp" "${LIB_DIR}/Interfaces/Camera/src/*.cpp")
file(GLOB_RECURSE LIB_FILES12 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Interfaces/Watchdog_Base/include/*.hpp" "${LIB_DIR}/Interfaces/Watchdog_Base/src/*.cpp")
file(GLOB_RECURSE LIB_FILES13 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/AnalysisTools/ImageAnalysis_OpenCV/include/*.hpp" "${LIB_DIR}/AnalysisTools/ImageAnalysis_OpenCV/src/*.cpp")
file(GLOB_RECURSE LIB_FILES14 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Message/include/*.hpp" "${LIB_DIR}/Objects/Message/src/*.cpp")

file(GLOB_RECURSE LIB_FILES15 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Image/include/*.hpp" "${LIB_DIR}/Objects/Image/src/*.cpp")
file(GLOB_RECURSE LIB_FILES16 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Logger/include/*.hpp" "${LIB_DIR}/Objects/Logger/src/*.cpp")

file(GLOB_RECURSE LIB_FILES17 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/PerformanceTools/StopWatch/include/*.hpp" "${LIB_DIR}/PerformanceTools/StopWatch/src/*.cpp")

set(MAIN_SOURCES
    Detector.cpp
 
)


#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# include python
include_directories(${PYTHON_INCLUDE_DIR})

find_library(WIRING_PI_LIB NAMES wiringPi)
# (4) Build the unit tests objects and link then with the app library
add_executable( ${APP_NAME} ${MAIN_SOURCES} ${COMP_FILES}  ${SRC_DIR}
${LIB_FILES1} ${LIB_FILES2} ${LIB_FILES3} ${LIB_FILES4} ${LIB_FILES5} ${LIB_FILES6} ${LIB_FILES7} ${LIB_FILES8} ${LIB_FILES9} ${LIB_FILES10} 
${LIB_FILES11} ${LIB_FILES12} ${LIB_FILES13} ${LIB_FILES14} ${LIB_FILES15} ${LIB_FILES16} ${LIB_FILES17} 
 )
target_link_libraries(   ${APP_NAME} ${APP_LIB_NAME} ${OpenCV_LIBS} ${PYTHON_LIBRARIES} ${WIRING_PI_LIB} Threads::Threads ${CURL_LIBRARIES} ${PQXX_LIB} ${PQ_LIB} ${raspicam_CV_LIBS}

)

