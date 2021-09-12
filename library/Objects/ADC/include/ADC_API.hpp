/*
 * ADC_API.hpp
 *
 *  Created on: Apr 14, 2020
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_ADC_INCLUDE_ADC_API_HPP_
#define MAIN_COMPONENTS_ADC_INCLUDE_ADC_API_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  ADC_API.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, ADC_API.hpp, is designed as:
 |
 | 	 	 	 	 	 Overview:
 |						The ESP32 integrates two 12-bit SAR (Successive Approximation Register)
 |						ADCs supporting a total of 18 measurement channels (analog enabled pins).
 |						The ADC driver API supports ADC1 (8 channels, attached to GPIOs 32 - 39),
 |						and ADC2 (10 channels, attached to GPIOs 0, 2, 4, 12 - 15 and 25 - 27)
 |					LINK:
 |						https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html
 |
 |
 |
 |
 |
 |  version       :   2020_04_23_08_50
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
 |  	Link:[ ], Apr 14, 2020
 |		Brief:
 |     Some of the ADC2 pins are used as strapping pins (GPIO 0, 2, 15) thus cannot be used freely. Such is the case in the following official Development Kits:
 | 	   ESP32 DevKitC: GPIO 0 cannot be used due to external auto program circuits.
 |	   ESP-WROVER-KIT: GPIO 0, 2, 4 and 15 cannot be used due to external connections for different purposes.
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Apr 14, 2020
 |
 |		Brief:
 |
 |     ADC2 is used by the Wi-Fi driver.
 |	   Therefore the application can only use ADC2 when the Wi-Fi driver has not started.
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
#include <stdint.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>
#endif

#include <iostream>
#include <string>

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
#ifdef __UNITTEST__
#define adc1_channel_t int
#endif

class ADC_API {
public:
	explicit ADC_API(const adc1_channel_t channel);
	~ADC_API();
	uint32_t get_raw_adc(void);
	uint32_t get_mV_adc(void);
	general_err_t set_number_samples(const uint16_t number_of_samples);
	general_err_t callibrate(void);
private:
	uint16_t m_number_of_samples;			// default multisamples
	const uint16_t m_vref;
    adc1_channel_t m_channel;// = ADC1_CHANNEL_6;     //GPIO34 if ADC1
#ifdef __ESP32__
	esp_adc_cal_characteristics_t m_adc_chars;
	const adc_bits_width_t m_width = ADC_WIDTH_BIT_12;
	const adc_atten_t m_atten =  ADC_ATTEN_DB_11;
	const adc_unit_t m_unit = ADC_UNIT_1;
#endif
};





#endif /* MAIN_COMPONENTS_ADC_INCLUDE_ADC_API_HPP_ */
