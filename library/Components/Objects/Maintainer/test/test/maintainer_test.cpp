/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include "../../include/Maintainer.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"

TEST_GROUP(MAINTAINER_GRP)
{
	Maintainer m_maintainer{{}};
	friend_Maintainer m_friend{&m_maintainer};

	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};
bool good_test(void)
{
	return true;
}
bool bad_test(void)
{
	return false;
}
// test init
TEST(MAINTAINER_GRP, init)
{
	Maintainer::install_system_test_fuction(good_test);
	Maintainer::install_system_test_fuction(bad_test);
	CHECK_EQUAL(GE_FAIL, m_friend.check_sys());
}

bool good_test2(void)
{
	std::cout << " testing some important functionality .... \n";
	return good_test();
}
// test init
TEST(MAINTAINER_GRP, init2)
{
	Maintainer::install_system_test_fuction(good_test2);
	CHECK_EQUAL(GE_OK, m_friend.check_sys());
}
