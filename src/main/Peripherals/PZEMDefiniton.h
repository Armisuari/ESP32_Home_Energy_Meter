#pragma once

#include <sdkconfig.h>

#ifdef ARDUINO_ARCH_ESP32
    #include "esp32-hal-log.h"
#endif

#ifndef CONFIG_PZEM004T_LOG_TAG
#define CONFIG_PZEM004T_LOG_TAG                 "PZEM004T"
#endif /* CONFIG_PZEM004T_LOG_TAG */
#define PZEM004TTAG CONFIG_PZEM004T_LOG_TAG

#ifndef CONFIG_PZEM004T_TASK_PRIO
#define CONFIG_PZEM004T_TASK_PRIO               1                       // default task Priority 1
#endif /* CONFIG_PZEM004T_TASK_PRIO */

#ifndef CONFIG_PZEM004T_TASK_NAME
#define CONFIG_PZEM004T_TASK_NAME               "PZEM004T-TASK"       // default task tag name
#endif /* CONFIG_PZEM004T_TASK_NAME */

#ifndef CONFIG_PZEM004T_TASK_STACK
#define CONFIG_PZEM004T_TASK_STACK               (4096)                 // 4KB task memory alloc
#endif /* CONFIG_PZEM004T_TASK_STACK */

#ifndef CONFIG_PZEM004T_SERIAL
#define CONFIG_PZEM004T_SERIAL                  Serial2                 // Rx Pin GPIO
#endif /* CONFIG_PZEM004T_SERIAL */


#ifndef CONFIG_PZEM004T_RX_PIN
#define CONFIG_PZEM004T_RX_PIN                   (16)                 // Rx Pin GPIO
#endif /* CONFIG_PZEM004T_RX_PIN */

#ifndef CONFIG_PZEM004T_TX_PIN
#define CONFIG_PZEM004T_TX_PIN                   (17)                 // Tx Pin GPIO
#endif /* CONFIG_PZEM004T_TX_PIN */

#ifndef CONFIG_PZEM004T_NUM
#define CONFIG_PZEM004T_NUM                      (2)                 // Number of PZEM device
#endif /* CONFIG_PZEM004T_NUM_PZEMS */