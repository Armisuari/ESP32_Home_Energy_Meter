#pragma once

#include <sdkconfig.h>

#ifdef ARDUINO_ARCH_ESP32
    #include "esp32-hal-log.h"
#endif

#ifndef CONFIG_WIFI_HANDLER_LOG_TAG
#define CONFIG_WIFI_HANDLER_LOG_TAG                 "WIFIHANDLER"
#endif /* CONFIG_WIFI_HANDLER_LOG_TAG */
#define WIFIHANDLERTAG CONFIG_WIFI_HANDLER_LOG_TAG

#ifndef CONFIG_WIFI_HANDLER_TASK_PRIO
#define CONFIG_WIFI_HANDLER_TASK_PRIO               1                       // default task Priority 1
#endif /* CONFIG_WIFI_HANDLER_TASK_PRIO */

#ifndef CONFIG_WIFI_HANDLER_TASK_NAME
#define CONFIG_WIFI_HANDLER_TASK_NAME               "WIFIHANDLERTASK"       // default task tag name
#endif /* CONFIG_WIFI_HANDLER_TASK_NAME */

#ifndef CONFIG_WIFI_HANDLER_TASK_STACK
#define CONFIG_WIFI_HANDLER_TASK_STACK               (4096)                 // 4KB task memory alloc
#endif /* CONFIG_WIFI_HANDLER_TASK_STACK */