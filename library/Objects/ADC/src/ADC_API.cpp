/*
 * ADC_API.cpp
 *
 *  Created on: Apr 14, 2020
 *      Author: espenv
 */



/***********************************************************************************************+
 *  \brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       ADC_API.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    2020_04_23_08_50
 *  \date       2020
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/ADC_API.hpp"
//#define DEBUG (1)
#ifdef DEBUG
static const char *LOG_TAG = "ADC_API";
#endif

ADC_API::ADC_API(const adc1_channel_t channel) :  m_number_of_samples{64},m_vref{1107} ,m_channel{channel}{
    callibrate();
}
ADC_API::~ADC_API() {
}

/**
 * @brief retunr raw adc value
 *
 * @attention
 */
uint32_t ADC_API::get_raw_adc(void) {
    uint32_t adc_reading = 0;
      //Multisampling
      for (uint16_t i = 0; i < m_number_of_samples; i++) {
#ifdef __ESP32__
              adc_reading += adc1_get_raw((adc1_channel_t)m_channel);
#else

#endif
      }
      // check that we do not divide by zero
      return   adc_reading > 0 ? adc_reading /= m_number_of_samples : 0;

}
/**
 * @brief set multi-sample for adc
 *
 * @param[in] number_of_samples
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t ADC_API::set_number_samples( const uint16_t number_of_samples) {

	#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> ADC_API::set_number_samples >> ");
	#endif
	// Executable code:
	m_number_of_samples = number_of_samples;

	#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< ADC_API::set_number_samples << ");
	#endif

	return GE_OK;


}
/**
 * @brief    return the measure voltage, in mV
 *
 */
uint32_t ADC_API::get_mV_adc(void) {
	uint32_t adc_val = get_raw_adc();

#ifdef __ESP32__
	return esp_adc_cal_raw_to_voltage(adc_val, &m_adc_chars);
#else
	return adc_val *1 ; // some conv
#endif
}

/**
 * @brief calibrate the ADC
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t ADC_API::callibrate(void) {
	#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> ADC_API::callibrate >> ");
	#endif
	// Executable code:

#ifdef __ESP32__
	// set the adc width
    adc1_config_width(m_width);
    // set the channel and attenuation
    adc1_config_channel_atten(m_channel, m_atten);
    // set the calc value
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(m_unit, m_atten, m_width, m_vref, &m_adc_chars);
#endif

	#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< ADC_API::callibrate << ");
	#endif

	return GE_OK;
}
