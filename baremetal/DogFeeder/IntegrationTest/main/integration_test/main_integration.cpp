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
#include <PWM_API_ESP32.hpp>
#include <ADC_API_ESP32.hpp>
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

void simple_connect(){
    /* -------------- INIT WIFI --------------------- */
           wifi_conf_t m_conf;
   #if 1
           m_conf.ssid = WIFI_SSID_LOCAL;
           m_conf.password = WIFI_PWD_LOCAL; // no one can see this password :)
   #endif
           static WiFi_API m_api{m_conf};

           if(m_api.connect() != GE_OK)
           {
               exit(-1);
           }
           /* ---------- init timeservice task ------------ */

           Timeservice m_time;
           m_time.initialize_sntp();

           /* --------------------------------------------- */
}

void test_pwm()
{
    simple_connect();

    HAL_ESP32::config conf,conf2,conf3;

    conf.channel = LEDC_CHANNEL_0;
    conf.duty = 50;
    conf.frequency = 50;
    conf.m_pin = GPIO_NUM_27;
    conf.mode = LEDC_LOW_SPEED_MODE;
    conf3 = conf2 = conf ;

    conf2.m_pin = GPIO_NUM_26;
    conf3.m_pin = GPIO_NUM_25;

    std::array<PWM_API_ESP32,3> vec{PWM_API_ESP32{conf,"pwm1"},PWM_API_ESP32{conf2,"pwm2"},PWM_API_ESP32{conf3,"pwm3"}};


    //assuming 120 degrees rotation,
    //assuming duty = 0 - 13%
    // duty = (14/120) * wanted_degree;

    int i = 0;
    for(;;) // we must not exit the main thread
    {
        float duty = (12.0/120.0) * i;
        std::cout<<"test i is : " << i <<  "duty is : " << duty << " \n";
        for(auto& ele:vec)
        {
          //  ele.setDutyCycle(duty);
        }

        ++i;
        if(i == 120)
        {
            i = 0;
        }

        vTaskDelay(1000);
    }
}

void test_adc()
{
    simple_connect();

       HAL_ESP32::config conf;

       conf.channel = LEDC_CHANNEL_0;
       conf.duty = 50;
       conf.frequency = 50;
       conf.m_pin = GPIO_NUM_25; // pwm3
       conf.mode = LEDC_LOW_SPEED_MODE;

       std::array<PWM_API_ESP32,1> vec{PWM_API_ESP32{conf,"pwm3"}};

       ADC_API_ESP32::config adc_conf;

       adc_conf.name = "adc_test";
       adc_conf.samples = 64;
       adc_conf.channel = ADC1_CHANNEL_5;
       adc_conf.vRef  = 1107;

       ADC_API_ESP32 m_adc{adc_conf};

       for(;;) // we must not exit the main thread
       {
           std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
           vTaskDelay(1000);
       }
}
int runnable(void)
{

 //  test_mqtt();

  //  test_pwm();
   test_adc();
   return 0;
}


#endif /* INTEGRATION_TEST_INCLUDE_MAIN_INTEGRATION_CPP_ */
