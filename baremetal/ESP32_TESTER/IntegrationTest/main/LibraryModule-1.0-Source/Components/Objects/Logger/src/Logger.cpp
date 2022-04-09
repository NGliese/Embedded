/*
 * Logger.cpp
 *
 *  Created on: Jun 14, 2021
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
 *  \file       Logger.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Logger.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "Logger";
#endif

general_err_t Logger::write(const msg_t& msg)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Logger::write >> ");
#endif
	// Executable code:
	if(msg.msg.empty())
	{
		return GE_NO_DATA;
	}

	// construct the message:
	std::string str;
	str.append("[");
	str.append(std::to_string((long long int)Timeservice::getTimeNow()));
	str.append("] [");
	str.append(PROJECT_NAME);
	str.append("] [");
	str.append(General_Error::errorToString(msg.error_code));
	str.append("] [");
	str.append(General_Error::responseToString(msg.respons_code));
	str.append("] [");
	str.append(msg.msg);
	str.append("]");

	hal::write(str);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Logger::write << ");
#endif

	return GE_OK;
}
