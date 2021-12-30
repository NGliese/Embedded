/*
 * DogFeederDoor.hpp
 *
 *  Created on: Nov 23, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_DOGFEEDERDOOR_HPP_
#define INCLUDE_DOGFEEDERDOOR_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  DogFeederDoor.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, DogFeederDoor.hpp, is designed as:
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
 |  	Link:[ ], Nov 23, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Nov 23, 2021
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


#include "../../../Actuator/ServoMotor/include/MG996R.hpp"


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/**
 * @Class This class is ment to be the "User" of the motor class
 * And also the current sensor class. It is acting as a "Controller/Superviser"
 * And has the ability to open and close the door.
 *
 * It is also responsible for acting upon faults occured by the motor.
 * It will notice fauls based on the current sensor data and will either stop/kill
 * the motor (and)/or report to the sensorlog that an fault has happend.
 *
 */



/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class DogFeederDoor {
#ifdef __UNITTEST__
    friend class friend_DogFeederDoor;
#endif
public:
    explicit DogFeederDoor(const mg996r_conf_t& conf) ;
    ~DogFeederDoor();
    general_err_t open();
    general_err_t close();
private:
    MG996R m_motor;
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_DogFeederDoor {
public:
    
    explicit friend_DogFeederDoor(DogFeederDoor * DogFeederDoor) : m_sensor{DogFeederDoor} { };

    ~friend_DogFeederDoor(){};

private:
    DogFeederDoor * m_sensor;
};
#endif





#endif /* INCLUDE_DOGFEEDERDOOR_HPP_ */
