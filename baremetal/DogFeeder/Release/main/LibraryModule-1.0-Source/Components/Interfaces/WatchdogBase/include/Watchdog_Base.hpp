/*
 * Watchdog_Base.hpp
 *
 *  Created on: Aug 27, 2020
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_WATCHDOG_INCLUDE_WATCHDOG_BASE_HPP_
#define MAIN_COMPONENTS_WATCHDOG_INCLUDE_WATCHDOG_BASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Watchdog_Base.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Watchdog_Base.hpp, is designed as:
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
 |  	Link:[ ], Aug 27, 2020
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Aug 27, 2020
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

enum watchdog_event_t{
    OK_EVENT=0,SEND_EVENT,NO_EVENT,FAIL_EVENT
};

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


template<typename T>
class Watchdog_Base {
public:
        Watchdog_Base(){};
        virtual ~Watchdog_Base(){};
        virtual general_err_t initialize(T parameter_to_watch)=0;
        virtual watchdog_event_t watch()=0;//{return watchdog_event_t::NO_EVENT; };
protected:
        T m_watch;
        bool m_initialized = false;
};



#endif /* MAIN_COMPONENTS_WATCHDOG_INCLUDE_WATCHDOG_BASE_HPP_ */
