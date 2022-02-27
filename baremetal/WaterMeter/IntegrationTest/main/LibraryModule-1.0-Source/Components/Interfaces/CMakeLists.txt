
#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]
cmake_minimum_required(VERSION 3.18.4)


add_subdirectory(ActuatorBase)
add_subdirectory(ADCBase)
add_subdirectory(Camera)
add_subdirectory(ProtocolBase)
add_subdirectory(PWMBase)
add_subdirectory(QueryBase)
add_subdirectory(SensorBase)
add_subdirectory(WatchdogBase)
add_subdirectory(SensorControllerBase)




