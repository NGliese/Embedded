/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <BASIC.hpp>

#include "./integration_test/include/main_integration.hpp"

#include <nvs_flash.h>

#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
void app_main(void);
// Your prototype or Definition
#ifdef __cplusplus
}
#endif

void app_main(void)
{

#ifdef __UNITTEST__
    sleep(5);
    std::cout << "!!! WE ARE IN UNIT TEST MODE !!! \n";
    sleep(5);
    std::cout << "!!! WE ARE IN UNIT TEST MODE !!! \n";
    sleep(5);
    std::cout << "!!! WE ARE IN UNIT TEST MODE !!! \n";
    sleep(5);
    std::cout << "!!! WE ARE IN UNIT TEST MODE !!! \n";
#endif

#ifdef __ESP32__
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
#endif

    std::cout << "resulting run :: " << runnable() << "\n";


}
