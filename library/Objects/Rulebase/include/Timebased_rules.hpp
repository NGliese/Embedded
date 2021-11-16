/*
 * Timebased_rules.hpp
 *
 *  Created on: Nov 16, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_TIMEBASED_RULES_HPP_
#define INCLUDE_TIMEBASED_RULES_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Timebased_rules.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Timebased_rules.hpp, is designed as:
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
 |  	Link:[ ], Nov 16, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Nov 16, 2021
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





/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Timebased_rules {
#ifdef __UNITTEST__
    friend class friend_Timebased_rules;
#endif
public:
    /**
     * Function to decide if it is night or not
     * Nighttime is defined as 20:00 to 05:00
     */
    static bool isItNight(void);
private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Timebased_rules {
public:
    friend_Timebased_rules(){};
    friend_Timebased_rules(Timebased_rules * Timebased_rules) : m_sensor{Timebased_rules} { };

    ~friend_Timebased_rules(){};

private:
    Timebased_rules * m_sensor;
};
#endif





#endif /* INCLUDE_TIMEBASED_RULES_HPP_ */
