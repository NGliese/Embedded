/*
 * System_Overall.hpp
 *
 *  Created on: Mar 2, 2021
 *      Author: espenv
 */

#ifndef COMPONENTS_OVERALL_SYSTEM_INCLUDE_SYSTEM_OVERALL_HPP_
#define COMPONENTS_OVERALL_SYSTEM_INCLUDE_SYSTEM_OVERALL_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  System_Overall.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, System_Overall.hpp, is designed as:
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
 |  	Link:[ ], Mar 2, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Mar 2, 2021
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


#include "../../../../../lib2pi/Global_Include/BASIC.hpp"
#include "../../../../../lib2pi/Objects/ErrorHandler/include/General_Error.hpp"


#include "../../../../../lib2pi/AnalysisTools/ImageAnalysis_OpenCV/include/Utility_Image.hpp"
#include "../../../../../lib2pi/Objects/Timeservice/include/Timeservice.hpp"
#include "../../../../../lib2pi/Sensor/RpiCamV2/include/RPICamV2.hpp"

#include "Image_Helper_v2.hpp"
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

#include <sys/time.h>
#include <iostream>
#include <string>

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class System_Overall {
#ifdef __UNITTEST__
    friend class friend_System_Overall;
#endif
public:
    System_Overall() ;
    ~System_Overall();
    void run(void);
private:
    Image_Helper_v2 m_helper;
    RPICamV2 m_cam;
};







#endif /* COMPONENTS_OVERALL_SYSTEM_INCLUDE_SYSTEM_OVERALL_HPP_ */
