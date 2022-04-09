#ifndef _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_COMMON_HPP_
#define _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_COMMON_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  i2c_common.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-04-07
 |
 |  @brief  	   :  This class, i2c_common.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  @version       : 1.0
 |
 |  @bug  		   :   no known bugs
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

struct i2c_conf_t
{
	uint32_t speed; // 100k Hz default
	GPIO_PIN pin_sda; // gpio pin for sda
	GPIO_PIN pin_sclk; // pgio pin for clk
};

#endif //_COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_COMMON_HPP_