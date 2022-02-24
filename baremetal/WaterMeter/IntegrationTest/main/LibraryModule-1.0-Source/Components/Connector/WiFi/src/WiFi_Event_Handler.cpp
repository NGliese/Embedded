/*
 * WiFi_Event_Handler.cpp
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
 *  \file       WiFi_Event_Handler.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/WiFi_Event_Handler.hpp"

#ifdef __ESP32__

#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "WiFi_Event_Handler";
#endif

WiFi_Event_Handler::~WiFi_Event_Handler() {}

esp_err_t WiFi_Event_Handler::apStaDisconnected(system_event_ap_stadisconnected_t info)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> WiFi_Event_Handler::apStaDisconnected >> ");
#endif
	// Executable code:
	LOG_PRINT_INFO(LOG_TAG, "esp_wifi_connect");
	esp_err_t errRc = ::esp_wifi_connect();
	if(errRc != ESP_OK)
	{
		abort();
	}
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< WiFi_Event_Handler::apStaDisconnected << ");
#endif

	return ESP_OK;
}
#endif
