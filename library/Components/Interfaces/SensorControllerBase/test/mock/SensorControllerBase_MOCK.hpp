#ifndef _COMPONENTS_INTERFACES_SENSORCONTROLLERBASE_TEST_MOCK_SENSORCONTROLLERBASE_MOCK_HPP_
#define _COMPONENTS_INTERFACES_SENSORCONTROLLERBASE_TEST_MOCK_SENSORCONTROLLERBASE_MOCK_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  SensorControllerBase_MOCK.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-02-27
 |
 |  @brief  	   :  This class, SensorControllerBase_MOCK.hpp, is designed as:
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

#include "../../include/SensorControllerBase.hpp"

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class SensorControllerBase_MOCK final : public SensorControllerBase
{
#ifdef __UNITTEST__
	friend class friend_SensorControllerBase_MOCK;
#endif
  public:
	SensorControllerBase_MOCK(const SensorControllerBase::init_conf& conf)
		: SensorControllerBase{conf} {};
	~SensorControllerBase_MOCK(){};

  private:
	general_err_t main_function() override;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_SensorControllerBase_MOCK
{
  public:
	explicit friend_SensorControllerBase_MOCK(SensorControllerBase_MOCK* sensor)
		: m_sensor{sensor} {};
	~friend_SensorControllerBase_MOCK();

  private:
	SensorControllerBase_MOCK* m_sensor;
};
#endif

#endif //_COMPONENTS_INTERFACES_SENSORCONTROLLERBASE_TEST_MOCK_SENSORCONTROLLERBASE_MOCK_HPP_