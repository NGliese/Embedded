/*
 * HAL.cpp
 *
 *  Created on: Sep 11, 2021
 *      Author: nikolaj
 */

#ifndef SRC_HAL_PWM_CPP_
#define SRC_HAL_PWM_CPP_

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
 *  \file       HAL.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/HAL.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "HAL";
#endif





#endif /* SRC_HAL_CPP_ */

HAL_ESP32::HAL_ESP32(const config& conf) : m_conf{conf}{
#ifdef __ESP32__


    ledc_timer_config_t timer_conf;
    timer_conf.speed_mode = conf.mode;
    timer_conf.duty_resolution = LEDC_TIMER_8_BIT; // 8bit = 0 -> 255 resolution
    timer_conf.timer_num = LEDC_TIMER_1;
    timer_conf.freq_hz = conf.frequency;
    timer_conf.clk_cfg = LEDC_AUTO_CLK; // deicde for yourself



    auto err = ledc_timer_config(&timer_conf);
    if(err != ESP_OK)
    {
        std::cout << " could not initialize ledc_timer_config  ... restarting ! \n";
        exit(-1);
    }



    ledc_channel_config_t led_conf;
    led_conf.gpio_num = conf.m_pin;
    led_conf.speed_mode = conf.mode;
    led_conf.channel = conf.channel;
    led_conf.intr_type = LEDC_INTR_DISABLE; // we do not use interrupts
    led_conf.timer_sel = LEDC_TIMER_1; // should not be needed to select timers
    led_conf.duty = 0;
    led_conf.hpoint = 0;

    err =  ledc_channel_config(&led_conf);
    if(err != ESP_OK)
    {
        std::cout << " could not initialize ledc_channel_config ... restarting ! \n";
        exit(-1);
    }


#endif

}

HAL_ESP32::~HAL_ESP32() {
}

general_err_t HAL_ESP32::setDutyCycle(const float &duty) {

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> HAL_ESP32::setDutyCycle >> ");
    #endif
    // Executable code:
#ifdef __ESP32__
    auto err =  ledc_set_duty(m_conf.mode, m_conf.channel, calculateDutyCycleBasedOnResolution(duty));
    if(err != ESP_OK)
    {
        std::cout << " could not  call ledc_set_duty ... restarting ! \n";
        exit(-1);
    }
    err =  ledc_update_duty(m_conf.mode, m_conf.channel );
    if(err != ESP_OK)
    {
        std::cout << " could not  call ledc_update_duty ... restarting ! \n";
        exit(-1);
    }
#endif
    // update duty cycle parameter
    m_conf.duty = duty;

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< HAL_ESP32::setDutyCycle << ");
    #endif

    return GE_OK;
}

general_err_t HAL_ESP32::setFrequency(const uint32_t &frequency) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> HAL_ESP32::setFrequency >> ");
    #endif
    // Executable code:
#ifdef __ESP32__
    auto err =   ledc_set_freq(m_conf.mode,  LEDC_TIMER_0, frequency);
    if(err != ESP_OK)
    {
        std::cout << " could not  call ledc_set_freq ... restarting ! \n";
        exit(-1);
    }
#endif
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< HAL_ESP32::setFrequency << ");
    #endif
    // update frequency parameter
    m_conf.frequency = frequency;

    return GE_OK;
}


general_err_t HAL_ESP32::stop(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> HAL_ESP32::stop >> ");
    #endif
    // Executable code:
#ifdef __ESP32__
    auto err =  ledc_stop(m_conf.mode, m_conf.channel, 0);
    if(err != ESP_OK)
     {
         std::cout << " could not  call ledc_stop ... restarting ! \n";
         exit(-1);
     }
#endif
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< HAL_ESP32::stop << ");
    #endif

    return GE_OK;
}

general_err_t HAL_ESP32::destroy(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> HAL_ESP32::destroy >> ");
    #endif
    // Executable code:
    stop();

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< HAL_ESP32::destroy << ");
    #endif

    return GE_OK;
}
/**
 * @brief a converter function to convert the duty cycle in [%] to resolution based
 *
 * @attention we are loosing some performance in the sense of math with floats, but
 *            this is not a time critical called function so we are willingly letting go.
 *
 *
 * @param[in] const float &duty
 * @param[out] duty in resolution domain
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
uint32_t HAL_ESP32::calculateDutyCycleBasedOnResolution(const float &duty) {
   // return (duty/100)*255 ;
    return static_cast<uint32_t>(duty);
}
