/*
 * Message_Protocol.hpp
 *
 *  Created on: Aug 20, 2020
 *      Author: espenv
 */

#ifndef MAIN_COMPONENTS_DATA_PACKAGE_INCLUDE_MESSAGE_PROTOCOL_HPP_
#define MAIN_COMPONENTS_DATA_PACKAGE_INCLUDE_MESSAGE_PROTOCOL_HPP_


/*------------------------------------------------------------------------------+
 |   		 	C L A S S   I N F O R M A T I O N                               |
 +------------------------------------------------------------------------------+
 |  ToDo: check auto generated function comment
 |
 |  Function Name:  Message_Protocol.hpp
 |
 |  Author       :  Nikolaj Gliese Pedersen
 |  Email 		 :  <nikolajgliese@tutanota.com>
 |
 |  Description  :  This class, Message_Protocol.hpp, is designed as:
 |
 |
 |
 |
 |
 |
 |
 |  version       : 1.0
 |
 |  Return Value  :   return_type
 |
 +-----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------+
 |   		 					Datasheet Awareness              		        |
 +------------------------------------------------------------------------------+
 |
 |
 |  Datasheet Awareness 1):
 |  	Link:[ ], Aug 20, 2020
 |		Brief:
 |
 |  Datasheet Awareness 2):
 |  	Link:[ ], Aug 20, 2020
 |
 |		Brief:
 |
 |
 |
 |
 |
  +-----------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------+
 |   		 					Includes                     		            |
 +------------------------------------------------------------------------------*/

/*----------------- DEFAULT INCLUDE -------------------------------------------*/
#include "../../../Global_Include/BASIC.hpp"
#include "../../../Objects/ErrorHandler/include/General_Error.hpp"
/*-----------------------------------------------------------------------------*/


#include <vector>



/*------------------------------------------------------------------------------+
 |                               Typedef                                        |
 +------------------------------------------------------------------------------*/


struct msg_control_t{
    uint16_t id;   // sensor id
    uint8_t flag; // quality flag
};

struct msg_data_t{
    float data = 0;
    timeval time_stamp;
};

enum msg_cnt_flag_t{
    STATUS_OK=0,RTC_REQUEST,RTC_RESPONSE
};

/*------------------------------------------------------------------------------+
 |   		 					 Class                     		                |
 +------------------------------------------------------------------------------*/

class Message_Protocol {
public:
        Message_Protocol(const msg_control_t& cnt,const msg_data_t& data);
        Message_Protocol();
        ~Message_Protocol();
        general_err_t setControl(const msg_control_t& cnt);
        const msg_control_t& getControl(void) const;
        general_err_t addData(const msg_data_t& data);
        const std::vector<msg_data_t> &  getBuffer(void) const;
        general_err_t clear(void);
        general_err_t toString(std::string * str) const;
        bool  isValid(void) const;
        inline static size_t parameterCount(void) { return 5; }; // id + flag + 2xtime + data = 5
        inline static size_t controlParameterCount(void) { return 2; }; // id + flag  = 2
        inline static size_t dataParameterCount(void) { return 3; }; // 2xtime + data = 3
private:
        msg_control_t m_control;
        std::vector<msg_data_t> m_buffer;
        bool m_initialized = false;
        bool m_valid = false;
};
#endif /* MAIN_COMPONENTS_DATA_PACKAGE_INCLUDE_MESSAGE_PROTOCOL_HPP_ */
