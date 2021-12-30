/*
 * PWM_API.hpp
 *
 *  Created on: Sep 11, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_PWM_API_ESP32_HPP_
#define INCLUDE_PWM_API_ESP32_HPP_

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

#include "../../../Interfaces/PWMBase/include/PWMBase.hpp"
#include "HAL.hpp"


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
// if every needed a pwm driver for another mcu, we should abstract this call
// and create a baseclass with these function and a template conf parameter for each mcu
class PWM_API_ESP32 final : public PWMBase<HAL_ESP32::config, HAL_ESP32>{
#ifdef __UNITTEST__
    friend class friend_PWM_API;
#endif
public:

    /**
     * @brief following RAII @instantiation we activate and start PWM
     */
    PWM_API_ESP32(const HAL_ESP32::config& conf,const std::string & name) ;
    ~PWM_API_ESP32();
    /**
     * @see PWMBase::setDutyCycle(const float& duty)
     */
    general_err_t setDutyCycle(const float& duty);
    /**
     * @see PWMBase::setFrequency(const uint32_t& frequency)
     */
    general_err_t setFrequency(const uint32_t& frequency);


private:
    general_err_t stop(void);
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_PWM_API {
public:
    friend_PWM_API(PWM_API_ESP32 * PWM_API) : m_sensor{PWM_API} { };
    ~friend_PWM_API(){};
    auto getConf(void) {return m_sensor->m_hal.getConfig(); }
private:
    PWM_API_ESP32 * m_sensor;
};
#endif





#endif /* INCLUDE_PWM_API_ESP32_HPP_ */
