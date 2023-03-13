/*
 * LoggerModule.h
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 */

#ifndef MODULES_LOGGERMODULE_H_
#define MODULES_LOGGERMODULE_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

#include "ApplicationTypes.h"

#define LOGGER_QUEUE_LENGTH 10
#define LOGGER_BLOCKING_TIME 0

PUBLIC void LoggerInit();
PUBLIC result_t LoggerEnqueue(iCommsMessage_t* msg);
PUBLIC result_t LoggerDequeue(iCommsMessage_t* msg);

#endif /* MODULES_LOGGERMODULE_H_ */
