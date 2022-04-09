/*
 * QueryAddExternalResources.hpp
 *
 *  Created on: Sep 6, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_QUERYADDEXTERNALRESOURCES_HPP_
#define INCLUDE_QUERYADDEXTERNALRESOURCES_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  QueryAddExternalResources.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, QueryAddExternalResources.hpp, is designed as:
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
 |   		 					Datasheet Awareness              		        |
 +------------------------------------------------------------------------------+
 |
 |
 |  Datasheet Awareness 1):
 |  	Link:[ ], Sep 6, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Sep 6, 2021
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |                              Includes                                        |
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

class QueryAddExternalResources final : public QueryBase<QueryURIMessage>
{
#ifdef __UNITTEST__
	friend class friend_QueryAddExternalResources;
#endif
  public:
	QueryAddExternalResources() = default;
	~QueryAddExternalResources(){};
	std::string start(void) override
	{
		return "INSERT INTO public.external_resources(tstz, entity_id, uri) VALUES ";
	};
	std::string content(const QueryURIMessage& msg) override;

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_QueryAddExternalResources
{
  public:
	friend_QueryAddExternalResources(QueryAddExternalResources* QueryAddExternalResources)
		: m_sensor{QueryAddExternalResources} {};

	~friend_QueryAddExternalResources(){};

  private:
	QueryAddExternalResources* m_sensor;
};
#endif

#endif /* INCLUDE_QUERYADDEXTERNALRESOURCES_HPP_ */
