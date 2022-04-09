/***********************************************************************************************+
 *  @brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  @note       ANY RELEVANT NOTES
 *
 *  @file       WaterEstimator_Service.cpp
 *  @author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  @version    1.0
 *  @date       2022-03-18
 *  @copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/WaterEstimator_Service.hpp"

#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "WaterEstimator_Service";
#endif

general_err_t WaterEstimator_Service::mainFunction()
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> WaterEstimator_Service::mainFunction >> ");
#endif
	// Executable code:
	uint64_t max_value = 0;
	uint64_t min_value = 50000;
	/*
	std::for_each(m_buffer.getData().begin(), m_buffer.getData().end(),
				  [&max_value, &min_value](const std::pair<uint64_t, uint64_t>& ele) {
					  if(ele.second > max_value){
						  max_value = ele.second;
						  }
					  if(ele.second < min_value){
						  min_value = ele.second;
						  }
				  });
	*/
	for(const auto& ele : m_buffer.getData())
	{
		if(ele.second > max_value)
		{
			max_value = ele.second;
		}
		if(ele.second < min_value)
		{
			min_value = ele.second;
		}
		auto err = m_estimator.addData(ele);
		if(err == GE_OK)
		{
			msg_count.addData(m_estimator.getPeriodCounter());
		}
	}
	msg_max.addData(max_value);
	msg_min.addData(min_value);

	// postData(msg_max);
	// postData(msg_min);
	postData(msg_count);

	msg_max.clear();
	msg_min.clear();
	msg_count.clear();

	std::cout << " max value is : " << (int)max_value << " min value is : " << (int)min_value
			  << " count is : " << m_estimator.getPeriodCounter() << "\n";

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<<  WaterEstimator_Service::mainFunction << ");
#endif

	return GE_OK;
}