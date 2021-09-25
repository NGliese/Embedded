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
#include "../../../RTOS/FreeRTOS/include/FreeRTOS.h"

#include <atomic>

#ifdef __ESP32__
#include <mqtt_client.h>
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
#define mqttclient int
#define mqttevent int
#else
#define mqttclient esp_mqtt_client_handle_t
#define mqttevent esp_mqtt_event_handle_t
#endif



/*------------------------------------------------------------------------------+
 |                               Class                                          |
 +------------------------------------------------------------------------------*/

class mqtt_api_v2 {
#ifdef __UNITTEST__
    friend class friend_mqtt_api_v2;
#endif
public:
    mqtt_api_v2(const std::string & uri = GLOBAL_MQTT_SERVER);
    ~mqtt_api_v2();
    /**
     * function to publish a topic to the mqtt server, with a given payload
     * @param [in] const std::string& topic
     * @param [in] const std::string& payload
     * @return general_err_t
     */
    general_err_t publish(const std::string& topic,const std::string& payload);
    /**
     * function to subscribe to a given topic from the mqtt server
     * @attention the user can use the returned semaphore to look for new data
     *            if the semaphore is release at some point, it means that new data has
     *            arrived. (used for blocking)
     * @param [in] const std::string& topic
     * @return FreeRTOS::Semaphore*
     */
    FreeRTOS::Semaphore*  subscribe(const std::string& topic);
    /**
     * get the recived data from the subscribtion
     * @param [out] std::string * str
     * @return general_err_t
     */
    general_err_t getData(std::string * str);
private:
    std::string m_uri;
    general_err_t connect(void);
    general_err_t disconnect(void);



#ifdef __ESP32__


    static esp_err_t event_handler(mqttevent event);

    static void mqtt_event_handler(void *handler_args,esp_event_base_t base, int32_t event_id, void *event_data);
    esp_mqtt_client_config_t m_mqtt_cfg;
#endif

};


/*------------------------------------------------------------------------------+
 |                           Unit Test Class                                    |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_mqtt_api_v2 {
public:

    friend_mqtt_api_v2(mqtt_api_v2 * MQTT_API) : m_sensor{MQTT_API} { };

    ~friend_mqtt_api_v2(){};

private:
    mqtt_api_v2 * m_sensor;
};
#endif





#endif /* INCLUDE_MQTT_API_V2_HPP_ */
