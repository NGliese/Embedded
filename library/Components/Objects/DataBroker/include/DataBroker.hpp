#ifndef _COMPONENTS_OBJECTS_DATABROKER_INCLUDE_DATABROKER_HPP_
#define _COMPONENTS_OBJECTS_DATABROKER_INCLUDE_DATABROKER_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  DataBroker.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-01
 |
 |  @brief  	   :  This class, DataBroker.hpp, is designed as:
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

#include "../../../Interfaces/SensorControllerBase/include/SensorControllerBase.hpp"
#include "../../../Interfaces/ServiceBase/include/ServiceBase.hpp"
#include "../../../Objects/Timeservice/include/Timeservice.hpp"
#include "../../../RTOS/FreeRTOS/include/FreeRTOS.h"
#include "../../../RTOS/FreeRTOS/include/Task.h"
#include <algorithm> // For std::for_each()
#include <atomic>
#include <iostream>
#include <vector>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
class DataBroker final : public Task
{
#ifdef __UNITTEST__
	friend class friend_DataBroker;
#endif
  public:
	DataBroker(const size_t delay_ms, SensorControllerBase& sensor)
		: m_delay_ms{delay_ms}, m_sensor{sensor} {};
	~DataBroker(){};
	general_err_t addService(ServiceBase<MQTT_Message>* service);
	inline const MQTT_Message& getSafeBuffer()
	{
		return m_sensor.getSafeBuffer();
	}

  private:
	void run(void* data) override;
	general_err_t main_function();
	const size_t m_delay_ms;
	SensorControllerBase& m_sensor;
	std::vector<ServiceBase<MQTT_Message>*> m_service_array;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_DataBroker
{
  public:
	explicit friend_DataBroker(DataBroker* sensor) : m_sensor{sensor} {};
	~friend_DataBroker(){};
	auto runMain()
	{
		return m_sensor->main_function();
	}

  private:
	DataBroker* m_sensor;
};

#endif

#endif //_COMPONENTS_OBJECTS_DATABROKER_INCLUDE_DATABROKER_HPP_