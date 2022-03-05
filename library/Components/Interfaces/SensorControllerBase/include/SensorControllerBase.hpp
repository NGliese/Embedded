#ifndef _COMPONENTS_INTERFACES_SENSORCONTROLLERBASE_INCLUDE_SENSORCONTROLLERBASE_HPP_
#define _COMPONENTS_INTERFACES_SENSORCONTROLLERBASE_INCLUDE_SENSORCONTROLLERBASE_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  SensorControllerBase.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-02-27
 |
 |  @brief  	   :  This class, SensorControllerBase.hpp, is designed as:
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

#include "../../../Objects/ErrorHandler/include/ErrorCodeParser.hpp"

#include "../../../Protocols/MQTT/include/MQTT_Message.hpp"
#include "../../../Protocols/MQTT/include/mqtt_api_v2.hpp"
#include "../../../RTOS/FreeRTOS/include/FreeRTOS.h"
#include "../../../RTOS/FreeRTOS/include/Task.h"
#include <atomic>
#include <iostream>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class SensorControllerBase : public Task
{
#ifdef __UNITTEST__
	friend class friend_SensorControllerBase;
#endif
  public:
	struct init_conf
	{
		MQTT_Message::msg_conf_t buffer_raw_conf;
		MQTT_Message::msg_conf_t buffer_external_conf;
		uint64_t task_delay;
		db_id error_code_id;
	};

	SensorControllerBase(const init_conf& conf)
		: m_buffer_raw{conf.buffer_raw_conf}, m_buffer_external{conf.buffer_external_conf},
		  m_delay{conf.task_delay}, m_error_id{conf.error_code_id} {};
	virtual ~SensorControllerBase(){};

	inline void setWantDataTrue()
	{
		setWantData(true);
		setDataReady(false);
	}

	inline const auto& getSafeBuffer()
	{
		return m_buffer_external;
	}
	inline const bool isDataReady()
	{
		return m_data_ready_flag;
	}

  protected:
	inline void setDataReadyTrue()
	{
		setDataReady(true);
		setWantData(false);
	}

	general_err_t postData(const MQTT_Message& message,
						   const std::string& topic = "mqtt/burst_msg");
	inline void postError(const general_err_t& err, const std::string& error_message)
	{
		ErrorCodeParser::postToMqtt(m_error_id, err, error_message);
	}
	virtual general_err_t main_function() = 0;
	MQTT_Message m_buffer_raw;
	MQTT_Message m_buffer_external;
	std::atomic<bool> m_want_data_flag;
	std::atomic<bool> m_data_ready_flag;
	const uint64_t m_delay;
	const db_id m_error_id;

  private:
	inline void setDataReady(bool flag)
	{
		m_data_ready_flag = flag;
	}
	inline void setWantData(bool flag)
	{
		m_want_data_flag = flag;
	}

	void run(void* data) override;

	mqtt_api_v2 m_mqtt;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_SensorControllerBase
{
  public:
	explicit friend_SensorControllerBase(SensorControllerBase* sensor) : m_sensor{sensor} {};
	~friend_SensorControllerBase();

  private:
	SensorControllerBase* m_sensor;
};
#endif

#endif //_COMPONENTS_INTERFACES_SENSORCONTROLLERBASE_INCLUDE_SENSORCONTROLLERBASE_HPP_