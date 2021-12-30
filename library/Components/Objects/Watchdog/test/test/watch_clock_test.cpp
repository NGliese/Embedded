/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
#include "../../include/Watch_Clock.hpp"

#include <iostream>

#include "CppUTest/TestHarness.h"

extern uint32_t fake_start_time;
extern uint32_t fake_end_time;

TEST_GROUP(WCH_CLK_GRP)
{
	Watch_Clock m_clock;
	void setup()
	{
		fake_start_time = 21;
		m_clock.initialize(200);
	}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(WCH_CLK_GRP, notinit)
{
	Watch_Clock wa;
	CHECK_EQUAL(watchdog_event_t::FAIL_EVENT, wa.watch());
}
// test init
TEST(WCH_CLK_GRP, ok)
{
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
}

// test init
TEST(WCH_CLK_GRP, test_nothing)
{
	fake_end_time = 100;
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
}

// test init
TEST(WCH_CLK_GRP, test_send)
{
	fake_end_time = 1000;
	CHECK_EQUAL(watchdog_event_t::SEND_EVENT, m_clock.watch());
}

// test init
TEST(WCH_CLK_GRP, test_wrong_time)
{
	Watch_Clock wa;
	fake_end_time = 10;
	fake_start_time = 1000;
	wa.initialize(200);
	CHECK_EQUAL(watchdog_event_t::FAIL_EVENT, wa.watch());
}

// test init
TEST(WCH_CLK_GRP, test_send_multi)
{
	fake_end_time = 1000;
	for(size_t i = 0; i < 10; i++)
	{
		fake_end_time += 201;
		CHECK_EQUAL(watchdog_event_t::SEND_EVENT, m_clock.watch());
	}
}

// test init
TEST(WCH_CLK_GRP, test_send_multi2)
{
	fake_end_time = 51;
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
	fake_end_time += 51;
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
	fake_end_time += 51;
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
	fake_end_time += 51;
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
	fake_end_time += 51;
	CHECK_EQUAL(watchdog_event_t::SEND_EVENT, m_clock.watch());
	fake_end_time += 51;
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
}

// test init
TEST(WCH_CLK_GRP, test_reset_1)
{
	fake_end_time = 0;
	for(size_t i = 0; i < 10; i++)
	{
		fake_end_time += 150;
		CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
		m_clock.reset();
	}
}

// test init
TEST(WCH_CLK_GRP, test_reset_2)
{
	fake_end_time = 0;
	for(size_t i = 0; i < 10; i++)
	{
		fake_end_time += 150;
		CHECK_EQUAL(watchdog_event_t::NO_EVENT, m_clock.watch());
		m_clock.reset();
	}

	for(size_t i = 0; i < 10; i++)
	{
		fake_end_time += 201;
		CHECK_EQUAL(watchdog_event_t::SEND_EVENT, m_clock.watch());
		//  m_clock.reset();
	}
}

// test init
TEST(WCH_CLK_GRP, new_init)
{
	Watch_Clock clock(200);
	fake_end_time = Timeservice::getTimeNow();
	auto evt = clock.watch();
	CHECK_EQUAL(watchdog_event_t::NO_EVENT, evt);
}
