#ifndef _MODULES_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADAPTER_V1_0_HPP_
#define _MODULES_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADAPTER_V1_0_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  esp32_i2c_adapter_v1_0.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-27
 |
 |  @brief  	   :  This class, esp32_i2c_adapter_v1_0.hpp, is designed as:
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
namespace esp32_i2c_adapter_v1_0
{
#ifdef __ESP32__
constexpr GPIO_PIN I2C_SDA = GPIO_NUM_22;
constexpr GPIO_PIN I2C_SCLK = GPIO_NUM_21;
#else
constexpr GPIO_PIN I2C_SDA = 22;
constexpr GPIO_PIN I2C_SCLK = 21;
#endif
} // namespace esp32_i2c_adapter_v1_0
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

#endif //_MODULES_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADAPTER_V1_0_HPP_