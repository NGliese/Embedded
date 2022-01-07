

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
 *  \file       Load_Image.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Utility_Image.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "Load_Image";
#endif

cv::Mat Utility_Image::load_image(const std::string& path, const loader_conf& conf)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Load_Image::load_image >> ");
#endif
	// Executable code:
	if(conf == loader_conf::gray)
		return cv::imread(path, cv::IMREAD_GRAYSCALE);

	// return color img
	return cv::imread(path);
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Load_Image::load_image << ");
#endif
}

void Utility_Image::view_image(const cv::Mat& m, const std::string& name)
{
	namedWindow(name, cv::WINDOW_NORMAL);
	cv::imshow(name, m);
}

cv::Mat Utility_Image::zoom(const cv::Mat& img, double scale)
{
	cv::Mat m;
	cv::resize(img, m, cv::Size(), scale, scale, cv::INTER_NEAREST);
	return m;
}

cv::Mat Utility_Image::draw_ellipse(const cv::Mat& img, const std::vector<cv::RotatedRect>& vec)
{
	auto m = img.clone();
	cv::Scalar color = cv::Scalar(0, 255, 0);
	for(auto ele : vec)
	{
		cv::ellipse(m, ele, color);
	}
	return m;
}

void Utility_Image::wait(uint16_t time_ms)
{
	cv::waitKey(time_ms);
}

void Utility_Image::saveImage(const timeval& time, const cv::Mat& m, const std::string& name,
							  const std::string& path)
{
	std::string full_path;
	full_path =
		path + std::to_string(time.tv_sec) + "_" + std::to_string(time.tv_usec) + name + ".png";
	std::cout << "writing to path : " << full_path << "\n";
	imwrite(full_path.c_str(), m);
}

/**
 * @brief  simple function to place a date at the top left corner of the image
 *
 * @attention
 *
 *
 * @param[in] cv::Mat &img
 *
 * @param[out] cv::Mat &img
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Utility_Image::putDate(cv::Mat& img)
{
	cv::putText(img, Timeservice::getCurrentDate(), {30, 30}, 1, 2, {255, 255, 0}, 3);
	return GE_OK;
}

/**
 * @brief simple function to put measured fps at the top right corner of an image
 *
 * @attention
 *
 *
 * @param[in] cv::Mat &img
 * @param[in] const uint16_t fps
 *
 * @param[out] cv::Mat &img
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Utility_Image::putFPS(cv::Mat& img, const uint16_t fps)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Utility_Image::putFPS >> ");
#endif
	// Executable code:
	cv::putText(img, std::to_string(fps), {img.cols - 100, 30}, 1, 2, {255, 255, 0}, 3);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Utility_Image::putFPS << ");
#endif

	return GE_OK;
}

/**
 * @brief      PutMask
 *        Place a rectangle mask over an image defined by the rect
 *
 * @attention
 *
 *
 * @param[in] const Image &src
 * @param[in]
 *
 * @param[out] Image &dist
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Utility_Image::putMask(const cv::Mat& src, cv::Mat& dist, const cv::Point& start,
									 const cv::Point& end)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> putMask >> ");
#endif
	// Executable code:
	src.copyTo(dist);
	cv::rectangle(dist, start, end, cv::Scalar(0, 255, 0), -1, cv::LINE_8);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< putMask << ");
#endif

	return GE_OK;
}

/**
 * @brief get a Region of interest of the image
 *
 * @attention
 *
 *
 * @param[in] const cv::Mat &src
 * @param[in] const cv::Rect ROI
 *
 * @param[out] cv::Mat &dist
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Utility_Image::getROI(const cv::Mat& src, const cv::Rect ROI, cv::Mat& dist)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> enclosing_method >> ");
#endif
	// Executable code:
	dist = cv::Mat(src, ROI);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< enclosing_method << ");
#endif

	return GE_OK;
}

/**
 * @brief
 *
 * @attention
 *
 *
 * @param[in] int newAngle
 *
 * @param[in / out] cv::Mat &src
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Utility_Image::rotateImage(cv::Mat& src, const double newAngle)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Utility_Image::rotateImage >> ");
#endif
	// Executable code:
	cv::Point2f pt(src.cols / 2., src.rows / 2.); // point from where to rotate
	cv::Mat r = cv::getRotationMatrix2D(pt, newAngle, 1.0); // Mat object for storing after rotation
	cv::warpAffine(src, src, r,
				   cv::Size(src.cols, src.rows)); /// applie an affine transforation to image.

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Utility_Image::rotateImage << ");
#endif

	return GE_OK;
}

/**
 * @brief Normalize/equalize the brighness in the image to reduce impact of
 *        Illumination noises
 *
 * @attention
 *
 *
 * @param[in] const cv::Mat &src
 * @param[in]
 *
 * @param[out] cv::Mat &dist
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Utility_Image::equalizeIllumination(const cv::Mat& src, cv::Mat& dist)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Utility_Image::equalizeIllumination >> ");
#endif
	// Executable code:

	// we are not going to redeclare this vector on every single image
	static std::vector<cv::Mat> equalizer_subset{3};

	cv::cvtColor(src, dist, cv::COLOR_RGB2Lab);
	cv::split(dist, equalizer_subset);

	cv::equalizeHist(equalizer_subset.at(0), equalizer_subset.at(0));

	cv::merge(equalizer_subset, dist);

	cv::cvtColor(dist, dist, cv::COLOR_Lab2RGB);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Utility_Image::equalizeIllumination << ");
#endif

	return GE_OK;
}
