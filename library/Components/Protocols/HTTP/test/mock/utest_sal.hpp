#ifndef _COMPONENTS_PROTOCOLS_HTTP_TEST_MOCK_UTEST_SAL_HPP_
#define _COMPONENTS_PROTOCOLS_HTTP_TEST_MOCK_UTEST_SAL_HPP_
/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  @file  utest_sal.hpp
 |
 |  @author        :  Nikolaj Gliese Pedersen
 |  @email         :  <nikolaj.gliese.pedersen@dansac.com>
 |  @date		   : 2022-01-07
 |
 |  @brief  	   :  This class, utest_sal.hpp, is designed as:
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
#include "../../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/

#include <iostream>

/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class utest_sal
{
#ifdef __UNITTEST__
	friend class friend_utest_sal;
#endif
  public:
	utest_sal(const std::string& server){};
	~utest_sal() = default;
	general_err_t initialize()
	{
		return GE_OK;
	};
	general_err_t open()
	{
		return GE_OK;
	};
	general_err_t close()
	{
		return GE_OK;
	};
	general_err_t post(const std::string& str)
	{
		std::cout << "posting : " << str << "\n";
		return GE_OK;
	};

  private:
};

/*------------------------------------------------------------------------------+
 |   		 				 Unit Test Class               		                |
 +------------------------------------------------------------------------------*/

#ifdef __UNITTEST__
class friend_utest_sal
{
  public:
	explicit friend_utest_sal(utest_sal* sensor) : m_sensor{sensor} {};
	~friend_utest_sal();

  private:
	utest_sal* m_sensor;
};
#endif

#endif //_COMPONENTS_PROTOCOLS_HTTP_TEST_MOCK_UTEST_SAL_HPP_
