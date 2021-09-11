/*
 * PWM_API.cpp
 *
 *  Created on: Sep 11, 2021
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
 *  \file       PWM_API.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/PWM_API.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "PWM_API";
#endif

PWM_API::PWM_API(const HAL_ESP32::config &conf) : m_hal{conf}{
}

PWM_API::~PWM_API() {
    m_hal.stop();
}

/**
 * @brief   set the duty cycle of the pwm
 *
 * @attention the function will call update()
 *            and automatically handle start/stop conditions for the
 *            pulse width modulation
 *
 *
 * @param[in] const uint32_t &frequency
 *
 * @return
 *    - GE_OK
 *    - GE_OUT_OF_RANGE
 *    -
 */
general_err_t PWM_API::setDutyCycle(const float &duty) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> PWM_API::setDutyCycle >> ");
    #endif
    // Executable code:

    if(duty > 100.0)
    {
        return GE_OUT_OF_RANGE;
    }
    if(duty < 0.0)
    {
        return GE_OUT_OF_RANGE;
    }


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< PWM_API::setDutyCycle << ");
    #endif

    return   m_hal.setDutyCycle(duty);
}
/**
 * @brief   set the frequency of the pwm
 *
 * @attention the function will call update()
 *            and automatically handle start/stop conditions for the
 *            pulse width modulation
 *
 *
 * @param[in] const uint32_t &frequency
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t PWM_API::setFrequency(const uint32_t &frequency) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> PWM_API::setFrequency >> ");
    #endif
    // Executable code:


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< PWM_API::setFrequency << ");
    #endif

    return m_hal.setFrequency(frequency);
}

/**
 * @brief stop the pwm
 *
 * @attention  this is a private function
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t PWM_API::stop(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> PWM_API::stop >> ");
    #endif
    // Executable code:


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< PWM_API::stop << ");
    #endif

    return m_hal.stop();
}
