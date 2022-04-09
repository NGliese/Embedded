#ifndef _COMPONENTS_OBJECTS_NONVOLATILESTORAGE_INCLUDE_NVS_ESP32_HPP_
#define _COMPONENTS_OBJECTS_NONVOLATILESTORAGE_INCLUDE_NVS_ESP32_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  NVS_esp32.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-24
 |
 |  @brief  	   :  This class, NVS_esp32.hpp, is designed as:
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

#include <iostream>

#ifdef __ESP32__
#include "esp_system.h"
#include "nvs.h"
#include "nvs_flash.h"
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class NVS_esp32
{
#ifdef __UNITTEST__
	friend class friend_NVS_esp32;
#endif
  public:
	static const uint64_t read_u64(const std::string& key);
	static general_err_t write_u64(const std::string& key, const uint64_t& value);

  private:
	static general_err_t initialize();
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_NVS_esp32
{
  public:
	explicit friend_NVS_esp32(NVS_esp32* sensor) : m_sensor{sensor} {};
	~friend_NVS_esp32();

  private:
	NVS_esp32* m_sensor;
};
#endif

#endif //_COMPONENTS_OBJECTS_NONVOLATILESTORAGE_INCLUDE_NVS_ESP32_HPP_
