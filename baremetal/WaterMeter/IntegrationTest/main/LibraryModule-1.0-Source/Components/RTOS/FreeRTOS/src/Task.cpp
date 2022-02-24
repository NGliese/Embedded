/*
 * Task.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: kolban
 */

#include "../include/Task.h"

// static char tag[] = "Task";

/**
 * @brief Create an instance of the task class.
 *
 * @param [in] taskName The name of the task to create.
 * @param [in] stackSize The size of the stack.
 * @return N/A.
 */
Task::Task(const std::string& taskName, const uint16_t& stackSize, const uint8_t& priority)
	: m_taskName{taskName}, m_stackSize{stackSize}, m_priority{priority}, m_taskData{nullptr}
{
#ifdef __ESP32__
	m_handle = nullptr;
	m_coreId = tskNO_AFFINITY;
#else
	m_coreId = 0;
	m_handle = 0;
#endif
} // Task

Task::~Task() {} // ~Task

/**
 * @brief Suspend the task for the specified milliseconds.
 *
 * @param [in] ms The delay time in milliseconds.
 * @return N/A.
 */

void Task::delay(int ms)
{
#ifdef __ESP32__
	::vTaskDelay(ms / portTICK_PERIOD_MS);
#endif
} // delay

/**
 * Static class member that actually runs the target task.
 *
 * The code here will run on the task thread.
 * @param [in] pTaskInstance The task to run.
 */
void Task::runTask(void* pTaskInstance)
{
	Task* pTask = static_cast<Task*>(pTaskInstance);
	pTask->run(pTask->m_taskData);
	pTask->stop();
} // runTask

/**
 * @brief Start an instance of the task.
 *
 * @param [in] taskData Data to be passed into the task.
 * @return N/A.
 */
void Task::start(void* taskData)
{
#ifdef __ESP32__
	if(m_handle != nullptr)
	{
	}
	m_taskData = taskData;

	::xTaskCreatePinnedToCore((TaskFunction_t)&runTask, m_taskName.c_str(), m_stackSize, this,
							  m_priority, &m_handle, m_coreId);
#endif
} // start

/**
 * @brief Stop the task.
 *
 * @return N/A.
 */
void Task::stop()
{
#ifdef __ESP32__
	if(m_handle == nullptr)
	{
		return;
	}
	xTaskHandle temp = m_handle;
	m_handle = nullptr;

	::vTaskDelete(temp);
#endif
} // stop

/**
 * @brief Set the stack size of the task.
 *
 * @param [in] stackSize The size of the stack for the task.
 * @return N/A.
 */
void Task::setStackSize(uint16_t stackSize)
{
	m_stackSize = stackSize;
} // setStackSize

/**
 * @brief Set the priority of the task.
 *
 * @param [in] priority The priority for the task.
 * @return N/A.
 */
void Task::setPriority(uint8_t priority)
{
	m_priority = priority;
} // setPriority

/**
 * @brief Set the name of the task.
 *
 * @param [in] name The name for the task.
 * @return N/A.
 */
void Task::setName(const std::string& name)
{
	m_taskName = name;
} // setName

/**
 * @brief Set the core number the task has to be executed on.
 * If the core number is not set, tskNO_AFFINITY will be used
 *
 * @param [in] coreId The id of the core.
 * @return N/A.
 */
void Task::setCore(BaseType_t coreId)
{
	m_coreId = coreId;
}
