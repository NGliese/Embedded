/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
#include "../../include/PeriodeEstimator.hpp" // example of include
#include "data.hpp"
#include <iostream>

// ------------- INCLUDE ABOVE ----------------
#include "CppUTest/TestHarness.h"
using states = PeriodeEstimator<100, 10, NVS_MOCK>::states;
// clang-format off
TEST_GROUP(PERI_GRP){

	PeriodeEstimator<100, 10,NVS_MOCK> m_estimator;
	friend_PeriodeEstimator m_friend{&m_estimator};
	void setup(){
		m_friend.setCurrentState(states::UNDEF);
		m_friend.setLastState(states::UNDEF);
	}
	void teardown(){
	// Uninit stuff
	}
};
// clang-format on

// test init
TEST(PERI_GRP, init)
{
	PeriodeEstimator<100, 10, NVS_MOCK> estimator;
	CHECK(states::UNDEF == m_friend.getCurrentState());
}
// fails due to static assert ( expected )
/*
// test init
TEST(PERI_GRP, init_bad)
{
	PeriodeEstimator<10, 100> m_estimator;
}
*/

// test init
TEST(PERI_GRP, dontchangeFromInitState)
{
	states new_state = states::LOW;
	m_friend.setInitialState(new_state);
	CHECK(states::UNDEF == m_friend.getCurrentState());
}
// test init
TEST(PERI_GRP, changeFromInitState)
{
	states new_state = states::HIGH;
	m_friend.setInitialState(new_state);
	CHECK(states::HIGH == m_friend.getCurrentState());
	CHECK(states::MIDDLE == m_friend.getLastState());
	LONGS_EQUAL(491327, m_estimator.getPeriodCounter());
}
// test init
TEST(PERI_GRP, setNextState)
{
	m_friend.setInitialState(states::HIGH);

	m_friend.setNextState(states::MIDDLE);
	CHECK(states::MIDDLE == m_friend.getCurrentState());
	CHECK(states::HIGH == m_friend.getLastState());
	LONGS_EQUAL(491327, m_estimator.getPeriodCounter());
}
// test init
TEST(PERI_GRP, setNextNextState)
{
	m_friend.setInitialState(states::HIGH);

	m_friend.setNextState(states::MIDDLE);
	m_friend.setNextState(states::LOW);
	CHECK(states::LOW == m_friend.getCurrentState());
	CHECK(states::MIDDLE == m_friend.getLastState());
	LONGS_EQUAL(491327, m_estimator.getPeriodCounter());
}
// test init
TEST(PERI_GRP, setNextState_FULLPERIODE)
{
	m_friend.setInitialState(states::HIGH);

	m_friend.setNextState(states::MIDDLE);
	m_friend.setNextState(states::LOW);
	m_friend.setNextState(states::MIDDLE);
	m_friend.setNextState(states::HIGH);
	CHECK(states::HIGH == m_friend.getCurrentState());
	CHECK(states::MIDDLE == m_friend.getLastState());
	LONGS_EQUAL(491328, m_estimator.getPeriodCounter());
}
/*
// test init
TEST(PERI_GRP, addData_more)
{
	std::vector<general_err_t> arr{GE_OK,	   GE_NO_DATA, GE_OK,	   GE_NO_DATA, GE_NO_DATA,
								   GE_NO_DATA, GE_OK,	   GE_NO_DATA, GE_NO_DATA, GE_OK};

	for(size_t i = 0; i < 10; i++)
	{
		auto val = vec.at(i);
		auto err = arr.at(i);

		auto res = m_estimator.addData(val);
		std::cout << " i is : " << i << " value is : " << val.second << "\n";
		CHECK_EQUAL(err, res);
	}
}

// test init
TEST(PERI_GRP, addData_all)
{
	size_t count = 0;
	for(auto& ele : vec)
	{
		auto res = m_estimator.addData(ele);
		if(res == GE_OK)
		{
			count++;
		}
	}
	LONGS_EQUAL(45, count);
}

// test init
TEST(PERI_GRP, calculate_period_counter)
{
	size_t count = 0;
	for(auto& ele : vec)
	{
		auto res = m_estimator.addData(ele);
		if(res == GE_OK)
		{
			count++;
		}
	}
	LONGS_EQUAL(m_estimator.getPeriodCounter(), count / 6);
}
*/