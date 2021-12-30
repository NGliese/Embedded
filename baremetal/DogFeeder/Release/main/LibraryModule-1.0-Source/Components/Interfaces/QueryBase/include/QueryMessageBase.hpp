/*
 * QueryMessageBase.hpp
 *
 *  Created on: Sep 6, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_QUERYMESSAGEBASE_HPP_
#define INCLUDE_QUERYMESSAGEBASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  QueryMessageBase.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, QueryMessageBase.hpp, is designed as:
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
#include "../../../Objects/Timeservice/include/Timeservice.hpp"

#include <vector>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
template<typename T>
class QueryMessageBase
{
  public:
	struct msg_data_t
	{
		uint64_t time_stamp;
		T data;
	};
	QueryMessageBase(const uint32_t enitity_id) : m_entity_id{enitity_id} {};
	QueryMessageBase(const uint32_t enitity_id, const msg_data_t& data)
		: m_entity_id{enitity_id}, m_buffer{data} {};

	virtual ~QueryMessageBase(){};
	//@brief add data with automatically timestamp handling
	virtual inline void addData(const T& data)
	{
		m_buffer.push_back({Timeservice::getTimeNow(), data});
	}
	//@brief add data with timestamp
	virtual inline void addData(const msg_data_t& data)
	{
		m_buffer.push_back(data);
	}
	//@brief get internal buffer
	inline auto& getBuffer(void) const
	{
		return m_buffer;
	};
	//@brief get id of message
	inline auto& getId(void) const
	{
		return m_entity_id;
	};
	//@breif check if the buffer is empty
	inline bool isEmpty(void) const
	{
		return m_buffer.size() == 0 ? true : false;
	};

  private:
	uint32_t m_entity_id;

  protected:
	std::vector<msg_data_t> m_buffer;
};

#endif /* INCLUDE_QUERYMESSAGEBASE_HPP_ */
