/*
 * OTA.hpp
 *
 *  Created on: Oct 4, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_OTA_HPP_
#define INCLUDE_OTA_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  OTA.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, OTA.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include "../../../RTOS/FreeRTOS/include/Task.h" // for vTaskdelete/create
#ifdef __ESP32__
#include "esp_ota_ops.h"
#endif

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

// https://github.com/yanbe/esp-idf-ota-template

/**
 * @class This OTA class is ment as an interface for handling Over-The-Air-Update
 *        the public function <i>general_err_t checkForUpdate(void);<\i> should be
 *        called periodically in order to maintain an up to date system.<br><br>
 *
 *        The class will handle the ota update internally.
 * @attention when an update is detected, the OTA class will block and stop all other threads and
 * communications in order to handle the update
 */

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class OTA
{
#ifdef __UNITTEST__
	friend class friend_OTA;
#endif
  public:
	OTA();
	~OTA();
	static general_err_t update(const char* msg, const size_t& length);
	static bool isUpdateStarted(void);

  private:
	static general_err_t start_process(const char* msg, const size_t& length);
	static general_err_t stop_process(const char* msg, const size_t& length);
	static general_err_t update_process(const char* msg, const size_t& length);
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_OTA
{
  public:
	explicit friend_OTA(OTA* OTA) : m_sensor{OTA} {};

	~friend_OTA(){};

  private:
	OTA* m_sensor;
};
#endif

#endif /* INCLUDE_OTA_HPP_ */
