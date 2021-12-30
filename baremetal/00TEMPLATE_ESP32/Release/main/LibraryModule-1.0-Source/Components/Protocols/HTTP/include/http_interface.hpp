/*
 * http_interface.hpp
 *
 *  Created on: Aug 25, 2020
 *      Author: espenv
 */

#ifndef COMPONENTS_DATA_PROTOCOL_INCLUDE_HTTP_INTERFACE_HPP_
#define COMPONENTS_DATA_PROTOCOL_INCLUDE_HTTP_INTERFACE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  http_interface.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, http_interface.hpp, is designed as:
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
#include "../../../Interfaces/ProtocolBase/include/ProtocolBase.hpp"

#include "Curl_SAL.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class http_interface final : public ProtocolBase
{
  public:
	explicit http_interface(const std::string& server);
	~http_interface();
	general_err_t initialize(void);
	general_err_t open(void) override;
	general_err_t close(void) override;
	general_err_t post(const std::string& str) override;

  private:
	bool m_initialized = false;
	bool m_open = false;
	Curl_SAL m_sal;
};

#endif /* COMPONENTS_DATA_PROTOCOL_INCLUDE_HTTP_INTERFACE_HPP_ */
