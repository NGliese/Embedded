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

TEST_GROUP(Utils_GRP){void setup(){

} void teardown(){
	// Uninit stuff

}};

TEST(Utils_GRP, deconcat)
{
	uint8_t m1, m2, m3, m4;

	m1 = 0xde;
	m2 = 0xad;
	m3 = 0xbe;
	m4 = 0xef;

	uint32_t test = 0xdeadbeef;
	auto val = basic_utils::shift8BitTo32(m1, m2, m3, m4);

	uint8_t b1, b2, b3, b4;
	auto err = basic_utils::shift32BitTo8(val, b1, b2, b3, b4);
	CHECK_EQUAL(GE_OK, err);

	LONGS_EQUAL(m1, b1);
	LONGS_EQUAL(m2, b2);
	LONGS_EQUAL(m3, b3);
	LONGS_EQUAL(m4, b4);
}
// test init
TEST(Utils_GRP, concat)
{
	uint8_t m1, m2, m3, m4;

	m1 = 0xde;
	m2 = 0xad;
	m3 = 0xbe;
	m4 = 0xef;

	uint32_t test = 0xdeadbeef;
	auto val = basic_utils::shift8BitTo32(m1, m2, m3, m4);
	LONGS_EQUAL(test, val);
}
// test init
TEST(Utils_GRP, split_string)
{
	std::string test_string = "1123,43242,222";

	auto test_vec = basic_utils::split(test_string, ",");
	LONGS_EQUAL(3, test_vec.size());

	STRCMP_EQUAL("1123", test_vec.at(0).c_str());
	STRCMP_EQUAL("43242", test_vec.at(1).c_str());
	STRCMP_EQUAL("222", test_vec.at(2).c_str());
}
