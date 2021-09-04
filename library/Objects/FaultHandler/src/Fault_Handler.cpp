/*
 * Fault_Handler.cpp
 *
 *  Created on: Jul 6, 2021
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
 *  \file       Fault_Handler.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/Fault_Handler.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "Fault_Handler";
#endif






Fault_Handler::Fault_Handler(const std::string& class_name) : m_name{class_name},m_counters{0,0,0}
{ }

Fault_Handler::~Fault_Handler() {
}

general_err_t Fault_Handler::countUp(const FaultHandler_n::msg_t& msg) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Fault_Handler::handle >> ");
    #endif
    // Executable code:
    switch (msg.level) {
        case FaultHandler_n::severity::lowest:
        case FaultHandler_n::severity::very_low:
        case FaultHandler_n::severity::low:
            ++m_counters.low;
            break;
        case FaultHandler_n::severity::medium_low:
        case FaultHandler_n::severity::medium:
        case FaultHandler_n::severity::medium_high:
            ++m_counters.medium;
            break;
        case FaultHandler_n::severity::high:
        case FaultHandler_n::severity::very_high:
        case FaultHandler_n::severity::highest:
            ++m_counters.high;
            break;
    }


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Fault_Handler::handle << ");
    #endif

    return GE_OK;
}

general_err_t Fault_Handler::handle(const FaultHandler_n::msg_t& msg) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Fault_Handler::toString >> ");
    #endif
    // Executable code:


    // check the low counter
    if(check_value(m_counters.low,FaultHandler_n::max_count_value_low) )
    {
        Logger::write({GE_FAIL,GR_REBOOT,toString(msg)});

#ifndef __UNITTEST__ // should not call exit in unittest mode
        Timeservice::wait_ms(10000);
        std::exit(-1);
#endif
    }

    // check the medium counter
    if(check_value(m_counters.medium,FaultHandler_n::max_count_value_medium) )
    {
        Logger::write({GE_FAIL,GR_REBOOT,toString(msg)});
#ifndef __UNITTEST__ // should not call exit in unittest mode
        Timeservice::wait_ms(10000);
        std::exit(-1);
#endif
    }
    // check the high counter
    if(check_value(m_counters.high,FaultHandler_n::max_count_value_high) )
    {
        Logger::write({GE_FAIL,GR_REBOOT,toString(msg)});
#ifndef __UNITTEST__ // should not call exit in unittest mode
        Timeservice::wait_ms(10000);
        std::exit(-1);
#endif
    }
    // no critical bounderies are breached and so we will only be writing to log file
    Logger::write({GE_FAIL,GR_NO_RESPONSE,toString(msg)});

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Fault_Handler::toString << ");
    #endif

    return GE_OK;
}

general_err_t Fault_Handler::handleFault(const FaultHandler_n::msg_t& msg) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Fault_Handler::handleFault >> ");
    #endif
    // Executable code:
    countUp(msg); // count up the fault
    handle(msg); // decide if we need to act, this includes logging and exiting

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Fault_Handler::handleFault << ");
    #endif

    return GE_OK;
}

std::string Fault_Handler::toString(const FaultHandler_n::msg_t& msg) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Fault_Handler::toString >> ");
    #endif
    // Executable code:


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Fault_Handler::toString << ");
    #endif

    return severity2string(msg.level)+","+m_name+","+msg.function_name+","+msg.describtion;
}

general_err_t Fault_Handler::resetFaultCounter(const FaultHandler_n::severity& level) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Fault_Handler::reset >> ");
    #endif
    // Executable code:
    switch (level) {
        case FaultHandler_n::severity::lowest:
        case FaultHandler_n::severity::very_low:
        case FaultHandler_n::severity::low:
            m_counters.low = 0;
            break;
        case FaultHandler_n::severity::medium_low:
        case FaultHandler_n::severity::medium:
        case FaultHandler_n::severity::medium_high:
            m_counters.medium = 0;
            break;
        case FaultHandler_n::severity::high:
        case FaultHandler_n::severity::very_high:
        case FaultHandler_n::severity::highest:
            m_counters.high = 0;
            break;
    }

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Fault_Handler::reset << ");
    #endif

    return GE_OK;
}

std::string Fault_Handler::severity2string(
        const FaultHandler_n::severity& level) {
    switch (level) {
           case FaultHandler_n::severity::lowest:
               return "lowest";
           case FaultHandler_n::severity::very_low:
               return "very_low";
           case FaultHandler_n::severity::low:
               return "low";
           case FaultHandler_n::severity::medium_low:
               return "medium_low";
           case FaultHandler_n::severity::medium:
               return "medium";
           case FaultHandler_n::severity::medium_high:
               return "medium_high";
           case FaultHandler_n::severity::high:
               return "high";
           case FaultHandler_n::severity::very_high:
               return "very_high";
           case FaultHandler_n::severity::highest:
               return "highest";
       }
return "FAIL";
}
