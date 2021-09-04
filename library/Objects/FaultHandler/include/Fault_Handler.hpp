/*
 * Fault_Handler.hpp
 *
 *  Created on: Jul 6, 2021
 *      Author: espenv
 */

#ifndef INCLUDE_FAULT_HANDLER_HPP_
#define INCLUDE_FAULT_HANDLER_HPP_



/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Fault_Handler.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Fault_Handler.hpp, is designed as:
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
 |  	Link:[ ], Jul 6, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jul 6, 2021
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

#include "../../../Objects/Logger/include/Logger.hpp"




/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

namespace FaultHandler_n
{
enum class severity : uint8_t{
lowest,
very_low,
low,
medium_low,
medium,
medium_high,
high,
very_high,
highest
};

struct msg_t{
        severity level;
        std::string function_name;
        std::string describtion;
};

// bounderies for the counter values
constexpr uint16_t max_count_value_low    = 10;
constexpr uint16_t max_count_value_medium = 5;
constexpr uint16_t max_count_value_high   = 1;
}



/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/


/*
 * Class description and usage
 * The fault handler should be implemeted in every class which has "something which might go wrong"
 * This could be:
 * # semaphores -> thread-related issues
 * # sensors -> bad measurements / hanging
 * # timeouts -> stuck in a endless loop
 * # other ....
 *
 *
 * @Class constructor:
 * Class A () : m_faultHandler{"Class A"}
 *
 *
 *
 *
 * @Faulty code:
 * void faulty_function
 * if(bug){
 *  m_faultHandler.handleFault( { FaultHandler_n::severity::very_high,"faulty_function","we have found a bug" } );
 * }
 *
 */


class Fault_Handler {
#ifdef __UNITTEST__
    friend class friend_Fault_Handler;
#endif
public:
    Fault_Handler(const std::string& class_name) ;
    ~Fault_Handler();

    general_err_t handleFault(const FaultHandler_n::msg_t& msg);
    general_err_t resetFaultCounter(const FaultHandler_n::severity& level);

private:
    general_err_t countUp(const FaultHandler_n::msg_t& msg);
    general_err_t handle(const FaultHandler_n::msg_t& msg);

    std::string toString(const FaultHandler_n::msg_t& msg);
    std::string severity2string(const FaultHandler_n::severity& level);


    inline bool check_value(const uint16_t& count, const uint16_t& boundery) const
    {
        return count >= boundery ? true : false;
    }

    std::string m_name;

    struct counters_t{
           uint16_t low;
           uint16_t medium;
           uint16_t high;
    };



    counters_t m_counters;

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Fault_Handler {
public:

    friend_Fault_Handler(Fault_Handler * Fault_Handler) : m_sensor{Fault_Handler} { };

    ~friend_Fault_Handler(){};

    auto countUp(const FaultHandler_n::msg_t& msg) { return m_sensor->countUp(msg);}
    auto handle(const FaultHandler_n::msg_t& msg) { return m_sensor->handle(msg);}
    auto toString(const FaultHandler_n::msg_t& msg) {return m_sensor->toString(msg);}
    auto check_value(const uint16_t& count, const uint16_t& boundery) {return m_sensor->check_value(count,boundery); }
    auto getCounterValue(const FaultHandler_n::severity& level){

        switch (level) {
              case FaultHandler_n::severity::lowest:
              case FaultHandler_n::severity::very_low:
              case FaultHandler_n::severity::low:
                  return m_sensor->m_counters.low;

              case FaultHandler_n::severity::medium_low:
              case FaultHandler_n::severity::medium:
              case FaultHandler_n::severity::medium_high:
                  return m_sensor->m_counters.medium;

              case FaultHandler_n::severity::high:
              case FaultHandler_n::severity::very_high:
              case FaultHandler_n::severity::highest:
                  return m_sensor->m_counters.high;

          }
        return m_sensor->m_counters.high;
    }
private:
    Fault_Handler * m_sensor;
};
#endif




#endif /* INCLUDE_FAULT_HANDLER_HPP_ */
