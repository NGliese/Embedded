/*
 * TEMPLATE.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: espenv
 */
//#include "../../../SSP/main/components/Sensor_Handler/include/Sensor_Dummy_Handler.hpp"

#include "../../include/QueryAddExternalResources.hpp"
#include "../../include/QueryAddSensorData.hpp"
#include <iostream>

#include "../../include/QueryMessage.hpp"
#include "CppUTest/TestHarness.h"

TEST_GROUP(Query_GRP)
{
	QueryAddSensorData m_query;
	QueryAddExternalResources m_query2;
	void setup() {}
	void teardown()
	{
		// Uninit stuff
	}
};

// test init
TEST(Query_GRP, test_start)
{
	STRCMP_EQUAL("INSERT INTO public.datapoints (tstz,entity_id,value) VALUES ",
				 m_query.start().c_str());
}
TEST(Query_GRP, test_content_empty)
{
	QueryDataMessage msg{101};
	STRCMP_EQUAL("", m_query.content(msg).c_str());
}

TEST(Query_GRP, test_content)
{
	QueryDataMessage msg{101};
	msg.addData(10.2);
	// STRCMP_EQUAL("",m_query.content(msg).c_str());
}
TEST(Query_GRP, test_content4)
{
	QueryDataMessage msg{101};
	msg.addData(10.2);
	STRCMP_EQUAL("('1970-01-01T00:00:10.2000Z',101,21.000000)",
				 m_query.content(QueryDataMessage{101, {10002, 21.0}}).c_str());
}
TEST(Query_GRP, test_content2)
{
	// std::cout << " time now : " << std::to_string(Timeservice::getTimeNow()) << "\n";
	QueryDataMessage msg{101};
	msg.addData({1630957469104, 10.2});
	STRCMP_EQUAL("('2021-09-06T19:44:29.104000Z',101,10.200000)", m_query.content(msg).c_str());
}
TEST(Query_GRP, test_full)
{
	// std::cout << " time now : " << std::to_string(Timeservice::getTimeNow()) << "\n";
	QueryDataMessage msg{101};
	msg.addData({1630957469104, 10.2});
	std::string full = m_query.start();
	full += m_query.content(msg);
	full += m_query.end();

	STRCMP_EQUAL("INSERT INTO public.datapoints (tstz,entity_id,value) VALUES "
				 "('2021-09-06T19:44:29.104000Z',101,10.200000);",
				 full.c_str());
}

TEST(Query_GRP, test_full_extern_resources)
{
	std::cout << " time now : " << std::to_string(Timeservice::getTimeNow()) << "\n";
	QueryURIMessage msg{101};
	msg.addData({1630957469104, "19219312_visual.png"});
	std::string full = m_query2.start();
	full += m_query2.content(msg);
	full += m_query2.end();

	STRCMP_EQUAL("INSERT INTO public.external_resources(tstz, entity_id, uri) VALUES "
				 "('2021-09-06T19:44:29.104000Z',101,'19219312_visual.png');",
				 full.c_str());
}
