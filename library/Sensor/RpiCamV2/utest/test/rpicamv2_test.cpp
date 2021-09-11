/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"


#include <iostream>

#include "../../include/RPICamV2.hpp"

#include "CppUTest/TestHarness.h"



TEST_GROUP(V2_GRP)
{

    RPICamV2 m_cam;
    friend_RPICamV2 m_friend{&m_cam};
	void setup(){


	}
	void teardown()
	{
	  // Uninit stuff

	}
};

// test init
TEST(V2_GRP, init)
{

FAIL("FAIL ME!");
}

