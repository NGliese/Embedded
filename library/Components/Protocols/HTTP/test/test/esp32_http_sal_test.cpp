/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"
#include "../../include/esp32_http_sal.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"

TEST_GROUP(ESP32_HTTP_GRP)
{
	esp32_http_sal m_http{"1.1.1.1."};
	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(ESP32_HTTP_GRP, get_string)
{
	std::string out;
	auto err = m_http.get("/test", out);
	CHECK_EQUAL(GE_OK, err); // we expect OK
	STRCMP_EQUAL("", out.c_str());
}

// test init
TEST(ESP32_HTTP_GRP, post)
{
	auto err = m_http.post("/esp32_postTest", esp32_http_sal::content_type::IMAGE, "{image}");
	CHECK_EQUAL(GE_OK, err);
}
