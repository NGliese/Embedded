/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include "../../include/MG996R.hpp"
#include "CppUTest/TestHarness.h"
#include <iostream>

TEST_GROUP(SERVO_GRP)
{
#if 0 // Equivalence
        mg996r_conf_t conf = {"test",{1,10.0,1000,2,3}};
        conf.name = "test1";
        conf.conf.channel=1;
        conf.conf.duty=10.0;
        conf.conf.frequency = 1000;
        conf.conf.m_pin = 2;
        conf.conf.mode = 3;
        conf.conf = {1,10.0,1000,2,3};
#endif
	MG996R m_servo{{"test", {1, 10.0, 1000, 2, 3}}};
	friend_MG996R m_friend{&m_servo};

	void setup() {}
	void teardown()
	{
		// Uninit stuff
		m_friend.setPoint(0);
	}
};

// test init
TEST(SERVO_GRP, init_val)
{
	DOUBLES_EQUAL(m_servo.getValue(), 0, 1);
}
// test init
TEST(SERVO_GRP, set_setval)
{
	m_friend.setPoint(10.1);
	DOUBLES_EQUAL(m_friend.getSetPoint(), 10.1, 3);
}

// test init
TEST(SERVO_GRP, set_setval_upper)
{
	m_friend.setPoint(100.1);
	DOUBLES_EQUAL(m_friend.getSetPoint(), 13, 3);
}
// test init
TEST(SERVO_GRP, set_setval_lower)
{
	m_friend.setPoint(-100.1);
	DOUBLES_EQUAL(m_friend.getSetPoint(), 2.5F, 3);
}

// test init
TEST(SERVO_GRP, actuate_error_TOO_HIGH)
{
	CHECK_EQUAL(GE_UPPER_BOUNDERY, m_servo.execute(15));
}

// test init
TEST(SERVO_GRP, actuat_max)
{
	m_servo.setToMaximum();

	// DOUBLES_EQUAL(m_servo.getValue(),14,1);
	CHECK(m_servo.getValue() == 13);
}
// test init
TEST(SERVO_GRP, actuat_min)
{
	m_servo.setToMinimum();
	CHECK(m_servo.getValue() == 2.5);
}

// test init
TEST(SERVO_GRP, OpenSlowly_1_run)
{
	m_servo.setToMinimum(); // is minimum now

	general_err_t err = GE_OK;
	float tick = m_servo.getValue() + 1.0;
	DOUBLES_EQUAL(tick, 3.5, 2);
	m_servo.execute(tick);
	DOUBLES_EQUAL(m_servo.getValue(), 3.5, 2);
}
// test init
TEST(SERVO_GRP, OpenSlowly_loop_run)
{
	m_servo.setToMinimum(); // is minimum now

	general_err_t err = GE_OK;
	do
	{
		float tick = m_servo.getValue() + 1.0;
		err = m_friend.setPoint(tick);
		if(err == GE_NO_DATA)
		{
			FAIL("Somethings wrong");
		}
		err = m_friend.actuate();
		DOUBLES_EQUAL(m_servo.getValue(), tick, 2);
		std::cout << "servo motor is : " << m_servo.getValue() << "\n";
		CHECK_EQUAL(GE_OK, err);

	} while(m_servo.getValue() < 13 && err == GE_OK);
	std::cout << "servo motor FINISHED is : " << m_servo.getValue() << "\n";
	DOUBLES_EQUAL(m_servo.getValue(), 13, 2);
}

TEST(SERVO_GRP, Closelowly_loop_run)
{
	m_servo.setToMaximum(); // is minimum now

	general_err_t err = GE_OK;
	do
	{
		float tick = m_servo.getValue() - 1.0;
		err = m_friend.setPoint(tick);
		if(err == GE_NO_DATA)
		{
			FAIL("Somethings wrong");
		}
		err = m_friend.actuate();
		DOUBLES_EQUAL(m_servo.getValue(), tick, 2);
		std::cout << "servo motor is : " << m_servo.getValue() << "\n";
		CHECK_EQUAL(GE_OK, err);

	} while(m_servo.getValue() > 2.5 && err == GE_OK);
	std::cout << "servo motor FINISHED is : " << m_servo.getValue() << "\n";
	DOUBLES_EQUAL(m_servo.getValue(), 2.5, 2);
}