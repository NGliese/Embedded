#ifndef _COMPONENTS_OBJECTS_NONVOLATILESTORAGE_INCLUDE_NVS_MOCK_HPP_
#define _COMPONENTS_OBJECTS_NONVOLATILESTORAGE_INCLUDE_NVS_MOCK_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  NVS_MOCK.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-24
 |
 |  @brief  	   :  This class, NVS_MOCK.hpp, is designed as:
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

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class NVS_MOCK
{
#ifdef __UNITTEST__
	friend class friend_NVS_MOCK;
#endif
  public:
	static const uint64_t read_u64(const std::string& key)
	{
		//  return NVS_HAL::
		return 0;
	};
	static general_err_t write_u64(const std::string& key, const uint64_t& value)
	{
		return GE_OK;
	};

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_NVS_MOCK
{
  public:
	explicit friend_NVS_MOCK(NVS_MOCK* sensor) : m_sensor{sensor} {};
	~friend_NVS_MOCK();

  private:
	NVS_MOCK* m_sensor;
};
#endif

#endif //_COMPONENTS_OBJECTS_NONVOLATILESTORAGE_INCLUDE_NVS_MOCK_HPP_