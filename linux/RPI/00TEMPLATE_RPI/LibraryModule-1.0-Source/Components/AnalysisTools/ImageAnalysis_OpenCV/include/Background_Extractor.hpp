#ifndef INCLUDE_BACKGROUND_EXTRACTOR_HPP_
#define INCLUDE_BACKGROUND_EXTRACTOR_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Background_Extractor.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Background_Extractor.hpp, is designed as:
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
 |  	Link:[ ], Jul 23, 2021
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Jul 23, 2021
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

#include "ConnectedComponents.hpp"
#include "Utility_Image.hpp"

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Background_Extractor {
#ifdef __UNITTEST__
    friend class friend_Background_Extractor;
#endif
public:
    enum class type{
        MOG2,KNN
    };

    struct background_conf_t{
        double learning_rate ; // -1 is default
        type m_type;
        int ksize;
        float zoom;
    };

    Background_Extractor(const background_conf_t& conf = {-1,type::MOG2,2,1} ) ;
    ~Background_Extractor();
    uint32_t countConnectedComponents(const cv::Mat& raw) ;
    ConnectedComponents::container_t statsConnectedComponents(const cv::Mat& raw) ;
   inline const cv::Mat& getBackgroundImage(void)const {return m_background;} ;
   inline const cv::Mat& getForgroundImage(void) const {return m_forground;} ;

    void view(void) const;
private:
    cv::Ptr<cv::BackgroundSubtractor> background;
    cv::Mat m_forground,m_background,m_previous,m_current;

    background_conf_t m_conf;
    std::string name;
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Background_Extractor {
public:
    friend_Background_Extractor(){};
    friend_Background_Extractor(Background_Extractor * Background_Extractor) : m_sensor{Background_Extractor} { };

    ~friend_Background_Extractor(){};

private:
    Background_Extractor * m_sensor;
};
#endif




#endif /* INCLUDE_BACKGROUND_EXTRACTOR_HPP_ */
