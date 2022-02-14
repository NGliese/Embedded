/*
 * Message_Handler.hpp
 *
 *  Created on: Aug 25, 2020
 *      Author: Nikolaj
 */

#ifndef COMPONENTS_DATA_PACKAGE_INCLUDE_MESSAGE_HANDLER_HPP_
#define COMPONENTS_DATA_PACKAGE_INCLUDE_MESSAGE_HANDLER_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Message_Handler.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Message_Handler.hpp, is designed as:
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
 |  	Link:[ ], Aug 25, 2020
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Aug 25, 2020
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

#include "Message_Protocol.hpp"
#include <iostream>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Message_Handler
{
  public:
	static general_err_t to_Postgres_Format(const Message_Protocol& msg, std::string* str);
	static const std::string to_Postgres_Form(const Message_Protocol& msg);

	static inline std::string postgres_start(void)
	{
		return "INSERT INTO MEASUREMENTS (tstz,sensor_id,value) VALUES ";
	};

	static const std::string to_Postgres_Subject(const Message_Protocol& msg);
	static inline std::string postgres_append(void)
	{
		return ",";
	};
	static inline std::string postgres_end(void)
	{
		return ";";
	};

  private:
};

#endif /* COMPONENTS_DATA_PACKAGE_INCLUDE_MESSAGE_HANDLER_HPP_ */
