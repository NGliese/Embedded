#ifndef _COMPONENTS_OBJECTS_JSMN_INCLUDE_JSMN_OBJECT_HPP_
#define _COMPONENTS_OBJECTS_JSMN_INCLUDE_JSMN_OBJECT_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  jsmn_object.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-01-17
 |
 |  @brief  	   :  This class, jsmn_object.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  @version       : 1.0
 |
 |  @bug  		   :   no known bugs
 |
 +-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/
//#define JSMN_HEADER (1) // required from github (?) GIVES AN ERROR ON TESTS
#include <jsmn.h> // from _deps

#include <cstdio>
#include <cstdlib>
#include <cstring>
/**
 * @brief simple function to compare the Key with the expected within json
 * 
 * @param json : json string
 * @param tok  : token
 * @param s    : expected key
 * @return int : 1 on true, 0 on false
 */
static int jsoneq(const char* json, jsmntok_t* tok, const char* s)
{
	if(tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
	   strncmp(json + tok->start, s, tok->end - tok->start) == 0)
	{
		return 0;
	}
	return -1;
}

/**
 * @brief simple function to retrive the int value within the json object
 * 
 * @param jsonstring : string of the json 
 * @param type  : must be "JSMN_PRIMITIVE" which is either a number or boolean
 * @param start : start index within json string
 * @param stop  : stop index within json string
 * @return int  : the value read, return 0 on fail
 */
static int json2int(const std::string& jsonstring, const jsmntype_t& type, int start, int stop)
{
	if(type != JSMN_PRIMITIVE)
	{
		return 0; // not a number
	}

	return std::atoi(jsonstring.substr(start, stop - start).c_str());
}

#endif //_COMPONENTS_OBJECTS_JSMN_INCLUDE_JSMN_OBJECT_HPP_