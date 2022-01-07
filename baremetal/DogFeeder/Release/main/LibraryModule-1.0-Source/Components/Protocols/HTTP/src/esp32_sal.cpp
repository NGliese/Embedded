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
 *  @file       esp32_sal.cpp
 *  @author     N.G Pedersen <nikolaj.gliese.pedersen@dansac.com>
 *  @version    1.0
 *  @date       2022-01-07
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/esp32_sal.hpp"

#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "esp32_sal";
#endif

esp32_sal::esp32_sal(const std::string& server) : m_server{server} {}
esp32_sal::~esp32_sal() {}

general_err_t esp32_sal::get(const std::string& api_call)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> esp32_sal::get >> ");
#endif
	// Executable code:
#ifdef __ESP32__
	char local_response_buffer[1024] = {0};
	esp_http_client_config_t config;

	config.host = m_server.c_str();
	config.path = api_call.c_str();
	config.user_data = local_response_buffer;
	config.disable_auto_redirect = true;

    
	esp_http_client_handle_t client = esp_http_client_init(&config);

	// GET
	esp_err_t err = esp_http_client_perform(client);
	if(err == ESP_OK)
	{
		std::cout << " HTTP Get Status : <" << (int)esp_http_client_get_status_code(client)
				  << "> , content length : <" << (int)esp_http_client_get_content_length(client)
				  << ">\n";
	}
	else
	{
		std::cout << "Error in HTTP request <" << (int)err << ">\n";
	}
#endif
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  esp32_sal::get << ");
#endif

	return GE_OK;
}

general_err_t esp32_sal::post(const std::string& api_call, const std::string& content)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> esp32_sal::post >> ");
#endif
	// Executable code:

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  esp32_sal::post << ");
#endif

	return GE_OK;
}