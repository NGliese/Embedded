#ifndef INCLUDE_CONNECTEDCOMPONENTS_HPP_
#define INCLUDE_CONNECTEDCOMPONENTS_HPP_

/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  ConnectedComponents.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, ConnectedComponents.hpp, is designed as:
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
 |  	Link:[ ], Jul 17, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jul 17, 2021
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


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <array>




/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class ConnectedComponents {
#ifdef __UNITTEST__
    friend class friend_ConnectedComponents;
#endif
public:

    struct ellipse_data_t
    {
        float height;
        float width;
        float aspect_ratio;
        float area;
    };

    struct container_t{
        uint32_t maxConnected;
        size_t amount_of_connections;
        ellipse_data_t ellipse;

    };

    static general_err_t drawConnectedComponents(const cv::Mat& forground, cv::Mat& drawing);
    static general_err_t drawConnectedComponentsOpenCV(const cv::Mat& forground, cv::Mat& drawing);
    static uint32_t maxConnectedComponents(const cv::Mat& forground,int ksize = 2);
    static container_t statsConnectedComponents(const cv::Mat& forground,int ksize = 2);
private:

};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_ConnectedComponents {
public:
    friend_ConnectedComponents(ConnectedComponents * ConnectedComponents) : m_sensor{ConnectedComponents} { };

    ~friend_ConnectedComponents(){};

private:
    ConnectedComponents * m_sensor;
};
#endif





#endif /* INCLUDE_CONNECTEDCOMPONENTS_HPP_ */
