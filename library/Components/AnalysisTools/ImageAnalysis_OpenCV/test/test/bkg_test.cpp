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
TEST(BACKGROUND_GRP, init)
{
	cv::Mat m;
	auto count = m_background.countConnectedComponents(m);
	LONGS_EQUAL(0, count);
}
