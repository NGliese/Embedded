/*
 * Load_Image.hpp
 *
 *  Created on: Feb 22, 2021
 *      Author: espenv
 */

#ifndef SIMULATION_TEST_UTILS_INCLUDE_UTILITY_IMAGE_HPP_
#define SIMULATION_TEST_UTILS_INCLUDE_UTILITY_IMAGE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Utility_Image.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Load_Image.hpp, is designed as:
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
 |  	Link:[ ], Feb 23, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Feb 23, 2021
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
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include "../../../Objects/Timeservice/include/Timeservice.hpp"

#include <opencv2/opencv.hpp>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Utility_Image
{
#ifdef __UNITTEST__
	friend class friend_Load_Image;
#endif
  public:
	enum class loader_conf
	{
		color,
		gray
	};
	enum class object_color
	{
		GREEN,
		RED,
		BLUE
	};
	static cv::Mat load_image(const std::string& path,
							  const loader_conf& conf = loader_conf::color);
	static void view_image(const cv::Mat& m, const std::string& name = "Viewer");
	static cv::Mat zoom(const cv::Mat& img, double scale = 5);
	static cv::Mat draw_ellipse(const cv::Mat& img, const std::vector<cv::RotatedRect>& vec);
	static void wait(uint16_t time_ms = 0);
	static void saveImage(const timeval& time, const cv::Mat& m, const std::string& name,
						  const std::string& path);
	static general_err_t getROI(const cv::Mat& src, const cv::Rect ROI, cv::Mat& dist);
	static general_err_t putDate(cv::Mat& img);
	static general_err_t putFPS(cv::Mat& img, const uint16_t fps);
	static general_err_t putMask(const cv::Mat& src, cv::Mat& dist, const cv::Point& start,
								 const cv::Point& end);
	static general_err_t rotateImage(cv::Mat& src, const double newAngle);
	static general_err_t equalizeIllumination(const cv::Mat& src, cv::Mat& dist);

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Load_Image
{
  public:
	friend_Load_Image(Utility_Image* Utility_Image) : m_sensor{Utility_Image} {};

	~friend_Load_Image(){};

  private:
	Utility_Image* m_sensor;
};
#endif

#endif /* SIMULATION_TEST_UTILS_INCLUDE_UTILITY_IMAGE_HPP_ */
