/*
 * Timebased_rules.cpp
 *
 *  Created on: Nov 16, 2021
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
 *  \file       Timebased_rules.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Timebased_rules.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "Timebased_rules";
#endif

constexpr int NIGHT_TIME_START = 20;
constexpr int NIGHT_TIME_END = 5;

constexpr int VACATION_START = 6;
constexpr int VACATION_END = 15;
bool Timebased_rules::isItNight(void)
{
	time_t now = time(0);
	struct tm tstruct;
	tstruct = *localtime(&now);

	if(tstruct.tm_hour >= NIGHT_TIME_START or tstruct.tm_hour <= NIGHT_TIME_END)
	{
		return true;
	}

	return false;
}

bool Timebased_rules::isItVacation(void)
{
	time_t now = time(0);
	struct tm tstruct;
	tstruct = *localtime(&now);

	std::cout << " current day is : " << (int)tstruct.tm_mday << "\n";
	if(tstruct.tm_mday >= VACATION_START and tstruct.tm_mday <= VACATION_END)
	{
		return true;
	}

	return false;
}
