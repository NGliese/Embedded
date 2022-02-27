/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
#include "../../include/SensorControllerBase.hpp" // example of include
#include "../mock/SensorControllerBase_MOCK.hpp" // example of include
#include <iostream>

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"

constexpr SensorControllerBase::init_conf DEFAULT_CONF{
	.buffer_raw_conf{.entity_id = db_id::DEBUG_ID1, .buffer_size = 50},
	.buffer_external_conf{.entity_id = db_id::DEBUG_ID2, .buffer_size = 50},
	.task_delay = 5U,
	.error_code_id = db_id::WATERSTATION_ERROR_CODE,
};

// clang-format off
TEST_GROUP(TEMP_GRP){
	SensorControllerBase_MOCK m_mock{DEFAULT_CONF};
	void setup(){

	}
	void teardown(){
	// Uninit stuff
	}
};
// clang-format on

// test init
TEST(TEMP_GRP, test_constness_of_extern_buffer)
{
	auto& buff = m_mock.getSafeBuffer();
	LONGS_EQUAL(buff.getBufferSize(), 0);
	// buff.addData(10); // cant do it due to being const!
	// LONGS_EQUAL(buff.getBufferSize(), 1);
	auto data = buff.getData();
	LONGS_EQUAL(data.size(), 0);
}
