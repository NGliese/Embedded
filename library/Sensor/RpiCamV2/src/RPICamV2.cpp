/*
 * RPICamV2.cpp
 *
 *  Created on: Jul 4, 2021
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
 *  \file       RPICamV2.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/RPICamV2.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "RPICamV2";
#endif

RPICamV2::RPICamV2() {

#ifdef __RPI__
if(!m_cam.open())
{
    exit(-1);
}

#endif


}

RPICamV2::~RPICamV2() {
#ifdef __RPI__

if(m_cam.isOpened()){
    std::cout << " Closing rpi cam ! \n";
    m_cam.release();
}
#endif
}

general_err_t RPICamV2::takePicture(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> RPICamV2::takePicture >> ");
    #endif
    // Executable code:

#ifdef __RPI__
   m_cam.grab(); // blocking function
   m_cam.retrieve(m_image);
#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< RPICamV2::takePicture << ");
    #endif

    return GE_OK;
}
