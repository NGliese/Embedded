/*
 * Watch_Clock.cpp
 *
 *  Created on: Aug 27, 2020
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
 *  \file       Watch_Clock.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2020
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/Watch_Clock.hpp"

#ifdef __UNITTEST__
uint32_t fake_start_time;
uint32_t fake_end_time;
#endif


Watch_Clock::Watch_Clock(const size_t& parameter)  {
    m_watch = parameter;
    m_last_time =  Timeservice::getTimeNow();
    m_initialized = true;
}

Watch_Clock::Watch_Clock() {

}
Watch_Clock::~Watch_Clock() {
}
/**
 * @brief    initialize the block
 *
 * @attention
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Watch_Clock::initialize(uint32_t parameter) {
#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, ">> Watch_Clock::initialize >> ");
#endif
// Executable code:

// delay between current time and last time
m_watch = parameter;

// get time:
#ifndef __UNITTEST__
m_last_time =  Timeservice::getTimeNow();
#else
//extern uint32_t fake_start_time; // found in watch_clock_test
m_last_time  = fake_start_time;
#endif

m_initialized = true;

#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, "<< Watch_Clock::initialize << ");
#endif

return GE_OK;
}


/**
 * @brief Watch the parameter
 *
 * @param[in] uint32_t timestamp
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
watchdog_event_t Watch_Clock::watch() {
#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, ">> Watch_Clock::watch >> ");
#endif
// Executable code:
if(!m_initialized)
{
   return watchdog_event_t::FAIL_EVENT;
}

// get time:


#ifndef __UNITTEST__
uint32_t current_time = Timeservice::getTimeNow();
#else
//extern uint32_t fake_end_time; // found in watch_clock_test
uint32_t current_time  = fake_end_time;
#endif


if(current_time < m_last_time)
{
    return watchdog_event_t::FAIL_EVENT;
}

if( (current_time - m_last_time) > m_watch )
{
    // we should update the last time here
    m_last_time = current_time;
    return watchdog_event_t::SEND_EVENT;
}

#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, "<< Watch_Clock::watch << ");
#endif

return watchdog_event_t::NO_EVENT;
}
/**
 * @brief  reset the watchdog, this is also called pet-the-dog
 *
 * @attention
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Watch_Clock::reset() {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Watch_Clock::reset >> ");
    #endif
    // Executable code:

    // get time:
    #ifndef __UNITTEST__
    uint32_t current_time = Timeservice::getTimeNow();
    #else
  //  extern uint32_t fake_end_time; // found in watch_clock_test
    uint32_t current_time  = fake_end_time;
    #endif

    m_last_time = current_time;

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Watch_Clock::reset << ");
    #endif

    return GE_OK;
}
