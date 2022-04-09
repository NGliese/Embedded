/*
 * OTA.cpp
 *
 *  Created on: Oct 4, 2021
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
 *  \file       OTA.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/OTA.hpp"

#include <cstring>
//#define DEBUG // default uncommeted

static const char* LOG_TAG = "OTA";

bool is_req_body_started = false;

int content_length = -1;
int content_received = 0;
#ifdef __ESP32__
esp_ota_handle_t ota_handle;
#endif

OTA::OTA() {}

OTA::~OTA() {}

general_err_t OTA::update(const char* msg, const size_t& length)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> OTA::update >> ");
#endif
	// Executable code:

	if(length < 25)
	{
		std::string str{msg, length};
		std::cout << str << "\n";
		if(str.compare("ota_start") == 0)
		{
			std::cout << "do ota start process ....\n";
			start_process(msg, length);
		}
		if(str.compare("ota_stop") == 0)
		{
			std::cout << "do ota stop process ....\n";
			stop_process(msg, length);
		}
	}
	else
	{
		update_process(msg, length);
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< OTA::update << ");
#endif

	return GE_OK;
}

general_err_t OTA::start_process(const char* msg, const size_t& length)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> OTA::start_process >> ");
#endif
	// Executable code:
#ifdef __ESP32__
	const esp_partition_t* update_partition = esp_ota_get_next_update_partition(NULL);
	ESP_ERROR_CHECK(esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &ota_handle));
#endif
	is_req_body_started = true;

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< OTA::start_process << ");
#endif

	return GE_OK;
}

general_err_t OTA::stop_process(const char* msg, const size_t& length)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> OTA::stop_process >> ");
#endif
	// Executable code:
	std::cout << " we have finished updating, and recieved a total of : " << content_received
			  << " bytes \n";
#ifdef __ESP32__
	ESP_ERROR_CHECK(esp_ota_end(ota_handle));
	const esp_partition_t* update_partition = esp_ota_get_next_update_partition(NULL);
	esp_err_t err = esp_ota_set_boot_partition(update_partition);
	const esp_partition_t* boot_partition = esp_ota_get_boot_partition();
	ESP_LOGI(LOG_TAG, "Next boot partition subtype %d at offset 0x%x", boot_partition->subtype,
			 boot_partition->address);
	ESP_LOGI(LOG_TAG, "Prepare to restart system!");
	esp_restart();
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< OTA::stop_process << ");
#endif

	return GE_OK;
}

general_err_t OTA::update_process(const char* msg, const size_t& length)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> OTA::update_process >> ");
#endif
	// Executable code:
	if(is_req_body_started)
	{
#ifdef __ESP32__
		esp_ota_write(ota_handle, msg, length);
#endif
		content_received += length;
	}
	else
	{
		return GE_FAIL;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< OTA::update_process << ");
#endif

	return GE_OK;
}

bool OTA::isUpdateStarted(void)
{
	return is_req_body_started;
}
