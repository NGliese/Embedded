/*
 * utils.h
 *
 *  Created on: Jun 17, 2018
 *      Author: nikolaj
 */

#ifndef COMPONENTS_MONITOR_INCLUDE_UTILS_H_
#define COMPONENTS_MONITOR_INCLUDE_UTILS_H_

#include <string>
#include <vector>

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/
//#include "FreeRTOS.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <sstream>  // Required for stringstreams
#include <string>
namespace basic_utils{
bool is_even(int16_t expr);
uint16_t leastSignificantByteExchange(uint16_t data,uint8_t exchange);
uint8_t getLeastSignificantByte(uint16_t data);
void delay(const uint32_t & delay_ms);
uint32_t shift8BitTo32(const uint8_t & b1,const uint8_t & b2,const uint8_t & b3,const uint8_t & b4);
general_err_t shift32BitTo8(const uint32_t & b32, uint8_t & b1, uint8_t & b2, uint8_t & b3, uint8_t & b4);
void split(const std::string& s, char delim,std::vector<std::string>& v);
std::vector<std::string> split(const std::string& s, const std::string& delim);
// psudo random : range [min,max]
int random(int min, int max);
}

std::string uint8ToString ( uint8_t number );
std::string timeToString ( time_t number );
std::string intToString(int number) ;
std::string uintToString(uint8_t number) ;
std::string floatToString(float number) ;
std::string floatToString ( float number , int precision);
void printBits(size_t const size, void const * const ptr);

#endif /* COMPONENTS_MONITOR_INCLUDE_UTILS_H_ */
