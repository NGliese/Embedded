/***********************************************************************************************+
 *  @brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  @note       ANY RELEVANT NOTES
 *
 *  @file       ErrorCodeParser.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-01-31
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/ErrorCodeParser.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "ErrorCodeParser";
#endif

general_err_t ErrorCodeParser::postToMqtt(const db_id& id, const general_err_t& err,
										  const std::string& description)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> ErrorCodeParser::postToMqtt >> ");
#endif
	// Executable code:
	mqtt_api_v2 mqtt;

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  ErrorCodeParser::postToMqtt << ");
#endif

	return mqtt.publish("mqtt/error_codes", toString(id, err, description));
}