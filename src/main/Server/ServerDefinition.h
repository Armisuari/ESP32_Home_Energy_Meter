#pragma once

#include <sdkconfig.h>

#ifndef CONFIG_SERVER_HANDLER_LOG_TAG
#define CONFIG_SERVER_HANDLER_LOG_TAG                 "SERVERHANDLER"
#endif /* CONFIG_SERVER_HANDLER_LOG_TAG */
#define SERVERHANDLERTAG CONFIG_SERVER_HANDLER_LOG_TAG

#ifndef CONFIG_SPIFFS_LOG_TAG
#define CONFIG_SPIFFS_LOG_TAG                 "SPIFFS"
#endif /* CONFIG_SPIFFS_LOG_TAG */
#define SPIFFSTAG CONFIG_SPIFFS_LOG_TAG

#ifndef CONFIG_SERVER_HANDLER_TASK_PRIO
#define CONFIG_SERVER_HANDLER_TASK_PRIO               5                       // default task Priority 1
#endif /* CONFIG_SERVER_HANDLER_TASK_PRIO */

#ifndef CONFIG_SERVER_HANDLER_TASK_NAME
#define CONFIG_SERVER_HANDLER_TASK_NAME               "SERVERHANDLERTASK"       // default task tag name
#endif /* CONFIG_SERVER_HANDLER_TASK_NAME */

#ifndef CONFIG_SERVER_HANDLER_TASK_STACK
#define CONFIG_SERVER_HANDLER_TASK_STACK               (1024 * 10)                 // 4KB task memory alloc
#endif /* CONFIG_SERVER_HANDLER_TASK_STACK */

#ifndef CONFIG_SERVER_HANDLER_SERVER_PORT
#define CONFIG_SERVER_HANDLER_SERVER_PORT               (80)                 // Port 80
#endif /* CONFIG_SERVER_HANDLER_SERVER_PORT */

#ifndef CONFIG_SERVER_HANDLER_SERVER_PRICE
#define CONFIG_SERVER_HANDLER_SERVER_PRICE               (1.352)     // for 900 VA users            // Port 80
#endif /* CONFIG_SERVER_HANDLER_SERVER_PRICE */

// 1352
//------
// 1000