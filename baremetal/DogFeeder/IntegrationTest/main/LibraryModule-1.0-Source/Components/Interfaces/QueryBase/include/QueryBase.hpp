/*
 * QueryBase.hpp
 *
 *  Created on: Sep 6, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_QUERYBASE_HPP_
#define INCLUDE_QUERYBASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  QueryBase.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, QueryBase.hpp, is designed as:
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

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
template<typename T>
class QueryBase
{
#ifdef __UNITTEST__
	friend class friend_QueryBase;
#endif
  public:
	virtual std::string start(void) = 0;
	virtual std::string content(const T& msg) = 0;
	virtual std::string append(void)
	{
		return ",";
	};
	virtual std::string end(void)
	{
		return ";";
	};

  private:
};

#endif /* INCLUDE_QUERYBASE_HPP_ */
