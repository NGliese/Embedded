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
	postData(m_buffer_raw);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  DistanceSensorController::fcn << ");
#endif

	return GE_OK;
}