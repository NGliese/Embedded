/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
#include "../../include/GPIO_API.hpp"

#include <iostream>

#include "CppUTest/TestHarness.h"

TEST_GROUP(GPIO_GRP)
{
	GPIO_API m_pin_input{11};
	GPIO_API m_pin_output{12};
	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(GPIO_GRP, notOutput)
{
	CHECK_EQUAL(GE_FAIL, m_pin_input.setHigh());
}
// test init
TEST(GPIO_GRP, isOutput)
{
	m_pin_input.setToOutput();
	CHECK_EQUAL(GE_OK, m_pin_input.setHigh());
}
// test init
TEST(GPIO_GRP, isOutputRead)
{
	m_pin_input.setToOutput();
	CHECK_EQUAL(false, m_pin_input.isHigh()); // always false
}
TEST(GPIO_GRP, isOutputRead2)
{
	m_pin_input.setToOutput();
	CHECK_EQUAL(false, m_pin_input.isLow()); // always false
}

TEST(GPIO_GRP, OutputisOutputRead)
{
	m_pin_output.setToOutput();
	CHECK_EQUAL(false, m_pin_output.isLow()); // always false
}

size_t cb_test_var = 0;
void cb_test(void*)
{
	++cb_test_var;
}
// test init
TEST(GPIO_GRP, installITR)
{
	auto err = m_pin_input.installInterrupt(GPIO_HAL::io_intr_t::ANY_EDGE, &cb_test);
	CHECK_EQUAL(GE_OK, err);
	LONGS_EQUAL(1, cb_test_var);
}
