/*
 * GPIO_API.cpp
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
 *  \file       GPIO_API.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/GPIO_API.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "GPIO_API";
#endif

GPIO_API::~GPIO_API() {}
/**
 * @brief  set the pin to input
 *
 * @attention
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t GPIO_API::setToInput()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> GPIO_API::setToOutput >> ");
#endif
	// Executable code:
	auto err = m_hal.setDirection(m_pin, GPIO_HAL::io_def_t::INPUT);
	if(err == GE_OK)
	{
		is_Output = true;
		return GE_OK;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< GPIO_API::setToOutput << ");
#endif

	return err;
}

/**
 * @brief  set the pin to output
 *
 * @attention
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t GPIO_API::setToOutput()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> GPIO_API::setToOutput >> ");
#endif
	// Executable code:
	auto err = m_hal.setDirection(m_pin, GPIO_HAL::io_def_t::OUTPUT);
	if(err == GE_OK)
	{
		is_Output = true;
		return GE_OK;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< GPIO_API::setToOutput << ");
#endif

	return err;
}
/**
 * @brief Set the pin high
 *
 * @attention
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t GPIO_API::setHigh()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> GPIO_API::setHigh >> ");
#endif
	// Executable code:
	if(!is_Output)
	{
		return GE_FAIL;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< GPIO_API::setHigh << ");
#endif

	return m_hal.setValue(m_pin, GPIO_HAL::io_val_t::HIGH);
}

/**
 * @brief Set the pin low
 *
 * @attention
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t GPIO_API::setLow()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> GPIO_API::setLow >> ");
#endif
	// Executable code:
	if(!is_Output)
	{
		return GE_FAIL;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< GPIO_API::setLow << ");
#endif

	return m_hal.setValue(m_pin, GPIO_HAL::io_val_t::LOW);
}
/**
 * @brief  check if the pin is high
 *
 * @attention
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
bool GPIO_API::isHigh() const
{
	if(is_Output)
	{
		std::cout << "this is an output, we cannot read the value from it \n";
		return false;
	}

	return m_hal.getValue(m_pin) == GPIO_HAL::io_val_t::HIGH ? true : false;
}

/**
 * @brief  check if the pin is low
 *
 * @attention
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
bool GPIO_API::isLow() const
{
	if(is_Output)
	{
		std::cout << "this is an output, we cannot read the value from it \n";
		return false;
	}

	return m_hal.getValue(m_pin) == GPIO_HAL::io_val_t::LOW ? true : false;
}

general_err_t GPIO_API::installInterrupt(const GPIO_HAL::io_intr_t& type,
										 void (*callbackfunction)(void*))
{
	return m_hal.installInterruptDriver(m_pin, callbackfunction, type);
}
