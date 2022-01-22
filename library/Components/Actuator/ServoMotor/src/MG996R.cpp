/*
 * MG996R.cpp
 *
 *  Created on: Oct 10, 2021
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
 *  \file       MG996R.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/MG996R.hpp"

constexpr float MIN_VALUE = 2.5; //<! start position of servo motor [duty cycle]
constexpr float MAX_VALUE = 13; //<! end position of servo motor   [duty cycle]
constexpr float SLOW_INCREMENT = 0.1; //<! incremental value for the slow method [delta duty cycle]
constexpr std::uint8_t SLOW_DELAY = 60; //<! delay for the slow method [ms]
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "MG996R";
#endif

MG996R::MG996R(const mg996r_conf_t& conf)
	: Actuator_Base(conf), m_pwm{conf.conf, "pwm"}, m_setPointValue{m_value}
{
}

MG996R::~MG996R() {}

general_err_t MG996R::setPoint(const float& value)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> MG996R::setPoint >> ");
#endif
	// Executable code:
	if(value > MAX_VALUE)
	{
		m_setPointValue = MAX_VALUE;
		return GE_UPPER_BOUNDERY;
	}
	if(value < MIN_VALUE)
	{
		m_setPointValue = MIN_VALUE;
		return GE_LOWER_BOUNDERY;
	}
	if(value == m_setPointValue)
	{
		return GE_NO_DATA;
	}

	m_setPointValue = value;
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< MG996R::setPoint << ");
#endif

	return GE_OK;
}

general_err_t MG996R::actuate(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> MG996R::actuate >> ");
#endif
	// Executable code:
	auto err = m_pwm.setDutyCycle(m_setPointValue);
	if(err != GE_OK)
	{
		m_faulthanlder.handleFault({FaultHandler_n::severity::medium, " MG996R::actuate(void)",
									" error is : " + General_Error::errorToString(err)});
		return GE_FAIL;
	}
	// at this point we can assume that the set point value is equivalent to the m_value
	m_value = m_setPointValue;

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< MG996R::actuate << ");
#endif

	return GE_OK;
}

general_err_t MG996R::setToMaximum(void)
{
	return execute(MAX_VALUE);
}

general_err_t MG996R::setToMinimum(void)
{
	return execute(MIN_VALUE);
}

general_err_t MG996R::setToMaximumSlowly(void)
{
	general_err_t err = GE_OK;
	do
	{
		float tick = getValue() + SLOW_INCREMENT;
		err = setPoint(tick);
		if(err == GE_NO_DATA)
		{
			return err;
		}
		err = actuate();
		Timeservice::wait_ms(SLOW_DELAY);
	} while(getValue() < MAX_VALUE && err == GE_OK);
	return err;
}

general_err_t MG996R::setToMinimumSlowly(void)
{
	general_err_t err = GE_OK;
	do
	{
		float tick = getValue() - SLOW_INCREMENT;
		err = setPoint(tick);
		if(err == GE_NO_DATA)
		{
			return err;
		}
		err = actuate();
		Timeservice::wait_ms(SLOW_DELAY);
	} while(getValue() > MIN_VALUE && err == GE_OK);
	return err;
}