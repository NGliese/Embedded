#ifndef _COMPONENTS_OBJECTS_JSON_INCLUDE_JSON_OBJECT_HPP_
#define _COMPONENTS_OBJECTS_JSON_INCLUDE_JSON_OBJECT_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  json_object.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolaj.gliese.pedersen@dansac.com>
 |  @date		   : 2022-01-09
 |
 |  @brief  	   :  This class, json_object.hpp, is designed as:
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

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class json_object
{
#ifdef __UNITTEST__
	friend class friend_json_object;
#endif
  public:
	json_object();
	~json_object();

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_json_object
{
  public:
	explicit friend_json_object(json_object* sensor) : m_sensor{sensor} {};
	~friend_json_object();

  private:
	json_object* m_sensor;
};
#endif

#endif //_COMPONENTS_OBJECTS_JSON_INCLUDE_JSON_OBJECT_HPP_
