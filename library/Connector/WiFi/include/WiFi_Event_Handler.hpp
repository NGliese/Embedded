/*
 * WiFi_Event_Handler.hpp
 *
 *  Created on: Feb 1, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_WIFI_API_INCLUDE_WIFI_EVENT_HANDLER_HPP_
#define MAIN_COMPONENTS_WIFI_API_INCLUDE_WIFI_EVENT_HANDLER_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  WiFi_Event_Handler.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, WiFi_Event_Handler.hpp, is designed as:
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
 |  	Link:[ ], Feb 1, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Feb 1, 2021
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

 #include "WiFiEventHandler.h"

#ifdef __ESP32__

#include <iostream>

#ifdef __ESP32__
#include <esp_system.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <nvs_flash.h>

#include <lwip/err.h>
#include <lwip/sys.h>
#include <esp_err.h>
#endif


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/



#ifdef __UNITTEST__
#define ERROR_CODE int
#define EVENT_BASE int
#else
#define ERROR_CODE esp_err_t
#define EVENT_BASE esp_event_base_t
#endif

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class WiFi_Event_Handler final : public WiFiEventHandler {
#ifdef __UNITTEST__
    friend class friend_WiFi_Event_Handler;
#endif
public:
    WiFi_Event_Handler() = default;
    ~WiFi_Event_Handler();
    esp_err_t apStaDisconnected(system_event_ap_stadisconnected_t info) override;
private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_WiFi_Event_Handler {
public:
    friend_WiFi_Event_Handler(){};
    friend_WiFi_Event_Handler(WiFi_Event_Handler * WiFi_Event_Handler) : m_sensor{WiFi_Event_Handler} { };

    ~friend_WiFi_Event_Handler(){};

private:
    WiFi_Event_Handler * m_sensor;
};
#endif


#endif


#endif /* MAIN_COMPONENTS_WIFI_API_INCLUDE_WIFI_EVENT_HANDLER_HPP_ */
