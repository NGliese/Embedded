/*
 * hal_mqtt_log.hpp
 *
 *  Created on: Jun 14, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_HAL_MQTT_LOG_HPP_
#define INCLUDE_HAL_MQTT_LOG_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  hal_mqtt_log.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, hal_mqtt_log.hpp, is designed as:
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
 |  	Link:[ ], Jun 14, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jun 14, 2021
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

#include "../../../Protocols/MQTT/include/mqtt_api_v2.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class hal_mqtt_log
{
#ifdef __UNITTEST__
	friend class friend_hal_mqtt_log;
#endif
  public:
	static void write(const std::string& str);

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_hal_mqtt_log
{
  public:
	explicit friend_hal_mqtt_log(hal_mqtt_log* hal_mqtt_log) : m_sensor{hal_mqtt_log} {};

	~friend_hal_mqtt_log(){};

  private:
	hal_mqtt_log* m_sensor;
};
#endif

#endif /* INCLUDE_HAL_MQTT_LOG_HPP_ */
