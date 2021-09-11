/*
 * RPICam_Capture.cpp
 *
 *  Created on: Jul 6, 2021
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
 *  \file       RPICam_Capture.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "include/RPICam_Capture.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "RPICam_Capture";
#endif

RPICam_Capture::~RPICam_Capture() {
}

general_err_t RPICam_Capture::capture(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> RPICam_Capture::capture >> ");
    #endif
    // Executable code:
    RPICamV2 m_cam;

    auto err = m_cam.takePicture();
    if (!General_Error::check_error(err, "Not able to capture image") )
    {
        exit(-1);
    }
    auto img = m_cam.getPicture();
    Utility_Image::view_image(img, "View");

    Timeservice::wait_ms(5000);


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< RPICam_Capture::capture << ");
    #endif

    return GE_OK;
}

general_err_t RPICam_Capture::stream(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> RPICam_Capture::stream >> ");
    #endif
    // Executable code:
    RPICamV2 m_cam;

    for(;;){
        std::cout << " taking picture ...\n";
#if 1
       auto err = m_cam.takePicture();
       if (!General_Error::check_error(err, "Not able to capture image") )
       {
           exit(-1);
       }
       auto img = m_cam.getPicture();
       Utility_Image::view_image(Utility_Image::zoom(img,0.25), "View");
#endif

       Utility_Image::wait(0);

    }


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< RPICam_Capture::stream << ");
    #endif

    return GE_OK;
}
#define IMG_PATH ("/media/pi/usb/CCTV/raw/")
#define IMG_COLOR ("/media/pi/usb/CCTV/MEGA/color/")
#define IMG_GRAY ("/media/pi/usb/CCTV/MEGA/gray/")
general_err_t RPICam_Capture::capture_and_save() {
#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, ">> RPICam_Capture::capture >> ");
#endif
// Executable code:
RPICamV2 m_cam;

auto err = m_cam.takePicture();
if (!General_Error::check_error(err, "Not able to capture image") )
{
    exit(-1);
}
auto img = m_cam.getPicture();
timeval tm; // get the time
gettimeofday(&tm,nullptr);
Utility_Image::saveImage(tm, img, "TestImage", IMG_PATH);


#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, "<< RPICam_Capture::capture << ");
#endif

return GE_OK;
}

general_err_t RPICam_Capture::stream_vinfo(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> enclosing_method >> ");
    #endif
    // Executable code:
    RPICamV2 m_cam;

    for(;;){

       auto err = m_cam.takePicture();
       if (!General_Error::check_error(err, "Not able to capture image") )
       {
           exit(-1);
       }
       auto img = m_cam.getPicture();
       Utility_Image::putDate(img);


       Utility_Image::view_image(Utility_Image::zoom(img,0.25), "View");

       Utility_Image::wait(1);

    }
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< enclosing_method << ");
    #endif

    return GE_OK;
}
