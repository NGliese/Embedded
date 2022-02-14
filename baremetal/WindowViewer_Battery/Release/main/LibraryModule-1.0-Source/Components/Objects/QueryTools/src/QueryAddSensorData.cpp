/*
 * QueryAddSensorData.cpp
 *
 *  Created on: Sep 6, 2021
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
 *  \file       QueryAddSensorData.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/QueryAddSensorData.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "QueryAddSensorData";
#endif

std::string QueryAddSensorData::content(const QueryDataMessage& msg)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> QueryAddSensorData::append >> ");
#endif
	// Executable code:
	std::string str;
	// Executable code:
	if(msg.isEmpty())
	{
		std::cout << "NOT VALID DATA \n";
		return "";
	}

	timeval tval;
	tval.tv_sec = msg.getBuffer().at(0).time_stamp / 1000;
	tval.tv_usec = (msg.getBuffer().at(0).time_stamp % 1000) * 1000;

	// get the millisec part

	tm* time_now = gmtime(&tval.tv_sec);
	char buffer[80];
	strftime(buffer, 80, "'%Y-%m-%dT%H:%M:%S", time_now);

	char currentTime[84] = "";
	sprintf(currentTime, "%s.%ldZ'", buffer, (tval.tv_usec));

	str.append("(");
	// timestamp
	str.append(currentTime);
	str.append(",");
	// Sensor id
	str.append(std::to_string(msg.getId()));
	str.append(",");

	// data, with 4 precision
	auto data = msg.getBuffer().at(0).data;
	str.append(std::to_string(data));
	str.append(")");

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< QueryAddSensorData::append << ");
#endif

	return str;
}
