
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
 *  \file       ConnectedComponents.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/ConnectedComponents.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "ConnectedComponents";
#endif

general_err_t ConnectedComponents::drawConnectedComponents(const cv::Mat& forground,
														   cv::Mat& drawing)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> ConnectedComponents::drawConnectedComponents >> ");
#endif
	// Executable code:

	int ksize = 2;
	cv::morphologyEx(forground, forground, cv::MORPH_OPEN,
					 cv::getStructuringElement(cv::MORPH_RECT, cv::Size_<int>{ksize, ksize}));
	cv::morphologyEx(forground, forground, cv::MORPH_CLOSE,
					 cv::getStructuringElement(cv::MORPH_RECT, cv::Size_<int>{ksize, ksize}));

	bool cont_found = false;
	std::vector<std::vector<cv::Point>> cont;
	findContours(forground, cont, cv::CHAIN_APPROX_SIMPLE, cv::RETR_TREE, cv::Point(0, 0));
	std::vector<int> ix;
	for(size_t i = 0; i < cont.size(); i++)
	{
		auto& ele = cont.at(i);
		double len = ele.size();
		double q = (forground.cols + forground.rows) / 4;

		std::cout << " size of len :" << (int)len << " size of q : " << (int)q << "\n";

		if(len > q)
		{
			ix.push_back(i);
		}
	}

	std::cout << " size of ix :" << (int)ix.size() << "\n";
	for(auto ele : ix)
	{
		cv::drawContours(drawing, cont, ele, cv::Scalar{255, 255, 0}, 1);
		cont_found = true;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< ConnectedComponents::drawConnectedComponents << ");
#endif

	return cont_found == true ? GE_OK : GE_NO_DATA;
}

general_err_t ConnectedComponents::drawConnectedComponentsOpenCV(const cv::Mat& forground,
																 cv::Mat& drawing)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> ConnectedComponents::drawConnectedComponents >> ");
#endif
	// Executable code:

	cv::connectedComponents(forground, drawing);
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< ConnectedComponents::drawConnectedComponents << ");
#endif

	return GE_NO_DATA;
}

uint32_t ConnectedComponents::maxConnectedComponents(const cv::Mat& forground, int ksize)
{
	cv::morphologyEx(forground, forground, cv::MORPH_OPEN,
					 cv::getStructuringElement(cv::MORPH_RECT, cv::Size_<int>{ksize, ksize}));
	cv::morphologyEx(forground, forground, cv::MORPH_CLOSE,
					 cv::getStructuringElement(cv::MORPH_RECT, cv::Size_<int>{ksize, ksize}));

	std::vector<std::vector<cv::Point>> cont;
	findContours(forground, cont, cv::CHAIN_APPROX_SIMPLE, cv::RETR_TREE, cv::Point(0, 0));
	uint32_t max = 0;

	for(auto ele : cont)
	{
		if(ele.size() > max)
		{
			max = ele.size();
		}
	}

	return max;
}

ConnectedComponents::container_t
	ConnectedComponents::statsConnectedComponents(const cv::Mat& forground, int ksize)
{
	cv::morphologyEx(forground, forground, cv::MORPH_OPEN,
					 cv::getStructuringElement(cv::MORPH_RECT, cv::Size_<int>{ksize, ksize}));
	cv::morphologyEx(forground, forground, cv::MORPH_CLOSE,
					 cv::getStructuringElement(cv::MORPH_RECT, cv::Size_<int>{ksize, ksize}));

	std::vector<std::vector<cv::Point>> cont;
	findContours(forground, cont, cv::CHAIN_APPROX_SIMPLE, cv::RETR_TREE, cv::Point(0, 0));

	container_t data;

	data.maxConnected = 0;
	data.amount_of_connections = cont.size();

	// "best" way to get index of max connected
	int index = 0;
	int count = 0;

	for(auto ele : cont)
	{
		if(ele.size() > data.maxConnected)
		{
			data.maxConnected = ele.size();
			index = count;
		}
		count++;
	}

	if(data.maxConnected > 5)
	{
		auto ellipse = cv::fitEllipse(cont.at(index));

		data.ellipse.height = ellipse.size.height;
		data.ellipse.width = ellipse.size.width;
		data.ellipse.aspect_ratio = ellipse.size.aspectRatio();
		data.ellipse.area = ellipse.size.area();
	}

	return data;
}
