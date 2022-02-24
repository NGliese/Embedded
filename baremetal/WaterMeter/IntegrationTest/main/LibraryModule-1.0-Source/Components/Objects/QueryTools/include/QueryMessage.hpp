/*
 * QueryMessage.hpp
 *
 *  Created on: Sep 6, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_QUERYMESSAGE_HPP_
#define INCLUDE_QUERYMESSAGE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  QueryDataMessage.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, QueryDataMessage.hpp, is designed as:
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

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include "../../../Interfaces/QueryBase/include/QueryMessageBase.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class QueryDataMessage final : public QueryMessageBase<float>
{
#ifdef __UNITTEST__
	friend class friend_QueryDataMessage;
#endif
  public:
	QueryDataMessage(const uint32_t enitity_id) : QueryMessageBase(enitity_id){};
	QueryDataMessage(const uint32_t enitity_id, const msg_data_t& data)
		: QueryMessageBase(enitity_id, data){};
	~QueryDataMessage(){};

  private:
};

/*------------------------------------------------------------------------------+
 |                               Class                                          |
 +------------------------------------------------------------------------------*/

class QueryURIMessage final : public QueryMessageBase<std::string>
{
#ifdef __UNITTEST__
	friend class friend_QueryDataMessage;
#endif
  public:
	QueryURIMessage(const uint32_t enitity_id) : QueryMessageBase(enitity_id){};
	QueryURIMessage(const uint32_t enitity_id, const msg_data_t& data)
		: QueryMessageBase(enitity_id, data){};
	~QueryURIMessage(){};

  private:
};

#endif /* INCLUDE_QUERYMESSAGE_HPP_ */
