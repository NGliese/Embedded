/*
 * MQTT_Message.hpp
 *
 *  Created on: Feb 3, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_DATA_PACKAGE_INCLUDE_MQTT_MESSAGE_HPP_
#define MAIN_COMPONENTS_DATA_PACKAGE_INCLUDE_MQTT_MESSAGE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  MQTT_Message.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, MQTT_Message.hpp, is designed as:
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
 |  	Link:[ ], Feb 3, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Feb 3, 2021
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
#include "../../../Global_Include/Database_ID_Base.hpp" // db id

#include "../../../Objects/Timeservice/include/Timeservice.hpp"

#include "../../../RTOS/FreeRTOS/include/FreeRTOS.h"

#include "../../../Utility/utils/include/utils.h"

#include "../../../Objects/Logger/include/Logger.hpp"

#include <utility>
#include <vector>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class MQTT_Message
{
#ifdef __UNITTEST__
	friend class friend_MQTT_Message;
#endif
  public:
	struct msg_conf_t
	{
		db_id entity_id;
		size_t buffer_size;
	};
	explicit MQTT_Message(const uint64_t& entity_id, const size_t& buffer_size = 1);
	explicit MQTT_Message(const msg_conf_t& conf);
	~MQTT_Message();
	general_err_t addData(const uint64_t& data);
	general_err_t addData(const uint64_t& time, const uint64_t& data);
	general_err_t addData_f(const float& data);
	inline bool isEmpty(void) const
	{
		return m_data.empty();
	};
	const std::string toString(void); // copy
	general_err_t clear(void);
	auto getBufferSize(void)
	{
		return m_data.size();
	}

	static MQTT_Message construct(const std::string& str);
	general_err_t append(const MQTT_Message& msg);
	const auto& getData(void) const
	{
		return m_data;
	};

  private:
	const uint64_t m_entity_id;
	const size_t m_buffer_size;
	std::vector<std::pair<uint64_t, uint64_t>> m_data;
#ifdef __ESP32__
	FreeRTOS::Semaphore m_semaphore;
#else
	std::string m_semaphore; // dirty fix for ctor
#endif
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_MQTT_Message
{
  public:
	explicit friend_MQTT_Message(MQTT_Message* MQTT_Message) : m_sensor{MQTT_Message} {};

	~friend_MQTT_Message(){};
	std::vector<std::pair<uint64_t, uint64_t>>* getbuffer()
	{
		return &(m_sensor->m_data);
	}
	auto getID(void)
	{
		return m_sensor->m_entity_id;
	}

  private:
	MQTT_Message* m_sensor;
};
#endif

#endif /* MAIN_COMPONENTS_DATA_PACKAGE_INCLUDE_MQTT_MESSAGE_HPP_ */
