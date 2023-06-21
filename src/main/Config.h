#pragma once

#include <Wire.h>

#ifdef ARDUINO_ARCH_ESP32
    #include "esp32-hal-log.h"
#endif

// const char *ssid = "eFisheryFS";
// const char *password = "123123123";

const char *ssid = "Tangga 1";//"Dapur 2";
const char *password = "bandungsatu";//"cirebondua";

#define CONFIG_CALCULATION_INTERVAL_H             (1000*60*60UL)
#define CONFIG_CALCULATION_INTERVAL_S             (500)

#define CONFIG_KOST_PERTAMA                     (0)

#define CONFIG_KOST_KEDUA                       (1)

#ifndef CONFIG_MAIN_LOG_TAG
#define CONFIG_MAIN_LOG_TAG                 "MAIN"
#endif /* CONFIG_MAIN_LOG_TAG */
#define MAINTAG CONFIG_MAIN_LOG_TAG