/*
 * WiFi_API.cpp
 *
 *  Created on: Feb 1, 2021
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
 *  \file       WiFi_API.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/WiFi_API.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "WiFi_API";
#endif

WiFi_API::WiFi_API() {
}

WiFi_API::WiFi_API(const wifi_conf_t& conf) : m_conf{conf}{
}

WiFi_API::~WiFi_API() {
}

general_err_t WiFi_API::connect() {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> WiFi_API::connect >> ");
    #endif
    // Executable code:f
#ifdef __ESP32__

    m_wifi.setWifiEventHandler(&m_handler);

   // m_wifi.setIPInfo("10.212.163.89", "10.212.163.254", "255.255.252.0");
    // api obtained by nkolban.
    // we are not going to change this back-box
    m_wifi.connectAP(m_conf.ssid,m_conf.password);

    if(!m_wifi.isConnectedToAP())
    {
        return GE_FAIL;
    }
#endif
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< WiFi_API::connect << ");
    #endif

    return GE_OK;
}

general_err_t WiFi_API::disconnect() {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> WiFi_API::disconnect >> ");
    #endif
    // Executable code:
#ifdef __ESP32__

#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< WiFi_API::disconnect << ");
    #endif

    return GE_OK;
}
