/*
 * Image_CodeBook.hpp
 *
 *  Created on: Jul 12, 2021
 *      Author: nikolaj
 */

#ifndef INCLUDE_IMAGE_CODEBOOK_HPP_
#define INCLUDE_IMAGE_CODEBOOK_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Image_CodeBook.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Image_CodeBook.hpp, is designed as:
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
 | Codebooks are just boxes delimiting intensity vakues; a box is formed t cover
 | a new value and slowly grows to cover nearby values;
 | if values are too far away then a new box is formed
 |
 |
 |  @WARNING:: SOFTWARE CONTAINS DYNAMIC ALLOCATION
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


#include <array>


/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

constexpr uint8_t CHANNELS = (3);


/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Image_CodeBook {
#ifdef __UNITTEST__
    friend class friend_Image_CodeBook;
#endif
public:
    Image_CodeBook(const size_t& amount_of_columns, const size_t amount_of_rows) ;
    ~Image_CodeBook();

private:
   // size_t m_channels =1;
    struct code_element_t{
        std::array<uint8_t,CHANNELS> learnHigh; // high side threshold for learning
        std::array<uint8_t,CHANNELS> learnLow;  // low side threshold for learning
        std::array<uint8_t,CHANNELS> max;       // high side of box boundary
        std::array<uint8_t,CHANNELS> min;       // low side of box boundary
        size_t last_update;                     // Allow us to kill stale entries
        size_t stale;                           // max negative run
    };

    struct code_book_t{
    code_element_t **ce;                          // pointer-to-pointer of code elements
    size_t number_of_entries;
    size_t counter;                               // count every acces
    };



    /*
     *    general_err_t update_codeBook(uint8_t *pixel,code_book_t& code_book,unsigned* cbBounds, size_t number_of_channels);
     *    Updates the codebook entry with a new data point
     *
     *    pixel                 Pointer to a YUV pixel
     *    code_book             codeBook for this pixel
     *    cbBounds              Learning bounds for codebook (Rule of thumb: 10)
     *    numChannels           Number of color channels we are learning
     *
     *    NOTES:
     *          cbBounds must be of length equal to numChannels
     *    RETURN:
     *      codebook index
     */

    int update_codeBook(uint8_t *pixel,code_book_t& code_book,unsigned* cbBounds, size_t number_of_channels);
};


/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_Image_CodeBook {
public:
    friend_Image_CodeBook(){};
    friend_Image_CodeBook(Image_CodeBook * Image_CodeBook) : m_sensor{Image_CodeBook} { };

    ~friend_Image_CodeBook(){};

private:
    Image_CodeBook * m_sensor;
};
#endif




#endif /* INCLUDE_IMAGE_CODEBOOK_HPP_ */
