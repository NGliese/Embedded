/***********************************************************************************************+
 *  @brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  @note       ANY RELEVANT NOTES
 *
 *  @file       DistanceSensorController.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-02-27
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/DistanceSensorController.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "DistanceSensorController";
#endif

general_err_t DistanceSensorController::main_function()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> DistanceSensorController::fcn >> ");
#endif
	// Executable code:

	m_buffer_raw.clear(); // make sure it is cleared
	for(size_t i = 0; i < m_buffer_raw.getMaxAllowedBufferSize(); i++)
	{
		m_buffer_raw.addData(Timeservice::getTimeNow(), m_adc.measureValue());
		Timeservice::wait_ms(m_time_between_adc_measurements);
	}
	// auto err = postData(m_buffer_raw); // do we want to send to prada?
	updateInternalBuffer();
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  DistanceSensorController::fcn << ");
#endif

	return GE_OK;
}

general_err_t DistanceSensorController::updateInternalBuffer()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> DistanceSensorController::fcn >> ");
#endif
	// Executable code:
	if(m_data_ready_flag)
	{
		// nothing to be done
		return GE_OK;
	}
	if(!m_want_data_flag)
	{
		// nothing to be done
		return GE_OK;
	}

	// m_buffer_external = m_buffer_raw;
	auto err = m_buffer_raw.copyTo(m_buffer_external);
	if(err != GE_OK)
	{
		return err;
	}

	setDataReadyTrue();
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  DistanceSensorController::fcn << ");
#endif

	return GE_OK;
}