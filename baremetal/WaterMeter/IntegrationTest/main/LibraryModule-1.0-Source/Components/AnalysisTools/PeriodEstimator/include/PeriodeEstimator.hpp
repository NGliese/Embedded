#ifndef _COMPONENTS_ANALYSISTOOLS_PERIODESTIMATOR_INCLUDE_PERIODEESTIMATOR_HPP_
#define _COMPONENTS_ANALYSISTOOLS_PERIODESTIMATOR_INCLUDE_PERIODEESTIMATOR_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  PeriodeEstimator.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolajgliese@tutanota.com>
 |  @date		   : 2022-03-19
 |
 |  @brief  	   :  This class, PeriodeEstimator.hpp, is designed as:
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
#include "../../../Objects/NonVolatileStorage/include/NVS.hpp"
#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/
constexpr uint64_t COUNTER_VALUE = 491327;
constexpr uint64_t INIT_VALUE = 0x44;
/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/
template<uint64_t HIGH_THRESHOLD, uint64_t LOW_THRESHOLD, typename NVS_TYPE>
class PeriodeEstimator
{
#ifdef __UNITTEST__
	friend class friend_PeriodeEstimator;
#endif
  public:
	enum class states : uint8_t
	{
		HIGH,
		MIDDLE,
		LOW,
		UNDEF
	};
	PeriodeEstimator()
		: m_high_threshold{HIGH_THRESHOLD}, m_low_threshold{LOW_THRESHOLD},
		  m_current_state{states::UNDEF}, m_last_state{states::UNDEF}, m_counter{COUNTER_VALUE}
	{
		static_assert(LOW_THRESHOLD < HIGH_THRESHOLD);

		if(NVS<NVS_TYPE>::read_u64("INIT_KEY") != INIT_VALUE)
		{
			NVS<NVS_TYPE>::write_u64("COUNTER", COUNTER_VALUE);
			NVS<NVS_TYPE>::write_u64("INIT_KEY", INIT_VALUE);
		}
		else
		{
			m_counter = NVS<NVS_TYPE>::read_u64("COUNTER");
		}
	};
	~PeriodeEstimator(){};
	/**
	 * @brief add data to the estimator in order to on-the-fly detect
	 *        periods.
	 *
	 *        The pair<uint64_t, uint64_t> is expected to be pair<Timestamp,Datapoint>
	 *
	 * @param data
	 * @return general_err_t
	 */
	general_err_t addData(std::pair<uint64_t, uint64_t> data)
	{
		auto& datapoint = data.second;
		states new_state = states::UNDEF;
		new_state = datapoint > m_high_threshold
						? states::HIGH
						: datapoint > m_low_threshold ? states::MIDDLE : states::LOW;
		return decideStateChange(new_state);
	}
	/**
	 * @brief Get the Period Counter object
	 * @return auto const&
	 */
	auto const getPeriodCounter()
	{
		return m_counter;
	}

  private:
	inline general_err_t decideStateChange(const states& new_state)
	{
		if(m_current_state != new_state)
		{
			return m_current_state == states::UNDEF ? setInitialState(new_state)
													: setNextState(new_state);
		}
		return GE_NO_DATA;
	}
	inline general_err_t setInitialState(const states& new_state)
	{
		// only change the state from UNDEF to HIGH if
		// the new state is high
		// this is to ensure that we know what state we are in
		// from the beginning. We might loose 1 whole period, pr init
		// but that is an acceptable risk
		if(new_state == states::HIGH)
		{
			m_current_state = new_state;
			m_last_state = states::MIDDLE;
		}
		return GE_NO_DATA;
	}
	inline general_err_t setNextState(const states& new_state)
	{
		if(isExpectedState(new_state))
		{
			m_last_state = m_current_state;
			m_current_state = new_state;

			if(m_current_state == states::HIGH)
			{
				m_counter++;
				NVS<NVS_TYPE>::write_u64("COUNTER", m_counter);
				return GE_OK;
			}
		}

		return GE_NO_DATA;
	}
	inline bool isExpectedState(const states& new_state)
	{
		if(new_state == states::HIGH and m_current_state == states::MIDDLE and
		   m_last_state == states::LOW)
		{
			return true;
		}
		if(new_state == states::MIDDLE and m_current_state == states::HIGH and
		   m_last_state == states::MIDDLE)
		{
			return true;
		}
		if(new_state == states::LOW and m_current_state == states::MIDDLE and
		   m_last_state == states::HIGH)
		{
			return true;
		}
		if(new_state == states::MIDDLE and m_current_state == states::LOW and
		   m_last_state == states::MIDDLE)
		{
			return true;
		}
		return false;
	}
	const uint64_t m_high_threshold;
	const uint64_t m_low_threshold;
	states m_current_state;
	states m_last_state;
	states m_next_expected;
	uint64_t m_counter;
	static constexpr std::uint_fast8_t PERIODE_SCALER = 1;
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__

class friend_PeriodeEstimator
{
  public:
	explicit friend_PeriodeEstimator(PeriodeEstimator<100, 10, NVS_MOCK>* sensor)
		: m_sensor{sensor} {};
	~friend_PeriodeEstimator(){};
	auto decideStateChange(const PeriodeEstimator<100, 10, NVS_MOCK>::states& state)
	{
		return m_sensor->decideStateChange(state);
	}
	auto setInitialState(const PeriodeEstimator<100, 10, NVS_MOCK>::states& state)
	{
		return m_sensor->setInitialState(state);
	}
	auto setNextState(const PeriodeEstimator<100, 10, NVS_MOCK>::states& state)
	{
		return m_sensor->setNextState(state);
	}
	auto getCurrentState()
	{
		return m_sensor->m_current_state;
	}
	auto getLastState()
	{
		return m_sensor->m_last_state;
	}
	void setCurrentState(const PeriodeEstimator<100, 10, NVS_MOCK>::states& state)
	{
		m_sensor->m_current_state = state;
	}
	void setLastState(const PeriodeEstimator<100, 10, NVS_MOCK>::states& state)
	{
		m_sensor->m_last_state = state;
	}

  private:
	PeriodeEstimator<100, 10, NVS_MOCK>* m_sensor;
};
#endif

#endif //_COMPONENTS_ANALYSISTOOLS_PERIODESTIMATOR_INCLUDE_PERIODEESTIMATOR_HPP_