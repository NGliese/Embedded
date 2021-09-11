/*
 * Sensor_Base.hpp
 *
 *  Created on: Aug 28, 2020
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_SENSOR_INCLUDE_SENSOR_BASE_HPP_
#define MAIN_COMPONENTS_SENSOR_INCLUDE_SENSOR_BASE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Sensor_Base.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :   <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Sensor_Base.hpp, is designed as:
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
 |  	Link:[ ], Aug 28, 2020
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Aug 28, 2020
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


struct sensor_conf_t{
    uint16_t sensor_address;
};


/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/



template<typename T,typename U>
class Sensor_Base {
public:
        Sensor_Base(const T& conf,const std::string& class_name="N/A") :m_value{0}, m_conf{conf},m_faultHanlder{class_name}{};
        virtual ~Sensor_Base(){};

        virtual general_err_t measure(void) = 0;
        inline const U& getValue(void){  return m_value;  };
        /* @brief Handle all parts of the sensor by measuring and returning value in one.
         * @warning error messages in measure() is neglected here, and should be considered as a fail safe solution.
         */
        inline const U& handleSensor(void) {
           return measure() == GE_OK ? getValue() : 0;
            }
protected:
        U m_value = 0;
        T m_conf;
        Fault_Handler m_faultHanlder;
};

#endif /* MAIN_COMPONENTS_SENSOR_INCLUDE_SENSOR_BASE_HPP_ */
