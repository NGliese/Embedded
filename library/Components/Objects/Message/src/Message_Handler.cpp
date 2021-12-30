/*
 * Message_Handler.cpp
 *
 *  Created on: Aug 25, 2020
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
 *  \file       Message_Handler.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2020
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/Message_Handler.hpp"

#define MAX_SIZE (1)
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "Message_Handler";
#endif

/**
 * @brief  Convert the message to a postgres sql format
 *
 *
 * @param[in] const Message_Protocol& msg
 * @param[in]
 *
 * @param[out] std::string* str
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Message_Handler::to_Postgres_Format(
        const Message_Protocol& msg, std::string* str) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Message_Handler::to_Postgres_Format >> ");
    #endif
    // Executable code:
    // Executable code:
     if(!msg.isValid())
     {
         return GE_EMPTY;
     }
     if(msg.getBuffer().size() > MAX_SIZE)
     {
         return GE_OVERFLOW;
     }
     // clear the string
     str->clear();


     tm * time_now = gmtime (&msg.getBuffer().at(0).time_stamp.tv_sec);
      char buffer [80];
      strftime(buffer, 80, "'%Y-%m-%dT%H:%M:%S", time_now);

      char currentTime[84] = "";
      sprintf(currentTime, "%s.%ldZ'", buffer, (msg.getBuffer().at(0).time_stamp.tv_usec) );

      str->append("INSERT INTO public.datapoints (tstz,entity_id,value) VALUES(");
      // timestamp
      str->append(currentTime);
      str->append(",");
      // Sensor id
      str->append(std::to_string( msg.getControl().id ) );
      str->append(",");

      // data, with 4 precision
      str->append(std::to_string( msg.getBuffer().at(0).data ) );
      str->append(");");

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Message_Handler::to_Postgres_Format << ");
    #endif

    return GE_OK;
}

const std::string Message_Handler::to_Postgres_Form(
        const Message_Protocol& msg) {
    std::string str;
    // Executable code:
    if(!msg.isValid())
    {
        std::cout << "NOT VALID DATA \n";
        return "";
    }
    if(msg.getBuffer().size() > MAX_SIZE)
    {
        std::cout << "BUFFER OVERFLOW \n";
        return "";
    }

    tm * time_now = gmtime (&msg.getBuffer().at(0).time_stamp.tv_sec);
     char buffer [80];
     strftime(buffer, 80, "'%Y-%m-%dT%H:%M:%S", time_now);

     char currentTime[84] = "";
     sprintf(currentTime, "%s.%ldZ'", buffer, (msg.getBuffer().at(0).time_stamp.tv_usec) );

     str.append("INSERT INTO public.datapoints (tstz,entity_id,value) VALUES(");
     // timestamp
     str.append(currentTime);
     str.append(",");
     // Sensor id
     str.append(std::to_string( msg.getControl().id ) );
     str.append(",");

     // data, with 4 precision
     str.append(std::to_string( msg.getBuffer().at(0).data ) );
     str.append(");");

     return str;
}

const std::string Message_Handler::to_Postgres_Subject(
        const Message_Protocol& msg) {
    std::string str;
    // Executable code:
    if(!msg.isValid())
    {
      std::cout << "NOT VALID DATA \n";
      return "";
    }
    if(msg.getBuffer().size() > MAX_SIZE)
    {
      std::cout << "BUFFER OVERFLOW \n";
      return "";
    }

    tm * time_now = gmtime (&msg.getBuffer().at(0).time_stamp.tv_sec);
    char buffer [80];
    strftime(buffer, 80, "'%Y-%m-%dT%H:%M:%S", time_now);

    char currentTime[84] = "";
    sprintf(currentTime, "%s.%ldZ'", buffer, (msg.getBuffer().at(0).time_stamp.tv_usec) );

    str.append("(");
    // timestamp
    str.append(currentTime);
    str.append(",");
    // Sensor id
    str.append(std::to_string( msg.getControl().id ) );
    str.append(",");

    // data, with 4 precision
    str.append(std::to_string( msg.getBuffer().at(0).data ) );
    str.append(")");

    return str;
}
