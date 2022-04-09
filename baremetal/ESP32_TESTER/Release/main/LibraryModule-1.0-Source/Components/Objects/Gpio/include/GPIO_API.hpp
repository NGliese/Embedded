/*
 * GPIO_API.hpp
 *
 *  Created on: Jan 5, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_GPIO_INCLUDE_GPIO_API_HPP_
#define MAIN_COMPONENTS_GPIO_INCLUDE_GPIO_API_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  GPIO_API.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, GPIO_API.hpp, is designed as:
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

#include "HAL.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class GPIO_API
{
#ifdef __UNITTEST__
	friend class friend_GPIO_API;
#endif
  public:
	GPIO_API() : m_pin{(GPIO_HAL::pin)0}, is_Output{false} {};
	GPIO_API(const GPIO_HAL::pin& pin) : m_pin{pin}, is_Output{false} {};
	~GPIO_API();
	general_err_t setToInput();
	general_err_t setToOutput();
	general_err_t setHigh();
	general_err_t setLow();
	bool isHigh() const;
	bool isLow() const;
	general_err_t installInterrupt(const GPIO_HAL::io_intr_t& type,
								   void (*callbackfunction)(void*));

	general_err_t enableInterrupt(void)
	{
		return m_hal.enableInterrupt(m_pin);
	};
	general_err_t disableInterrupt(void)
	{
		return m_hal.disableInterrupt(m_pin);
	};

  private:
	GPIO_HAL::pin m_pin;
	bool is_Output;

	GPIO_HAL m_hal;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_GPIO_API
{
  public:
	friend_GPIO_API(){};
	friend_GPIO_API(GPIO_API* GPIO_API) : m_sensor{GPIO_API} {};

	~friend_GPIO_API(){};

  private:
	GPIO_API* m_sensor;
};
#endif

#endif /* MAIN_COMPONENTS_GPIO_INCLUDE_GPIO_API_HPP_ */
