/*
 * Maintainer.hpp
 *
 *  Created on: Sep 20, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_MAINTAINER_HPP_
#define INCLUDE_MAINTAINER_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Maintainer.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Maintainer.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Datasheet Awareness              		        |
 +------------------------------------------------------------------------------+
 |
 |
 |  Datasheet Awareness 1):
 |  	Link:[ ], Sep 20, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Sep 20, 2021
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/
#include "../../../Objects/FaultHandler/include/Fault_Handler.hpp"

#include "../../../Connector/WiFi/include/WiFi_API.hpp"
#include "../../../RTOS/FreeRTOS/include/Task.h"

#include "../../../Objects/OTA/include/OTA.hpp"
#include "../../../Protocols/MQTT/include/mqtt_api_v2.hpp"

#include <vector>

// this macro is placed in the cmake files of the project
#ifndef MQTT_OTA_TOPIC
#define MQTT_OTA_TOPIC ("mqtt/test")
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Maintainer final : public Task
{
#ifdef __UNITTEST__
	friend class friend_Maintainer;
#endif
  public:
	explicit Maintainer(const wifi_conf_t& wifi_conf, size_t delay_sec = 60, int priority = 2);
	~Maintainer();
	static general_err_t install_system_test_fuction(bool (*callbackfunction)(void));
	void run(void* data) override;

	/**
	 * This function might be thread blocking if OTA update is in progress
	 * We want to use this function to test for OTA updates, if an update is in progress
	 * we want to make sure no other task is running.
	 *
	 * @attention : might be a blocking call
	 *
	 */
	static general_err_t checkOTAUpdate(void);
	/**
	 * This function will return the status of the OTA_Update_flag, it is static
	 * because we want to be able to call this function as a standard wait
	 */
	static bool isOTAUpdateStarted(void)
	{
		return OTA::isUpdateStarted();
	}

  private:
	general_err_t periodic_restart(void);
	general_err_t check_system_functions(void);
	Fault_Handler m_faulthandler;
	uint64_t start_time;
	size_t m_delay_sec;

	WiFi_API m_wifi;

#ifdef __WITH_OTA__
	mqtt_api_v2 m_mqtt;
#endif
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Maintainer
{
  public:
	explicit friend_Maintainer(Maintainer* Maintainer) : m_sensor{Maintainer} {};
	~friend_Maintainer(){};
	auto check_sys(void)
	{
		return m_sensor->check_system_functions();
	};

  private:
	Maintainer* m_sensor;
};

#endif

#endif /* INCLUDE_MAINTAINER_HPP_ */
