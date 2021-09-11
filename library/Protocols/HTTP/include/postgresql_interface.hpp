/*
 * postgresql_interface.hpp
 *
 *  Created on: Dec 29, 2020
 *      Author: espenv
 */

#ifndef COMPONENTS_DATA_PROTOCOL_INCLUDE_POSTGRESQL_INTERFACE_HPP_
#define COMPONENTS_DATA_PROTOCOL_INCLUDE_POSTGRESQL_INTERFACE_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  postgresql_interface.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, postgresql_interface.hpp, is designed as:
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
 |  	Link:[ ], Dec 29, 2020
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Dec 29, 2020
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

#include <iostream>

#ifdef __RPI__
#include <pqxx/pqxx>
#endif


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class postgresql_interface final : public ProtocolBase{
#ifdef __UNITTEST__
    friend class friend_postgresql_interface;
#endif


public:
    postgresql_interface() = default;
    ~postgresql_interface();
    general_err_t open(void) override;
    general_err_t post(const std::string & str) override;
    general_err_t close(void) override;
private:
    bool m_open = false;
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_postgresql_interface {
public:
    friend_postgresql_interface(){};
    friend_postgresql_interface(postgresql_interface * postgresql_interface) { m_sensor = postgresql_interface;};

    ~friend_postgresql_interface(){};
private:
    postgresql_interface * m_sensor;
};
#endif




#endif /* COMPONENTS_DATA_PROTOCOL_INCLUDE_POSTGRESQL_INTERFACE_HPP_ */
