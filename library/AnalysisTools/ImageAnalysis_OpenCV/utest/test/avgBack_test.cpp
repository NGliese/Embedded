/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include <iostream>



#include "../../include/AveragingBackground.hpp"




#include "CppUTest/TestHarness.h"




TEST_GROUP(AVG_GRP)
{
	void setup(){

	}
	void teardown()
	{
	  // Uninit stuff

	}
};

// test init
TEST(AVG_GRP, init)
{
cv::Mat test_img(260, 301, CV_8UC3, cv::Scalar(0, 0, 0));

AveragingBackground m_background{test_img};

}

