/*
 * AveragingBackground.hpp
 *
 *  Created on: Jul 12, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_AVERAGINGBACKGROUND_HPP_
#define INCLUDE_AVERAGINGBACKGROUND_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  AveragingBackground.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, AveragingBackground.hpp, is designed as:
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
 |  	Link:[ ], Jul 12, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jul 12, 2021
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


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <array>




/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class AveragingBackground {
#ifdef __UNITTEST__
    friend class friend_AveragingBackground;
#endif
public:
    AveragingBackground(const cv::Mat& img) ;
    ~AveragingBackground();

    general_err_t run(const cv::Mat& img, cv::Mat& foreground);
    general_err_t clearBackground(const cv::Mat &img);
    general_err_t accumulateBackground(const cv::Mat& img);
    general_err_t createModelsFromStats(void);
    general_err_t getForeground(const cv::Mat& img, cv::Mat& foreground);


    general_err_t updateBackground(const cv::Mat& img);

private:
// Float, 3-channel images
cv::Mat IavgF,IdiffF,IprevF,IhiF,IlowF;
cv::Mat Iscratch1,Iscratch2;
// Float, 1-channel images
cv::Mat Igray1,Igray2,Igray3;
cv::Mat Ilow1,Ilow2,Ilow3;
cv::Mat Ihi1,Ihi2,Ihi3;
// Byte, 1-channel image
cv::Mat Imask;

general_err_t setHighThreshold(float scale);
general_err_t setLowThreshold(float scale);
//counts number of images learned for averaging later
float Icount;
bool m_first_accumulation;
bool m_first_background;

// counters to keep track of run time flow
size_t min_avg_counter; // we want at least this amount of images before we create a background


// default values for the counters
size_t default_min_avg_counter;
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_AveragingBackground {
public:
    friend_AveragingBackground(){};
    friend_AveragingBackground(AveragingBackground * AveragingBackground) : m_sensor{AveragingBackground} { };

    ~friend_AveragingBackground(){};

private:
    AveragingBackground * m_sensor;
};
#endif





#endif /* INCLUDE_AVERAGINGBACKGROUND_HPP_ */
