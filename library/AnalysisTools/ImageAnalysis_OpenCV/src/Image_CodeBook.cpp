/*
 * Image_CodeBook.cpp
 *
 *  Created on: Jul 12, 2021
 *      Author: nikolaj
 */




/***********************************************************************************************+
 *  \brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       Image_CodeBook.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/Image_CodeBook.hpp"


//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "Image_CodeBook";
#endif

Image_CodeBook::Image_CodeBook(const size_t &amount_of_columns,
        const size_t amount_of_rows) {
}

Image_CodeBook::~Image_CodeBook() {
}


int Image_CodeBook::update_codeBook(uint8_t *pixel, code_book_t &code_book,
        unsigned *cbBounds, size_t number_of_channels) {

    int32_t high[number_of_channels], low[number_of_channels];
    for(size_t n=0; n < number_of_channels; n++)
    {
        high[n] = *(pixel+n)+*(cbBounds+n);
        if(high[n] > 255) { high[n] = 255; }

        low[n] = *(pixel+n)-*(cbBounds+n);
        if(low[n] < 0) { low[n] = 0; }

    }

    size_t matchChannel;
    // see if this fits an existing codebook
    for(size_t i = 0; i < code_book.number_of_entries; i++)
    {
        matchChannel=0;
        for(size_t n=0; n < number_of_channels; n++)
        {
            if( (code_book.ce[i]->learnLow[n] <= *(pixel+n)) && (*(pixel+n) <= code_book.ce[i]->learnHigh[n]) )
            {
                ++matchChannel;
            }
        } //for(size_t n=0; n < number_of_channels; n++)

        if(number_of_channels == matchChannel)
        {
            code_book.ce[i]->last_update = code_book.counter;
            // adjust this codebook for the first channel
            for(size_t n = 0; n < number_of_channels ; n++)
            {

                if(code_book.ce[i]->max[n] < *(pixel+n) )
                {
                    code_book.ce[i]->max[n] = *(pixel+n);
                } else if(code_book.ce[i]->min[n] > *(pixel+n) )
                {
                    code_book.ce[i]->min[n] = *(pixel+n);
                }


            }// for(size_t n = 0; n < number_of_channels ; n++)
            break;
        }//if(number_of_channels == matchChannel)

    }// for(size_t i = 0; i < code_book.number_of_entries; i++)


    // overhead to track stale entries
    for(size_t s = 0; s < code_book.number_of_entries; s++)
    {
        // Track which codebook entries are going stale
        int negRun = code_book.counter - code_book.ce[s]->last_update;
        if(code_book.ce[s]->stale < negRun) { code_book.ce[s]->stale = negRun; }
    }
return 0;
}
