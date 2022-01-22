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

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class jsmn_object
{
#ifdef __UNITTEST__
	friend class friend_jsmn_object;
#endif
  public:
	/**
	 * @brief Get the Parsed Integer Value object
	 *
	 * @param str
	 * @param key
	 * @return int : retunr 0 if fail, parsed value otherwise
	 */
	static int getParsedIntegerValue(const std::string& str, const std::string& key,
									 const std::uint8_t size = 128)
	{
		jsmn_parser p;
		jsmntok_t t[size]; /* We expect no more than 128 JSON tokens */

		jsmn_init(&p);
		auto res = jsmn_parse(&p, str.c_str(), str.size(), t,
							  size); // "s" is the char array holding the json content

		for(size_t i = 1; i < res; i++)
		{
			if(jsoneq(str.c_str(), &t[i], "value") == 0)
			{
				return json2int(str, t[i + 1].type, t[i + 1].start, t[i + 1].end);
			}
		}
		return 0;
	}

  private:
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
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_jsmn_object
{
  public:
	static auto jsoneq(const char* json, jsmntok_t* tok, const char* s)
	{
		return jsmn_object::jsoneq(json, tok, s);
	}
	static auto json2int(const std::string& jsonstring, const jsmntype_t& type, int start, int stop)
	{
		return jsmn_object::json2int(jsonstring, type, start, stop);
	}

  private:
};
#endif

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

#endif //_COMPONENTS_OBJECTS_JSMN_INCLUDE_JSMN_OBJECT_HPP_