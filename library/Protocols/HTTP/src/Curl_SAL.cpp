/*
 * Curl_SAL.cpp
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
 *  \file       Curl_SAL.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2020
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/Curl_SAL.hpp"

#define DB_CONNECTION_TIMEOUT (2)
#define DB_SEND_TIMEOUT       (2)
#define DATA_OK                  (0)
#define WITH_DATABASE_CONNECTION    (0)
#define MAX_DATA_VALUE           (10000)
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "Curl_SAL";
#endif

Curl_SAL::Curl_SAL(const std::string& server) : m_server{server} {
}

Curl_SAL::~Curl_SAL() {
#ifdef __RPI__
  /* always cleanup */
  curl_easy_cleanup(m_curl);
  curl_global_cleanup();
#endif

}
/**
 * @brief    initialize the block
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
general_err_t Curl_SAL::initialize(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Curl_SAL::initialize >> ");
    #endif
    // Executable code:
#ifdef __RPI__
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    /* get a curl handle */
    m_curl = curl_easy_init();
    // set timeout for connection
    curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT,DB_CONNECTION_TIMEOUT);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT,DB_SEND_TIMEOUT);
#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Curl_SAL::initialize << ");
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
general_err_t Curl_SAL::rpi_open(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Curl_SAL::rpi_close >> ");
    #endif
    // Executable code:


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Curl_SAL::rpi_close << ");
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
general_err_t Curl_SAL::rpi_close(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Curl_SAL::rpi_publish >> ");
    #endif
    // Executable code:


    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Curl_SAL::rpi_publish << ");
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
general_err_t Curl_SAL::rpi_publish(const std::string& str) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> Curl_SAL::rpi_publish >> ");
    #endif
    // Executable code:
#ifdef __RPI__
      CURLcode res;
        if(m_curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */

#endif
    // load server
    std::string local_server = m_server;
    // append http url
    local_server.append(str.c_str());

    std::cout << local_server << "\n";

#ifdef __RPI__
      // send url to curl
       curl_easy_setopt(m_curl, CURLOPT_URL, local_server.c_str());
       /* Perform the request, res will get the return code */
       res = curl_easy_perform(m_curl);
       /* Check for errors */
       if(res != CURLE_OK){
       fprintf(stderr, "curl_easy_perform() failed: %s\n",
          curl_easy_strerror(res));
          // return sad
       return GE_FAIL;
       }
    }

#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< Curl_SAL::rpi_publish << ");
    #endif

    return GE_OK;
}
