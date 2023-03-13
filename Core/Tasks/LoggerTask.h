/*
 * LoggerTask.h
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 */

#ifndef TASKS_LOGGERTASK_H_
#define TASKS_LOGGERTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"


PUBLIC void InitLoggerTask(void);
PRIVATE void LoggerTask(void *argument);

#endif /* TASKS_LOGGERTASK_H_ */
