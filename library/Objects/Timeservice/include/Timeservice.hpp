/*
 * Timeservice.hpp
 *
 *  Created on: Sep 6, 2020
 *      Author: nikolaj
 */

#ifndef COMPONENTS_TIMESERVICE_INCLUDE_TIMESERVICE_HPP_
#define COMPONENTS_TIMESERVICE_INCLUDE_TIMESERVICE_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Timeservice.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Timeservice.hpp, is designed as:
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

#include "RTC_HAL.hpp"
#include <chrono>
#include <thread>
#include <iomanip>
/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/



class Timeservice {
public:
        Timeservice();
        ~Timeservice();
    static  uint64_t getTimeNow(void);
    static uint64_t getTimeInUsNow(void);
    static general_err_t wait_ms(size_t ms_to_wait);
    static general_err_t wait_untill_ms(const uint64_t& start_time, const uint64_t& ms_to_wait);
    general_err_t initialize_sntp(void);
    static std::string getCurrentDate(void);
    static std::string getCurrentDate(const timeval& time);
private:
};


#endif /* COMPONENTS_TIMESERVICE_INCLUDE_TIMESERVICE_HPP_ */
