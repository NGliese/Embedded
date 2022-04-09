#ifndef _COMPONENTS_PROTOCOLS_I2C_TEST_MOCK_I2C_MOCK_HPP_
#define _COMPONENTS_PROTOCOLS_I2C_TEST_MOCK_I2C_MOCK_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  i2c_mock.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-04-07
 |
 |  @brief  	   :  This class, i2c_mock.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  @version       : 1.0
 |
 |  @bug  		   :   no known bugs
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../../Global_Include/BASIC.hpp"
#include "../../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

#include "../../include/i2c_common.hpp"

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class i2c_mock
{
#ifdef __UNITTEST__
	friend class friend_i2c_mock;
#endif
  public:
	i2c_mock(const i2c_conf_t& conf){};
	~i2c_mock(){};
	bool slavePresent(uint8_t address)
	{
		hasBeenCalledAmount_slavePresent++;
		return true;
	};

	general_err_t writeByte(const uint8_t& slave_address, const uint8_t& byte)
	{
		hasBeenCalledAmount_writeByte++;
		return GE_OK;
	};
	general_err_t writeWord(const uint8_t& slave_address, const uint16_t& word)
	{
		hasBeenCalledAmount_writeWord++;
		return GE_OK;
	};
	uint8_t readByte(const uint8_t& slave_address)
	{
		hasBeenCalledAmount_readByte++;
		return 0xfa;
	}
	uint16_t readWord(const uint8_t& slave_address)
	{
		hasBeenCalledAmount_readWord++;
		return 0xfafa;
	}
	void reset()
	{
		hasBeenCalledAmount_slavePresent = 0;
		hasBeenCalledAmount_writeByte = 0;
		hasBeenCalledAmount_writeWord = 0;
		hasBeenCalledAmount_readByte = 0;
		hasBeenCalledAmount_readWord = 0;
	}

	int hasBeenCalledAmount_slavePresent = 0;
	int hasBeenCalledAmount_writeByte = 0;
	int hasBeenCalledAmount_writeWord = 0;
	int hasBeenCalledAmount_readByte = 0;
	int hasBeenCalledAmount_readWord = 0;

  private:
	general_err_t initialize_transaction()
	{
		return GE_OK;
	};
	general_err_t execute_transaction()
	{
		return GE_OK;
	};
	general_err_t insert_start_bit()
	{
		return GE_OK;
	};
	general_err_t insert_stop_bit()
	{
		return GE_OK;
	};
};

#endif //_COMPONENTS_PROTOCOLS_I2C_TEST_MOCK_I2C_MOCK_HPP_