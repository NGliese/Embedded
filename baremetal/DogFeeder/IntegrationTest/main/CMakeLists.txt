set(LIB_DIR "~/github/Embedded/library")

idf_component_register(SRC_DIRS "."									INCLUDE_DIRS "${LIB_DIR}/Global_Include/"
			SRC_DIRS  "./integration_test/"  						INCLUDE_DIRS "./integration_test/include" 
			SRC_DIRS  "${LIB_DIR}/Objects/ErrorHandler/src/"  		INCLUDE_DIRS "${LIB_DIR}/Objects/ErrorHandler/include/" 
			SRC_DIRS  "${LIB_DIR}/Objects/FaultHandler/src/"  		INCLUDE_DIRS "${LIB_DIR}/Objects/FaultHandler/include/" 
			SRC_DIRS  "${LIB_DIR}/Objects/Logger/src/"  			INCLUDE_DIRS "${LIB_DIR}/Objects/Logger/include/" 
			SRC_DIRS  "${LIB_DIR}/Objects/Timeservice/src/"  		INCLUDE_DIRS "${LIB_DIR}/Objects/Timeservice/include/"
			SRC_DIRS  "${LIB_DIR}/Objects/PWM/src/"  				INCLUDE_DIRS "${LIB_DIR}/Objects/PWM/include/"  
			SRC_DIRS  "${LIB_DIR}/Objects/ADC/src/"  				INCLUDE_DIRS "${LIB_DIR}/Objects/ADC/include/"  
			SRC_DIRS  "${LIB_DIR}/RTOS/FreeRTOS/src/"  				INCLUDE_DIRS "${LIB_DIR}/RTOS/FreeRTOS/include/" 
			SRC_DIRS  "${LIB_DIR}/Connector/WiFi/src/"  			INCLUDE_DIRS "${LIB_DIR}/Connector/WiFi/include/" 
			SRC_DIRS  "${LIB_DIR}/Protocols/MQTT/src/"  			INCLUDE_DIRS "${LIB_DIR}/Protocols/MQTT/include/" 
			SRC_DIRS  "${LIB_DIR}/Utility/utils/src/"  				INCLUDE_DIRS "${LIB_DIR}/Utility/utils/include/" 
			SRC_DIRS  "${LIB_DIR}/Interfaces/ProtocolBase/src/"  	INCLUDE_DIRS "${LIB_DIR}/Interfaces/ProtocolBase/include/" 
			SRC_DIRS  "${LIB_DIR}/Interfaces/SensorBase/src/"    	INCLUDE_DIRS "${LIB_DIR}/Interfaces/SensorBase/include/" 
			SRC_DIRS  "${LIB_DIR}/Interfaces/ADCBase/src/"    	    INCLUDE_DIRS "${LIB_DIR}/Interfaces/ADCBase/include/" 
			SRC_DIRS  "${LIB_DIR}/Interfaces/PWMBase/src/"    		INCLUDE_DIRS "${LIB_DIR}/Interfaces/PWMBase/include/" 
		INCLUDE_DIRS "")
