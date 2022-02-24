/*
 * Background_Extractor.cpp
 *
 *  Created on: Jul 23, 2021
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
 *  \file       Background_Extractor.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Background_Extractor.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "Background_Extractor";
#endif

Background_Extractor::Background_Extractor(const background_conf_t& conf) : m_conf{conf}
{
	switch(m_conf.m_type)
	{
		case type::MOG2:
			background = cv::createBackgroundSubtractorMOG2();
			name = "MOG2_";
			break;
		case type::KNN:
			background = cv::createBackgroundSubtractorKNN();
			name = "KNN_";
			break;
	}
	// static_assert(background.empty(),"failed to allocate a backgroundSubtractor");
}

Background_Extractor::~Background_Extractor() {}

uint32_t Background_Extractor::countConnectedComponents(const cv::Mat& raw)
{
	// make sure we do not feed in an empty image

	if(raw.empty())
	{
		std::cerr << "we recieved an empty image in countConnectedComponents! \n";
		return 0;
	}
	// update ref for images
	m_previous = m_current;
	m_current = raw;

	background->apply(raw, m_forground, m_conf.learning_rate);
	background->getBackgroundImage(m_background);
	return ConnectedComponents::maxConnectedComponents(m_forground, m_conf.ksize);
}

ConnectedComponents::container_t Background_Extractor::statsConnectedComponents(const cv::Mat& raw)
{
	// update ref for images
	m_previous = m_current;
	m_current = raw;

	background->apply(raw, m_forground, m_conf.learning_rate);
	background->getBackgroundImage(m_background);
	return ConnectedComponents::statsConnectedComponents(m_forground, m_conf.ksize);
}

void Background_Extractor::view(void) const
{
	if(!m_background.empty())
		Utility_Image::view_image(Utility_Image::zoom(m_background, m_conf.zoom),
								  name + "background");
	if(!m_forground.empty())
		Utility_Image::view_image(Utility_Image::zoom(m_forground, m_conf.zoom),
								  name + "forground");
	if(!m_current.empty())
		Utility_Image::view_image(Utility_Image::zoom(m_current, m_conf.zoom), name + "m_current");
	if(!m_previous.empty())
		Utility_Image::view_image(Utility_Image::zoom(m_previous, m_conf.zoom),
								  name + "m_previous");
}
