/*
 * Logger.hpp
 *
 *  Created on: Jun 14, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_LOGGER_HPP_
#define INCLUDE_LOGGER_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Logger.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Logger.hpp, is designed as:
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
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/


#include "../../../Objects/Timeservice/include/Timeservice.hpp"
#ifdef __UNITTEST__
#define LOGGER_STDOUT (1)
//#define LOGGER_MQTT (1)
#endif


// This macro should be placed in the top of the main function ( should work? )
#ifdef PROJECT_NAME
#else
#define PROJECT_NAME ("Unit test")
#endif


//#define LOGGER_STDOUT (1)
// This macro should also be placed in the top of the main function ( best way? )
#ifdef LOGGER_STDOUT
#include "hal_stdout.hpp"
using hal = hal_stdout;
#endif


#ifdef LOGGER_MQTT
#include "hal_mqtt_log.hpp"
using hal = hal_mqtt_log;
#endif

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/



/* -----------------------------------------------------------------------------+
 *  The following error format is shown below:
 *   [Timestamp]  [ProjectName] [ErrorCode]  [Message] [Response]
 *
 */

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Logger {
#ifdef __UNITTEST__
    friend class friend_Logger;
#endif
public:
    struct msg_t{
        general_err_t error_code;
        general_resp_t respons_code;
        std::string msg;
    };
    static general_err_t write(const msg_t& msg);
private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Logger {
public:
    friend_Logger(){};
    friend_Logger(Logger * Logger) : m_sensor{Logger} { };

    ~friend_Logger(){};

private:
    Logger * m_sensor;
};
#endif





#endif /* INCLUDE_LOGGER_HPP_ */
