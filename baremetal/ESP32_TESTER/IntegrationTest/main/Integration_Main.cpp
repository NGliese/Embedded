/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <Timeservice.hpp>
#include <iostream>

#include <MQTT_Message.hpp>
#include <Maintainer.hpp>
#include <array>
#include <esp32_i2c_adapter_v1_0.hpp>
#include <i2c.hpp>
#include <i2c_esp32.hpp>
const wifi_conf_t wifi_conf{.ssid = WIFI_SSID_LOCAL, .password = WIFI_PWD_LOCAL};

#ifdef __cplusplus
extern "C" {
#endif
void app_main(void);
// Your prototype or Definition
#ifdef __cplusplus
}
#endif

void test_i2c_byte()
{
	i2c_conf_t conf{50000, esp32_i2c_adapter_v1_0::I2C_SDA, esp32_i2c_adapter_v1_0::I2C_SCLK};
	auto m_i2c = i2c<i2c_esp32>::getInstance(conf);

	for(;;)
	{
		std::cout << " Testing i2c WRITING  ...\n";
		m_i2c.writeByte(0x25, 0xfa);
		Timeservice::wait_sec(3);
		std::cout << " Testing i2c READING  ...\n";
		m_i2c.readByte(0x25);
		Timeservice::wait_sec(3);
	}
}

void app_main(void)
{
	//	Maintainer m_maintain{wifi_conf, db_id::DEBUG_ID3};
	//	m_maintain.start();
	test_i2c_byte();
	for(;;)
	{
		std::cout << "Running a test ! \n ";

		Timeservice::wait_sec(5);
	}
}
