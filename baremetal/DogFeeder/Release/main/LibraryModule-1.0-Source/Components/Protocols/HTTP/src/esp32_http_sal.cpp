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
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-01-07
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/esp32_http_sal.hpp"
#include "../include/esp32_http_settings.hpp"
//#define DEBUG // default uncommeted

//#ifdef DEBUG
static const char* LOG_TAG = "esp32_sal";
//#endif
static std::string m_recieved_content;
static FreeRTOS::Semaphore m_semaphore_client_handler; // there should only be one

#ifdef __ESP32__
esp_err_t esp32_http_sal::_http_event_handle(esp_http_client_event_t* evt)
{
	switch(evt->event_id)
	{
		case HTTP_EVENT_ERROR:
			LOG_PRINT_INFO(LOG_TAG, "HTTP_EVENT_ERROR");
			break;
		case HTTP_EVENT_ON_CONNECTED:
			LOG_PRINT_INFO(LOG_TAG, "HTTP_EVENT_ON_CONNECTED");
			break;
		case HTTP_EVENT_HEADER_SENT:
			LOG_PRINT_INFO(LOG_TAG, "HTTP_EVENT_HEADER_SENT");
			break;
		case HTTP_EVENT_ON_HEADER:
			LOG_PRINT_INFO(LOG_TAG, "HTTP_EVENT_ON_HEADER");
			printf("%.*s", evt->data_len, (char*)evt->data);
			break;
		case HTTP_EVENT_ON_DATA:
			LOG_PRINT_INFO(LOG_TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
			if(!esp_http_client_is_chunked_response(evt->client))
			{
				std::string str((char*)evt->data, (size_t)evt->data_len);
				m_recieved_content = str;
#ifdef DEBUG
				std::cout << "recieved data is : <" << m_recieved_content << ">\n";
#endif
			}

			break;
		case HTTP_EVENT_ON_FINISH:
			LOG_PRINT_INFO(LOG_TAG, "HTTP_EVENT_ON_FINISH");

			break;
		case HTTP_EVENT_DISCONNECTED:
			LOG_PRINT_INFO(LOG_TAG, "HTTP_EVENT_DISCONNECTED");
			break;
	}
	return ESP_OK;
}
#endif
esp32_http_sal::esp32_http_sal(const std::string& server, const int& port)
	: m_server{server}, m_port{port}
{
}
esp32_http_sal::~esp32_http_sal() {}

general_err_t esp32_http_sal::get(const std::string& api_call, std::string& output)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> esp32_sal::get >> ");
#endif
	// Executable code:

	std::cout << " calling get request : <" << m_server << api_call << "> on port <" << m_port
			  << ">\n";

	if(!m_semaphore_client_handler.take(5000, m_server + api_call + std::to_string(m_port)))
	{
		std::cerr << " Not able to take semaphore! \n";
		return GE_SEMAPHORE_NOT_TAKEN;
	}
	general_err_t ge_err = GE_OK;
#ifdef __ESP32__
	esp_http_client_config_t config = DEFAULT_HTTP_CONFIG;
	config.url = m_server.c_str();
	config.host = m_server.c_str();
	config.port = m_port;
	config.path = api_call.c_str();
	config.event_handler = this->_http_event_handle;

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> getting handle ... >> ");
#endif
	m_client = esp_http_client_init(&config);
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> handle OK ... >> ");
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Perform http request ... >> ");
#endif
	// GET

	esp_err_t err = esp_http_client_perform(m_client);
	if(err == ESP_OK)
	{
		std::cout << " HTTP Get Status : <" << (int)esp_http_client_get_status_code(m_client)
				  << "> , content length : <" << (int)esp_http_client_get_content_length(m_client)
				  << ">\n";
		output = m_recieved_content;
	}
	else
	{
		std::cout << "Error in HTTP request <" << (int)err << ">\n";
		ge_err = GE_FAIL;
	}

	esp_http_client_cleanup(m_client);
	// make sure we release the semaphore
	m_semaphore_client_handler.give();
#endif
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  esp32_sal::get << ");
#endif

	return ge_err;
}
general_err_t esp32_http_sal::get(const std::string& api_call, json& output)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> esp32_http_sal::getJSON >> ");
#endif
	// Executable code:
	std::string str;
	auto err = get(api_call, str);
	if(err != GE_OK)
	{
		Logger::write({err, GR_NO_RESPONSE, "Not able to call get command <" + api_call + ">"});
		return err;
	}

	output = json::parse(str, nullptr, false);
	if(output.is_discarded())
	{
		Logger::write({GE_NO_DATA, GR_NO_RESPONSE,
					   "Not able to convert string to json: str<" + str + "> : json <" +
						   output.dump() + ">"});
		return GE_NO_DATA;
	}
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  esp32_http_sal::getJSON << ");
#endif

	return GE_OK;
}
general_err_t esp32_http_sal::post(const std::string& api_call, const std::string& content)
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