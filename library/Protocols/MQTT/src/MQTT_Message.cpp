/*
 * MQTT_Message.cpp
 *
 *  Created on: Feb 3, 2021
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
 *  \file       MQTT_Message.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/MQTT_Message.hpp"


#define CONSTRUCT_MIN_SIZE (3)
#define CONSTRUCT_PARAMETER_OFFSET (1)
#define CONSTRUCT_EXPECTED_MOD (2)
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "MQTT_Message";
#endif

MQTT_Message::MQTT_Message(const uint64_t& entity_id,const size_t& buffer_size ) : m_entity_id{entity_id},
        m_buffer_size{buffer_size}, m_semaphore{"mqtt message"}{
#ifdef __ESP32__
            m_semaphore.give();
#endif
}

MQTT_Message::MQTT_Message(const msg_conf_t& conf)  : m_entity_id{map.at(conf.entity_id)},  m_buffer_size{conf.buffer_size}, m_semaphore{"mqtt message"}{
#ifdef __ESP32__
            m_semaphore.give();
#endif
}

MQTT_Message::~MQTT_Message() {
}

general_err_t MQTT_Message::addData(const uint64_t& data) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> MQTT_Message::addData >> ");
    #endif

    // Executable code:
    if( m_buffer_size <= m_data.size() )
    {
        return GE_OUT_OF_RANGE;
    }
#ifdef __ESP32__
    if(!m_semaphore.take(5000,"addData") )
    {
        return GE_SEMAPHORE_NOT_TAKEN;
    }
#endif
    m_data.push_back({Timeservice::getTimeNow() ,data} );
#ifdef __ESP32__
    m_semaphore.give();
#endif
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< MQTT_Message::addData << ");
    #endif

    return GE_OK;
}

general_err_t MQTT_Message::addData_f(const float& data) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> enclosing_method >> ");
    #endif
    // Executable code:


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< enclosing_method << ");
    #endif

    return GE_OK;
}

const std::string MQTT_Message::toString(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> MQTT_Message::toString >> ");
    #endif
    // Executable code:
    std::string str="";
#ifdef __ESP32__
    if(!m_semaphore.take(5000,"toString") )
    {
        return str;
    }
#endif

    str=std::to_string(m_entity_id)+",";
    for(auto ele : m_data)
    {
        str+=std::to_string(ele.first);
        str+=",";
        str+=std::to_string(ele.second);
        str+=",";
    }
#ifdef __ESP32__
    m_semaphore.give();
#endif
    // remove the last ","
    str = str.substr(0,str.size()-1);
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< MQTT_Message::toString << ");
    #endif

    return str;

}

general_err_t MQTT_Message::clear(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> MQTT_Message::clear >> ");
    #endif
#ifdef __ESP32__
    // Executable code:
    if(!m_semaphore.take(5000,"toString") )
    {
        return GE_SEMAPHORE_NOT_TAKEN;
    }
#endif
    m_data.clear();
#ifdef __ESP32__
    m_semaphore.give();
#endif
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< MQTT_Message::clear << ");
    #endif

    return GE_OK;
}

MQTT_Message MQTT_Message::construct(const std::string& str) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> MQTT_Message::construct >> ");
    #endif
    // Executable code:

    auto vec = basic_utils::split(str,",");

    if(vec.empty() or vec.size() < CONSTRUCT_MIN_SIZE or ( (vec.size() - CONSTRUCT_PARAMETER_OFFSET)%CONSTRUCT_EXPECTED_MOD) )
    {
        std::cout << "fault in construction of MQTT message! \n";
        Logger::write({GE_FAIL,GR_NO_RESPONSE,"fault in construction of MQTT message!"});
    }


    MQTT_Message msg{0,0};



    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< MQTT_Message::construct << ");
    #endif

    return msg;
}
