/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
#include "../../include/json_object.hpp" // example of include
#include <iostream>

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"

// clang-format off
TEST_GROUP(JSON_GRP){

	
	void setup(){

	}
	void teardown(){
	// Uninit stuff
	}
};
// clang-format on

// test init
TEST(JSON_GRP, init)
{
	json j = json::parse(
		"{\"tstz\":\"2022-01-08T17:02:10.267Z\",\"sensor_id\":\"104\",\"value\":\"100\"}");
	// simple demo of how to use json
	STRCMP_EQUAL("\"2022-01-08T17:02:10.267Z\"", j["tstz"].dump().c_str());
	STRCMP_EQUAL("\"104\"", j["sensor_id"].dump().c_str());
	STRCMP_EQUAL("\"100\"", j["value"].dump().c_str());
}

// test init
TEST(JSON_GRP, bad_pare)
{
	json j = json::parse("empty", nullptr, false);
	CHECK(j.is_discarded());
}
