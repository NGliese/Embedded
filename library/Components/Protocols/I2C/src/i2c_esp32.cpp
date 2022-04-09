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
 *  @file       i2c_esp32.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-04-07
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/i2c_esp32.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "i2c_esp32";
#endif

i2c_esp32::i2c_esp32(const i2c_conf_t& conf)
{
#ifdef __ESP32__
	i2c_config_t esp32_i2c_conf;
	esp32_i2c_conf.mode = I2C_MODE_MASTER;
	esp32_i2c_conf.sda_io_num = conf.pin_sda;
	esp32_i2c_conf.scl_io_num = conf.pin_sclk;
	esp32_i2c_conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
	esp32_i2c_conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
	esp32_i2c_conf.master.clk_speed = conf.speed;
	esp32_i2c_conf.clk_flags = 0;
	esp_err_t errRc = ::i2c_param_config(m_portNum, &esp32_i2c_conf);
	if(errRc != ESP_OK)
	{
		return;
	}

	errRc = ::i2c_driver_install(m_portNum, esp32_i2c_conf.mode, 0, 0, 0);
	if(errRc != ESP_OK)
	{
		return;
	}
#endif
}
i2c_esp32::~i2c_esp32() {}

bool i2c_esp32::slavePresent(uint8_t address)
{
#ifdef __ESP32__
	i2c_cmd_handle_t cmd = ::i2c_cmd_link_create();
	::i2c_master_start(cmd);
	::i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
	::i2c_master_stop(cmd);

	esp_err_t espRc = ::i2c_master_cmd_begin(m_portNum, cmd, 100 / portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
	return espRc == 0; // Return true if the slave is present and false otherwise.
#else
	return true;
#endif
}

general_err_t i2c_esp32::writeByte(const uint8_t& slave_address, const uint8_t& byte)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c::writeByte >> ");
#endif
	// Executable code:
	auto err = initialize_transaction();
	if(err != GE_OK)
	{
		return err;
	}

	insert_start_bit();
	insert_write_byte(slave_address, byte);
	insert_stop_bit();

	err = execute_transaction();
	if(err != GE_OK)
	{
		return err;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c::writeByte << ");
#endif

	return GE_OK;
}
const uint8_t i2c_esp32::readByte(const uint8_t& slave_address)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::readByte >> ");
#endif
	// Executable code:
	uint8_t byte_to_read = 0x00;
	auto err = initialize_transaction();
	if(err != GE_OK)
	{
		return byte_to_read;
	}

	insert_start_bit();
	insert_read_byte(slave_address, &byte_to_read);
	insert_stop_bit();

	err = execute_transaction();
	if(err != GE_OK)
	{
		return byte_to_read;
	}
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::readByte << ");
#endif

	return byte_to_read;
}
general_err_t i2c_esp32::writeWord(const uint8_t& slave_address, const uint16_t& word)
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
const uint16_t i2c_esp32::readWord(const uint8_t& slave_address)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::readWord >> ");
#endif
	// Executable code:

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::readWord << ");
#endif

	return GE_OK;
}

general_err_t i2c_esp32::initialize_transaction()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::initialize_transaction >> ");
#endif
	// Executable code:

#ifdef __ESP32__
	m_cmd = ::i2c_cmd_link_create();
	esp_err_t errRc = ::i2c_master_start(m_cmd);
	if(errRc != ESP_OK)
	{
		return GE_PROTOCOL_FAILED;
	}
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::initialize_transaction << ");
#endif

	return GE_OK;
}
general_err_t i2c_esp32::insert_start_bit()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::insert_start_bit >> ");
#endif
	// Executable code:
#ifdef __ESP32__
	esp_err_t errRc = ::i2c_master_start(m_cmd);
	if(errRc != ESP_OK)
	{
		return GE_PROTOCOL_FAILED;
	}
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::insert_start_bit << ");
#endif

	return GE_OK;
}

general_err_t i2c_esp32::insert_write_byte(const uint8_t& slave_address, const uint8_t& byte)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::insert_write_byte >> ");
#endif
	// Executable code:

#ifdef __ESP32__
	esp_err_t errRc =
		::i2c_master_write_byte(m_cmd, (slave_address << 1) | I2C_MASTER_WRITE, false);
	if(errRc != ESP_OK)
	{
		return GE_FAIL;
	}
	errRc = ::i2c_master_write_byte(m_cmd, byte, false);
	if(errRc != ESP_OK)
	{
		return GE_FAIL;
	}
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::insert_write_byte << ");
#endif

	return GE_OK;
}
general_err_t i2c_esp32::insert_read_byte(const uint8_t& slave_address, uint8_t* byte)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::insert_read_byte >> ");
#endif
	// Executable code:
#ifdef __ESP32__

	esp_err_t errRc = ::i2c_master_write_byte(m_cmd, (slave_address << 1) | I2C_MASTER_READ, false);
	if(errRc != ESP_OK)
	{
		return GE_PROTOCOL_FAILED;
	}
	ESP_ERROR_CHECK(::i2c_master_read_byte(m_cmd, byte, I2C_MASTER_ACK));
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::insert_read_byte << ");
#endif

	return GE_OK;
}

general_err_t i2c_esp32::insert_stop_bit()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::insert_stop_bit >> ");
#endif
	// Executable code:
#ifdef __ESP32__
	esp_err_t errRc = ::i2c_master_stop(m_cmd);
	if(errRc != ESP_OK)
	{
		return GE_PROTOCOL_FAILED;
	}
#endif
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::insert_stop_bit << ");
#endif

	return GE_OK;
}
general_err_t i2c_esp32::execute_transaction()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> i2c_esp32::execute_transaction >> ");
#endif
	// Executable code:

#ifdef __ESP32__
	esp_err_t errRc = ::i2c_master_cmd_begin(m_portNum, m_cmd, 1000 / portTICK_PERIOD_MS);
	::i2c_cmd_link_delete(m_cmd);

	if(errRc != ESP_OK)
	{
		return GE_PROTOCOL_FAILED;
	}
#endif

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  i2c_esp32::execute_transaction << ");
#endif

	return GE_OK;
}