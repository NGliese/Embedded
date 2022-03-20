#ifndef _COMPONENTS_INTERFACES_SERVICEBASE_INCLUDE_SERVICEBASE_HPP_
#define _COMPONENTS_INTERFACES_SERVICEBASE_INCLUDE_SERVICEBASE_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  ServiceBase.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-06
 |
 |  @brief  	   :  This class, ServiceBase.hpp, is designed as:
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
#include "../../../Global_Include/Database_ID_Base.hpp"
#include "../../../Objects/ErrorHandler/include/ErrorCodeParser.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include "../../../Objects/Timeservice/include/Timeservice.hpp"

#include "../../../RTOS/FreeRTOS/include/FreeRTOS.h"
#include "../../../RTOS/FreeRTOS/include/Task.h"

#include "../../../Protocols/MQTT/include/MQTT_Message.hpp"
#include "../../../Protocols/MQTT/include/mqtt_api_v2.hpp"

#include "../../../Objects/Gpio/include/GPIO_API.hpp"

#include <atomic>
#include <iostream>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

template<typename BUFFER_TYPE, typename QUEUE_TYPE = FreeRTOS::Queue>
class ServiceBase : public Task
{
#ifdef __UNITTEST__
	friend class friend_ServiceBase;
#endif
  public:
	ServiceBase(size_t queue_size, size_t size_of_item, const BUFFER_TYPE& buffer,
				const db_id error_id)
		: m_queue{queue_size, size_of_item}, m_test_pin{}, m_buffer{buffer}, m_isActive{false},
		  m_error_id{error_id} {};
	virtual ~ServiceBase(){};
	inline const auto& isActive() const
	{
		return m_isActive;
	}
	inline auto& getQueue()
	{
		return m_queue;
	}

  protected:
	/**
	 * @brief Main function for the derived class to work in
	 *        It is expected that the function is a single-run function
	 *        And that it should not be blocking
	 *
	 * @return general_err_t
	 */
	virtual general_err_t mainFunction() = 0;
	/**
	 * @brief Set the Is Active object
	 *
	 * @param isActive
	 */

	virtual inline void setIsActive(bool isActive)
	{
		m_isActive = isActive;
	}
	/**
	 * @brief Function to post data to database
	 *
	 * @param message
	 * @param topic
	 * @return general_err_t
	 */
	general_err_t postData(const MQTT_Message& message, const std::string& topic = "mqtt/burst_msg")
	{
		return m_mqtt.publish(topic, message.toString());
	}

	/**
	 * @brief loop for the service
	 *        We are waiting "forever" on a queue recieve
	 *        When we recieve something we will call the mainFunction()
	 *        Which should be a single-end run for the derived class
	 *        if any error happends it will be reported online.
	 *
	 * @param data N/A
	 */
	void run(void* data) override
	{
		size_t recived;
		constexpr size_t WAIT_FOREVER = (10000000UL);
		for(;;)
		{
			if(m_queue.recieve(&recived, WAIT_FOREVER))
			{
				// if the queue returns 1 it means some error happend
				// most likely the wait-time has passed.
				// we will simply just skip the loop.
				continue;
			}
			setIsActive(true);
			auto err = mainFunction();
			{
				if(err != GE_OK)
				{
					ErrorCodeParser::postToMqtt(
						m_error_id, err, "Some error happend in the execution of main function");
				}
			}
			setIsActive(false);
		}
	}

  protected:
	QUEUE_TYPE m_queue;
	GPIO_API m_test_pin;
	const BUFFER_TYPE& m_buffer;

  private:
	std::atomic<bool> m_isActive;

	mqtt_api_v2 m_mqtt;
	db_id m_error_id;
};

/*------------------------------------------------------------------------------+
 |   		 				 HARDWARE Test Class               		            |
 +------------------------------------------------------------------------------*/
template<typename BUFFER_TYPE, typename QUEUE_TYPE = FreeRTOS::Queue>
class ServiceBase_HW_TEST : public ServiceBase<BUFFER_TYPE, QUEUE_TYPE>
{
  public:
	ServiceBase_HW_TEST(size_t queue_size, size_t size_of_item, const MQTT_Message& buffer,
						const db_id error_id, GPIO_HAL::pin test_pin)
		: ServiceBase<BUFFER_TYPE, QUEUE_TYPE>(queue_size, size_of_item, buffer, error_id),
		  m_test_pin{test_pin}
	{
		m_test_pin.setToOutput();
	};
	~ServiceBase_HW_TEST(){};

  private:
	inline void setIsActive(bool isActive) override
	{
		ServiceBase<BUFFER_TYPE, QUEUE_TYPE>::setIsActive(isActive); // call the base function
		isActive == true ? m_test_pin.setHigh() : m_test_pin.setLow();
		std::cout << " setisActive to : "
				  << (isActive == true ? "m_test_pin.setHigh()" : "m_test_pin.setLow()") << "\n";
	}
	GPIO_API m_test_pin;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_ServiceBase
{
  public:
	explicit friend_ServiceBase(ServiceBase<MQTT_Message>* sensor) : m_sensor{sensor} {};
	~friend_ServiceBase(){};

  private:
	ServiceBase<MQTT_Message>* m_sensor;
};

class service_MOCK : public ServiceBase<MQTT_Message, Queue_MOCK>
{
  public:
	service_MOCK(size_t queue_size, size_t size_of_item, const MQTT_Message& buffer,
				 const db_id error_id)
		: ServiceBase(queue_size, size_of_item, buffer, error_id){};
	~service_MOCK(){};

	auto hasBeenCalled()
	{
		return m_queue.hasBeenCalled();
	}
	auto amountOfCalls()
	{
		return m_queue.amountOfCalls();
	}

  private:
	general_err_t mainFunction() override
	{
#ifdef DEBUG
		LOG_PRINT_INFO(LOG_TAG, ">> DataBroker::fcn >> ");
#endif
		// Executable code:

#ifdef DEBUG
		LOG_PRINT_INFO(LOG_TAG, "<<  DataBroker::fcn << ");
#endif

		return GE_OK;
	}
};

class service_SIMPLE : public ServiceBase<MQTT_Message>
{
  public:
	service_SIMPLE(size_t queue_size, size_t size_of_item, const MQTT_Message& buffer,
				   const db_id error_id)
		: ServiceBase(queue_size, size_of_item, buffer, error_id){};
	~service_SIMPLE(){};

  private:
	general_err_t mainFunction() override
	{
#ifdef DEBUG
		LOG_PRINT_INFO(LOG_TAG, ">> DataBroker::fcn >> ");
#endif
		// Executable code:

#ifdef DEBUG
		LOG_PRINT_INFO(LOG_TAG, "<<  DataBroker::fcn << ");
#endif

		return GE_OK;
	}
};

#endif

#endif //_COMPONENTS_INTERFACES_SERVICEBASE_INCLUDE_SERVICEBASE_HPP_