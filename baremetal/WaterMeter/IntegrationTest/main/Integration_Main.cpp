/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <ADC_API_ESP32.hpp>
#include <DataBroker.hpp>
#include <DistanceSensorController.hpp>
#include <GPIO_API.hpp>
#include <MQTT_Message.hpp>
#include <Maintainer.hpp>
#include <Timeservice.hpp>
#include <WaterEstimator_Service.hpp>
#include <iostream>
#include <mqtt_api_v2.hpp>
void test_adc()
{
	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_6; // GPIO34
	adc_conf.vRef = 1114;

	ADC_API_ESP32 m_adc{adc_conf};

	GPIO_API m_pin{GPIO_HAL::pin::GPIO_NUM_27};
	m_pin.setToOutput();
	bool toogler = false;
	for(;;)
	{
		std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
		if(toogler)
		{
			m_pin.setHigh();
			toogler = false;
		}
		else
		{
			m_pin.setLow();
			toogler = true;
		}
		Timeservice::wait_ms(5U);
	}
}

void measure() {}

void measure_and_send()
{
	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_6; // GPIO34
	adc_conf.vRef = 1114;

	ADC_API_ESP32 m_adc{adc_conf};

	GPIO_API m_pin{GPIO_HAL::pin::GPIO_NUM_27};
	m_pin.setToOutput();
	bool toogler = false;

	// Executable code:
	constexpr size_t AMOUNT_OF_MEASUREMENTS = 300;
	constexpr size_t WAIT_DELAY = 20;

	MQTT_Message m_msg{{db_id::WATERSTATION_RAW_ADC, AMOUNT_OF_MEASUREMENTS}};
	mqtt_api_v2 m_mqtt;

	for(;;)
	{
		m_msg.clear(); // make sure it is cleared
		for(size_t i = 0; i < AMOUNT_OF_MEASUREMENTS; i++)
		{
			m_msg.addData(Timeservice::getTimeNow(), m_adc.measureValue());
			Timeservice::wait_ms(WAIT_DELAY);
		}
		m_mqtt.publish("mqtt/burst_msg", m_msg.toString());

		if(toogler)
		{
			m_pin.setHigh();
			toogler = false;
		}
		else
		{
			m_pin.setLow();
			toogler = true;
		}
		Timeservice::wait_ms(5U);
	}
}

const wifi_conf_t wifi_conf{.ssid = WIFI_SSID_LOCAL, .password = WIFI_PWD_LOCAL};

#ifdef __cplusplus
extern "C" {
#endif
void app_main(void);
// Your prototype or Definition
#ifdef __cplusplus
}
#endif

constexpr size_t AMOUNT_OF_MEASUREMENTS = 300;
constexpr size_t WAIT_DELAY = 100;
constexpr SensorControllerBase::init_conf DEFAULT_CONF{
	.buffer_raw_conf{.entity_id = db_id::WATERSTATION_RAW_ADC,
					 .buffer_size = AMOUNT_OF_MEASUREMENTS},
	.buffer_external_conf{.entity_id = db_id::WATERSTATION_RAW_ADC,
						  .buffer_size = AMOUNT_OF_MEASUREMENTS},
	.task_delay = 5U,
	.error_code_id = db_id::WATERSTATION_ERROR_CODE,
};

const ADC_API_ESP32::config DEFAULT_ADC{

	.name = "adc_test",
	.samples = 64U,
	.channel = ADC1_CHANNEL_6, // GPIO34
	.vRef = 1114UL,

};

void sensor_controller_test()
{
	DistanceSensorController m_controller{{DEFAULT_CONF, WAIT_DELAY, DEFAULT_ADC}};

	m_controller.start();

	for(;;)
	{
		std::cout << " testing sensor_controller_test.... \n";
		Timeservice::wait_sec(10);
	}
}

void service_test()
{
	DistanceSensorController m_controller{{DEFAULT_CONF, WAIT_DELAY, DEFAULT_ADC}};
	m_controller.start();

	DataBroker m_broker{1000, m_controller};

	// init services
	WaterEstimator_Service m_service{3, sizeof(int), m_broker.getSafeBuffer(),
									 db_id::WATERSTATION_ERROR_CODE, GPIO_HAL::pin::GPIO_NUM_27};
	m_service.start();

	// add services
	m_broker.addService(&m_service);

	// start broker

	m_broker.start();

	// test pins

	for(;;)
	{
		std::cout << " testing sensor_controller_test.... \n";
		Timeservice::wait_sec(5);
	}
}

void app_main(void)
{
	Maintainer m_maintain{wifi_conf};
	m_maintain.start();

	// test_adc();
	// measure_and_send();
	// sensor_controller_test();

	service_test();
	for(;;)
	{
		std::cout << "Running a test ! \n ";

		Timeservice::wait_sec(5);
	}
}
