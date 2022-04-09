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
 *  @file       i2c.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-02-22
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/i2c.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "i2c";
#endif
i2c::i2c(const i2c_conf_t& conf) : m_conf{conf}
{
#ifdef __ESP32__
	i2c_config_t esp32_i2c_conf;
	esp32_i2c_conf.mode = I2C_MODE_MASTER;
	esp32_i2c_conf.sda_io_num = m_conf.pin_sda;
	esp32_i2c_conf.scl_io_num = m_conf.pin_sclk;
	esp32_i2c_conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
	esp32_i2c_conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
	esp32_i2c_conf.master.clk_speed = m_conf.speed;
	esp32_i2c_conf.clk_flags = 0;
	esp_err_t errRc = ::i2c_param_config(I2C_NUM_0, &esp32_i2c_conf);
	if(errRc != ESP_OK)
	{
		return;
	}

	errRc = ::i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
	if(errRc != ESP_OK)
	{
		return;
	}
#endif
}

general_err_t i2c::writeWord(const uint16_t& word)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c::writeWord >> ");
#endif
	// Executable code:

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c::writeWord << ");
#endif

	return GE_OK;
}
general_err_t i2c::writeByte(const uint8_t& byte)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c::writeByte >> ");
#endif
	// Executable code:

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c::writeByte << ");
#endif

	return GE_OK;
}

void i2c::scan()
{
#ifdef __UNITTEST__
	return;
#endif

	printf("Data Pin: %d, Clock Pin: %d\n", m_conf.pin_sda, m_conf.pin_sclk);
	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
	printf("00:         ");
	for(uint8_t i = 0; i < 0x78; i++)
	{
		if(i % 16 == 0)
		{
			printf("\n%.2x:", i);
		}
		if(slavePresent(i))
		{
			printf(" %.2x", i);
		}
		else
		{
			printf(" --");
		}
	}
	printf("\n");
}

bool i2c::slavePresent(uint8_t address)
{
#ifdef __ESP32__
	i2c_cmd_handle_t cmd = ::i2c_cmd_link_create();
	::i2c_master_start(cmd);
	::i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
	::i2c_master_stop(cmd);

	esp_err_t espRc = ::i2c_master_cmd_begin(I2C_NUM_0, cmd, 100 / portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
	return espRc == 0; // Return true if the slave is present and false otherwise.
#else
	return 1;
#endif
}
