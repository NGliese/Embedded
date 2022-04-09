/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <Timeservice.hpp>
#include <iostream>

#include <ADC_API_ESP32.hpp>
#include <MQTT_Message.hpp>
#include <Maintainer.hpp>
#include <array>

#include <GPIO_API.hpp>
#include <esp32_i2c_adc_battery_v1_0.hpp>
#include <i2c.hpp>
void test_adc()
{
	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_5;
	adc_conf.vRef = 1114;

	ADC_API_ESP32 m_adc{adc_conf};

	for(;;) // we must not exit the main thread
	{
		std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
		vTaskDelay(100);
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

void test_board_IO()
{
	GPIO_API m_pin{esp32_i2c_adc_battery_v1_0::ON_OFF_SENSOR};
	m_pin.setToOutput();
	for(;;)
	{
		m_pin.setHigh();
		Timeservice::wait_sec(5);
		m_pin.setLow();
		Timeservice::wait_sec(5);
	}
}
void test_board_i2c()
{
	i2c_conf_t conf{50000, esp32_i2c_adc_battery_v1_0::I2C_SDA,
					esp32_i2c_adc_battery_v1_0::I2C_SCLK};
	auto m_i2c = i2c::getInstance(conf);

	GPIO_API m_pin{esp32_i2c_adc_battery_v1_0::ON_OFF_SENSOR};
	m_pin.setToOutput();
	for(;;)
	{
		std::cout << "Running a test ! \n ";
		m_i2c.scan();
		m_pin.setHigh();
		Timeservice::wait_sec(5);
		m_pin.setLow();
		Timeservice::wait_sec(5);
	}
}

void test_board_adc_battery()
{
	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = esp32_i2c_adc_battery_v1_0::ADC_BATTERY;
	adc_conf.vRef = 1114;

	ADC_API_ESP32 m_adc{adc_conf};

	GPIO_API m_pin{esp32_i2c_adc_battery_v1_0::ON_OFF_SENSOR};
	m_pin.setToOutput();
	for(;;)
	{
		std::cout << "Running a test ! \n ";

		m_pin.setHigh();
		Timeservice::wait_sec(2);
		// measure adc
		std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
		Timeservice::wait_sec(3);
		m_pin.setLow();
		Timeservice::wait_sec(5);
	}
}

void post_board_battery_test()
{
	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = esp32_i2c_adc_battery_v1_0::ADC_BATTERY;
	adc_conf.vRef = 1114;

	ADC_API_ESP32 m_adc{adc_conf};

	GPIO_API m_pin{esp32_i2c_adc_battery_v1_0::ON_OFF_SENSOR};
	m_pin.setToOutput();

	mqtt_api_v2 m_mqtt;
	MQTT_Message message{{db_id::ESP32_BAT_HW_BATTERY_ADC, 100}};

	for(;;)
	{
		std::cout << "Running a test ! \n ";

		m_pin.setHigh();
		Timeservice::wait_sec(2);

		message.addData(m_adc.measureValue());
		m_mqtt.publish("mqtt/burst_msg", message.toString());
		message.clear();

		Timeservice::wait_sec(3);
		m_pin.setLow();
		Timeservice::wait_sec(5);
	}
}
void app_main(void)
{
	Maintainer m_maintain{wifi_conf, db_id::ESP32_BAT_HW_BATTERY_ADC};
	m_maintain.start();
	//	test_board_IO();
	// test_board_i2c();
	// test_board_adc_battery();
	post_board_battery_test();
	for(;;)
	{
		std::cout << "Running a test ! \n ";

		Timeservice::wait_sec(5);
	}
}
