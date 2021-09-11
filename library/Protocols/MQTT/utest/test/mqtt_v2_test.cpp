/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"
#include "../../include/mqtt_api_v2.hpp"

#include <iostream>

#include "CppUTest/TestHarness.h"




TEST_GROUP(MQTT_V2_GRP)
{

    mqtt_api_v2 m_mqtt{"test uri"};
    friend_mqtt_api_v2 m_friend{&m_mqtt};
	void setup(){

	}
	void teardown()
	{
	  // Uninit stuff

	}
};

// test init
TEST(MQTT_V2_GRP, init)
{


}

