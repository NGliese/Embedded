/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"
#include "../../include/Logger.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"




TEST_GROUP(LOG_GRP)
{
	void setup(){

	}
	void teardown()
	{
	  // Uninit stuff

	}
};

// test init
TEST(LOG_GRP, nodata)
{
CHECK_EQUAL(GE_NO_DATA,Logger::write({}));
}

// test init
TEST(LOG_GRP, okdata)
{
CHECK_EQUAL(GE_OK,Logger::write({GE_FAIL,GR_REBOOT,"fail"}));
}


