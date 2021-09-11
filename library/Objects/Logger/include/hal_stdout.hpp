/*
 * hal_stdout.hpp
 *
 *  Created on: Jun 14, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_HAL_STDOUT_HPP_
#define INCLUDE_HAL_STDOUT_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  hal_stdout.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, hal_stdout.hpp, is designed as:
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
 |  	Link:[ ], Jun 14, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jun 14, 2021
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
#include <iostream>
/*-----------------------------------------------------------------------------*/






/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class hal_stdout {
#ifdef __UNITTEST__
    friend class friend_hal_stdout;
#endif
public:
    static void write(const std::string& str) { std::cout << str << "\n"; }
private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_hal_stdout {
public:
    friend_hal_stdout(){};
    friend_hal_stdout(hal_stdout * hal_stdout) : m_sensor{hal_stdout} { };

    ~friend_hal_stdout(){};

private:
    hal_stdout * m_sensor;
};
#endif




#endif /* INCLUDE_HAL_STDOUT_HPP_ */
