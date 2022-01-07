/*
 * FreeRTOS.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: kolban
 */

#include "../include/FreeRTOS.h"
#ifdef __ESP32__
#include <freertos/FreeRTOS.h> // Include the base FreeRTOS definitions
#include <freertos/semphr.h> // Include the semaphore definitions
#include <freertos/task.h> // Include the task definitions
#include <iomanip>
#include <sstream>
#include <string>
#endif
static const char* LOG_TAG = "FreeRTOS";

/**
 * Sleep for the specified number of milliseconds.
 * @param[in] ms The period in milliseconds for which to sleep.
 */
void FreeRTOS::sleep(uint32_t ms)
{
#ifdef __ESP32__
	::vTaskDelay(ms / portTICK_PERIOD_MS);
#endif
} // sleep

/**
 * Start a new task.
 * @param[in] task The function pointer to the function to be run in the task.
 * @param[in] taskName A string identifier for the task.
 * @param[in] param An optional parameter to be passed to the started task.
 * @param[in] stackSize An optional paremeter supplying the size of the stack in which to run the
 * task.
 */
void FreeRTOS::startTask(void task(void*), std::string taskName, void* param, int stackSize)
{
#ifdef __ESP32__
	::xTaskCreate(task, taskName.data(), stackSize, param, 5, NULL);
#endif
} // startTask

/**
 * Delete the task.
 * @param[in] pTask An optional handle to the task to be deleted.  If not supplied the calling task
 * will be deleted.
 */
void FreeRTOS::deleteTask(TaskHandle_t pTask)
{
#ifdef __ESP32__
	::vTaskDelete(pTask);
#endif
} // deleteTask

/**
 * Get the time in milliseconds since the %FreeRTOS scheduler started.
 * @return The time in milliseconds since the %FreeRTOS scheduler started.
 */
uint32_t FreeRTOS::getTimeSinceStart()
{
#ifdef __ESP32__
	return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
#else
	return 0;
#endif

} // getTimeSinceStart

/*
 * 	public:
		Semaphore(std::string = "<Unknown>");
		~Semaphore();
		void give();
		void take(std::string owner="<Unknown>");
		void take(uint32_t timeoutMs, std::string owner="<Unknown>");
	private:
		SemaphoreHandle_t m_semaphore;
		std::string m_name;
		std::string m_owner;
	};
 *
 */

/**
 * @brief Wait for a semaphore to be released by trying to take it and
 * then releasing it again.
 * @param [in] owner A debug tag.
 * @return The value associated with the semaphore.
 */
uint32_t FreeRTOS::Semaphore::wait(const std::string& owner)
{
#ifdef __ESP32__
	ESP_LOGV(LOG_TAG, ">> wait: Semaphore waiting: %s for %s", toString().c_str(), owner.c_str());

	if(m_usePthreads)
	{
		pthread_mutex_lock(&m_pthread_mutex);
	}
	else
	{
		xSemaphoreTake(m_semaphore, portMAX_DELAY);
		//	xSemaphoreTake(m_semaphore,  3000/portTICK_PERIOD_MS);
	}

	m_owner = owner;

	if(m_usePthreads)
	{
		pthread_mutex_unlock(&m_pthread_mutex);
	}
	else
	{
		xSemaphoreGive(m_semaphore);
	}

	ESP_LOGV(LOG_TAG, "<< wait: Semaphore released: %s", toString().c_str());
	m_owner = std::string("<N/A>");
#endif
	return m_value;
} // wait

FreeRTOS::Semaphore::Semaphore(const std::string& name)
	: m_name{name}, m_owner{"<N/A>"}, m_value{0}, m_usePthreads{false}
{
#ifdef __ESP32__
	if(m_usePthreads)
	{
		pthread_mutex_init(&m_pthread_mutex, nullptr);
	}
	else
	{
		//	m_semaphore = xSemaphoreCreateMutex();
		/*
		 * apperently a bug has been happening in the FreeRTOS due to Mutex, so maybe binary
		 * semaphore is acceptable, -> usually semaphore is used as a single lock, so why not?
		 * 190813-bug, can binary work? :: https://github.com/espressif/arduino-esp32/issues/2723
		 */
		m_semaphore = xSemaphoreCreateBinary();
	}
#endif
}

FreeRTOS::Semaphore::~Semaphore()
{
#ifdef __ESP32__
	if(m_usePthreads)
	{
		pthread_mutex_destroy(&m_pthread_mutex);
	}
	else
	{
		vSemaphoreDelete(m_semaphore);
	}
#endif
}

/**
 * @brief Give a semaphore.
 * The Semaphore is given.
 */
void FreeRTOS::Semaphore::give()
{
#ifdef __ESP32__
	ESP_LOGV(LOG_TAG, "Semaphore giving: %s", toString().c_str());
	if(m_usePthreads)
	{
		pthread_mutex_unlock(&m_pthread_mutex);
	}
	else
	{
		xSemaphoreGive(m_semaphore);
	}
#endif

	m_owner = std::string("<N/A>");
} // Semaphore::give

/**
 * @brief Give a semaphore.
 * The Semaphore is given with an associated value.
 * @param [in] value The value to associate with the semaphore.
 */
void FreeRTOS::Semaphore::give(uint32_t value)
{
	m_value = value;
	give();
} // give

/**
 * @brief Give a semaphore from an ISR.
 */
void FreeRTOS::Semaphore::giveFromISR()
{
#ifdef __ESP32__
	BaseType_t higherPriorityTaskWoken;
	if(m_usePthreads)
	{
		assert(false); // @suppress("Function cannot be resolved") // @suppress("Invalid arguments")
	}
	else
	{
		xSemaphoreGiveFromISR(m_semaphore, &higherPriorityTaskWoken);
	}
#endif
} // giveFromISR

/**
 * @brief Take a semaphore.
 * Take a semaphore and wait indefinitely.
 * @param [in] owner The new owner (for debugging)
 * @return True if we took the semaphore.
 */
bool FreeRTOS::Semaphore::take(const std::string& owner)
{
#ifdef __ESP32__
	ESP_LOGV(LOG_TAG, "Semaphore taking: %s for %s", toString().c_str(), owner.c_str());
	bool rc = false;
	if(m_usePthreads)
	{
		pthread_mutex_lock(&m_pthread_mutex);
	}
	else
	{
		rc = ::xSemaphoreTake(m_semaphore, portMAX_DELAY);
	}
	m_owner = owner;
	if(rc)
	{
		ESP_LOGV(LOG_TAG, "Semaphore taken:  %s", toString().c_str());
	}
	else
	{
		ESP_LOGE(LOG_TAG, "Semaphore NOT taken:  %s", toString().c_str());
	}
	return rc;
#else
	return true;
#endif
} // Semaphore::take

/**
 * @brief Take a semaphore.
 * Take a semaphore but return if we haven't obtained it in the given period of milliseconds.
 * @param [in] timeoutMs Timeout in milliseconds.
 * @param [in] owner The new owner (for debugging)
 * @return True if we took the semaphore.
 */
bool FreeRTOS::Semaphore::take(uint32_t timeoutMs, const std::string& owner)
{
#ifdef __ESP32__
	ESP_LOGV(LOG_TAG, "Semaphore taking: %s for %s", toString().c_str(), owner.c_str());
	bool rc = false;
	if(m_usePthreads)
	{
		ESP_LOGW(LOG_TAG, "We apparently don't have a timed wait for pthreads.  %s",
				 toString().c_str());
		//	assert(false);  // We apparently don't have a timed wait for pthreads. //
		//@suppress("Function cannot be resolved")
	}
	else
	{
		rc = ::xSemaphoreTake(m_semaphore, timeoutMs / portTICK_PERIOD_MS);
	}
	m_owner = owner;
	if(rc)
	{
		ESP_LOGV(LOG_TAG, "Semaphore taken:  %s", toString().c_str());
	}
	else
	{
		ESP_LOGE(LOG_TAG, "Semaphore NOT taken:  %s", toString().c_str());
	}
	return rc;
#else
	return true;
#endif
} // Semaphore::take

/**
 * @brief Create a string representation of the semaphore.
 * @return A string representation of the semaphore.
 */
std::string FreeRTOS::Semaphore::toString()
{
#ifdef __ESP32__
	std::stringstream stringStream;
	stringStream << "name: " << m_name << " (0x" << std::hex << std::setfill('0')
				 << (uint32_t)m_semaphore << "), owner: " << m_owner;
	return stringStream.str();
#else
	return "";
#endif
} // toString

/**
 * @brief Set the name of the semaphore.
 * @param [in] name The name of the semaphore.
 */
void FreeRTOS::Semaphore::setName(const std::string& name)
{
	m_name = name;
} // setName

FreeRTOS::Queue::Queue() {}

FreeRTOS::Queue::~Queue() {}
/**
 * @brief Initialize the queue.
 * @param [in] amount of items
 * @param [in] size of one item
 */
int FreeRTOS::Queue::initialize(size_t amount_of_items, size_t size_of_item)
{
#ifdef __ESP32__
	m_handle = xQueueCreate(amount_of_items, size_of_item);
#endif
	return 0;
}
/**
 * @brief Send data to the queue
 * @param [in] item willing to send
 * @param [in] delay willing to wait
 */
int FreeRTOS::Queue::send(const void* const item_to_send, size_t delay)
{
	if(m_handle == 0)
	{ // error
		return 1;
	}
#ifdef __ESP32__
	BaseType_t xStatus = xQueueSend(m_handle, item_to_send, delay);
	if(xStatus != pdPASS)
	{
		std::cout << " NOT ABLE TO SEND TO QUEUE!!"
				  << "\n";
		return 1;
	}
#endif
	// ok
	return 0;
}
/**
 * @brief Recieve data from the queue
 * @param [out] buffer with recieved item
 * @param [in] delay willing to wait
 */
int FreeRTOS::Queue::recieve(void* pvBuffer, size_t delay)
{
	if(m_handle == 0)
	{ // error
		return 1;
	}
#ifdef __ESP32__
	BaseType_t xStatus = xQueueReceive(m_handle, pvBuffer, delay);
	if(xStatus != pdPASS)
	{
		std::cout << " NOT ABLE TO RECIEVE FROM QUEUE!!"
				  << "\n";
		return 1;
	}
#endif
	// ok
	return 0;
}
