#ifndef _COMPONENTS_OBJECTS_ERRORHANDLER_INCLUDE_ERRORCODEPARSER_HPP_
#define _COMPONENTS_OBJECTS_ERRORHANDLER_INCLUDE_ERRORCODEPARSER_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  ErrorCodeParser.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-01-31
 |
 |  @brief  	   :  This class, ErrorCodeParser.hpp, is designed as:
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
#include "../../../Global_Include/Database_ID_Base.hpp"
#include "../../../Objects/Timeservice/include/Timeservice.hpp"
#include "../../../Protocols/MQTT/include/mqtt_api_v2.hpp"
#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class ErrorCodeParser
{
#ifdef __UNITTEST__
	friend class friend_ErrorCodeParser;
#endif
  public:
	/**
	 * @brief postToMqtt sends a signle error code to the database with the given ID
	 *
	 * @param id
	 * @param err
	 * @return general_err_t
	 */
	static general_err_t postToMqtt(const db_id& id, const general_err_t& err,
									const std::string& description = "");

  private:
	inline const static std::string toString(const db_id& id, const general_err_t& err,
											 const std::string& description)
	{
		return std::to_string(map.at(id)) + "," + std::to_string(Timeservice::getTimeNow()) + "," +
			   std::to_string(static_cast<uint8_t>(err) + 10 /* offset zero values for grafana */) +
			   "," + description;
	};
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_ErrorCodeParser
{
  public:
	explicit friend_ErrorCodeParser(ErrorCodeParser* sensor) : m_sensor{sensor} {};
	~friend_ErrorCodeParser();
	static std::string toString(const db_id& id, const general_err_t& err,
								const std::string& description)
	{
		return ErrorCodeParser::toString(id, err, description);
	}

  private:
	ErrorCodeParser* m_sensor;
};
#endif

#endif //_COMPONENTS_OBJECTS_ERRORHANDLER_INCLUDE_ERRORCODEPARSER_HPP_
