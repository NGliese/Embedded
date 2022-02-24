/*
 * WiFi_API.hpp
 *
 *  Created on: Feb 1, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_WIFI_API_INCLUDE_WIFI_API_HPP_
#define MAIN_COMPONENTS_WIFI_API_INCLUDE_WIFI_API_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  WiFi_API.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, WiFi_API.hpp, is designed as:
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

#include "../../../Objects/Timeservice/include/Timeservice.hpp"

#include <cstring>

#include "WiFi.h"
#include "WiFi_Event_Handler.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

struct wifi_conf_t
{
	std::string ssid;
	std::string password;
};

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class WiFi_API
{
#ifdef __UNITTEST__
	friend class friend_WiFi_API;
#endif
  public:
	WiFi_API();
	explicit WiFi_API(const wifi_conf_t& conf);
	~WiFi_API();
	general_err_t connect();
	general_err_t disconnect();

  private:
	wifi_conf_t m_conf;
#ifdef __ESP32__
	WiFi_Event_Handler m_handler;

	WiFi m_wifi;
#endif
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_WiFi_API
{
  public:
	explicit friend_WiFi_API(WiFi_API* WiFi_API) : m_sensor{WiFi_API} {};

	~friend_WiFi_API(){};

  private:
	WiFi_API* m_sensor;
};
#endif

#endif /* MAIN_COMPONENTS_WIFI_API_INCLUDE_WIFI_API_HPP_ */
