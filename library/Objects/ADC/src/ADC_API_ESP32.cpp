/*
 * ADC_API_ESP32.cpp
 *
 *  Created on: Sep 21, 2021
 *      Author: nikolaj
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
 *  \file       ADC_API_ESP32.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/ADC_API_ESP32.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "ADC_API_ESP32";
#endif

ADC_API_ESP32::ADC_API_ESP32(const config& conf) : ADCBase(conf.name,conf.samples) , m_conf{conf}{

#ifdef __ESP32__
    // set the adc width
    adc1_config_width(m_width);
    // set the channel and attenuation
    adc1_config_channel_atten(m_conf.channel, m_atten);
    // set the calc value
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(m_unit, m_atten, m_width, m_conf.vRef, &m_adc_chars);
#endif
}

ADC_API_ESP32::~ADC_API_ESP32() {
}
/*
 * @brief measure the adc value over an average of  m_number_of_samples
 * return result
 */
uint32_t ADC_API_ESP32::measureValue(void) {

    uint64_t adc_reading = 0;
    for(size_t i = 0; i < m_number_of_samples ; ++i)
    {
    #ifdef __ESP32__
      adc_reading += adc1_get_raw(m_conf.channel);
    #endif
    }
    // check that we do not divide by zero
    return   adc_reading > 0 ? static_cast<uint32_t>(adc_reading /= m_number_of_samples) : 0 ;

}
