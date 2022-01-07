/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include <iostream>

#include "CppUTest/TestHarness.h"

#include "../../include/Timeservice.hpp"

TEST_GROUP(TIME_GRP){void setup(){

} void teardown(){
	// Uninit stuff

}};

// test init
TEST(TIME_GRP, init)
{
	std::cout << " current date is : " << Timeservice::getCurrentDate() << "\n";
}
