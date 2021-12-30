/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include "../../include/OTA.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"

TEST_GROUP(OTA_GRP)
{
	OTA m_ota;
	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(OTA_GRP, check_update)
{
	CHECK_EQUAL(false, m_ota.isUpdateStarted());
}
