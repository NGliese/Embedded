/***********************************************************************************************+
 *  @brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  @note       ANY RELEVANT NOTES
 *
 *  @file       NVS_esp32.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-03-24
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/NVS_esp32.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "NVS_esp32";
#endif
static bool isInitialized = false;

general_err_t NVS_esp32::initialize()
{
	general_err_t gen_err = GE_OK;
#ifdef __ESP32__
	esp_err_t err = nvs_flash_init();
	if(err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		// NVS partition was truncated and needs to be erased
		// Retry nvs_flash_init
		ESP_ERROR_CHECK(nvs_flash_erase());
		err = nvs_flash_init();
	}
	if(err != ESP_OK)
	{
		gen_err = GE_FAIL;
	}
#endif

	return gen_err;
}
const uint64_t NVS_esp32::read_u64(const std::string& key)
{
	if(!isInitialized)
	{
		if(initialize() == GE_OK)
		{
			isInitialized = true;
		}
		else
		{
			exit(1);
		}
	}
	uint64_t value = 0; // value will default to 0, if not set yet in NVS
#ifdef __ESP32__
	nvs_handle_t my_handle;
	nvs_open("storage", NVS_READWRITE, &my_handle);
	nvs_get_u64(my_handle, key.c_str(), &value);
	// Close
	nvs_close(my_handle);
#endif
	return value;
}

general_err_t NVS_esp32::write_u64(const std::string& key, const uint64_t& value)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> NVS_esp32::fcn >> ");
#endif
	// Executable code:
	if(!isInitialized)
	{
		if(initialize() == GE_OK)
		{
			isInitialized = true;
		}
		else
		{
			exit(1);
		}
	}
#ifdef __ESP32__
	nvs_handle_t my_handle;
	nvs_open("storage", NVS_READWRITE, &my_handle);
	nvs_set_u64(my_handle, key.c_str(), value);
	nvs_commit(my_handle);
	// Close
	nvs_close(my_handle);
#endif
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  NVS_esp32::fcn << ");
#endif

	return GE_OK;
}