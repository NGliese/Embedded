/*
 * Image_Helper_v2.cpp
 *
 *  Created on: Jul 29, 2021
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
 *  \file       Image_Helper_v2.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Image_Helper_v2.hpp"

#define KNN_MAX_DIV_MIN (80)
#define KNN_MAX_DIV_MAX (400)
#define MOG2_MAX_DIV_MIN (80)
#define MOG2_MAX_DIV_MAX (400)

#define MOG2_MAX_AREA (20000)
//#define DEBUG // default uncommeted

#define IMAGE_PATH_RAW ("/media/pi/RPI_ROBOT/Lepton_img/Raw/")
#define IMAGE_PATH_COLOR ("/media/pi/usb/CCTV/MEGA/color/")

#define IMAGE_PATH_PYTHON ("/media/pi/usb/CCTV/MEGA/python/")

#ifdef DEBUG
static const char* LOG_TAG = "Image_Helper_v2";
#endif

Image_Helper_v2::Image_Helper_v2()
	: m_isDataValid{false}, m_container{{0, 0, 0, {0, 0}}, {}, {}, {}},
	  m_background1{{0.6, Background_Extractor::type::MOG2, 2, 1}},
	  m_background2{{0.6, Background_Extractor::type::KNN, 2, 1}}
{
	if(m_interface.open() != GE_OK)
	{
		std::cout << " Cant reach database! \n";
		exit(-1);
	}
}

Image_Helper_v2::~Image_Helper_v2() {}

general_err_t Image_Helper_v2::doGeometryCalculation(const cv::Mat& image)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Image_Helper_v2::doTemperatureCalculation >> ");
#endif
	// Executable code:

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Image_Helper_v2::doTemperatureCalculation << ");
#endif

	return GE_OK;
}

general_err_t Image_Helper_v2::doTemperatureCalculation(const cv::Mat& image)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Image_Helper_v2::doTemperatureCalculation >> ");
#endif
	// Executable code:
	auto mean = cv::mean(image);
	double min, max;
	cv::minMaxLoc(image, &min, &max);

	m_container.ROI_image.max = static_cast<uint16_t>(max);
	m_container.ROI_image.min = static_cast<uint16_t>(min);
	m_container.ROI_image.mean = static_cast<uint16_t>(mean[0]);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Image_Helper_v2::doTemperatureCalculation << ");
#endif

	return GE_OK;
}

general_err_t Image_Helper_v2::doOutlierDetection(const cv::Mat& image)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Image_Helper_v2::doOutlierDetection >> ");
#endif

	cv::Mat edge;
	doImageProcessing(image, edge);

	m_container.m_outlier.background1.data = m_background1.statsConnectedComponents(edge);
	m_container.m_outlier.background2.data = m_background2.statsConnectedComponents(edge);

	m_background1.view();

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Image_Helper_v2::doOutlierDetection << ");
#endif

	return GE_OK;
}

bool Image_Helper_v2::isObjectValid(void)
{
	bool valid = false;

	if((m_container.m_outlier.background1.data.maxConnected > MOG2_MAX_DIV_MIN) and
	   (m_container.m_outlier.background1.data.maxConnected < MOG2_MAX_DIV_MAX))
	{
		if((m_container.m_outlier.background2.data.ellipse.area < MOG2_MAX_AREA))
		{
			valid = true;
		}
	}
	return valid;
}

void Image_Helper_v2::reportAnalysis(void)
{
	using MSG = Message_Protocol;
	using HANDLER = Message_Handler;

	std::string str = HANDLER::postgres_start();

	auto& time = m_container.m_aquicision.timeOfCapture;
	auto& img_aq = m_container.m_aquicision;
	auto& temp_ROI = m_container.ROI_image;
	auto& outliers = m_container.m_outlier;
	auto& geometry = m_container.m_geometry;

	str += HANDLER::to_Postgres_Subject(
		MSG{{map.at(db_id::CCTV01_MOG2_CC), 0}, {outliers.background1.data.maxConnected, time}});
	str += HANDLER::postgres_append();
	/*
	str += HANDLER::to_Postgres_Subject(
		MSG{{map.at(db_id::CCTV01_HEIGHT), 0}, {outliers.background1.data.ellipse.height, time}});
	str += HANDLER::postgres_append();
	str += HANDLER::to_Postgres_Subject(
		MSG{{map.at(db_id::CCTV01_WIDTH), 0}, {outliers.background1.data.ellipse.width, time}});
	str += HANDLER::postgres_append();
	str += HANDLER::to_Postgres_Subject(
		MSG{{map.at(db_id::CCTV01_AREA), 0}, {outliers.background1.data.ellipse.area, time}});
	str += HANDLER::postgres_append();
	str += HANDLER::to_Postgres_Subject(MSG{
		{map.at(db_id::CCTV01_ASPECT), 0}, {outliers.background1.data.ellipse.aspect_ratio, time}});
	str += HANDLER::postgres_append();
	str +=
		HANDLER::to_Postgres_Subject(MSG{{map.at(db_id::CCTV01_AMOUNT), 0},
										 {outliers.background1.data.amount_of_connections, time}});
	str += HANDLER::postgres_append();
	*/

	str += HANDLER::to_Postgres_Subject(
		MSG{{map.at(db_id::CCTV01_KNN_CC), 0}, {outliers.background2.data.maxConnected, time}});

	str += HANDLER::postgres_end();

	m_interface.post(str);
}

void Image_Helper_v2::reportImages(const cv::Mat& raw, const cv::Mat& raw_ROI,
								   const cv::Mat& visual)
{
	saveImage(visual, "visual", IMAGE_PATH_COLOR);
	save2Python(visual, "Python_Test", IMAGE_PATH_PYTHON);
}
/**
 * @brief doPreproccessing
 * This function handles the preprocessing of the raw image
 * Converting it to a normalized_u8 image ( for further analysis : e.g edge detected )
 * We are also creating the visual representation of the image ( color image )
 *
 * @attention
 *  both the visual and normalized image is streached in values ( autoscaled ) so that the
 *  largest value is mapped to 255 and lowest mapped to 0.  Therefor the normalized image is not
 *  directly related to a temperature. The Raw image is, however.
 *
 * @param[in] const cv::Mat& raw
 *
 * @param[out] cv::Mat& normalized_u8
 * @param[out] cv::Mat& visual
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Image_Helper_v2::doPreproccessing(const cv::Mat& raw, cv::Mat& normalized_u8,
												cv::Mat& visual)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Image_Helper_v2::doPreproccessing >> ");
#endif
	// Executable code:

	cv::normalize(raw, normalized_u8, 0, 255, cv::NORM_MINMAX);
	normalized_u8.convertTo(normalized_u8, CV_8UC1);
	normalized_u8.copyTo(visual);
	cv::applyColorMap(visual, visual, cv::COLORMAP_HOT);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Image_Helper_v2::doPreproccessing << ");
#endif

	return GE_OK;
}
/**
 * @brief  doRegionOfInterestCut
 *  Cut the image to the boarders of the rectangle in order to reduce noise and computation time
 * @attention
 *
 *  ROI created as :  cv::Rect(cv::Point& start_px, cv::Point& end_px)
 *
 * @param[in] const cv::Mat& raw
 * @param[in] const cv::Rect& ROI
 *
 * @param[out] cv::Mat& raw_ROI
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Image_Helper_v2::doRegionOfInterestCut(const cv::Mat& raw, const cv::Rect& ROI,
													 cv::Mat& raw_ROI)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Image_Helper_v2::saveImage >> ");
#endif
	// Executable code:
	raw_ROI = cv::Mat(raw, ROI).clone();

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Image_Helper_v2::saveImage << ");
#endif

	return GE_OK;
}

bool Image_Helper_v2::isDataValid(void)
{
	return m_isDataValid;
}

general_err_t Image_Helper_v2::setDataToValid(const timeval& timeOfCapture)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Image_Helper_v2::setDataToValid >> ");
#endif
	// Executable code:
	m_isDataValid = true;
	m_container.m_aquicision.timeOfCapture = timeOfCapture;
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Image_Helper_v2::setDataToValid << ");
#endif

	return GE_OK;
}

void Image_Helper_v2::save2Python(const cv::Mat& image, const std::string& name,
								  const std::string& path)
{
	std::string full_path;
	full_path = path + name + ".png";
	std::cout << "writing to path : " << full_path << "\n";
	cv::imwrite(full_path.c_str(), image);
}

void Image_Helper_v2::saveImage(const cv::Mat& image, const std::string& name,
								const std::string& path)
{
	std::string full_path;
	//  full_path =  path +
	//  std::to_string(time.tv_sec)+"_"+std::to_string(time.tv_usec)+name+".png";
	full_path = path + Timeservice::getCurrentDate() + "_" + name + ".png";
	std::cout << "writing to path : " << full_path << "\n";
	cv::imwrite(full_path.c_str(), image);
}

void Image_Helper_v2::reset()
{
	m_isDataValid = false;
}

general_err_t Image_Helper_v2::doImageProcessing(const cv::Mat& src, cv::Mat& dist)
{
	Utility_Image::equalizeIllumination(src, dist);

	src.copyTo(dist);
}

void Image_Helper_v2::reportAlarm(void)
{
	using MSG = Message_Protocol;
	using HANDLER = Message_Handler;

	std::string str = HANDLER::postgres_start();

	auto& time = m_container.m_aquicision.timeOfCapture;

	str += HANDLER::to_Postgres_Subject(MSG{{map.at(db_id::CCTV01_ALARM), 0}, {100, time}});

	str += HANDLER::postgres_end();

	m_interface.post(str);
}
