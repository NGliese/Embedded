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
    /**
     * function to obtain the current time in milliseconds.
     *      if RTC is enabled the returned time will be the amount of ms since 1.jan-1970
     *      if RTC is not enabled the returned time will be the amout of ms since startup
     * @return uint64_t
     */
    static  uint64_t getTimeNow(void);
    /**
     * function to obtain the current time in microseconds.
     *      if RTC is enabled the returned time will be the amount of µs since 1.jan-1970
     *      if RTC is not enabled the returned time will be the amout of µs since startup
     * @return uint64_t
     */
    static uint64_t getTimeInUsNow(void);
    /**
     * function to wait for x amount of milliseconds
     *      this function is putting the current thread to sleep and so is a non-blocking wait function
     * @param [in] size_t ms_to_wait
     * @return general_err_t
     */
    static general_err_t wait_ms(const size_t& ms_to_wait);
    /**
     * function to wait untill x amount of milliseconds has passed
     *      this function is putting the current thread to sleep and so is a non-blocking wait function
     * @param [in] const uint64_t& start_time
     * @param [in] const uint64_t& ms_to_wait
     * @return general_err_t
     */
    static general_err_t wait_untill_ms(const uint64_t& start_time, const uint64_t& ms_to_wait);
    /**
     * enable sntp in order to obtain a real time clock from a mcu's perspective
     * @attention this function is a call to the @RTC_HAL
     * @return error_code
     */
    general_err_t initialize_sntp(void);
    /**
     * get the current date in [yyyymmdd_hhmm_ss] format
     * @return std::string
     */
    static std::string getCurrentDate(void);
    /**
     * get the current date in [yyyymmdd_hhmm_ss] format
     * @param [in] const timeval& time
     * @return std::string
     */
    static std::string getCurrentDate(const timeval& time);
private:
};


#endif /* COMPONENTS_TIMESERVICE_INCLUDE_TIMESERVICE_HPP_ */
