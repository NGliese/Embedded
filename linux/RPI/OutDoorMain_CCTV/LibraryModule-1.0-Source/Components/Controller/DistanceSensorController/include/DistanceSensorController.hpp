#ifndef _COMPONENTS_CONTROLLER_DISTANCESENSORCONTROLLER_INCLUDE_DISTANCESENSORCONTROLLER_HPP_
#define _COMPONENTS_CONTROLLER_DISTANCESENSORCONTROLLER_INCLUDE_DISTANCESENSORCONTROLLER_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  DistanceSensorController.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-02-27
 |
 |  @brief  	   :  This class, DistanceSensorController.hpp, is designed as:
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
#include "../../../Interfaces/SensorControllerBase/include/SensorControllerBase.hpp"
#include "../../../Objects/ADC/include/ADC_API_ESP32.hpp"
#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class DistanceSensorController final : public SensorControllerBase
{
#ifdef __UNITTEST__
	friend class friend_DistanceSensorController;
#endif
  public:
	struct config
	{
		SensorControllerBase::init_conf init_conf;
		const uint64_t time_between_adc_measurements;
		ADC_API_ESP32::config adc_conf;
	};
	DistanceSensorController(const DistanceSensorController::config& conf)
		: SensorControllerBase{conf.init_conf},
		  m_time_between_adc_measurements{conf.time_between_adc_measurements},
		  m_adc{conf.adc_conf} {};
	~DistanceSensorController(){};

  private:
	general_err_t main_function() override;
	general_err_t updateInternalBuffer();
	const uint64_t m_time_between_adc_measurements;
	ADC_API_ESP32 m_adc;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_DistanceSensorController
{
  public:
	explicit friend_DistanceSensorController(DistanceSensorController* sensor)
		: m_sensor{sensor} {};
	~friend_DistanceSensorController(){};
	void setDataReady()
	{
		m_sensor->setDataReadyTrue();
	}

  private:
	DistanceSensorController* m_sensor;
};
#endif

#endif //_COMPONENTS_CONTROLLER_DISTANCESENSORCONTROLLER_INCLUDE_DISTANCESENSORCONTROLLER_HPP_
