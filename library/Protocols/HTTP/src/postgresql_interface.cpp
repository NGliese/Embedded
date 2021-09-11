/*
 * postgres_interface.cpp
 *
 *  Created on: Dec 29, 2020
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
 *  \file       postgres_interface.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2020
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/postgresql_interface.hpp"


#ifdef __RPI__
#ifdef __DATABASE__
 static pqxx::connection m_connect("dbname = sensordb user = write2db password = 1234 \
         hostaddr = 192.168.1.157 port = 5432");
#endif
#endif

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "postgresql_interface";
#endif

postgresql_interface::~postgresql_interface() {
    close();
}

general_err_t postgresql_interface::open(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> postgresql_interface::open >> ");
    #endif
    // Executable code:
#ifdef __RPI__
#ifdef __DATABASE__
try{
    m_connect = pqxx::connection("dbname = sensordb user = write2db password = 1234 \
            hostaddr = 192.168.1.157 port = 5432");


} catch (const std::exception &e) {
   std::cerr << e.what() << std::endl;
   return GE_FAIL;
}
#endif
#endif
    m_open = true;

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< postgresql_interface::open << ");
    #endif

    return GE_OK;

}

general_err_t postgresql_interface::post(const std::string& str) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> postgresql_interface::close >> ");
    #endif
    // Executable code:

 //   std::cout << " sql querey : " << str << "\n";
#ifdef __RPI__
#ifdef __DATABASE__
try{
    if (!m_connect.is_open()) {
       std::cout << "Can't open database" << std::endl;
       return GE_NOT_CONNECTED;
    }
    /* Create a transactional object. */
    pqxx::work W(m_connect);

      /* Execute SQL query */
      W.exec( str.c_str() );
      W.commit();
   } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
      return GE_FAIL;
   }
#endif
#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< postgresql_interface::close << ");
    #endif

    return GE_OK;
}

general_err_t postgresql_interface::close(void) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> postgresql_interface::close >> ");
    #endif
    // Executable code:
    m_open = false;
#ifdef __RPI__
#ifdef __DATABASE__
    try{
    m_connect.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return GE_FAIL;
     }
#endif
#endif
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< postgresql_interface::close << ");
    #endif

    return GE_OK;
}
