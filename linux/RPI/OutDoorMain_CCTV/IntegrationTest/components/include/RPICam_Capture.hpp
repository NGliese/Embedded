/*
 * RPICam_Capture.hpp
 *
 *  Created on: Jul 6, 2021
 *      Author: nikolaj
 */

#ifndef COMPONENTS_INCLUDE_RPICAM_CAPTURE_HPP_
#define COMPONENTS_INCLUDE_RPICAM_CAPTURE_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  RPICam_Capture.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, RPICam_Capture.hpp, is designed as:
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

/*----------------- DEFAULT INCLUDE -------------------------------------------*/

#include "../../../LibraryModule-1.0-Source/Components/Global_Include/BASIC.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include "../../../LibraryModule-1.0-Source/Components/AnalysisTools/ImageAnalysis_OpenCV/include/Background_Extractor.hpp"
#include "../../../LibraryModule-1.0-Source/Components/AnalysisTools/ImageAnalysis_OpenCV/include/Utility_Image.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Global_Include/Database_ID_Base.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Objects/Message/include/Message_Handler.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Objects/Timeservice/include/Timeservice.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Protocols/HTTP/include/postgresql_interface.hpp"

#include "../../../LibraryModule-1.0-Source/Components/Objects/Timeservice/include/Timeservice.hpp"
#include "../../../LibraryModule-1.0-Source/Components/Objects/Watchdog/include/Watch_Clock.hpp"

#include "../../../LibraryModule-1.0-Source/Components/Sensor/RpiCamV2/include/RPICamV2.hpp"

#include <ctime>
#include <opencv2/bgsegm.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <sys/time.h>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class RPICam_Capture
{
#ifdef __UNITTEST__
	friend class friend_RPICam_Capture;
#endif
  public:
	RPICam_Capture() = default;
	~RPICam_Capture();
	general_err_t capture(void);
	general_err_t stream(void);
	general_err_t capture_and_save();
	general_err_t stream_vinfo(void);

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_RPICam_Capture
{
  public:
	friend_RPICam_Capture(){};
	friend_RPICam_Capture(RPICam_Capture* RPICam_Capture) : m_sensor{RPICam_Capture} {};

	~friend_RPICam_Capture(){};

  private:
	RPICam_Capture* m_sensor;
};
#endif

#endif /* COMPONENTS_INCLUDE_RPICAM_CAPTURE_HPP_ */
