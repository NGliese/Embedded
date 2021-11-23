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
#include <MG996R.hpp>
#include <array>
#include <DogFeederDoor.hpp>
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
       conf.m_pin = GPIO_NUM_27; // pwm1
       conf.mode = LEDC_LOW_SPEED_MODE;

       std::array<PWM_API_ESP32,1> vec{PWM_API_ESP32{conf,"pwm1"}};

       ADC_API_ESP32::config adc_conf;

       adc_conf.name = "adc_test";
       adc_conf.samples = 64;
       adc_conf.channel = ADC1_CHANNEL_5;
       adc_conf.vRef  = 1114;

       ADC_API_ESP32 m_adc{adc_conf};
       int i = 0;
       for(;;) // we must not exit the main thread
       {

           float duty = (12.0/120.0) * i;
           std::cout<<"test i is : " << i <<  "duty is : " << duty << " \n";
           for(auto& ele:vec)
           {
              ele.setDutyCycle(duty);
           }
           std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";

           ++i;
           if(i == 120)
           {
               i = 0;
           }

           vTaskDelay(100);

       }
}
constexpr float START_POSITION = 2.5;
constexpr float END_POSITION = 13;
void test_go_to_0()
{
    simple_connect();

          HAL_ESP32::config conf;

          conf.channel = LEDC_CHANNEL_0;
          conf.duty = 50;
          conf.frequency = 50;
          conf.m_pin = GPIO_NUM_27; // pwm1
          conf.mode = LEDC_LOW_SPEED_MODE;

          std::array<PWM_API_ESP32,1> vec{PWM_API_ESP32{conf,"pwm1"}};

          ADC_API_ESP32::config adc_conf;

          adc_conf.name = "adc_test";
          adc_conf.samples = 64;
          adc_conf.channel = ADC1_CHANNEL_5;
          adc_conf.vRef  = 1114;

          ADC_API_ESP32 m_adc{adc_conf};

          std::cout << ">> Go to start position >>\n ";
       //   float duty = (12.0/120.0) * 25;

          for(auto& ele:vec)
        {
         //  ele.setDutyCycle(END_POSITION);
              ele.setDutyCycle(START_POSITION);
        }

          for(;;)
          {
              std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";

              vTaskDelay(100);
          }
          std::cout << "<< Go to start position <<\n ";
}

void test_motor0()
{
    mg996r_conf_t motor_conf;
    auto& pwm_conf = motor_conf.conf;

    pwm_conf.channel = LEDC_CHANNEL_0;
    pwm_conf.duty = 50;
    pwm_conf.frequency = 50;
    pwm_conf.m_pin = GPIO_NUM_27; // pwm1
    pwm_conf.mode = LEDC_LOW_SPEED_MODE;

    motor_conf.name = "motor";
    MG996R m_motor{motor_conf};

    m_motor.execute(END_POSITION);
    for(;;)
    {
      //  std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
        std::cout << " waiting for stuf to happen...\n";
        vTaskDelay(100);
    }

}

void test_door()
{
    simple_connect();
    mg996r_conf_t motor_conf;
    auto& pwm_conf = motor_conf.conf;

    pwm_conf.channel = LEDC_CHANNEL_0;
    pwm_conf.duty = 50;
    pwm_conf.frequency = 50;
    pwm_conf.m_pin = GPIO_NUM_27; // pwm1
    pwm_conf.mode = LEDC_LOW_SPEED_MODE;

    motor_conf.name = "motor";
    DogFeederDoor m_door{motor_conf};


    for(;;)
    {
      //  std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
        std::cout << " ... Opening door ... \n";
        General_Error::printError("Open door", m_door.open());
        vTaskDelay(5000);
        std::cout << " ... Closing door ... \n";
        General_Error::printError("Close door", m_door.close());
        vTaskDelay(5000);
    }

}
int runnable(void)
{

 //  test_mqtt();

  //  test_pwm();
  // test_adc();
   //test_go_to_0();
  //  test_motor0();
    test_door();
   return 0;
}


#endif /* INTEGRATION_TEST_INCLUDE_MAIN_INTEGRATION_CPP_ */
