/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
// #include "../../include/esp32Cam.hpp" // example of include
#include <iostream>

#include "../../include/i2c.hpp"
#include "../mock/i2c_mock.hpp"

i2c_conf_t conf{50000, 5, 10};

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"

constexpr uint8_t SLAVE_ID = 0x53;

// clang-format off
TEST_GROUP(I2C_GRP){

	i2c<i2c_mock> m_i2c = i2c<i2c_mock>::getInstance(conf);
	friend_i2c m_friend{&m_i2c};

	void setup(){

	}
	void teardown(){
	// Uninit stuff
	m_friend.getHAL().reset();
	}
};
// clang-format on

// test init
TEST(I2C_GRP, init)
{
	i2c<i2c_mock> n_i2c = i2c<i2c_mock>::getInstance(conf);
	CHECK(true);
}

// test init
TEST(I2C_GRP, scan_all)
{
	m_i2c.scan();
	LONGS_EQUAL(120, m_friend.getHAL().hasBeenCalledAmount_slavePresent);
}
// test init
TEST(I2C_GRP, check_slave)
{
	m_i2c.slavePresent(SLAVE_ID);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_slavePresent);
}

// test init
TEST(I2C_GRP, write_a_byte)
{
	m_i2c.writeByte(SLAVE_ID, 0xff);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_writeByte);
}
// test init
TEST(I2C_GRP, write_a_word)
{
	m_i2c.writeWord(SLAVE_ID, 0xffaa);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_writeWord);
}

// test init
TEST(I2C_GRP, read_a_byte)
{
	m_i2c.readByte(SLAVE_ID);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_readByte);
}
// test init
TEST(I2C_GRP, read_a_word)
{
	m_i2c.readWord(SLAVE_ID);
	LONGS_EQUAL(1, m_friend.getHAL().hasBeenCalledAmount_readWord);
}