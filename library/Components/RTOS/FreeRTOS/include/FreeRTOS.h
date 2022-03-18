/*
 * FreeRTOS.h
 *
 *  Created on: Feb 24, 2017
 *      Author: kolban
 */

#ifndef MAIN_FREERTOS_H_
#define MAIN_FREERTOS_H_

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/
#ifdef __ESP32__
#include <pthread.h>
#include <stdint.h>
#include <string>

#include <freertos/FreeRTOS.h> // Include the base FreeRTOS definitions.
#include <freertos/queue.h> // Include the queue definitions.
#include <freertos/semphr.h> // Include the semaphore definitions.
#include <freertos/task.h> // Include the task definitions.
#endif
#include <iostream>

#ifndef __ESP32__
struct TaskHandle_t
{
};
#endif
/**
 * @brief Interface to %FreeRTOS functions.
 */
class FreeRTOS
{
  public:
	static void sleep(uint32_t ms);
	static void startTask(void task(void*), std::string taskName, void* param = nullptr,
						  int stackSize = 2048);
#ifdef __ESP32__
	static void deleteTask(TaskHandle_t pTask = nullptr);
#else
	static void deleteTask(TaskHandle_t pTask);
#endif
	static uint32_t getTimeSinceStart();

	class Semaphore
	{
	  public:
		Semaphore(const std::string& owner = "<Unknown>");
		~Semaphore();
		void give();
		void give(uint32_t value);
		void giveFromISR();
		void setName(const std::string& name);
		bool take(const std::string& owner = "<Unknown>");
		bool take(uint32_t timeoutMs, const std::string& owner = "<Unknown>");
		std::string toString();
		uint32_t wait(const std::string& owner = "<Unknown>");

	  private:
#ifdef __ESP32__
		SemaphoreHandle_t m_semaphore;
		pthread_mutex_t m_pthread_mutex;
#else
		int m_semaphore = 0;
		int m_pthread_mutex = 0;
#endif
		std::string m_name;
		std::string m_owner;
		uint32_t m_value;
		bool m_usePthreads;
	};

	class Queue
	{
	  public:
		// Queue();
		/**
		 * @brief Construct a new Queue object
		 *
		 * @param amount_of_items
		 * @param size_of_item  : use sizeof(ITEM_OF_INTEREST)
		 */
		explicit Queue(size_t amount_of_items, size_t size_of_item);
		~Queue();
		/**
		 * @brief Send data to the queue
		 * @param [in] item willing to send
		 * @param [in] delay willing to wait
		 */
		virtual int send(const void* const item_to_send, size_t delay);
		/**
		 * @brief Recieve data from the queue
		 * @param [out] buffer with recieved item
		 * @param [in] delay willing to wait
		 */
		int recieve(void* pvBuffer, size_t delay);

	  private:
#ifdef __ESP32__
		xQueueHandle m_handle = 0;
#else
		int m_handle = 0;
#endif
	};
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
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
	int send(const void* const item_to_send, size_t delay) override
	{
		// m_dataCalledWith = *(static_cast<const std::atomic<size_t>*>(item_to_send));
		m_hasBeenCalled = true;
		m_amountOfCalls++;
		return 0;
	}
};
#endif

#endif /* MAIN_FREERTOS_H_ */
