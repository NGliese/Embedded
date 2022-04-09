/*
 * Maintainer.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: espenv
 */

/***********************************************************************************************+
 *  \brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       Maintainer.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Maintainer.hpp"

// vector of function pointers
static std::vector<bool (*)(void)> maintainer_pointer_vec;
#define PERIODIC_RESTART_TIME (21600000UL) // every 6th hour
//#define PERIODIC_RESTART_TIME (3600000UL) // every 1th hour for testing
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "Maintainer";
#endif

Maintainer::Maintainer(const wifi_conf_t& wifi_conf, const db_id& error_id, bool withPeriodicReboot,
					   size_t delay_sec, int priority)
	: m_faulthandler{"Maintainer"}, m_delay_sec{delay_sec}, m_wifi{wifi_conf}, m_error_id{error_id},
	  m_withPeriodicReboot{withPeriodicReboot}
{
	setPriority(priority);
	setName("Maintainer");
#if 0
    auto err = m_wifi.connect();
    if(err != GE_OK)
    {
        std::cout << "[Maintainer] not able to connect to wifi, rebooting ...\n";
        Timeservice::wait_ms(1000);
        exit(-1);
    }
#endif
	Timeservice::wait_ms(1000);
	general_err_t err = GE_OK;
	size_t count = 1;
	do
	{
		std::cout << "[Maintainer] setting up sntp, attempt <" << (int)count << "/3> ...\n";
		err = Timeservice::initialize_sntp();
		Timeservice::wait_ms(1000);
	} while(err != GE_OK && count++ < 3);

	if(err != GE_OK)
	{
		std::cout << "[Maintainer] not able to get RTC, rebooting ...\n";
		Timeservice::wait_ms(1000);
		exit(-1);
	}
	std::cout << "[Maintainer] sntp successfully initialized in  <" << (int)count
			  << "> attempts ...\n";
	start_time = Timeservice::getTimeNow();
#ifdef __WITH_OTA__
	// in the maintainer class, we want to enable OTA service. In this point of the code we are sure
	// that we have a WiFi access, therefor we can safly start the service:
	//   m_mqtt.subscribe(MQTT_OTA_TOPIC,&(OTA::update));
#endif
}

Maintainer::~Maintainer() {}
/**
 * @brief   install a function for the test service in order to periodically check
 *          that everything is working as intended.
 * @attention
 *          The function must return a boolean with the definition :
 *          True  -> test has passed, everything is working.
 *          False -> test has failed, we need to restart.
 *
 * @param[in] bool (*callbackfunction)(void)
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Maintainer::install_system_test_fuction(bool (*callbackfunction)(void))
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> enclosing_method >> ");
#endif
	// Executable code:

	maintainer_pointer_vec.push_back(callbackfunction);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< enclosing_method << ");
#endif

	return GE_OK;
}

void Maintainer::run(void* data)
{
	for(;;)
	{
		Timeservice::wait_sec(m_delay_sec);
		check_system_functions();
		if(m_withPeriodicReboot)
		{
			periodic_restart();
		}
	}
}
/**
 * @brief  a private function to make sure the sensors are restarted every 6th hour.
 *
 * @attention
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Maintainer::periodic_restart(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Maintainer::periodic_restart >> ");
#endif
	// Executable code:

	if(Timeservice::getTimeNow() - start_time > PERIODIC_RESTART_TIME)
	{
		m_faulthandler.handleFault(
			{FaultHandler_n::severity::very_high, "periodic_restart", "We are forcing a restart"});
		ErrorCodeParser::postToMqtt(m_error_id, GE_TIMEOUT, "We are forcing a restart");
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Maintainer::periodic_restart << ");
#endif

	return GE_OK;
}
/**
 * @brief a private function which is called periodically to check the vector of function pointers
 *
 * @attention
 *          if any tests fails we log it and restart
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Maintainer::check_system_functions(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Maintainer::check_system_functions >> ");
#endif
	// Executable code:

	for(const auto& ele : maintainer_pointer_vec)
	{
		if(!ele())
		{
			m_faulthandler.handleFault({FaultHandler_n::severity::very_high,
										"Maintainer::check_system_functions",
										"A fault has been detected in the system checks!"});
			ErrorCodeParser::postToMqtt(m_error_id, GE_FAIL,
										"Function 'check_system_functions' failed to execute");

			return GE_FAIL;
		}
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Maintainer::check_system_functions << ");
#endif

	return GE_OK;
}

general_err_t Maintainer::checkOTAUpdate(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Maintainer::checkOTAUpdate >> ");
#endif
	// Executable code:
	if(Maintainer::isOTAUpdateStarted())
	{
		Timeservice::wait_ms(50000);
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Maintainer::checkOTAUpdate << ");
#endif

	return GE_OK;
}
