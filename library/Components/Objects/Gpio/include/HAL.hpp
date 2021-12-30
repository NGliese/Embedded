/*
 * HAL.hpp
 *
 *  Created on: Jan 5, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_GPIO_INCLUDE_HAL_HPP_
#define MAIN_COMPONENTS_GPIO_INCLUDE_HAL_HPP_


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
 |  	Link:[ ], Jan 5, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jan 5, 2021
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
#include <driver/gpio.h>
#endif


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class GPIO_HAL {
#ifdef __UNITTEST__
    friend class friend_HAL;
#endif
public:
// define the calling for pin
#ifdef __ESP32__
    typedef gpio_num_t pin;
#else
    typedef int pin;
#endif
typedef enum{
    INPUT = 0,
    OUTPUT = 1
}io_def_t;
typedef enum{
    LOW = 0,
    HIGH = 1
}io_val_t;
typedef enum{
FALLING_EDGE = 0,
RISING_EDGE,
ANY_EDGE
}io_intr_t;
GPIO_HAL() = default;
    ~GPIO_HAL() {};

    general_err_t setDirection(const GPIO_HAL::pin& pin,const GPIO_HAL::io_def_t& dir);
    general_err_t setValue(const GPIO_HAL::pin& pin,const GPIO_HAL::io_val_t& val);
    GPIO_HAL::io_val_t  getValue(const GPIO_HAL::pin& pin) const;
    general_err_t installInterruptDriver(const GPIO_HAL::pin& pin,  void (*callbackfunction)(void*)  ,const GPIO_HAL::io_intr_t& intr);
    general_err_t enableInterrupt(const GPIO_HAL::pin& pin);
    general_err_t disableInterrupt(const GPIO_HAL::pin& pin);

private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_HAL {
public:
    friend_HAL(){};
    friend_HAL(GPIO_HAL * HAL) : m_sensor{HAL} { };

    ~friend_HAL(){};

private:
    GPIO_HAL * m_sensor;
};
#endif




#endif /* MAIN_COMPONENTS_GPIO_INCLUDE_HAL_HPP_ */
