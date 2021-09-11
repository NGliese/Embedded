/*
 * HAL.hpp
 *
 *  Created on: Sep 6, 2020
 *      Author: nikolaj
 */

#ifndef COMPONENTS_TIMESERVICE_INCLUDE_RTC_HAL_HPP_
#define COMPONENTS_TIMESERVICE_INCLUDE_RTC_HAL_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  HAL.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, HAL.hpp, is designed as:
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
 |   		 					Datasheet Awareness              		        |
 +------------------------------------------------------------------------------+
 |
 |
 |  Datasheet Awareness 1):
 |  	Link:[ ], Sep 6, 2020
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Sep 6, 2020
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#ifdef __ESP32__
#include "esp_sntp.h"
#endif

#include <ctime>

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/



class RTC_HAL {
public:
     RTC_HAL();
     ~RTC_HAL();
     general_err_t sntp_update();

private:

};



#endif /* COMPONENTS_TIMESERVICE_INCLUDE_RTC_HAL_HPP_ */
