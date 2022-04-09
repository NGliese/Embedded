#ifndef _COMPONENTS_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADC_BATTERY_V1_0_HPP_
#define _COMPONENTS_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADC_BATTERY_V1_0_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  esp32_i2c_adc_battery_v1_0.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-27
 |
 |  @brief  	   :  This class, esp32_i2c_adc_battery_v1_0.hpp, is designed as:
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

#include <iostream>

#ifdef __ESP32__
#include <driver/gpio.h>
#endif
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

namespace esp32_i2c_adc_battery_v1_0
{
#ifdef __ESP32__
constexpr GPIO_PIN I2C_SDA = GPIO_NUM_13;
constexpr GPIO_PIN I2C_SCLK = GPIO_NUM_14;
constexpr ADC_PIN ADC_BATTERY = ADC1_CHANNEL_5; // might change to adc_pin
constexpr ADC_PIN ADC_SENSOR = ADC1_CHANNEL_6; // might change to adc_pin
constexpr GPIO_PIN ON_OFF_SENSOR = GPIO_NUM_27;
#else
constexpr GPIO_PIN I2C_SDA = 13;
constexpr GPIO_PIN I2C_SCLK = 14;
constexpr ADC_PIN ADC_BATTERY = 33;
constexpr ADC_PIN ADC_SENSOR = 34;
constexpr GPIO_PIN ON_OFF_SENSOR = 27;
#endif
} // namespace esp32_i2c_adc_battery_v1_0

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#endif //_COMPONENTS_BOARDS_ESP32_BOARDS_INCLUDE_ESP32_I2C_ADC_BATTERY_V1_0_HPP_