/*
 * Curl_SAL.hpp
 *
 *  Created on: Aug 25, 2020
 *      Author: espenv
 */

#ifndef COMPONENTS_DATA_PROTOCOL_INCLUDE_CURL_SAL_HPP_
#define COMPONENTS_DATA_PROTOCOL_INCLUDE_CURL_SAL_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Curl_SAL.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Curl_SAL.hpp, is designed as:
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


#ifdef __RPI__
#include <curl/curl.h>
#endif


#include <iostream>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/



class Curl_SAL{
public:
        Curl_SAL(const std::string& server);
        ~Curl_SAL();
        general_err_t initialize(void);
        general_err_t rpi_open(void);
        general_err_t rpi_close(void);
        general_err_t rpi_publish(const std::string & str);

private:
#ifdef __RPI__
        CURL *m_curl;
#endif
    
        const std::string m_server;
};



#endif /* COMPONENTS_DATA_PROTOCOL_INCLUDE_CURL_SAL_HPP_ */
