/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"
#include "../../include/utils.h"
#include <iostream>

#include "CppUTest/TestHarness.h"




TEST_GROUP(Utils_GRP)
{
	void setup(){

	}
	void teardown()
	{
	  // Uninit stuff

	}
};

TEST(Utils_GRP, deconcat)
{
    uint8_t m1,m2,m3,m4;

    m1 = 0xde;
    m2 = 0xad;
    m3 = 0xbe;
    m4 = 0xef;

    uint32_t test=0xdeadbeef;
    auto val = gliese_utils::shift8BitTo32(m1,m2,m3,m4);

    uint8_t b1,b2,b3,b4;
    auto err = gliese_utils::shift32BitTo8(val,b1,b2,b3,b4);
    CHECK_EQUAL(GE_OK,err);

    LONGS_EQUAL(m1,b1);
    LONGS_EQUAL(m2,b2);
    LONGS_EQUAL(m3,b3);
    LONGS_EQUAL(m4,b4);

}
// test init
TEST(Utils_GRP, concat)
{
    uint8_t m1,m2,m3,m4;

    m1 = 0xde;
    m2 = 0xad;
    m3 = 0xbe;
    m4 = 0xef;

    uint32_t test=0xdeadbeef;
    auto val = gliese_utils::shift8BitTo32(m1,m2,m3,m4);
    LONGS_EQUAL(test,val);

}
