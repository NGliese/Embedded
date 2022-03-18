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

general_err_t DataBroker::addService(ServiceBase<MQTT_Message>* service)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> DataBroker::fcn >> ");
#endif

	m_service_array.push_back(service);

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
		std::atomic<size_t> inUseCoder;
		inUseCoder = 0xdeadbeef; // reset
		std::for_each(m_service_array.begin(), m_service_array.end(),
					  [&inUseCoder](ServiceBase<MQTT_Message>* ele) {
						  ele->getQueue().send(&inUseCoder, QUEUE_SEND_MAX_TIMOUT);
					  });

		/**
		 * @brief check all the available flags to see if any of the
		 * services are in use. If they are in use, wait 500ms and poll again
		 * 	- we are assuming that we will hit a break at some point.
		 */
		bool isActive = false;
		do
		{
			std::for_each(m_service_array.begin(), m_service_array.end(),
						  [&isActive](ServiceBase<MQTT_Message>* ele) {
							  if(ele->isActive())
							  {
								  isActive = true;
							  }
						  });
			Timeservice::wait_ms(500);
		} while(isActive);

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

void DataBroker::run(void* data)
{
	for(;;)
	{
		main_function();
		Timeservice::wait_ms(m_delay_ms);
	}
}