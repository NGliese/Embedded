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
 *  @file       SensorControllerBase_MOCK.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-02-27
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "SensorControllerBase_MOCK.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "SensorControllerBase_MOCK";
#endif

general_err_t SensorControllerBase_MOCK::main_function()
{
	return GE_OK;
}