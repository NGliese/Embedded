/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include "../../include/ADC_API_ESP32.hpp"

#include <iostream>

#include "CppUTest/TestHarness.h"

TEST_GROUP(ADC_GRP)
{
	ADC_API_ESP32 m_adc{{"adc", 64}};
	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(ADC_GRP, simple_test)
{
	LONGS_EQUAL(0, m_adc.measureValue());
}

// test init
TEST(ADC_GRP, check_samples)
{
	LONGS_EQUAL(64, m_adc.getSampleNumber());
}

// test init
TEST(ADC_GRP, check_samples_minus)
{
	m_adc.setSampleNumber(-1);

	LONGS_EQUAL(64, m_adc.getSampleNumber());
}

// test init
TEST(ADC_GRP, check_samples_min)
{
	m_adc.setSampleNumber(1);

	LONGS_EQUAL(1, m_adc.getSampleNumber());
}
// test init
TEST(ADC_GRP, check_samples_max)
{
	m_adc.setSampleNumber(5000);

	LONGS_EQUAL(5000, m_adc.getSampleNumber());
}
