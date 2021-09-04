/*
 * RPICamV2.hpp
 *
 *  Created on: Jul 4, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_RPICAMV2_HPP_
#define INCLUDE_RPICAMV2_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  RPICamV2.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, RPICamV2.hpp, is designed as:
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
 |  	Link:[ ], Jul 4, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jul 4, 2021
 |
 |		Brief:
 |      We are using a 3rd party library by AVA reseach team, link:
 |      https://www.uco.es/investiga/grupos/ava/node/40
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



#include "../../../Interfaces/Camera/include/Camera.hpp"
#ifdef __RPI__
#include <raspicam/raspicam_cv.h>
#endif


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class RPICamV2 final : public Camera_CV {
#ifdef __UNITTEST__
    friend class friend_RPICamV2;
#endif
public:
    RPICamV2() ;
    ~RPICamV2();
    general_err_t takePicture(void) override ;
private:
#ifdef __RPI__
    raspicam::RaspiCam_Cv m_cam;
#endif


};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_RPICamV2 {
public:
    friend_RPICamV2(){};
    friend_RPICamV2(RPICamV2 * RPICamV2) : m_sensor{RPICamV2} { };

    ~friend_RPICamV2(){};

private:
    RPICamV2 * m_sensor;
};
#endif





#endif /* INCLUDE_RPICAMV2_HPP_ */
