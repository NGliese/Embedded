/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"
#include "../../include/HAL.hpp"

#include <iostream>

#include "CppUTest/TestHarness.h"

static size_t cb_call = 0;
void test_cb(void*)
{
 ++cb_call;
}

TEST_GROUP(HAL_GRP)
{

    GPIO_HAL m_hal;
	void setup(){

	}
	void teardown()
	{
	  // Uninit stuff

	}
};

// test init
TEST(HAL_GRP, init)
{
    m_hal.installInterruptDriver(5,&test_cb,GPIO_HAL::io_intr_t::ANY_EDGE);
LONGS_EQUAL(1,cb_call);
}

