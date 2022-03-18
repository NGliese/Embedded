
#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]
cmake_minimum_required(VERSION 3.18.4)
add_subdirectory(Actuator) 
add_subdirectory(AnalysisTools) #

add_subdirectory(Connector)
add_subdirectory(Controller)

add_subdirectory(Interfaces)

add_subdirectory(Objects)

add_subdirectory(Protocols)

add_subdirectory(RTOS)

add_subdirectory(Sensor)
add_subdirectory(Service)

add_subdirectory(User)

add_subdirectory(Utility) 










