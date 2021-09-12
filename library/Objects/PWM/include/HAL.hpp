/*
 * HAL.hpp
 *
 *  Created on: Sep 11, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_HAL_PWM_HPP_
#define INCLUDE_HAL_PWM_HPP_


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


#ifdef __ESP32__
#include <driver/ledc.h>
#endif


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class HAL_ESP32 {
#ifdef __UNITTEST__
    friend class friend_HAL;
#endif
public:

    // define the calling for pin
    #ifdef __ESP32__
        typedef ledc_mode_t  speed_mode;
        typedef ledc_channel_t lcd_channel;
        typedef gpio_num_t pin;
    #else
        typedef int speed_mode;
        typedef int lcd_channel;
        typedef int pin;
    #endif

    struct config{
        HAL_ESP32::pin m_pin;
        float duty;
        uint32_t frequency;
        lcd_channel channel;
        speed_mode mode;
    };

    HAL_ESP32(const config& conf) ;
    ~HAL_ESP32();
    general_err_t setDutyCycle(const uint32_t& duty);
    general_err_t setFrequency(const uint32_t& frequency);
    general_err_t stop(void);
    general_err_t destroy(void);

    const auto& getConfig(void) {return m_conf;}

private:
    uint32_t calculateDutyCycleBasedOnResolution(const float& duty);

    config m_conf;
};





#endif /* INCLUDE_HAL_HPP_ */
