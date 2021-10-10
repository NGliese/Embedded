## 
## Library directory addon
##



cmake_minimum_required(VERSION 3.13)

# assuming 1 level lower than lib/
set(LIB_DIR ../../../)


#### GLOBAL INCLUDE ####
file(GLOB_RECURSE LIB_FILES0 RELATIVE  ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Global_Include/*.h") 

#### UTILITY
file(GLOB_RECURSE LIB_FILES1 RELATIVE  ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Utility/utils/include/*.h" "${LIB_DIR}/Utility/utils/src/*.cpp") 
file(GLOB_RECURSE LIB_FILES2 RELATIVE  ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Utility/Serialized/include/*.h" "${LIB_DIR}/Utility/Serialized/src/*.cpp") 


#### PROTOCOLS #####
file(GLOB_RECURSE LIB_FILES3 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Protocols/HTTP/include/*.h" "${LIB_DIR}/Protocols/HTTP/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESPR1 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Protocols/MQTT/include/*.h" "${LIB_DIR}/Protocols/MQTT/src/*.cpp") 


#### RTOS #####
file(GLOB_RECURSE LIB_FILESRT1 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/RTOS/FreeRTOS/include/*.h" "${LIB_DIR}/RTOS/FreeRTOS/src/*.cpp") 

#### OBJECTS ####
file(GLOB_RECURSE LIB_FILES4 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/ErrorHandler/include/*.h" "${LIB_DIR}/Objects/ErrorHandler/src/*.cpp") 
file(GLOB_RECURSE LIB_FILES5 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Message/include/*.h" "${LIB_DIR}/Objects/Message/src/*.cpp") 
file(GLOB_RECURSE LIB_FILES6 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Timeservice/include/*.h" "${LIB_DIR}/Objects/Timeservice/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESOB1 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Logger/include/*.h" "${LIB_DIR}/Objects/Logger/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESOB2 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/Gpio/include/*.h" "${LIB_DIR}/Objects/Gpio/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESOB3 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/FaultHandler/include/*.h" "${LIB_DIR}/Objects/FaultHandler/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESOB4 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/ADC/include/*.h" "${LIB_DIR}/Objects/ADC/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESOB5 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Objects/PWM/include/*.h" "${LIB_DIR}/Objects/PWM/src/*.cpp") 
#### INTERFACES ####
file(GLOB_RECURSE LIB_FILES7 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Interfaces/Camera/include/*.h" "${LIB_DIR}/Interfaces/Camera/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESIN1 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Interfaces/PWMBase/include/*.h" "${LIB_DIR}/Interfaces/PWMBase/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESIN2 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Interfaces/ADCBase/include/*.h" "${LIB_DIR}/Interfaces/ADCBase/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESIN3 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Interfaces/SensorBase/include/*.h" "${LIB_DIR}/Interfaces/SensorBase/src/*.cpp") 
file(GLOB_RECURSE LIB_FILESIN4 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Interfaces/ActuatorBase/include/*.h" "${LIB_DIR}/Interfaces/ActuatorBase/src/*.cpp") 

#### ANALYSIS TOOLS ####
file(GLOB_RECURSE LIB_FILES8 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/AnalysisTools/ImageAnalysis_OpenCV/include/*.h" "${LIB_DIR}/AnalysisTools/ImageAnalysis_OpenCV/src/*.cpp") 


#### SENSORS ####
file(GLOB_RECURSE LIB_FILES9 RELATIVE ${CMAKE_SOURCE_DIR} CONFIGURE_DEPENDS  "${LIB_DIR}/Sensor/RpiCamV2/include/*.h" "${LIB_DIR}/Sensor/RpiCamV2/src/*.cpp") 

set(source_list 
${LIB_FILES1} ${LIB_FILES2} ${LIB_FILES3} ${LIB_FILES4} ${LIB_FILES5} ${LIB_FILES6} ${LIB_FILES7} ${LIB_FILES8} ${LIB_FILES9} ${LIB_FILESPR1} ${LIB_FILESOB1} ${LIB_FILESRT1}
${LIB_FILESOB2} ${LIB_FILESIN1} ${LIB_FILESIN2} ${LIB_FILESIN3} ${LIB_FILESOB3} ${LIB_FILESOB4} ${LIB_FILESIN4} ${LIB_FILESOB5}
)



#message("At last, the source_list is: \"${source_list}\"")

