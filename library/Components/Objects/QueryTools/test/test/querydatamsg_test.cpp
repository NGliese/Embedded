/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include <iostream>

#include "../../include/QueryMessage.hpp"
#include "CppUTest/TestHarness.h"

TEST_GROUP(QDMSG_GRP)
{
	QueryDataMessage msg{101};

	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(QDMSG_GRP, test_size)
{
	msg.addData(10.2);
	LONGS_EQUAL(1, msg.getBuffer().size());
}

// test init
TEST(QDMSG_GRP, test_value)
{
	msg.addData(10);
	LONGS_EQUAL(10, msg.getBuffer().at(0).data);
}
TEST(QDMSG_GRP, test_id)
{
	LONGS_EQUAL(101, msg.getId());
}
TEST(QDMSG_GRP, test_init2)
{
	QueryDataMessage msg{101, {10021, 12.0}};

	LONGS_EQUAL(1, msg.getBuffer().size());
}
