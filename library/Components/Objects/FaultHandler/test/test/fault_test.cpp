/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include <iostream>

#include "../../include/Fault_Handler.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(FAULT_GRP)
{
	Fault_Handler m_handler{"UnitTest"};
	friend_Fault_Handler m_friend{&m_handler};
	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(FAULT_GRP, count_medium)
{
	auto err = m_friend.countUp({FaultHandler_n::severity::medium, "init", "test"});
	CHECK_EQUAL(GE_OK, err);

	auto val = m_friend.getCounterValue(FaultHandler_n::severity::medium);
	LONGS_EQUAL(1, val);
}

// test init
TEST(FAULT_GRP, count_medium_and_reset)
{
	auto err = m_friend.countUp({FaultHandler_n::severity::medium, "init", "test"});
	m_handler.resetFaultCounter(FaultHandler_n::severity::medium);

	auto val = m_friend.getCounterValue(FaultHandler_n::severity::medium);
	LONGS_EQUAL(0, val);
}
// test init
TEST(FAULT_GRP, count_low_medium_high_and_reset_low)
{
	m_friend.countUp({FaultHandler_n::severity::medium, "init", "test"});
	m_friend.countUp({FaultHandler_n::severity::low, "init", "test"});
	m_friend.countUp({FaultHandler_n::severity::high, "init", "test"});
	m_handler.resetFaultCounter(FaultHandler_n::severity::low);

	auto val = m_friend.getCounterValue(FaultHandler_n::severity::medium);
	LONGS_EQUAL(1, val);
	val = m_friend.getCounterValue(FaultHandler_n::severity::low);
	LONGS_EQUAL(0, val);
	val = m_friend.getCounterValue(FaultHandler_n::severity::high);
	LONGS_EQUAL(1, val);
}

// test init
TEST(FAULT_GRP, check_boundery)
{
	CHECK(m_friend.check_value(10, 5));
	CHECK(m_friend.check_value(5, 5));
	CHECK_FALSE(m_friend.check_value(0, 5));
}
// test init
TEST(FAULT_GRP, count_medium_and_handle)
{
	FaultHandler_n::msg_t msg = {FaultHandler_n::severity::medium, "init", "test"};
	for(size_t i = 0; i < 100; ++i)
	{
		m_friend.countUp(msg);
	}
	m_friend.handle(msg);
}

// test init
TEST(FAULT_GRP, msg_toString)
{
	FaultHandler_n::msg_t msg = {FaultHandler_n::severity::medium, "init", "test"};
	auto str = m_friend.toString(msg);
	STRCMP_EQUAL("medium,UnitTest,init,test", str.c_str());
}
