/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include "../../include/MQTT_Message.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"

constexpr uint8_t id = 10;


TEST_GROUP(MSG_GRP)
{
    MQTT_Message msg{id,3};
    friend_MQTT_Message m_friend{&msg};
	void setup(){

	}
	void teardown()
	{
	  // Uninit stuff

	}
};

// test init
TEST(MSG_GRP, empty)
{
CHECK(msg.isEmpty());
CHECK_EQUAL(id,m_friend.getID());
}


// test init
TEST(MSG_GRP, add_3)
{
    MQTT_Message msg{id,3};
    auto err = msg.addData(120);
    CHECK_EQUAL(GE_OK,err);
    err = msg.addData(120);
    CHECK_EQUAL(GE_OK,err);
    err = msg.addData(120);
    CHECK_EQUAL(GE_OK,err);
    err = msg.addData(120);
    CHECK_EQUAL(GE_OUT_OF_RANGE,err);
}



// test init
TEST(MSG_GRP, toString)
{
    MQTT_Message msg{id,3};
    auto err = msg.addData(120);

    auto str = msg.toString();

    std::cout << " test string : msg buffer " << str << "\n";

}


