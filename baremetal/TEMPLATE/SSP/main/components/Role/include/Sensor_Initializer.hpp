/*
 * Sensor_Initializer.hpp
 *
 *  Created on: Mar 5, 2021
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_ROLE_INCLUDE_SENSOR_INITIALIZER_HPP_
#define MAIN_COMPONENTS_ROLE_INCLUDE_SENSOR_INITIALIZER_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Sensor_Initializer.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Sensor_Initializer.hpp, is designed as:
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
 |  	Link:[ ], Mar 5, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Mar 5, 2021
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
#include <BASIC.hpp>
#include <General_Error.hpp>
/*-----------------------------------------------------------------------------*/
#include <FreeRTOS.h>
 
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Sensor_Initializer {
#ifdef __UNITTEST__
    friend class friend_Sensor_Initializer;
#endif
public:
    Sensor_Initializer() ;
    ~Sensor_Initializer();
    general_err_t run(void);
private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Sensor_Initializer {
public:
    friend_Sensor_Initializer(){};
    friend_Sensor_Initializer(Sensor_Initializer * Sensor_Initializer) : m_sensor{Sensor_Initializer} { };

    ~friend_Sensor_Initializer(){};

private:
    Sensor_Initializer * m_sensor;
};
#endif




#endif /* MAIN_COMPONENTS_ROLE_INCLUDE_SENSOR_INITIALIZER_HPP_ */
