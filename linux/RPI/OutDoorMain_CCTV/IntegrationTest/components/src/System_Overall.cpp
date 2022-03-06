/*
 * System_Overall.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: espenv
 */

/***********************************************************************************************+
 *  \brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       System_Overall.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/System_Overall.hpp"

//#define DEBUG // default uncommeted

static const char* LOG_TAG = "System_Overall";
#define SCALE_FACTOR (2)

System_Overall::System_Overall() {}

System_Overall::~System_Overall() {}

void System_Overall::run(void)
{
	cv::Mat raw, masked, edge, visual;
	general_err_t err;
	timeval timeOfCapture;
	for(;;)
	{
		err = m_cam.takePicture();
		if(err != GE_OK)
		{
			continue;
		}
		raw = m_cam.getPicture();
		gettimeofday(&timeOfCapture, NULL);
		m_helper.setDataToValid(timeOfCapture);

		Utility_Image::rotateImage(raw, 180);

		cv::Point p1(800, 450 + 160);
		cv::Point p2(raw.cols, raw.rows);
		//   Utility_Image::putMask(raw,masked,p1,p2);

		Utility_Image::getROI(raw, {p1, p2}, masked);

		// Utility_Image::rotateImage(masked,180);

		m_helper.doOutlierDetection(masked);

		raw.copyTo(visual);

		Utility_Image::putDate(visual);
		if(m_helper.isObjectValid())
		{
			m_helper.reportAnalysis();
			m_helper.reportImages(raw, edge, visual);
			// if(Timebased_rules::isItNight())
			if(Timebased_rules::isItVacation() or Timebased_rules::isItNight())
			{
				m_helper.reportAlarm();
			}
		}

		// std::cout << "Viewing images....  \n";

		Utility_Image::view_image(Utility_Image::zoom(visual, 0.25), "visual color");
		Utility_Image::view_image(Utility_Image::zoom(masked, 0.25), "masked color");
		Utility_Image::wait(10);
	}
}
