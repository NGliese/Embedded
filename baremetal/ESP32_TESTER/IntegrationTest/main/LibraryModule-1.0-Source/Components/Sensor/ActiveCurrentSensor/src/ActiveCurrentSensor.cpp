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
 *  @file       ActiveCurrentSensor.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-01-22
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/ActiveCurrentSensor.hpp"
const std::string recieved_queue_message = "we are activating the queue";
#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "ActiveCurrentSensor";
#endif

ActiveCurrentSensor::ActiveCurrentSensor(const ADC_API_ESP32::config& adc_conf,
										 const MQTT_Message::msg_conf_t& msg_conf)
	: m_adc{adc_conf}, m_msg{msg_conf}, m_isRunning{false}, m_queue{1,
																	recieved_queue_message.size()}
{
	// m_queue.initialize(1, recieved_queue_message.size());
}
ActiveCurrentSensor::~ActiveCurrentSensor() {}

void ActiveCurrentSensor::activateQueue()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> ActiveCurrentSensor::activateQueue >> ");
#endif
	// Executable code:

	m_queue.send(recieved_queue_message.c_str(), 5000);
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  ActiveCurrentSensor::activateQueue << ");
#endif
}

void ActiveCurrentSensor::run(void* data)
{
	std::string str;
	for(;;)
	{
		if(!m_queue.recieve(&str, 50000)) // we should wait forever here
		{
			// check OTA flag
			// this might be a blocking call ( expected )
			Maintainer::checkOTAUpdate();
			m_isRunning = true;
			// run main function
			main_function();
			m_isRunning = false;
		}
	}
	// exit the thread
	// this->stop();
}

general_err_t ActiveCurrentSensor::main_function()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> ActiveCurrentSensor::main_function >> ");
#endif
	// Executable code:
	constexpr size_t AMOUNT_OF_MEASUREMENTS = 300;
	constexpr size_t WAIT_DELAY = 20;
	m_msg.clear(); // make sure it is cleared
	for(size_t i = 0; i < AMOUNT_OF_MEASUREMENTS; i++)
	{
		m_msg.addData(m_adc.measureValue());
		Timeservice::wait_ms(WAIT_DELAY);
	}
	m_mqtt.publish("mqtt/burst_msg", m_msg.toString());
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  ActiveCurrentSensor::main_function << ");
#endif

	return GE_OK;
}