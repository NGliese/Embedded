/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include <iostream>

#include "CppUTest/TestHarness.h"

#include "../../include/Timebased_rules.hpp"

TEST_GROUP(TEMPL_GRP){void setup(){

} void teardown(){
	// Uninit stuff

}};

// test init
TEST(TEMPL_GRP, isItNight)
{
	CHECK_EQUAL(false, Timebased_rules::isItNight());
}
