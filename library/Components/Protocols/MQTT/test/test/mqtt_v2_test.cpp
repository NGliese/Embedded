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

static bool have_cb_been_called = false;

TEST_GROUP(MQTT_V2_GRP)
{
	mqtt_api_v2 m_mqtt{"test uri"};
	friend_mqtt_api_v2 m_friend{&m_mqtt};
	void setup() {}
	void teardown()
	{
		// Uninit stuff
		have_cb_been_called = false;
	}
};

int poi = 10;

int* pointer_test(void)
{
	return &poi;
}
// test init
TEST(MQTT_V2_GRP, pointToPoi)
{
	int* p1 = nullptr;
	p1 = pointer_test();
	CHECK((&poi) == p1);
}
// test init
TEST(MQTT_V2_GRP, pointToPoi_simple)
{
	int* p1 = nullptr;
	int poi = 10;
	p1 = &poi;
	CHECK((&poi) == p1);
	// LONGS_EQUAL(&poi,p1);
}

// test init
TEST(MQTT_V2_GRP, notsubscribe)
{
	std::string str;
	CHECK_EQUAL(GE_FAIL, m_mqtt.getData(&str));
}

static general_err_t test_callback_function(const char* data, const size_t length)
{
	std::string str{data, length};
	std::cout << " revieced data is : " << str << "\n";
	have_cb_been_called = true;
	return GE_OK;
}

TEST(MQTT_V2_GRP, subscribeWithFunctionPointer)
{
	std::string topic = "OTA_UPDATE";
	auto err = m_mqtt.subscribe(topic, &test_callback_function);
	m_friend.handle_event(topic.c_str(), topic.size(), "1234", 4);
	CHECK_EQUAL(true, have_cb_been_called);
}

TEST(MQTT_V2_GRP, subscribeWithFunctionPointer_wrongTopic)
{
	std::string topic = "OTA_UPDATE";
	auto err = m_mqtt.subscribe(topic, &test_callback_function);
	m_friend.handle_event(topic.c_str(), 3, "1234", 4);
	CHECK_EQUAL(false, have_cb_been_called);
}
