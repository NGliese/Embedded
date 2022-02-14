/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <ADC_API_ESP32.hpp>
#include <ActiveCurrentSensor.hpp>
#include <DogFeederDoor.hpp>
#include <ErrorCodeParser.hpp>
#include <MG996R.hpp>
#include <MQTT_Message.hpp>
#include <Maintainer.hpp>
#include <PWM_API_ESP32.hpp>
#include <Timeservice.hpp>
#include <WiFi_API.hpp>
#include <array>
#include <esp32_http_sal.hpp>
#include <iostream>
#include <jsmn_object.hpp>

#include <esp_sleep.h> // sleep

const wifi_conf_t wifi_conf{.ssid = WIFI_SSID_LOCAL, .password = WIFI_PWD_LOCAL};

void test_mqtt()
{
	/* -------------- INIT WIFI --------------------- */
	wifi_conf_t m_conf;
#if 1
	m_conf.ssid = WIFI_SSID_LOCAL;
	m_conf.password = WIFI_PWD_LOCAL; // no one can see this password :)
#endif
	WiFi_API m_api{m_conf};

	if(m_api.connect() != GE_OK)
	{
		exit(-1);
	}
	/* ---------- init timeservice task ------------ */

	Timeservice m_time;
	m_time.initialize_sntp();

	/* --------------------------------------------- */

	for(;;) // we must not exit the main thread
	{
		std::cout << "test \n";
		vTaskDelay(1000);
	}
}

void simple_connect()
{
	/* -------------- INIT WIFI --------------------- */

	static WiFi_API m_api{wifi_conf};

	if(m_api.connect() != GE_OK)
	{
		exit(-1);
	}
	/* ---------- init timeservice task ------------ */

	//    Timeservice m_time;
	//    m_time.initialize_sntp();

	/* --------------------------------------------- */
}

void test_pwm()
{
	simple_connect();

	HAL_ESP32::config conf, conf2, conf3;

	conf.channel = LEDC_CHANNEL_0;
	conf.duty = 50;
	conf.frequency = 50;
	conf.m_pin = GPIO_NUM_27;
	conf.mode = LEDC_LOW_SPEED_MODE;
	conf3 = conf2 = conf;

	conf2.m_pin = GPIO_NUM_26;
	conf3.m_pin = GPIO_NUM_25;

	std::array<PWM_API_ESP32, 3> vec{PWM_API_ESP32{conf, "pwm1"}, PWM_API_ESP32{conf2, "pwm2"},
									 PWM_API_ESP32{conf3, "pwm3"}};

	// assuming 120 degrees rotation,
	// assuming duty = 0 - 13%
	// duty = (14/120) * wanted_degree;

	int i = 0;
	for(;;) // we must not exit the main thread
	{
		float duty = (12.0 / 120.0) * i;
		std::cout << "test i is : " << i << "duty is : " << duty << " \n";
		for(auto& ele : vec)
		{
			//  ele.setDutyCycle(duty);
		}

		++i;
		if(i == 120)
		{
			i = 0;
		}

		vTaskDelay(1000);
	}
}

void test_adc()
{
	simple_connect();

	HAL_ESP32::config conf;

	conf.channel = LEDC_CHANNEL_0;
	conf.duty = 50;
	conf.frequency = 50;
	conf.m_pin = GPIO_NUM_27; // pwm1
	conf.mode = LEDC_LOW_SPEED_MODE;

	std::array<PWM_API_ESP32, 1> vec{PWM_API_ESP32{conf, "pwm1"}};

	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_5;
	adc_conf.vRef = 1114;

	ADC_API_ESP32 m_adc{adc_conf};
	int i = 0;
	for(;;) // we must not exit the main thread
	{
		float duty = (12.0 / 120.0) * i;
		std::cout << "test i is : " << i << "duty is : " << duty << " \n";
		for(auto& ele : vec)
		{
			ele.setDutyCycle(duty);
		}
		std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";

		++i;
		if(i == 120)
		{
			i = 0;
		}

		vTaskDelay(100);
	}
}
constexpr float START_POSITION = 2.5;
constexpr float END_POSITION = 13;
void test_go_to_0()
{
	simple_connect();

	HAL_ESP32::config conf;

	conf.channel = LEDC_CHANNEL_0;
	conf.duty = 50;
	conf.frequency = 50;
	conf.m_pin = GPIO_NUM_27; // pwm1
	conf.mode = LEDC_LOW_SPEED_MODE;

	std::array<PWM_API_ESP32, 1> vec{PWM_API_ESP32{conf, "pwm1"}};

	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_5;
	adc_conf.vRef = 1114;

	ADC_API_ESP32 m_adc{adc_conf};

	std::cout << ">> Go to start position >>\n ";
	//   float duty = (12.0/120.0) * 25;

	for(auto& ele : vec)
	{
		//  ele.setDutyCycle(END_POSITION);
		ele.setDutyCycle(START_POSITION);
	}

	for(;;)
	{
		std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";

		vTaskDelay(100);
	}
	std::cout << "<< Go to start position <<\n ";
}

void test_motor0()
{
	mg996r_conf_t motor_conf;
	auto& pwm_conf = motor_conf.conf;

	pwm_conf.channel = LEDC_CHANNEL_0;
	pwm_conf.duty = 50;
	pwm_conf.frequency = 50;
	pwm_conf.m_pin = GPIO_NUM_27; // pwm1
	pwm_conf.mode = LEDC_LOW_SPEED_MODE;

	motor_conf.name = "motor";
	MG996R m_motor{motor_conf};

	m_motor.execute(END_POSITION);
	for(;;)
	{
		//  std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
		std::cout << " waiting for stuf to happen...\n";
		vTaskDelay(100);
	}
}

void test_door_init_open()
{
	mg996r_conf_t motor_conf;
	auto& pwm_conf = motor_conf.conf;

	pwm_conf.channel = LEDC_CHANNEL_0;
	pwm_conf.duty = 13;
	pwm_conf.frequency = 50;
	pwm_conf.m_pin = GPIO_NUM_27; // pwm1
	pwm_conf.mode = LEDC_LOW_SPEED_MODE;

	motor_conf.name = "motor";
	DogFeederDoor m_door{motor_conf};

	for(;;)
	{
		std::cout << "testing init open \n";
		vTaskDelay(5000);
	}
}
RTC_NOINIT_ATTR uint8_t rtc_noinit_data = 0;

void test_door_init_open_deepSleep()
{
	if(rtc_noinit_data == 0)
	{
		rtc_noinit_data = 13;
	}

	switch(esp_sleep_get_wakeup_cause())
	{
		case ESP_SLEEP_WAKEUP_TIMER: {
			std::cout << "woke up from deep sleep ... @time : <" << (int)Timeservice::getTimeNow()
					  << "\n";
			mg996r_conf_t motor_conf;
			auto& pwm_conf = motor_conf.conf;

			pwm_conf.channel = LEDC_CHANNEL_0;
			// toggle between open and close
			if(rtc_noinit_data == 13)
			{
				std::cout << " The door was open, lets close it  \n";
				rtc_noinit_data = 2.5;
			}
			else
			{
				std::cout << " The door was closed, lets open it  \n";
				rtc_noinit_data = 13;
			}
			pwm_conf.duty = rtc_noinit_data;
			pwm_conf.frequency = 50;
			pwm_conf.m_pin = GPIO_NUM_27; // pwm1
			pwm_conf.mode = LEDC_LOW_SPEED_MODE;

			motor_conf.name = "motor";
			DogFeederDoor m_door{motor_conf};
			Timeservice::wait_sec(5);
			break;
		}
		case ESP_SLEEP_WAKEUP_UNDEFINED:
		default:
			printf("Not a deep sleep reset\n");
	}
	const int wakeup_time_sec = 20;
	std::cout << " enabling timer wake-up from deep sleep, sleeping for  <" << wakeup_time_sec
			  << "> sec \n";
	esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000000);
	esp_deep_sleep_start();
}

void test_door()
{
	mg996r_conf_t motor_conf;
	auto& pwm_conf = motor_conf.conf;

	pwm_conf.channel = LEDC_CHANNEL_0;
	pwm_conf.duty = 50;
	pwm_conf.frequency = 50;
	pwm_conf.m_pin = GPIO_NUM_27; // pwm1
	pwm_conf.mode = LEDC_LOW_SPEED_MODE;

	motor_conf.name = "motor";
	DogFeederDoor m_door{motor_conf};

	for(;;)
	{
		//  std::cout << " measure adc value is : " << std::to_string(m_adc.measureValue()) << "\n";
		std::cout << " ... Opening door ... \n";
		General_Error::printError("Open door", m_door.open());
		vTaskDelay(5000);
		std::cout << " ... Closing door ... \n";
		General_Error::printError("Close door", m_door.close());
		vTaskDelay(5000);
	}
}
constexpr std::uint8_t DOOR_CLOSE = 100;
constexpr std::uint8_t DOOR_OPEN = 200;
void test_get_door_status()
{
	esp32_http_sal m_http{"192.168.1.157", 1880};
	for(;;)
	{
		std::cout << " ... Getting request ... \n";
		Timeservice::wait_sec(5);
		std::string out;
		if(m_http.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << " recieved output is : <" << out << ">\n";
		}
	}
}

void test_get_jsmn()
{
	esp32_http_sal m_http{"192.168.1.157", 1880};
	for(;;)
	{
		std::cout << " ... Getting request ... \n";
		Timeservice::wait_sec(5);
		std::string out;
		if(m_http.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << "test_get_jsmn:: recieved output is : <" << out << ">\n";
			std::string str = out;
			auto val = jsmn_object::getParsedIntegerValue(out, "value");
			std::cout << " converted value is : <" << val << ">\n";
			if(val == DOOR_CLOSE)
			{
				std::cout << "CLOSE DOOR \n";
			}
			if(val == DOOR_OPEN)
			{
				std::cout << "OPEN DOOR \n";
			}
		}
	}
}

void test_get_door_status_http_semaphore_test()
{
	esp32_http_sal m_http1{"192.168.1.157", 1880}; // OK
	esp32_http_sal m_http2{"192.168.1.157", 188}; // bad
	esp32_http_sal m_http3{"192.168.1.15", 1880}; // bad
	esp32_http_sal m_http4{"192.168.1.15", 188}; // bad
	esp32_http_sal m_http5{"", 1880}; // bad

	for(;;)
	{
		std::cout << " ... Getting request ... \n";
		Timeservice::wait_sec(5);
		std::string out;
		if(m_http1.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << " recieved output is : <" << out << ">\n";
		}
		if(m_http2.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << " recieved output is : <" << out << ">\n";
		}
		if(m_http3.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << " recieved output is : <" << out << ">\n";
		}
		if(m_http4.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << " recieved output is : <" << out << ">\n";
		}
		if(m_http5.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << " recieved output is : <" << out << ">\n";
		}
	}
}

void test_jsmn_and_door()
{
	mg996r_conf_t motor_conf;
	auto& pwm_conf = motor_conf.conf;

	pwm_conf.channel = LEDC_CHANNEL_0;
	pwm_conf.duty = 50;
	pwm_conf.frequency = 50;
	pwm_conf.m_pin = GPIO_NUM_27; // pwm1
	pwm_conf.mode = LEDC_LOW_SPEED_MODE;

	motor_conf.name = "motor";
	DogFeederDoor m_door{motor_conf};
	esp32_http_sal m_http{"192.168.1.157", 1880};

	for(;;)
	{
		std::cout << " ... Getting request ... \n";
		Timeservice::wait_sec(5);
		std::string out;
		if(m_http.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << "test_get_jsmn:: recieved output is : <" << out << ">\n";
			std::string str = out;
			auto val = jsmn_object::getParsedIntegerValue(out, "value");
			std::cout << " converted value is : <" << val << ">\n";
			if(val == DOOR_CLOSE)
			{
				std::cout << " ... Closing door ... \n";
				General_Error::printError("Close door", m_door.close());
			}
			if(val == DOOR_OPEN)
			{
				std::cout << " ... Opening door ... \n";
				General_Error::printError("Open door", m_door.open());
			}
		}
	}
}

void test_activeCurrentSensor()
{
	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_5;
	adc_conf.vRef = 1114;

	MQTT_Message::msg_conf_t msg_conf{
		.entity_id = db_id::DOGFEEDER_CURRENT_SENSOR,
		.buffer_size = 100,
	};

	ActiveCurrentSensor m_sensor{adc_conf, msg_conf};
	m_sensor.start();

	for(;;)
	{
		std::cout << " ... Measuring adc ...\n";
		m_sensor.activateQueue();
		Timeservice::wait_sec(25);
	}
}

void test_everything_connected()
{
	mg996r_conf_t motor_conf;
	auto& pwm_conf = motor_conf.conf;

	pwm_conf.channel = LEDC_CHANNEL_0;
	pwm_conf.duty = 50;
	pwm_conf.frequency = 50;
	pwm_conf.m_pin = GPIO_NUM_27; // pwm1
	pwm_conf.mode = LEDC_LOW_SPEED_MODE;

	motor_conf.name = "motor";
	DogFeederDoor m_door{motor_conf};
	esp32_http_sal m_http{"192.168.1.157", 1880};

	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_5;
	adc_conf.vRef = 1114;

	MQTT_Message::msg_conf_t msg_conf{
		.entity_id = db_id::DOGFEEDER_CURRENT_SENSOR,
		.buffer_size = 400,
	};

	ActiveCurrentSensor m_sensor{adc_conf, msg_conf};
	m_sensor.start();
	uint8_t OLD_VALUE = 0;
	constexpr size_t SLEEP_TIME = 5;
	for(;;)
	{
		std::cout << " ... Measuring adc ...\n";

		std::cout << " ... Getting request ... \n";
		Timeservice::wait_sec(SLEEP_TIME);
		std::string out;
		if(m_http.get("/getDogFeederFlag", out) == GE_OK)
		{
			std::cout << "test_get_jsmn:: recieved output is : <" << out << ">\n";
			std::string str = out;
			auto val = jsmn_object::getParsedIntegerValue(out, "value");
			std::cout << " converted value is : <" << val << ">\n";
			if(val == DOOR_CLOSE)
			{
				if(OLD_VALUE != val)
				{
					m_sensor.activateQueue();
				}
				std::cout << " ... Closing door ... \n";
				General_Error::printError("Close door", m_door.close());
			}
			if(val == DOOR_OPEN)
			{
				if(OLD_VALUE != val)
				{
					m_sensor.activateQueue();
				}
				std::cout << " ... Opening door ... \n";
				General_Error::printError("Open door", m_door.open());
			}
			OLD_VALUE = val;
		}
	}
}

void test_sleep()
{
	switch(esp_sleep_get_wakeup_cause())
	{
		case ESP_SLEEP_WAKEUP_TIMER: {
			std::cout << "woke up from deep sleep ... @time : <" << (int)Timeservice::getTimeNow()
					  << "\n";

			break;
		}
		case ESP_SLEEP_WAKEUP_UNDEFINED:
		default:
			printf("Not a deep sleep reset\n");
	}
	const int wakeup_time_sec = 20;
	std::cout << " enabling timer wake-up from deep sleep, sleeping for  <" << wakeup_time_sec
			  << "> sec \n";
	esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000000);

	esp_deep_sleep_start();
}

RTC_NOINIT_ATTR uint8_t rtc_noinit_pwm_data = 0;
RTC_NOINIT_ATTR uint8_t OLD_VALUE = 0;

void init_motor_and_open()
{
	mg996r_conf_t motor_conf;
	auto& pwm_conf = motor_conf.conf;

	pwm_conf.channel = LEDC_CHANNEL_0;
	pwm_conf.duty = rtc_noinit_pwm_data;
	pwm_conf.frequency = 50;
	pwm_conf.m_pin = GPIO_NUM_27; // pwm1
	pwm_conf.mode = LEDC_LOW_SPEED_MODE;

	motor_conf.name = "motor";
	DogFeederDoor m_door{motor_conf};
	General_Error::printError("Open door", m_door.open());
	Timeservice::wait_sec(5);
}

void init_motor_and_close()
{
	mg996r_conf_t motor_conf;
	auto& pwm_conf = motor_conf.conf;

	pwm_conf.channel = LEDC_CHANNEL_0;
	pwm_conf.duty = rtc_noinit_pwm_data;
	pwm_conf.frequency = 50;
	pwm_conf.m_pin = GPIO_NUM_27; // pwm1
	pwm_conf.mode = LEDC_LOW_SPEED_MODE;

	motor_conf.name = "motor";
	DogFeederDoor m_door{motor_conf};
	General_Error::printError("Close door", m_door.close());
	Timeservice::wait_sec(5);
}

general_err_t run_everything()
{
	esp32_http_sal m_http{"192.168.1.157", 1880};

	ADC_API_ESP32::config adc_conf;

	adc_conf.name = "adc_test";
	adc_conf.samples = 64;
	adc_conf.channel = ADC1_CHANNEL_5;
	adc_conf.vRef = 1114;

	MQTT_Message::msg_conf_t msg_conf{
		.entity_id = db_id::DOGFEEDER_CURRENT_SENSOR,
		.buffer_size = 400,
	};

	ActiveCurrentSensor m_sensor{adc_conf, msg_conf};
	m_sensor.start();

	std::string out;
	if(m_http.get("/getDogFeederFlag", out) == GE_OK)
	{
		std::cout << "test_get_jsmn:: recieved output is : <" << out << ">\n";
		std::string str = out;
		auto val = jsmn_object::getParsedIntegerValue(out, "value");
		std::cout << " converted value is : <" << val << ">\n";
		if(val == DOOR_CLOSE)
		{
			if(OLD_VALUE != val)
			{
				m_sensor.activateQueue();
				std::cout << " ... Closing door ... \n";
				init_motor_and_close();
			}
			// update rtc value
			rtc_noinit_pwm_data = 2.5;
		}
		if(val == DOOR_OPEN)
		{
			if(OLD_VALUE != val)
			{
				m_sensor.activateQueue();
				std::cout << " ... Opening door ... \n";
				init_motor_and_open();
			}
			// update rtc value
			rtc_noinit_pwm_data = 13;
		}
		OLD_VALUE = val;
	}

	do
	{
		Timeservice::wait_ms(50);
	} while(m_sensor.isRunning());
	return GE_OK;
}

void test_sleep_and_everything()
{
	mqtt_api_v2 mqtt;
	MQTT_Message msg{{db_id::DOGFEEDER_ERROR_CODE, 1}};
	switch(esp_sleep_get_wakeup_cause())
	{
		case ESP_SLEEP_WAKEUP_TIMER: {
			std::cout << "woke up from deep sleep ... @time : <" << (int)Timeservice::getTimeNow()
					  << "\n";
			ErrorCodeParser::postToMqtt(db_id::DOGFEEDER_ERROR_CODE, GE_OK,
										"Just woke up running sequence");
			Timeservice::wait_sec(5);
			auto err = run_everything();
			if(err != GE_OK)
			{
				std::cout << "something went wrong ... <" << General_Error::errorToString(err)
						  << ">\n";
			}
			break;
		}
		case ESP_SLEEP_WAKEUP_UNDEFINED:
		default: {
			printf("Not a deep sleep reset\n");

			ErrorCodeParser::postToMqtt(db_id::DOGFEEDER_ERROR_CODE, GE_NO_DATA,
										"Just rebooted no data available");
			Timeservice::wait_sec(5);
		}
	}
	const int wakeup_time_sec = 30 * 60;
	//	const int wakeup_time_sec = 60;
	std::cout << " enabling timer wake-up from deep sleep, sleeping for  <" << wakeup_time_sec
			  << "> sec \n";
	esp_sleep_enable_timer_wakeup(wakeup_time_sec * 1000000);

	esp_deep_sleep_start();
}

#ifdef __cplusplus
extern "C" {
#endif
void app_main(void);
// Your prototype or Definition
#ifdef __cplusplus
}
#endif

void app_main(void)
{
	static Maintainer m_maintain{wifi_conf};
	m_maintain.start();

	// simple_connect();
	// test_door();
	// test_door_init_open();
	// test_door_init_open_deepSleep();
	// test_get_door_status();
	// test_get_door_status_http_semaphore_test();
	// test_get_json();
	// test_get_jsmn();
	// test_jsmn_and_door();
	// test_activeCurrentSensor();
	// test_everything_connected();
	// test_sleep();
	test_sleep_and_everything();
	for(;;)
	{
		std::cout << "Running a test ! \n ";

		Timeservice::wait_sec(5);
	}
}
