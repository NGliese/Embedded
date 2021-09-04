/*
 * mqtt_api_v2.cpp
 *
 *  Created on: May 31, 2021
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
 *  \file       mqtt_api_v2.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "../include/mqtt_api_v2.hpp"
static bool m_isSubscribed{false};
static std::atomic<bool> m_inUse{false};
static std::atomic<bool> m_connected{false};
static std::atomic<bool> m_initialized{false};
static  FreeRTOS::Semaphore m_semaphore = FreeRTOS::Semaphore("mqtt_publish");
static  FreeRTOS::Semaphore m_semaphore_subscribe = FreeRTOS::Semaphore("mqtt_subscribe");
static std::string m_data_recieved{""};
mqttclient m_client;
//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "mqtt_api_v2";
#endif

mqtt_api_v2::mqtt_api_v2( const std::string & uri ) : m_uri{uri}  {

    if(!m_initialized)
    {
        m_initialized = true;

        auto err = connect();
        if(!General_Error::check_error(err,"Cant initialize mqtt"))
        {
            exit(-1);
        }
        m_semaphore_subscribe.give();
        m_semaphore.give();
    }
}

mqtt_api_v2::~mqtt_api_v2() {
}

general_err_t mqtt_api_v2::connect(void) {

#ifdef DEBUG
 LOG_PRINT_INFO(LOG_TAG, ">> MQTT_API::connect >> ");
#endif




#ifdef __ESP32__

 esp_mqtt_client_config_t mqtt_cfg = {
         .uri =  m_uri.c_str(),
 };

 m_mqtt_cfg = mqtt_cfg;

 m_client = esp_mqtt_client_init(&m_mqtt_cfg);
 auto err = esp_mqtt_client_register_event(m_client, (esp_mqtt_event_id_t)ESP_EVENT_ANY_ID, &(mqtt_api_v2::mqtt_event_handler), m_client);

 if(err != ESP_OK)
 {
     return GE_FAIL;
 }

 err = esp_mqtt_client_start(m_client);
 if(err != ESP_OK)
 {
     return GE_FAIL;
 }
#endif

#ifdef __UNITTEST__
 m_connected = true;
#endif

 #ifdef DEBUG
 LOG_PRINT_INFO(LOG_TAG, "<< MQTT_API::connect << ");
 #endif

 return GE_OK;

}

general_err_t mqtt_api_v2::disconnect(void) {
#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, ">> MQTT_API::disconnect >> ");
#endif
// Executable code:


#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, "<< MQTT_API::disconnect << ");
#endif

return GE_OK;
}

general_err_t mqtt_api_v2::publish(const std::string& topic,
        const std::string& payload) {
#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, ">> MQTT_API::publish >> ");
#endif
// Executable code:
if(!m_connected)
{
    return GE_NOT_CONNECTED;
}

if(!m_semaphore.take(500,"publish"))
{
    return GE_SEMAPHORE_NOT_TAKEN;
}

#ifdef __ESP32__
esp_mqtt_client_publish(m_client, topic.c_str(), payload.c_str(), payload.size(), 1, 0);
#endif

m_semaphore.give();

#ifdef DEBUG
LOG_PRINT_INFO(LOG_TAG, "<< MQTT_API::publish << ");
#endif

return GE_OK;
}
/**
 * @brief
 *
 * @attention  THIS IS A SINGLETON FUNCTION WITH ONE (1) SUBSCRIBER UNIT
 *
 *
 * @param[in]
 * @param[in]
 *
 * @param[out]
 * @param[out]
 *
 * @return
 *    - GE_OK
 *    -
 *    -
 */
FreeRTOS::Semaphore*  mqtt_api_v2::subscribe(const std::string& topic ) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> mqtt_api_v2::subscribe >> ");
    #endif
    // take the semaphore
    if(!m_semaphore_subscribe.take(500,"subscribe init"))
    {
        return nullptr;
    }





#ifdef __ESP32__
esp_mqtt_client_subscribe(m_client, topic.c_str(), 0);
#endif
#ifdef __UNITTEST__
    // we are now subscribed
    m_isSubscribed = true;
#endif

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< mqtt_api_v2::subscribe << ");
    #endif
    // return a pointer of the semaphore for subscibtion handling
    return &m_semaphore_subscribe;
}

general_err_t mqtt_api_v2::getData(std::string* str) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> mqtt_api_v2::getData >> ");
    #endif
    // Executable code:
    if(!m_connected)
    {
        return GE_NOT_CONNECTED;
    }

    if(!m_isSubscribed)
    {
        return GE_FAIL;
    }

    *str = m_data_recieved;

    if(!m_semaphore_subscribe.take(500,"subscribe init"))
    {
        return GE_SEMAPHORE_NOT_TAKEN;
    }

    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< mqtt_api_v2::getData << ");
    #endif

    return GE_OK;
}

#ifdef __ESP32__
esp_err_t mqtt_api_v2::event_handler(mqttevent event) {
    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, ">> MQTT_API::event_handler >> ");
    #endif
    // Executable code:

    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " MQTT EVENT CONNECTED ");
            #endif

            m_connected = true;


            break;
        case MQTT_EVENT_DISCONNECTED:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " MQTT EVENT DISCONNECTED ");
            #endif
            m_connected = false;
            //esp_mqtt_client_start(client);
            sleep(10);// wait 10 sec, and then just exit program
            exit(-1);
            break;
        case MQTT_EVENT_SUBSCRIBED:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " MQTT EVENT SUBSCRIBED ");
            #endif
            // we are now subscribed
            m_isSubscribed = true;


            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " MQTT EVENT UNSUBSCRIBED ");
            #endif
            // we are now subscribed
            m_isSubscribed = false;


            break;
        case MQTT_EVENT_PUBLISHED:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " MQTT EVENT PUBLISHED ");
            #endif



            break;
        case MQTT_EVENT_DATA:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " MQTT EVENT DATA ");
            #endif
            m_data_recieved.assign(event->data,event->data_len);
            m_semaphore_subscribe.give();


            break;
        case MQTT_EVENT_ERROR:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " MQTT EVENT ERROR ");
            #endif



            break;
        default:
            #ifdef DEBUG
            LOG_PRINT_INFO(LOG_TAG, " UNKNOWN EVENT ");
            #endif

            break;
    }




    #ifdef DEBUG
    LOG_PRINT_INFO(LOG_TAG, "<< MQTT_API::event_handler << ");
    #endif
    return ESP_OK;
}
#endif
#ifdef __ESP32__
void mqtt_api_v2::mqtt_event_handler(void* handler_args, esp_event_base_t base,
        int32_t event_id, void* event_data) {
    event_handler((mqttevent)event_data);
}
#endif
