#ifndef _COMPONENTS_PROTOCOLS_HTTP_INCLUDE_ESP32_SAL_HPP_
#define _COMPONENTS_PROTOCOLS_HTTP_INCLUDE_ESP32_SAL_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  esp32_sal.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolaj.gliese.pedersen@dansac.com>
 |  @date		   : 2022-01-07
 |
 |  @brief  	   :  This class, esp32_sal.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  @version       : 1.0
 |
 |  @bug  		   :   no known bugs
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include <array>
#include <iostream>
#ifdef __ESP32__
#include <esp_http_client.h>
#endif

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class esp32_sal
{
#ifdef __UNITTEST__
	friend class friend_esp32_sal;
#endif
  public:
	explicit esp32_sal(const std::string& server);
	~esp32_sal();
	/**
	 * @brief Call a basic GET function to the specified server
	 *
	 * @param api_call : specifed remote function, example "/get_status_of_something"
	 * @return general_err_t
	 */
	general_err_t get(const std::string& api_call);
	/**
	 * @brief
	 *
	 * @param api_call : specifed remote function, example "/post_to_database"
	 * @param content
	 * @return general_err_t
	 */
	general_err_t post(const std::string& api_call, const std::string& content);

  private:
	const std::string m_server;
	std::array<char, 100> local_user_data;
#ifdef __ESP32__
	esp_http_client_handle_t client;
#endif
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_esp32_sal
{
  public:
	explicit friend_esp32_sal(esp32_sal* sensor) : m_sensor{sensor} {};
	~friend_esp32_sal();

  private:
	esp32_sal* m_sensor;
};
#endif

#endif //_COMPONENTS_PROTOCOLS_HTTP_INCLUDE_ESP32_SAL_HPP_