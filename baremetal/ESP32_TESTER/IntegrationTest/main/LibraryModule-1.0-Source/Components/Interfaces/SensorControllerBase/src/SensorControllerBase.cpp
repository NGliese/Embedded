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
 *  @file       SensorControllerBase.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-02-27
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/SensorControllerBase.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "SensorControllerBase";
#endif

void SensorControllerBase::run(void* data)
{
	for(;;)
	{
		auto err = main_function();
		if(err != GE_OK)
		{
			postError(err, "Main function failed");
		}

		Timeservice::wait_ms(m_delay);
	}
}

general_err_t SensorControllerBase::postData(const MQTT_Message& message, const std::string& topic)
{
	return m_mqtt.publish(topic, message.toString());
}