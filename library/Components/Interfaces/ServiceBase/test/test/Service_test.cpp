/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
#include "../../include/ServiceBase.hpp" // example of include
#include <iostream>

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"

// clang-format off
TEST_GROUP(SERVICE_TEST){
	MQTT_Message buffer{{db_id::DEBUG_ID1,1}};
	service_MOCK m_mock{10,10,buffer,db_id::DEBUG_ID2};
	void setup(){
	
	}
	void teardown(){
	// Uninit stuff
	}
};
// clang-format on

// test init
TEST(SERVICE_TEST, notActive)
{
	CHECK_FALSE(m_mock.isActive());
}
