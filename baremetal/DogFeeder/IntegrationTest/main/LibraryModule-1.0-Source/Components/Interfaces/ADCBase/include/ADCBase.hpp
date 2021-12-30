/*
 * ADCBase.hpp
 *
 *  Created on: Sep 20, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_ADCBASE_HPP_
#define INCLUDE_ADCBASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  ADCBase.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, ADCBase.hpp, is designed as:
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
 |  	Link:[ ], Sep 20, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Sep 20, 2021
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
template<typename T>
class ADCBase {
#ifdef __UNITTEST__
    friend class friend_ADCBase;
#endif
public:
    //@brief following RAII @instantiation we activate and start ADC
    ADCBase(const std::string& name, const size_t samples) : m_faulthanlder{name}, m_number_of_samples{samples} {};
    virtual ~ADCBase(){};

    /**
     * measure the value of the adc
     * @return template variable T
     *
     */
    virtual T measureValue(void) = 0;
    /**
     * set the number of samples for the low pass filter
     * @param [in] const size_t& samples
     * @return N/A
     *
     */
    inline void setSampleNumber(const size_t& samples) {
        if( (samples >= minimum_number_of_samples) and (samples <= maximum_number_of_samples) )
        {
            m_number_of_samples = samples;
        }
    }
    /**
     * get the sample number
     * @return size_t sample_number
     *
     */
    inline auto getSampleNumber(void) {return m_number_of_samples;}
protected:
    Fault_Handler m_faulthanlder;
    size_t m_number_of_samples;
private:

    static constexpr size_t minimum_number_of_samples = 1;
    static constexpr size_t maximum_number_of_samples = 5000; // just a large number
};






#endif /* INCLUDE_ADCBASE_HPP_ */
