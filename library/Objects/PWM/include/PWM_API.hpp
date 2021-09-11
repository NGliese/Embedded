/*
 * PWM_API.hpp
 *
 *  Created on: Sep 11, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_PWM_API_HPP_
#define INCLUDE_PWM_API_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  PWM_API.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, PWM_API.hpp, is designed as:
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
 |  	Link:[ ], Sep 11, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Sep 11, 2021
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

#include "HAL.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
// if every needed a pwm driver for another mcu, we should abstract this call
// and create a baseclass with these function and a template conf parameter for each mcu
class PWM_API {
#ifdef __UNITTEST__
    friend class friend_PWM_API;
#endif
public:



    //@brief following RAII @instantiation we activate and start PWM
    PWM_API(const HAL_ESP32::config& conf) ;
    ~PWM_API();
    //@brief between 0 and 100. decimal allowed
    // we are allowed to update the duty cycle without the need
    // of handling start and stop conditions for the pwm.
    // in other words, we can update live
    general_err_t setDutyCycle(const float& duty);
    //@brief set frequency in Hz
    // we are allowed to update the frequency without the need
    // of handling start and stop conditions for the pwm.
    // in other words, we can update live
    general_err_t setFrequency(const uint32_t& frequency);


private:
    general_err_t update(void);


    general_err_t stop(void);


    HAL_ESP32 m_hal;
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_PWM_API {
public:
    friend_PWM_API(PWM_API * PWM_API) : m_sensor{PWM_API} { };
    ~friend_PWM_API(){};
    auto getConf(void) {return m_sensor->m_hal.getConfig(); }
private:
    PWM_API * m_sensor;
};
#endif





#endif /* INCLUDE_PWM_API_HPP_ */
