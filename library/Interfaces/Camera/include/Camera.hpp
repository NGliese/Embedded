/*
 * Camera.hpp
 *
 *  Created on: May 28, 2020
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_CAMERA_INCLUDE_CAMERA_HPP_
#define MAIN_COMPONENTS_CAMERA_INCLUDE_CAMERA_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Camera.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Camera.hpp, is designed as:
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
 |  	Link:[ ], May 28, 2020
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], May 28, 2020
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

#ifdef __WITH_OPENCV__
#include <opencv2/opencv.hpp>
#endif


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/







/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------+
 |                               Class                                          |
 +------------------------------------------------------------------------------*/

class Camera_CV {
public:
    Camera_CV() {};
    virtual ~Camera_CV() {};
    virtual general_err_t takePicture(void) =0 ;
    const cv::Mat& getPicture() {return m_image;};
protected:
    cv::Mat m_image;
private:
};


#endif /* MAIN_COMPONENTS_CAMERA_INCLUDE_CAMERA_HPP_ */
