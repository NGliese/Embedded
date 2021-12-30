/*
 * HAL.cpp
 *
 *  Created on: Jan 5, 2021
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
/**
 * @brief      set the direction of the pin
 *
 * @attention
 *
 *
 * @param[in] const HAL::pin& pin
 * @param[in] const HAL::io_def& dir
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t GPIO_HAL::setDirection(const GPIO_HAL::pin& pin, const GPIO_HAL::io_def_t& dir) {
#ifdef __ESP32__
    if(gpio_set_direction(pin,dir==GPIO_HAL::io_def_t::OUTPUT ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT) == ESP_OK)
    {
        return GE_OK;
    }else{
        return GE_FAIL;
    }
#else
    return GE_OK;
#endif
}
/**
 * @brief set the value of the pin
 *
 * @attention
 *
 *
 * @param[in] const HAL::pin& pin
 * @param[in] const HAL::io_val_t& val
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t GPIO_HAL::setValue(const GPIO_HAL::pin& pin, const GPIO_HAL::io_val_t& val) {
#ifdef __ESP32__
    if(gpio_set_level(pin,val==GPIO_HAL::io_val_t::HIGH ? true : false) == ESP_OK)
    {
        return GE_OK;
    }else{
        return GE_FAIL;
    }
#else
    return GE_OK;
#endif
}
/**
 * @brief    read the value of the pin
 *
 * @attention
 *
 *
 * @param[in] const HAL::pin& pin
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
GPIO_HAL::io_val_t GPIO_HAL::getValue(const GPIO_HAL::pin& pin) const {

#ifdef __ESP32__
    return gpio_get_level(pin) == 1 ? GPIO_HAL::io_val_t::HIGH : GPIO_HAL::io_val_t::LOW;
#else
    return GPIO_HAL::io_val_t::LOW;
#endif
}



general_err_t GPIO_HAL::enableInterrupt(const GPIO_HAL::pin& pin) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> GPIO_HAL::enableInterrupt >> ");
    #endif
    // Executable code:
#ifdef __ESP32__
   return  gpio_intr_enable(pin) == ESP_OK ? GE_OK : GE_FAIL;   // Enable the pin for interrupts
#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< GPIO_HAL::enableInterrupt << ");
    #endif

    return GE_OK;
}

general_err_t GPIO_HAL::disableInterrupt(const GPIO_HAL::pin& pin) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> GPIO_HAL::disableInterrupt >> ");
    #endif
    // Executable code:
#ifdef __ESP32__
    return gpio_intr_disable(pin) == ESP_OK ? GE_OK : GE_FAIL; // disable the pin for interrupts
#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< GPIO_HAL::disableInterrupt << ");
    #endif

    return GE_OK;
}

general_err_t GPIO_HAL::installInterruptDriver(const GPIO_HAL::pin& pin,
        void (*callbackfunction)(void*) , const GPIO_HAL::io_intr_t& intr) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> GPIO_HAL::installInterruptDriver >> ");
    #endif
    // Executable code:


#ifdef __ESP32__
    switch (intr) {
        case GPIO_HAL::io_intr_t::ANY_EDGE:
            gpio_set_intr_type(pin,GPIO_INTR_ANYEDGE);
            break;
        case GPIO_HAL::io_intr_t::FALLING_EDGE:
            gpio_set_intr_type(pin,GPIO_INTR_NEGEDGE);
            break;
        case GPIO_HAL::io_intr_t::RISING_EDGE:
            gpio_set_intr_type(pin,GPIO_INTR_POSEDGE);
            break;
        default:
            break;
    }


    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL3); // Todo
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(pin, callbackfunction, NULL);
#else
    // call the callback function for testing purposes
    callbackfunction(nullptr);

#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< GPIO_HAL::installInterruptDriver << ");
    #endif

    return GE_OK;
}
