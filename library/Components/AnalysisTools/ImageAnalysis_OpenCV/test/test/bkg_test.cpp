/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include "../../include/Background_Extractor.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"

TEST_GROUP(BACKGROUND_GRP)
{
	Background_Extractor m_background;

	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
IGNORE_TEST(BACKGROUND_GRP, init)
{
	FAIL("FAIL ME!");
}
