/*
 * mqtt_api_v2.hpp
 *
 *  Created on: May 31, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_MQTT_API_V2_HPP_
#define INCLUDE_MQTT_API_V2_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  mqtt_api_v2.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, mqtt_api_v2.hpp, is designed as:
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
 |  	Link:[ ], May 31, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], May 31, 2021
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |                              Includes                                        |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/
#include "../../../Objects/OTA/include/OTA.hpp"
#include "../../../RTOS/FreeRTOS/include/FreeRTOS.h"
#include <atomic>
#include <map>
#ifdef __ESP32__
#include <mqtt_client.h>
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

#ifndef __ESP32__
#define mqttclient int
#define mqttevent int
#else
#define mqttclient esp_mqtt_client_handle_t
#define mqttevent esp_mqtt_event_handle_t
#endif

#ifndef GLOBAL_MQTT_SERVER
#ifdef __ESP32__
#warning "GLOBAL_MQTT_SERVER Not defined, using 1.1.1.1"
#define GLOBAL_MQTT_SERVER ("1.1.1.1")
#else
// ignore warning since we do not have a mqtt compatable target
#define GLOBAL_MQTT_SERVER ("1.1.1.1")
#endif
#endif
/*------------------------------------------------------------------------------+
 |                               Class                                          |
 +------------------------------------------------------------------------------*/

class mqtt_api_v2
{
#ifdef __UNITTEST__
	friend class friend_mqtt_api_v2;
#endif
  public:
	mqtt_api_v2(const std::string& uri = GLOBAL_MQTT_SERVER);
	~mqtt_api_v2();

	general_err_t publish(const std::string& topic, const std::string& payload);
	FreeRTOS::Semaphore* subscribe(const std::string& topic);
	general_err_t subscribe(const std::string& topic,
							general_err_t (*callbackfunction)(const char* data,
															  const size_t data_length));

	general_err_t getData(std::string* str);

  private:
	static general_err_t handle_event(const char* topic, const size_t topic_length,
									  const char* data, const size_t data_length);
	std::string m_uri;
	general_err_t connect(void);
	general_err_t disconnect(void);

#ifdef __ESP32__

	static esp_err_t event_handler(mqttevent event);

	static void mqtt_event_handler(void* handler_args, esp_event_base_t base, int32_t event_id,
								   void* event_data);
	esp_mqtt_client_config_t m_mqtt_cfg;
#endif
};

/*------------------------------------------------------------------------------+
 |                           Unit Test Class                                    |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_mqtt_api_v2
{
  public:
	explicit friend_mqtt_api_v2(mqtt_api_v2* MQTT_API) : m_sensor{MQTT_API} {};

	~friend_mqtt_api_v2(){};
	auto handle_event(const char* topic, const size_t topic_length, const char* data,
					  const size_t data_length)
	{
		return m_sensor->handle_event(topic, topic_length, data, data_length);
	}

  private:
	mqtt_api_v2* m_sensor;
};
#endif

#endif /* INCLUDE_MQTT_API_V2_HPP_ */
