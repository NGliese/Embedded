#ifndef _COMPONENTS_SERVICE_WATERESTIMATOR_INCLUDE_WATERESTIMATOR_SERVICE_HPP_
#define _COMPONENTS_SERVICE_WATERESTIMATOR_INCLUDE_WATERESTIMATOR_SERVICE_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  WaterEstimator_Service.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-18
 |
 |  @brief  	   :  This class, WaterEstimator_Service.hpp, is designed as:
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
#include "../../../AnalysisTools/PeriodEstimator/include/PeriodeEstimator.hpp"
#include "../../../Interfaces/ServiceBase/include/ServiceBase.hpp"
#include <algorithm> // For std::for_each()
#include <iostream>
/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class WaterEstimator_Service final : public ServiceBase<MQTT_Message>
{
#ifdef __UNITTEST__
	friend class friend_WaterEstimator_Service;
#endif
  public:
	WaterEstimator_Service(size_t queue_size, size_t size_of_item, const MQTT_Message& buffer,
						   const db_id error_id)
		: ServiceBase(queue_size, size_of_item, buffer, error_id),
		  msg_max{{db_id::WATERSTATION_MAX_ADC_VAL, 1}},
		  msg_min{{db_id::WATERSTATION_MIN_ADC_VAL, 1}}, msg_count{
															 {db_id::WATERSTATION_COUNTER, 100}} {};
	~WaterEstimator_Service(){};

  private:
	general_err_t mainFunction();
	MQTT_Message msg_max;
	MQTT_Message msg_min;
	MQTT_Message msg_count;
#ifdef __ESP32__
	PeriodeEstimator<1900, 1800, NVS_esp32> m_estimator;
#else
	PeriodeEstimator<1900, 1800, NVS_MOCK> m_estimator;
#endif
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_WaterEstimator_Service
{
  public:
	explicit friend_WaterEstimator_Service(WaterEstimator_Service* sensor) : m_sensor{sensor} {};
	~friend_WaterEstimator_Service(){};

  private:
	WaterEstimator_Service* m_sensor;
};
#endif

#endif //_COMPONENTS_SERVICE_WATERESTIMATOR_INCLUDE_WATERESTIMATOR_SERVICE_HPP_