#ifndef _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_HPP_
#define _COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  i2c.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-02-22
 |
 |  @brief  	   :  This class, i2c.hpp, is designed as:
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
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include <array>
#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/
#ifdef __ESP32__
#include <driver/gpio.h>
#include <driver/i2c.h>
#endif

struct i2c_conf_t
{
	uint32_t speed; // 100k Hz default
	GPIO_PIN pin_sda; // gpio pin for sda
	GPIO_PIN pin_sclk; // pgio pin for clk
};
/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class i2c
{
#ifdef __UNITTEST__
	friend class friend_i2c;
#endif
  public:
	/**
	 * @brief Get the Instance object
	 * 	TODO Make sure that users can re-install with new config file
	 * 		 Currently we can pnly install it once
	 * @param conf
	 * @return i2c&
	 */
	static i2c& getInstance(const i2c_conf_t& conf)
	{
		static i2c ref_to_i2c{conf};
		return ref_to_i2c;
	}
	~i2c(){};
	general_err_t writeByte(const uint8_t& byte);
	//  general_err_t writeBytes(const std::array& array); // should be an array
	general_err_t writeWord(const uint16_t& word);
	void scan();

  private:
	bool slavePresent(uint8_t address);
	i2c(const i2c_conf_t& conf);
	i2c_conf_t m_conf;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_i2c
{
  public:
	explicit friend_i2c(i2c* sensor) : m_sensor{sensor} {};
	~friend_i2c();

  private:
	i2c* m_sensor;
};
#endif

#endif //_COMPONENTS_PROTOCOLS_I2C_INCLUDE_I2C_HPP_