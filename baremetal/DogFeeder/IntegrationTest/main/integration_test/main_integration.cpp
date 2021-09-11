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
#include <Timeservice.hpp>

#include <MQTT_Message.hpp>
#include <PWM_API.hpp>
#include <array>
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

        std::cout<<"test \n";
        vTaskDelay(1000);
    }

}
void test_pwm()
{
    HAL_ESP32::config conf,conf2,conf3;

    conf.channel = LEDC_CHANNEL_0;
    conf.duty = 50;
    conf.frequency = 5000;
    conf.m_pin = GPIO_NUM_27;
    conf.mode = LEDC_LOW_SPEED_MODE;
    conf3 = conf2 = conf ;

    conf2.m_pin = GPIO_NUM_26;
    conf3.m_pin = GPIO_NUM_25;

    std::array<PWM_API,3> vec{PWM_API{conf},PWM_API{conf2},PWM_API{conf3}};




    int i = 0;
    for(;;) // we must not exit the main thread
    {

        std::cout<<"test \n";
        for(auto& ele:vec)
        {
            ele.setDutyCycle(i);
        }
        ++i;
        vTaskDelay(100);
    }
}
int runnable(void)
{

 //  test_mqtt();

    test_pwm();
   return 0;
}


#endif /* INTEGRATION_TEST_INCLUDE_MAIN_INTEGRATION_CPP_ */
