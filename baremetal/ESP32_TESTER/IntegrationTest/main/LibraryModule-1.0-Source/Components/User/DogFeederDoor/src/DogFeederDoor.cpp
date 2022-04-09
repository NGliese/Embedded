/*
 * DogFeederDoor.cpp
 *
 *  Created on: Nov 23, 2021
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
 *  \file       DogFeederDoor.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/DogFeederDoor.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "DogFeederDoor";
#endif

DogFeederDoor::DogFeederDoor(const mg996r_conf_t& conf) : m_motor{conf} {}

DogFeederDoor::~DogFeederDoor() {}

general_err_t DogFeederDoor::open()
{
	return m_motor.setToMaximumSlowly();
}

general_err_t DogFeederDoor::close()
{
	return m_motor.setToMinimumSlowly();
}
