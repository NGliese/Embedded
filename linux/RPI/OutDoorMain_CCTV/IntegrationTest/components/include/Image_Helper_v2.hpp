/*
 * Image_Helper_v2.hpp
 *
 *  Created on: Jul 29, 2021
 *      Author: espenv
 */

#ifndef SRC_COMPONENTS_INCLUDE_IMAGE_HELPER_V2_HPP_
#define SRC_COMPONENTS_INCLUDE_IMAGE_HELPER_V2_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Image_Helper_v2.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Image_Helper_v2.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Datasheet Awareness              		        |
 +------------------------------------------------------------------------------+
 |
 |
 |  Datasheet Awareness 1):
 |  	Link:[ ], Jul 29, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jul 29, 2021
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/

#include "../../../LibraryModule-1.0-Source/Components/Global_Include/BASIC.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include "../../../LibraryModule-1.0-Source/Components/AnalysisTools/ImageAnalysis_OpenCV/include/Background_Extractor.hpp"
#include "../../../LibraryModule-1.0-Source/Components/AnalysisTools/ImageAnalysis_OpenCV/include/Utility_Image.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Global_Include/Database_ID_Base.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Objects/Message/include/Message_Handler.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Objects/Timeservice/include/Timeservice.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Protocols/HTTP/include/postgresql_interface.hpp"

#include <opencv2/opencv.hpp>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Image_Helper_v2
{
#ifdef __UNITTEST__
	friend class friend_Image_Helper_v2;
#endif
  public:
	Image_Helper_v2();
	~Image_Helper_v2();
	general_err_t doGeometryCalculation(const cv::Mat& image);
	general_err_t doTemperatureCalculation(const cv::Mat& image);
	general_err_t doOutlierDetection(const cv::Mat& image);
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
	general_err_t doPreproccessing(const cv::Mat& raw, cv::Mat& normalized_u8, cv::Mat& visual);
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
	general_err_t doRegionOfInterestCut(const cv::Mat& raw, const cv::Rect& ROI, cv::Mat& raw_ROI);
	general_err_t setDataToValid(const timeval& timeOfCapture);
	bool isObjectValid(void);
	bool isDataValid(void);

	void reportAnalysis(void);
	void reportAlarm(void);
	void reportImages(const cv::Mat& raw, const cv::Mat& raw_ROI, const cv::Mat& visual);

	void saveImage(const cv::Mat& image, const std::string& name, const std::string& path);
	void save2Python(const cv::Mat& image, const std::string& name, const std::string& path);
	void reset();

	inline void incrementImageCaptureSuccess(void)
	{
		m_container.m_aquicision.amount_of_success++;
	};
	inline void incrementImageCaptureFail(void)
	{
		m_container.m_aquicision.amount_of_fail++;
	};
	inline void incrementImageCaptureTimeout(void)
	{
		m_container.m_aquicision.amount_of_timeout++;
	};

  private:
	general_err_t doImageProcessing(const cv::Mat& src, cv::Mat& dist);

	struct image_aquicision
	{
		uint64_t amount_of_success = 0;
		uint64_t amount_of_fail = 0;
		uint64_t amount_of_timeout = 0;
		timeval timeOfCapture = {0, 0};
	};
	struct temperature_container_t
	{
		uint16_t min;
		uint16_t max;
		uint16_t mean;
	};
	struct geometry_container_t
	{
	};
	struct background_data_counter_t
	{
		//   uint16_t count_connected_components;
		ConnectedComponents::container_t data;
	};

	struct outlier_container_t
	{
		background_data_counter_t background1;
		background_data_counter_t background2;
	};

	struct data_container_t
	{
		image_aquicision m_aquicision;
		temperature_container_t ROI_image;
		temperature_container_t Object_image;
		geometry_container_t m_geometry;
		outlier_container_t m_outlier;
	};

	bool m_isDataValid;
	data_container_t m_container;
	Background_Extractor m_background1;
	Background_Extractor m_background2;
	postgresql_interface m_interface;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Image_Helper_v2
{
  public:
	friend_Image_Helper_v2(){};
	friend_Image_Helper_v2(Image_Helper_v2* Image_Helper_v2) : m_sensor{Image_Helper_v2} {};

	~friend_Image_Helper_v2(){};

  private:
	Image_Helper_v2* m_sensor;
};
#endif

#endif /* SRC_COMPONENTS_INCLUDE_IMAGE_HELPER_V2_HPP_ */
