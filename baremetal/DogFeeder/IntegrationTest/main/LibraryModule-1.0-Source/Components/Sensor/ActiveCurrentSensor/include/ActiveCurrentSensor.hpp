#ifndef _COMPONENTS_SENSOR_ACTIVECURRENTSENSOR_INCLUDE_ACTIVECURRENTSENSOR_HPP_
#define _COMPONENTS_SENSOR_ACTIVECURRENTSENSOR_INCLUDE_ACTIVECURRENTSENSOR_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  ActiveCurrentSensor.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-01-22
 |
 |  @brief  	   :  This class, ActiveCurrentSensor.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  @version       : 1.0
 |
 |  @bug  		   :   no known bugs
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/
#include "../../../Objects/ADC/include/ADC_API_ESP32.hpp"
#include "../../../Objects/Maintainer/include/Maintainer.hpp"
#include "../../../Objects/Timeservice/include/Timeservice.hpp"
#include "../../../Protocols/MQTT/include/MQTT_Message.hpp"
#include "../../../Protocols/MQTT/include/mqtt_api_v2.hpp"
#include "../../../RTOS/FreeRTOS/include/FreeRTOS.h"
#include "../../../RTOS/FreeRTOS/include/Task.h"
#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class ActiveCurrentSensor final : public Task
{
#ifdef __UNITTEST__
	friend class friend_ActiveCurrentSensor;
#endif
  public:
	ActiveCurrentSensor(const ADC_API_ESP32::config& adc_conf,
						const MQTT_Message::msg_conf_t& msg_conf);
	~ActiveCurrentSensor();
	void run(void* data) override;
	void activateQueue();

  private:
	general_err_t main_function(void);
	FreeRTOS::Queue m_queue;
	ADC_API_ESP32 m_adc;
	MQTT_Message m_msg;
	mqtt_api_v2 m_mqtt;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_ActiveCurrentSensor
{
  public:
	explicit friend_ActiveCurrentSensor(ActiveCurrentSensor* sensor) : m_sensor{sensor} {};
	~friend_ActiveCurrentSensor();

  private:
	ActiveCurrentSensor* m_sensor;
};
#endif

#endif //_COMPONENTS_SENSOR_ACTIVECURRENTSENSOR_INCLUDE_ACTIVECURRENTSENSOR_HPP_