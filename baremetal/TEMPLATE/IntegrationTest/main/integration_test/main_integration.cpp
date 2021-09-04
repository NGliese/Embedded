/*
 * main_integration.cpp
 *
 *  Created on: Nov 15, 2020
 *      Author: espenv
 */

#ifndef INTEGRATION_TEST_INCLUDE_MAIN_INTEGRATION_CPP_
#define INTEGRATION_TEST_INCLUDE_MAIN_INTEGRATION_CPP_

#include "include/main_integration.hpp"

#include <WiFi_API.hpp>
#include <MQTT_API.hpp>
#include <Timeservice.hpp>

#include <MQTT_Message.hpp>


void test_mqtt()
{
	   /* -------------- INIT WIFI --------------------- */
		wifi_conf_t m_conf;
#if 1
		m_conf.ssid = WIFI_SSID_LOCAL; 
		m_conf.password = WIFI_PWD_LOCAL; // no one can see this password :)
#endif
		WiFi_API m_api{m_conf};

	    if(m_api.connect() != GE_OK)
	    {
	        exit(-1);
	    }
	    /* ---------- init timeservice task ------------ */

	    Timeservice m_time;
	    m_time.initialize_sntp();

	    /* --------------------------------------------- */

    for(;;) // we must not exit the main thread
    {
        vTaskDelay(100000);
    }

}

int runnable(void)
{

   test_mqtt();
   return 0;
}


#endif /* INTEGRATION_TEST_INCLUDE_MAIN_INTEGRATION_CPP_ */
