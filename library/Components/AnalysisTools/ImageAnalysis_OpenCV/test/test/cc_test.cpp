/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"
#include "../../include/ConnectedComponents.hpp"
#include <iostream>

#include "CppUTest/TestHarness.h"

TEST_GROUP(CC_GRP){void setup(){

} void teardown(){
	// Uninit stuff

}};

// test init
TEST(CC_GRP, draw_empty1)
{
	cv::Mat m1, m2;
	auto err = ConnectedComponents::drawConnectedComponents(m1, m2);
	CHECK_EQUAL(GE_EMPTY, err);
}
// test init
TEST(CC_GRP, count_connected_components_empty1)
{
	cv::Mat m1, m2;
	auto count = ConnectedComponents::maxConnectedComponents(m1);
	CHECK_EQUAL(0, count);
}
// test init
TEST(CC_GRP, count_connected_components_empty2)
{
	cv::Mat m1, m2;
	auto container = ConnectedComponents::statsConnectedComponents(m1);

	CHECK_EQUAL(0, container.amount_of_connections);
	CHECK_EQUAL(0, container.maxConnected);
}
