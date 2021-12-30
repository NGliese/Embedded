/*
 * http_interface.cpp
 *
 *  Created on: Aug 25, 2020
 *      Author: espenv
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
 *  \file       http_interface.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2020
 *  \copyright  --
 *
 *
 ***********************************************************************************************/

#include "../include/http_interface.hpp"

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char* LOG_TAG = "http_interface";
#endif

http_interface::http_interface(const std::string& server) : m_sal{server} {}

http_interface::~http_interface() {}

/**
 * @brief    initialize the block
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t http_interface::initialize(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> http_interface::initialize >> ");
#endif
	// Executable code:
	if(m_sal.initialize() != GE_OK)
	{
		return GE_FAIL;
	}
	m_initialized = true;

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< http_interface::initialize << ");
#endif

	return GE_OK;
}
/**
 * @brief Open the connection
 *
 * @attention
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t http_interface::open(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> http_interface::open >> ");
#endif
	// Executable code:
	if(!m_initialized)
	{
		return GE_NOT_INITIALIZED;
	}
	if(m_sal.rpi_open() != GE_OK)
	{
		return GE_FAIL;
	}

	m_open = true;

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< http_interface::open << ");
#endif

	return GE_OK;
}
/**
 * @brief      Close the connection
 *
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t http_interface::close(void)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> http_interface::close >> ");
#endif
	// Executable code:
	if(!m_initialized)
	{
		return GE_NOT_INITIALIZED;
	}

	if(m_sal.rpi_close() != GE_OK)
	{
		return GE_FAIL;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< http_interface::close << ");
#endif

	return GE_OK;
}
/**
 * @brief      publish the content
 *
 * @attention
 *
 *
 * @param[in] const std::string& str
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t http_interface::post(const std::string& str)
{
#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, ">> http_interface::publish >> ");
#endif
	// Executable code:
	if(!m_initialized)
	{
		return GE_NOT_INITIALIZED;
	}

#ifdef DEBUG
	LOG_PRINT_INFO(LOG_TAG, "<< http_interface::publish << ");
#endif

	return m_sal.rpi_publish(str);
}
