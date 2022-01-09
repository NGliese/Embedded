
#[[ 
We must always set the miminum required version
This will also explicit set the cmake behavior.
It is recommendend to use 3.17+ due to some changes (?)
]]
cmake_minimum_required(VERSION 3.18.4)

add_subdirectory(ADC)
add_subdirectory(ErrorHandler) # PORTABLE
add_subdirectory(FaultHandler)
add_subdirectory(Gpio)
add_subdirectory(Logger)
add_subdirectory(Maintainer) # ESP32 -- lets wait with this big component
add_subdirectory(Message) # PORTABLE
add_subdirectory(OTA) # ESP32
add_subdirectory(PWM)
add_subdirectory(QueryTools) # LINUX
add_subdirectory(Rulebase)
add_subdirectory(Timeservice) 
add_subdirectory(Watchdog) # PORTABLE
add_subdirectory(Json) # PORTABLE









