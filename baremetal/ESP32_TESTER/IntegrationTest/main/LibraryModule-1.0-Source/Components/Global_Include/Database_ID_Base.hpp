/*
 * ID_Base.hpp
 *
 *  Created on: Mar 2, 2021
 *      Author: Nikolaj
 */

#ifndef COMPONENTS_DATA_PROTOCOL_INCLUDE_ID_BASE_HPP_
#define COMPONENTS_DATA_PROTOCOL_INCLUDE_ID_BASE_HPP_
/*------------------------------------------------------------------------------+
 |              C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Database_ID_Base.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email        :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Database_ID_Base.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/**
 * @brief database header file to map database ID's with enum names for easier visual description
 */

/*------------------------------------------------------------------------------+
 |                              Includes                                        |
 +------------------------------------------------------------------------------*/

#include <map>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

enum class db_id
{
	/* DEBUG SENSOR */
	DEBUG_ID1,
	DEBUG_ID2,
	DEBUG_ID3,
	DEBUG_ID4,
	DEBUG_ID5,
	DEBUG_ID6,
	DEBUG_ID7,
	DEBUG_ID8,
	DEBUG_ID9,
	/* Window Detector */
	WINDOW_DETECT_OFFICE1,
	WINDOW_DETECT_BEDROOM1,
	WINDOW_DETECT_GYM1,
	WINDOW_DETECT_GYM2,
	WINDOW_DETECT_LIVINGROOM1,
	WINDOW_DETECT_KITCHEN1,
	/* ENV - SKUR */
	ENV_SKUR_TEMP1,
	ENV_SKUR_HUM1,

	/* GreenHouse Sensing */
	GH_AMBIENT_TEMP,
	GH_AMBIENT_HUM,
	GH_AMBIENT_LIGHT,
	GH_AMBIENT_C02,
	GH_WATER_LEVEL,
	GH_MOIST1,
	GH_MOIST2,
	GH_MOIST3,
	GH_MOIST4,

	/*  Network Maintainer */
	NETWORK_MAINTAINER_STATUS,

	/* ENV01 */
	ENV01_TEMPERATURE,
	ENV01_HUMIDITY,
	ENV01_CO2,
	ENV01_LUX,
	CCTV01_DEBUG1,
	CCTV01_DEBUG2,
	CCTV01_DEBUG3,
	CCTV01_DEBUG4,
	CCTV01_DEBUG5,
	CCTV01_KNN_CC,
	CCTV01_MOG2_CC,
	CCTV01_HEIGHT,
	CCTV01_WIDTH,
	CCTV01_AREA,
	CCTV01_ASPECT,
	CCTV01_AMOUNT,
	CCTV01_ALARM,
	/* DOGFEEDER */
	DOGFEEDER_CURRENT_SENSOR,
	DOGFEEDER_DOOR_SIGNAL,
	DOGFEEDER_ERROR_CODE,
	DOGFEEDER_ACTUATOR_SET_POINT,

	/* WaterStation */
	WATERSTATION_RAW_ADC,
	WATERSTATION_COUNTER,
	WATERSTATION_ERROR_CODE,
	WATERSTATION_MAX_ADC_VAL,
	WATERSTATION_MIN_ADC_VAL,

	/* esp32 battery test */
	ESP32_BAT_HW_BATTERY_ADC,
	ESP32_BAT_HW_SENSOR_ADC,
};

static const std::map<db_id, uint32_t> map{
	{db_id::DEBUG_ID1, 1},
	{db_id::DEBUG_ID2, 2},
	{db_id::DEBUG_ID3, 3},
	{db_id::DEBUG_ID4, 4},
	{db_id::DEBUG_ID5, 5},
	{db_id::DEBUG_ID6, 6},
	{db_id::DEBUG_ID7, 7},
	{db_id::DEBUG_ID8, 8},
	{db_id::DEBUG_ID9, 9},
	{db_id::WINDOW_DETECT_OFFICE1, 10},
	{db_id::WINDOW_DETECT_BEDROOM1, 11},
	{db_id::WINDOW_DETECT_GYM1, 12},
	{db_id::WINDOW_DETECT_GYM2, 13},
	{db_id::WINDOW_DETECT_LIVINGROOM1, 14},
	{db_id::WINDOW_DETECT_KITCHEN1, 15},
	{db_id::ENV_SKUR_TEMP1, 16},
	{db_id::ENV_SKUR_HUM1, 17},
	{db_id::GH_AMBIENT_TEMP, 18},
	{db_id::GH_AMBIENT_HUM, 19},
	{db_id::GH_AMBIENT_LIGHT, 20},
	{db_id::GH_AMBIENT_C02, 21},
	{db_id::GH_WATER_LEVEL, 22},
	{db_id::GH_MOIST1, 23},
	{db_id::GH_MOIST2, 24},
	{db_id::GH_MOIST3, 25},
	{db_id::GH_MOIST4, 26},
	{db_id::NETWORK_MAINTAINER_STATUS, 27},
	{db_id::ENV01_TEMPERATURE, 28},
	{db_id::ENV01_HUMIDITY, 29},
	{db_id::ENV01_CO2, 30},
	{db_id::ENV01_LUX, 31},
	{db_id::CCTV01_DEBUG1, 32},
	{db_id::CCTV01_DEBUG2, 33},
	{db_id::CCTV01_DEBUG3, 34},
	{db_id::CCTV01_DEBUG4, 35},
	{db_id::CCTV01_DEBUG5, 36},
	{db_id::CCTV01_KNN_CC, 102},
	{db_id::CCTV01_MOG2_CC, 103},
	{db_id::CCTV01_HEIGHT, 39},
	{db_id::CCTV01_WIDTH, 40},
	{db_id::CCTV01_AREA, 41},
	{db_id::CCTV01_ASPECT, 42},
	{db_id::CCTV01_AMOUNT, 43},
	{db_id::CCTV01_ALARM, 108},
	{db_id::DOGFEEDER_DOOR_SIGNAL, 104},
	{db_id::DOGFEEDER_ERROR_CODE, 105},
	{db_id::DOGFEEDER_CURRENT_SENSOR, 106},
	{db_id::DOGFEEDER_ACTUATOR_SET_POINT, 107},

	{db_id::WATERSTATION_RAW_ADC, 109},
	{db_id::WATERSTATION_COUNTER, 111},
	{db_id::WATERSTATION_ERROR_CODE, 110},
	{db_id::WATERSTATION_MAX_ADC_VAL, 112},
	{db_id::WATERSTATION_MIN_ADC_VAL, 113},

	{db_id::ESP32_BAT_HW_BATTERY_ADC, 114},
	{db_id::ESP32_BAT_HW_SENSOR_ADC, 115},
};

#endif /* COMPONENTS_DATA_PROTOCOL_INCLUDE_ID_BASE_HPP_ */
