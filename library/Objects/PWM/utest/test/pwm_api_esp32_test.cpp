/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"
#include "../../include/PWM_API_ESP32.hpp"




TEST_GROUP(PWM_GRP)
{
    PWM_API_ESP32 m_api{{16,10,10000},"test"};
    friend_PWM_API m_friend{&m_api};
	void setup(){

	}
	void teardown()
	{
	  // Uninit stuff

	}
};

// test init
TEST(PWM_GRP, check_config)
{

CHECK_EQUAL(m_friend.getConf().duty,10);
CHECK_EQUAL(m_friend.getConf().frequency,10000);
CHECK_EQUAL(m_friend.getConf().m_pin,16);


}
// test init
TEST(PWM_GRP, update_freq)
{

m_api.setFrequency(100);
CHECK_EQUAL(m_friend.getConf().frequency,100);

}


// test init
TEST(PWM_GRP, update_duty)
{

m_api.setDutyCycle(15);
CHECK_EQUAL(m_friend.getConf().duty,15);

}

// test init
TEST(PWM_GRP, update_duty_incorrect)
{

m_api.setDutyCycle(150);

CHECK_EQUAL(m_friend.getConf().duty,10);

}


// test init
TEST(PWM_GRP, update_duty_incorrect2)
{

m_api.setDutyCycle(-150);

CHECK_EQUAL(m_friend.getConf().duty,10);

}
