/*
 * Watch_Clock.hpp
 *
 *  Created on: Aug 27, 2020
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_WATCHDOG_INCLUDE_WATCH_CLOCK_HPP_
#define MAIN_COMPONENTS_WATCHDOG_INCLUDE_WATCH_CLOCK_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Watch_Clock.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Watch_Clock.hpp, is designed as:
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

#include "../../../Interfaces/WatchdogBase/include/Watchdog_Base.hpp"
#include "../../../Objects/Timeservice/include/Timeservice.hpp"
#include <ctime>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Watch_Clock : public Watchdog_Base<uint32_t>
{
  public:
	Watch_Clock(const size_t& parameter);
	Watch_Clock();
	~Watch_Clock();
	general_err_t initialize(uint32_t parameter) override;
	watchdog_event_t watch() override;
	general_err_t reset();

  private:
	uint32_t m_last_time = 0;
};

#endif /* MAIN_COMPONENTS_WATCHDOG_INCLUDE_WATCH_CLOCK_HPP_ */
