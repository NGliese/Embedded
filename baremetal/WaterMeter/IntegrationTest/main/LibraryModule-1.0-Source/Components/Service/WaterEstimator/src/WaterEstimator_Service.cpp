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
 *  @file       WaterEstimator_Service.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-03-18
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/WaterEstimator_Service.hpp"

#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "WaterEstimator_Service";
#endif

general_err_t WaterEstimator_Service::mainFunction()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> WaterEstimator_Service::mainFunction >> ");
#endif
	// Executable code:
	Timeservice::wait_sec(10);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  WaterEstimator_Service::mainFunction << ");
#endif

	return GE_OK;
}