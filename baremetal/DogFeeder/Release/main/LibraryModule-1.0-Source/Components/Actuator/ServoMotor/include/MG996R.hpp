/*
 * MG996R.hpp
 *
 *  Created on: Oct 10, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_MG996R_HPP_
#define INCLUDE_MG996R_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  MG996R.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, MG996R.hpp, is designed as:
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
 |  	Link:[ ], Oct 10, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Oct 10, 2021
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

#include "../../../Interfaces/ActuatorBase/include/Actuator_Base.hpp"
#include "../../../Objects/PWM/include/PWM_API_ESP32.hpp"
#include "../../../Objects/Timeservice/include/Timeservice.hpp"


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/


struct mg996r_conf_t{
        std::string name;
        HAL_ESP32::config conf;
};



/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
/**
 *
 * class for MG996R pwm driven servo motor
 *
 * @attention due to the servo motors internal parameters we are limited to
 * a pwm duty cycle between 2.5% and 13%
 *
 * @code{.cpp}
 *  // initialize the motor config:
 * mg996r_conf_t conf = { "servo motor 1" {gpio_pin,duty_cycle,frequency,lcd_channel,speed_mode } };
 * MG996R m_servo{conf};
 *
 *  // somewhere in the main function
 * for(;;)
 * {
 *  m_servo.execute(incremental_value);
 * }
 *
 * @endcode
 */
class MG996R final : public Actuator_Base<mg996r_conf_t,float> {
#ifdef __UNITTEST__
    friend class friend_MG996R;
#endif
public:
    MG996R(const mg996r_conf_t& conf) ;
    ~MG996R();
    general_err_t setToMaximum(void) override;
    general_err_t setToMinimum(void) override;

private:
    general_err_t setPoint(const float& value)  override;
    general_err_t actuate(void) override;
    PWM_API_ESP32 m_pwm;
    float m_setPointValue;
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_MG996R {
public:

    friend_MG996R(MG996R * MG996R) : m_sensor{MG996R} { };

    ~friend_MG996R(){};
    auto setPoint(const float& value) { return m_sensor->setPoint(value);}
    auto actuate(void) { return m_sensor->actuate(); }
    auto getSetPoint(void) { return m_sensor->m_setPointValue;}

private:
    MG996R * m_sensor;
};
#endif




#endif /* INCLUDE_MG996R_HPP_ */
