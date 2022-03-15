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
	general_err_t addQueue(FreeRTOS::Queue* queue);
	general_err_t addServiceFlag(std::atomic<bool>* flag);

  private:
	void run(void* data) override;
	general_err_t main_function();
	general_err_t pushQueues();
	std::vector<FreeRTOS::Queue*> m_queue_array;
	std::vector<std::atomic<bool>*> m_flag_array;
	const size_t m_delay_ms;
	SensorControllerBase& m_sensor;
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
	auto getQueueSize()
	{
		return m_sensor->m_queue_array.size();
	}
	auto runMain()
	{
		return m_sensor->main_function();
	}

  private:
	DataBroker* m_sensor;
};

class Queue_MOCK : public FreeRTOS::Queue
{
  private:
	/* data */
	bool m_hasBeenCalled = false;
	size_t m_amountOfCalls = 0;
	size_t m_dataCalledWith = 0;

  public:
	Queue_MOCK(size_t amount_of_items, size_t size_of_item)
		: FreeRTOS::Queue(amount_of_items, size_of_item){};
	~Queue_MOCK(){};
	auto hasBeenCalled()
	{
		return m_hasBeenCalled;
	}
	auto amountOfCalls()
	{
		return m_amountOfCalls;
	}
	auto dataCalledWith()
	{
		return m_dataCalledWith;
	}
	int send(const void* const item_to_send, size_t delay) override
	{
		m_dataCalledWith = *(static_cast<const std::atomic<size_t>*>(item_to_send));
		m_hasBeenCalled = true;
		m_amountOfCalls++;
	}
};

#endif

#endif //_COMPONENTS_OBJECTS_DATABROKER_INCLUDE_DATABROKER_HPP_