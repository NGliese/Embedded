/*
 * Task.h
 *
 *  Created on: Mar 4, 2017
 *      Author: kolban
 */

#ifndef COMPONENTS_CPP_UTILS_TASK_H_
#define COMPONENTS_CPP_UTILS_TASK_H_
/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/
#ifdef __ESP32__
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#else
#define BaseType_t uint16_t
#define xTaskHandle uint16_t
#endif
#include <string>
/**
 * @brief Encapsulate a runnable task.
 *
 * This class is designed to be subclassed with the method:
 *
 * @code{.cpp}
 * void run(void *data) { ... }
 * @endcode
 *
 * For example:
 *
 * @code{.cpp}
 * class CurlTestTask : public Task {
 *    void run(void *data) {
 *       // Do something
 *    }
 * };
 * @endcode
 *
 * implemented.
 */

class Task
{
  public:
	Task(const std::string& taskName = "Task", const uint16_t& stackSize = 10000,
		 const uint8_t& priority = 5);
	virtual ~Task();
	void setStackSize(uint16_t stackSize);
	void setPriority(uint8_t priority);
	void setName(const std::string& name);
	void setCore(BaseType_t coreId);
	void start(void* taskData = nullptr);
	void stop();
	/**
	 * @brief Body of the task to execute.
	 *
	 * This function must be implemented in the subclass that represents the actual task to run.
	 * When a task is started by calling start(), this is the code that is executed in the
	 * newly created task.
	 * WHY IS IT NOT PRIVATE???
	 *
	 * @param [in] data The data passed in to the newly started task.
	 */
	virtual void run(void* data) = 0; // Make run pure virtual
	void delay(int ms);

  private:
	xTaskHandle m_handle;
	static void runTask(void* pTaskInstance);
	std::string m_taskName;
	uint16_t m_stackSize;
	uint8_t m_priority;
	void* m_taskData;
	BaseType_t m_coreId;
};

#endif /* COMPONENTS_CPP_UTILS_TASK_H_ */
