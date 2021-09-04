/*
 * ProtocolBase.hpp
 *
 *  Created on: May 14, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_PROTOCOLBASE_HPP_
#define INCLUDE_PROTOCOLBASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  ProtocolBase.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, ProtocolBase.hpp, is designed as:
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
 |  	Link:[ ], May 14, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], May 14, 2021
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






/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class ProtocolBase {
#ifdef __UNITTEST__
    friend class friend_ProtocolBase;
#endif
public:
    ProtocolBase() {};
    virtual ~ProtocolBase() {};
    virtual general_err_t open(void) = 0;
    virtual general_err_t post(const std::string & str) = 0;
    virtual general_err_t close(void) = 0;
private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_ProtocolBase {
public:
    friend_ProtocolBase(){};
    friend_ProtocolBase(ProtocolBase * ProtocolBase) : m_sensor{ProtocolBase} { };

    ~friend_ProtocolBase(){};

private:
    ProtocolBase * m_sensor;
};
#endif






#endif /* INCLUDE_PROTOCOLBASE_HPP_ */
