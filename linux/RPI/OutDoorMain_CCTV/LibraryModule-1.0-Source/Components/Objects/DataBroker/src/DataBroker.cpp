/***********************************************************************************************+
 *  @brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  @note       ANY RELEVANT NOTES
 *
 *  @file       DataBroker.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-03-01
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/DataBroker.hpp"

//#define DEBUG // default uncommeted

constexpr size_t QUEUE_SEND_MAX_TIMOUT = 100;
#ifdef DEBUG
static const char* LOG_TAG = "DataBroker";
#endif
general_err_t DataBroker::addQueue(FreeRTOS::Queue* queue)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> DataBroker::fcn >> ");
#endif
	// Executable code:
	m_queue_array.push_back(queue);
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  DataBroker::fcn << ");
#endif

	return GE_OK;
}

general_err_t DataBroker::main_function()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> DataBroker::fcn >> ");
#endif

	if(m_sensor.isDataReady())
	{
		// auto& buffer = m_sensor.getSafeBuffer();
		std::atomic<size_t> inUseCounter;
		inUseCounter = 0; // reset
		std::for_each(m_queue_array.begin(), m_queue_array.end(),
					  [&inUseCounter](FreeRTOS::Queue* ele) {
						  // we *know* that the buffer is in use for each service
						  // therefor lets make it the databrokers responsible for
						  // incrementing the inUseCounter and the services'
						  // responsible to decrement it
						  inUseCounter++;
						  ele->send(&inUseCounter, QUEUE_SEND_MAX_TIMOUT);
					  });
		// wait for each service to be executed
		while(inUseCounter > 0)
		{
			Timeservice::wait_ms(500);
		}

		return GE_OK;
	}
	/*
	 *  we want to set the WantData flag to
	 * 	true here, in order to get new data
	 */

	m_sensor.setWantDataTrue();

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  DataBroker::fcn << ");
#endif

	return GE_NO_DATA;
}

general_err_t DataBroker::pushQueues()
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

void DataBroker::run(void* data)
{
	for(;;)
	{
		main_function();
		Timeservice::wait_ms(m_delay_ms);
	}
}