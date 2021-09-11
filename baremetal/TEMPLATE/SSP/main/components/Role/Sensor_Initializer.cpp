/*
 * Sensor_Initializer.cpp
 *
 *  Created on: Mar 5, 2021
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
 *  \file       Sensor_Initializer.cpp
 *  \author     N.G Pedersen <nikolajgliese@tutanota.com>
 *  \version    1.0
 *  \date       2021
 *  \copyright  --
 *
 *
 ***********************************************************************************************/


#include "include/Sensor_Initializer.hpp"

#ifdef __UNITTEST__
#define GPIO_NUM_5 (5)
#define GPIO_NUM_26 (26)
#define GPIO_NUM_25 (25)
#endif

//#define DEBUG // default uncommeted

#ifdef DEBUG
static const char *LOG_TAG = "Sensor_Initializer";
#endif

Sensor_Initializer::Sensor_Initializer() {
}

Sensor_Initializer::~Sensor_Initializer() {
}

general_err_t Sensor_Initializer::run(void) {


#ifdef __ESP32__
        for(;;) // we must not exit the main thread
        {

            vTaskDelay(100000);

        }
#endif
}
