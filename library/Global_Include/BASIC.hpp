/*
 * BASIC.hpp
 *
 *  Created on: May 22, 2020
 *      Author: nikolaj
 */
/**
 * @brief header file to interchange between UnitTestMode, ESP32 and RPI.
 *        Macro definition decides what state the system is in.
 */

#ifndef BPS_INCLUDE_BASIC_HPP_
#define BPS_INCLUDE_BASIC_HPP_

#define UNIT_TEST_MODE (1)

#define __WITH_OPENCV__ (1)

#define GLOBAL_MQTT_SERVER ("mqtt://192.168.1.157:1883")

#ifndef UNIT_TEST_MODE
//#define __RPI__ (1)
#define __DATABASE__ (1)

#ifndef __RPI__
#define __ESP32__ (1)
#endif

#endif
#ifdef UNIT_TEST_MODE
#define __UNITTEST__ (1)
#endif

#ifdef __ESP32__
#include <esp_log.h>
#include <esp_err.h>
#include "sdkconfig.h"
#endif

#endif /* BPS_INCLUDE_BASIC_HPP_ */
