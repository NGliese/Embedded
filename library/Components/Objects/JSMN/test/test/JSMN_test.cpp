/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
// #include "../../include/esp32Cam.hpp" // example of include
#include <iostream>

#include "../../include/jsmn_object.hpp"

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"

// clang-format off
TEST_GROUP(JSMN_GRP){

	
	void setup(){

	}
	void teardown(){
	// Uninit stuff
	}
};
// clang-format on

// test init
TEST(JSMN_GRP, init)
{
	std::string s = "{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000, \"groups\": "
					"[\"users\", \"wheel\", \"audio\", \"video\"]}";
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 JSON tokens */

	jsmn_init(&p);
	auto res = jsmn_parse(&p, s.c_str(), s.size(), t,
						  128); // "s" is the char array holding the json content
	LONGS_EQUAL(13, res);

	for(size_t i = 1; i < res; i++)
	{
		if(jsoneq(s.c_str(), &t[i], "uid") == 0)
		{
			std::cout << "UID start : " << t[i + 1].start << " ends : " << t[i + 1].end
					  << " value is :" << s.substr(t[i + 1].start, t[i + 1].end - t[i + 1].start)
					  << "\n";

			CHECK_EQUAL(JSMN_PRIMITIVE, t[i + 1].type);
			auto val = json2int(s, t[i + 1].type, t[i + 1].start, t[i + 1].end);
			LONGS_EQUAL(1000, val);
		}
	}
}
