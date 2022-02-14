/*
 * QueryAddData.hpp
 *
 *  Created on: Sep 6, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_QUERYADDSENSORDATA_HPP_
#define INCLUDE_QUERYADDSENSORDATA_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  QueryAddData.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, QueryAddData.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include "../../../Interfaces/QueryBase/include/QueryBase.hpp"
#include "QueryMessage.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class QueryAddSensorData final : public QueryBase<QueryDataMessage>
{
#ifdef __UNITTEST__
	friend class friend_QueryAddData;
#endif
  public:
	QueryAddSensorData() = default;
	~QueryAddSensorData(){};
	std::string start(void) override
	{
		return "INSERT INTO public.datapoints (tstz,entity_id,value) VALUES ";
	};
	std::string content(const QueryDataMessage& msg) override;

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_QueryAddData
{
  public:
	friend_QueryAddData(QueryAddSensorData* QueryAddSensorData) : m_sensor{QueryAddSensorData} {};

	~friend_QueryAddData(){};

  private:
	QueryAddSensorData* m_sensor;
};
#endif

#endif /* INCLUDE_QUERYADDSENSORDATA_HPP_ */
