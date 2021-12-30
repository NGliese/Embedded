/*
 * PWMBase.hpp
 *
 *  Created on: Sep 12, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_PWMBASE_HPP_
#define INCLUDE_PWMBASE_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  PWMBase.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, PWMBase.hpp, is designed as:
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
 |  	Link:[ ], Sep 12, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Sep 12, 2021
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
template<typename T, typename U>
class PWMBase {
#ifdef __UNITTEST__
    friend class friend_PWMBase;
#endif
public:
    /**
     * @brief following RAII @instantiation we activate and start PWM
     */
    PWMBase(const T& config,const std::string& name) : m_hal{config},m_faulthanlder{name} {};
    virtual ~PWMBase() {};
    //@brief

    /**
     * between 0 and 100. decimal allowed we are allowed to update the duty
     * cycle without the need of handling start and stop conditions for the pwm.
     * in other words, we can update live
     * @param [in] const float& duty
     * @return general_err_t
     */
   virtual general_err_t setDutyCycle(const float& duty) = 0;
    //@brief set frequency in Hz

   /**
    * set frequency in Hz
    * we are allowed to update the frequency without the need of handling start
    * and stop conditions for the pwm. in other words, we can update live
    * @param [in] const uint32_t& frequency
    * @return general_err_t
    */
   virtual general_err_t setFrequency(const uint32_t& frequency) = 0;


protected:
   U m_hal;                      ///< internal HAL object
   Fault_Handler m_faulthanlder; ///< internal faulthandler
private:
   virtual general_err_t stop(void) = 0;

};



#endif /* INCLUDE_PWMBASE_HPP_ */
