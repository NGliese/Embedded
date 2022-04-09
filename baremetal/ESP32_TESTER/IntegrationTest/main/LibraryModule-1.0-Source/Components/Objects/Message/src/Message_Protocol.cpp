/*
 * Message_Protocol.cpp
 *
 *  Created on: Aug 20, 2020
 *      Author: nikolaj
 */

/***********************************************************************************************+
 *  \brief       -- XX -- Library - CPP Source file
 *  \par
 *  \par        @DETAILS
 *
 *
 *  \li         LIMITATION-TO-CLASS
 *  \li         LIMITATION-TO-CLASS
 *
 *  \note       ANY RELEVANT NOTES
 *
 *  \file       Message_Protocol.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2020
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/Message_Protocol.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "Message_Protocol";
#endif

Message_Protocol::Message_Protocol() {}

Message_Protocol::Message_Protocol(const msg_control_t& cnt, const msg_data_t& data)
	: m_control{cnt}, m_initialized{true}
{
	m_buffer.push_back(data);
}

Message_Protocol::~Message_Protocol() {}

/**
 * @brief   set the control parameters
 *
 *
 * @param[in] const msg_control_t& cnt
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Message_Protocol::setControl(const msg_control_t& cnt)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> enclosing_method >> ");
#endif
	// Executable code:

	m_control = cnt;
	// we are now initialized
	m_initialized = true;

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< enclosing_method << ");
#endif

	return GE_OK;
}
/**
 * @brief      add data to the buffer
 *
 * @param[in] const msg_data_t<T>& data
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */

general_err_t Message_Protocol::addData(const msg_data_t& data)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> enclosing_method >> ");
#endif
	// Executable code:
	if(!m_initialized)
	{
		return GE_NOT_INITIALIZED;
	}
	m_buffer.push_back(data);

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< enclosing_method << ");
#endif

	return GE_OK;
}
/**
 * @brief  get the buffer
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
const std::vector<msg_data_t>& Message_Protocol::getBuffer(void) const
{
	return m_buffer;
}

/**
 * @brief get the control parameter
 *
 *
 * @return
 *    - N/A
 *    -
 *    -
 */
const msg_control_t& Message_Protocol::getControl(void) const
{
	return m_control;
}
/**
 * @brief  clear the buffer and uninitialize the package
 *
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Message_Protocol::clear(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Message_Protocol::clear >> ");
#endif
	// Executable code:
	m_initialized = false;
	m_control = {0, 0};
	m_buffer.clear();

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Message_Protocol::clear << ");
#endif

	return GE_OK;
}
/**
 * @brief
 *
 * @attention
 *  [CONTROL PARAMS] [ BUFFER ....]
 * --------------------------------------------------------....
 * |        |       |         |        |        |       |
 * |    ID  |  Flag |   SEC   |  USEC  |  DATA  |  SEC  |
 * |        |       |         |        |        |       |
 * ---------------------------------------------------------.....
 *
 * @param[out] std::string* str
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Message_Protocol::toString(std::string* str) const
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> Message_Protocol::toString >> ");
#endif
	// clear the input parameter
	str->clear();
	// Executable code:
	str->append(std::to_string(m_control.id));
	str->append(",");
	str->append(std::to_string(m_control.flag));

	for(auto const& ele : m_buffer)
	{
		str->append(",");
		str->append(std::to_string(ele.time_stamp.tv_sec));
		str->append(",");
		str->append(std::to_string(ele.time_stamp.tv_usec));
		str->append(",");
		str->append(std::to_string(ele.data));
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< Message_Protocol::toString << ");
#endif

	return GE_OK;
}
/**
 * @brief    check if the protocol is valid
 *
 *
 * @return
 *    - N/A
 *    -
 *    -
 */
bool Message_Protocol::isValid(void) const
{
	return ((m_buffer.size() == 0) or !m_initialized) ? false : true;
}
