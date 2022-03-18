/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
#include "../../../../Controller/DistanceSensorController/include/DistanceSensorController.hpp"
#include "../../include/DataBroker.hpp" // example of include
#include <iostream>

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"
constexpr size_t AMOUNT_OF_MEASUREMENTS = 300;
constexpr size_t WAIT_DELAY = 20;
constexpr SensorControllerBase::init_conf DEFAULT_CONF{
	.buffer_raw_conf{.entity_id = db_id::WATERSTATION_RAW_ADC,
					 .buffer_size = AMOUNT_OF_MEASUREMENTS},
	.buffer_external_conf{.entity_id = db_id::WATERSTATION_RAW_ADC,
						  .buffer_size = AMOUNT_OF_MEASUREMENTS},
	.task_delay = 5U,
	.error_code_id = db_id::WATERSTATION_ERROR_CODE,
};

#define ADC1_CHANNEL_6 (6U);
const ADC_API_ESP32::config DEFAULT_ADC{

	.name = "adc_test",
	.samples = 64U,
	.channel = 6U, // GPIO34
	.vRef = 1114UL,

};
// clang-format off
TEST_GROUP(TEMP_GRP){

DistanceSensorController m_controller{
	{DEFAULT_CONF ,WAIT_DELAY,DEFAULT_ADC}
 };
	DataBroker m_broker{100,m_controller};
	friend_DataBroker m_friend{&m_broker};
	friend_DistanceSensorController m_sensorFriend{&m_controller};
	void setup(){

	}
	void teardown(){
	// Uninit stuff
	}
};
// clang-format on

// test init
TEST(TEMP_GRP, init)
{
	DataBroker m_broker{100, m_controller};
	CHECK(true);
}

// test init
TEST(TEMP_GRP, run_main_no_data)
{
	CHECK_EQUAL(GE_NO_DATA, m_friend.runMain());
}

// test init
TEST(TEMP_GRP, run_main_with_data)
{
	MQTT_Message buffer{{db_id::DEBUG_ID1, 1}};
	service_SIMPLE m_mock{3, sizeof(int), buffer, db_id::DEBUG_ID2};
	m_broker.addService(&m_mock);
	// do something
	m_sensorFriend.setDataReady();
	CHECK_EQUAL(GE_OK, m_friend.runMain());
}
