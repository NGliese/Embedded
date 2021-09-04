/*
 * hal_mqtt_log.cpp
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
 *  \file       hal_mqtt_log.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/hal_mqtt_log.hpp"

#if 0
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "hal_mqtt_log";
#endif

void hal_mqtt_log::write(const std::string& str) {
    mqtt_api_v2 mqtt;
    mqtt.publish("mqtt/sensor_log_msg",str); // ToDo find en god måde at sende topic med

}

#endif
