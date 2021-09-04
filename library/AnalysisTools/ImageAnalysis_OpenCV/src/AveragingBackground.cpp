/*
 * AveragingBackground.cpp
 *
 *  Created on: Jul 12, 2021
 *      Author: nikolaj
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
 *  \file       AveragingBackground.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/AveragingBackground.hpp"




//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "AveragingBackground";
#endif

AveragingBackground::AveragingBackground(const cv::Mat &img) : m_first_accumulation{true}, min_avg_counter{150},m_first_background{true} {




    auto size = img.size();
    IavgF = cv::Mat(size,CV_32FC3, cv::Scalar(0, 0, 0));
    IdiffF = cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));
    IprevF = cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));
    IhiF = cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));
    IlowF = cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));

    Ilow1 = cv::Mat(size,CV_32FC1,cv::Scalar(0));
    Ilow2 = cv::Mat(size,CV_32FC1,cv::Scalar(0));
    Ilow3 = cv::Mat(size,CV_32FC1,cv::Scalar(0));
    Ihi1 = cv::Mat(size,CV_32FC1,cv::Scalar(0));
    Ihi2 = cv::Mat(size,CV_32FC1,cv::Scalar(0));
    Ihi3 = cv::Mat(size,CV_32FC1,cv::Scalar(0));

    Icount = 0.00001; // Protect against divide by zero

    Iscratch1 = cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));
    Iscratch2 = cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));

    Igray1 = cv::Mat(size,CV_32FC1,cv::Scalar(0));
    Igray2 = cv::Mat(size,CV_32FC1,cv::Scalar(0));
    Igray3 = cv::Mat(size,CV_32FC1,cv::Scalar(0));

    Imask =  cv::Mat(size,CV_8UC1,cv::Scalar(0));
  //  cv::size(img);


    // store the default counter values
    default_min_avg_counter = min_avg_counter;

}

AveragingBackground::~AveragingBackground() {
    IavgF.release();
    IdiffF.release();
    IprevF.release();
    IhiF.release();
    IlowF.release();

    Ilow1.release();
    Ilow2.release();
    Ilow3.release();
    Ihi1.release();
    Ihi2.release();
    Ihi3.release();

    Iscratch1.release();
    Iscratch2.release();

    Igray1.release();
    Igray2.release();
    Igray3.release();
    Imask.release();
}

/**
 * @brief
 * Learn the background statistcs for one more frame
 * img is a color sample of the background, 3-channel , 8u
 *
 *
 * @param[in] const cv::Mat &img
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t AveragingBackground::accumulateBackground(const cv::Mat &img) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::accumulateBackground >> ");
    #endif
    // Executable code:
   //cv::cvtColor(img, Iscratch1,cv::COLOR_RGB2RGBA);
    img.convertTo(Iscratch1, CV_32F, 1,0);
    // cv::convertScaleAbs(img, Iscratch1);
    if(!m_first_accumulation)
    {

        cv::accumulate(Iscratch1, IavgF);
        cv::absdiff(Iscratch1, IprevF, Iscratch2);
        cv::accumulate(Iscratch2, IdiffF);
        Icount += 1.0;
    }
    m_first_accumulation = false;
    IprevF = Iscratch1.clone();
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::accumulateBackground << ");
    #endif

    return GE_OK;
}

general_err_t AveragingBackground::createModelsFromStats() {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::createModelsFromStats >> ");
    #endif
    // Executable code:
    //cv::cvtColor(img, Iscratch1,cv::COLOR_RGB2RGBA);
    IavgF.convertTo(IavgF, CV_32F, (double)(1.0/Icount));
    IdiffF.convertTo(IdiffF, CV_32F, (double)(1.0/Icount));

    // make sure idiff is always not 0
    cv::add(IdiffF, cv::Scalar(1.0,1.0,1.0), IdiffF);
    setHighThreshold( 7.0 );
    setLowThreshold( 6.0 );

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::createModelsFromStats << ");
    #endif

    return GE_OK;
}

general_err_t AveragingBackground::setHighThreshold(float scale) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::setHighThreshold >> ");
    #endif
    // Executable code:
    IdiffF.convertTo(Iscratch1, CV_32F, scale);
    cv::add(Iscratch1, IavgF, IhiF);
    cv::extractChannel(IhiF, Ihi1,0);
    cv::extractChannel(IhiF, Ihi2,1);
    cv::extractChannel(IhiF, Ihi3,2);

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::setHighThreshold << ");
    #endif

    return GE_OK;
}
/**
 * @brief
 *  Create a binary 0,255 mask where 255 means foreground pixel
 *
 * @attention
 *
 *
 * @param[in] const cv::Mat &img : the raw image
 * @param[in]
 *
 * @param[out] cv::Mat &foreground an 8bit foreground-only image 0 -> background : 255 -> foreground
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t AveragingBackground::getForeground(const cv::Mat &img,
        cv::Mat &foreground) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::getForeground >> ");
    #endif
    // Executable code:
    img.convertTo(Iscratch1, CV_32F, 1,0);
    cv::extractChannel(Iscratch1, Igray1,0);
    cv::extractChannel(Iscratch1, Igray2,1);
    cv::extractChannel(Iscratch1, Igray3,2);

    //channel 1
    cv::inRange(Igray1, Ilow1, Ihi1, foreground);

    // channel 2
    cv::inRange(Igray2, Ilow2, Ihi2, Imask);
    cv::bitwise_or(foreground, Imask, foreground);

    // channel 3
    cv::inRange(Igray3, Ilow3, Ihi3, Imask);
    cv::bitwise_or(foreground, Imask, foreground);

    cv::bitwise_not(foreground, foreground);


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::getForeground << ");
    #endif

    return GE_OK;
}

general_err_t AveragingBackground::clearBackground(const cv::Mat &img) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::clearBackground >> ");
    #endif
    // Executable code:
    auto size = img.size();
    // release old memory
    IavgF.release();
    IdiffF.release();
    IprevF.release();

    IavgF = cv::Mat(size,CV_32FC3, cv::Scalar(0, 0, 0));
    IdiffF = cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));
    IprevF =  cv::Mat(size,CV_32FC3,cv::Scalar(0, 0, 0));
    Icount = 0.0001;
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::clearBackground << ");
    #endif

    return GE_OK;
}


general_err_t AveragingBackground::setLowThreshold(float scale) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::setLowThreshold >> ");
    #endif
    // Executable code:
    IdiffF.convertTo(Iscratch1, CV_32F, scale);
       cv::subtract( IavgF,Iscratch1, IlowF);
       cv::extractChannel(IlowF, Ilow1,0);
       cv::extractChannel(IlowF, Ilow2,1);
       cv::extractChannel(IlowF, Ilow3,2);


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::setLowThreshold << ");
    #endif

    return GE_OK;
}


/**
 * @brief      Main function to call. If we return GE_OK, we know that a foreground has been captured
 *              The creation of background and how we are segmenting the foreground from the background is encapsulated inside the function
 *
 * @attention
 *              If error code is not GE_OK, the foreground is not usable
 *
 *
 *
 * @param[in] const cv::Mat &img
 * @param[in]
 *
 * @param[out] cv::Mat &foreground
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    - GE_NO_DATE
 *    -
 */
general_err_t AveragingBackground::run(const cv::Mat &img,
        cv::Mat &foreground) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::run >> ");
    #endif
    // Executable code:

    auto err = updateBackground(img);
    if(m_first_background and  err != GE_OK )
    {
        return GE_NO_DATA;
    }
    //we have a background
    m_first_background = false;

    // we are getting the foreground
    err = getForeground(img, foreground);


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::run << ");
    #endif

    return err;
}



general_err_t AveragingBackground::updateBackground(const cv::Mat &img) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> AveragingBackground::updateBackground >> ");
    #endif
    // Executable code:


    accumulateBackground(img);
    --min_avg_counter;
    if(min_avg_counter > 0)
    {
        // we do not yet have a background ready
        return GE_NO_DATA;
    }

    // update statistical model
    createModelsFromStats();

    // clear background
    clearBackground(img);
    // reset counter
    min_avg_counter = default_min_avg_counter;



    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< AveragingBackground::updateBackground << ");
    #endif

    return GE_OK;
}

