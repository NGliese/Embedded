/*
 * Actuator_Base.hpp
 *
 *  Created on: Apr 26, 2021
 *      Author: nikolaj
 */

#ifndef MAIN_COMPONENTS_ACTUATOR_INCLUDE_ACTUATOR_BASE_HPP_
#define MAIN_COMPONENTS_ACTUATOR_INCLUDE_ACTUATOR_BASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Actuator_Base.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Actuator_Base.hpp, is designed as:
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
 |  	Link:[ ], Apr 26, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Apr 26, 2021
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


#include "../../../Objects/FaultHandler/include/Fault_Handler.hpp"




/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
template<typename T,typename U>
class Actuator_Base {
#ifdef __UNITTEST__
    friend class friend_Actuator_Base;
#endif
public:
    Actuator_Base(const T& conf) :m_value{0}, m_conf{conf},m_faulthanlder{"actuator_base"}{};
    virtual ~Actuator_Base() {};
    /**
     * function to apply the setpoint value to the actuator and
     * to call the actuate() function, if the setpoint is valid.
     */
    inline general_err_t execute(const U& value) {
        auto err = setPoint(value);
        return (err == GE_OK) ?  actuate() :  err;
    }
    /**
     * function to return the current value of the actuator
     */
    inline const U& getValue(void) const {  return m_value;  } ;
    /**
     * function to set the actuator to the maximum possible value
     */
    virtual general_err_t setToMaximum(void) = 0;
    /**
     * function to set the actuator to the minimum possible value
     */
     virtual general_err_t setToMinimum(void) = 0;
protected:
    /**
     * Setpoint function, the derived class is able to define its own function to accommodate fault handling
     * @attention: no fault handling applied in the default function
     */
    virtual general_err_t setPoint(const U& value) { m_value = value; return GE_OK; };
    /**
     * Purely virtual function for the derived class to define for it self.
     */
    virtual general_err_t actuate(void) = 0;

    U m_value ;
    T m_conf;
    Fault_Handler m_faulthanlder; ///< internal faulthandler
};








#endif /* MAIN_COMPONENTS_ACTUATOR_INCLUDE_ACTUATOR_BASE_HPP_ */
