/*
 * BatteryTask.h
 *
 *  Created on: May 9, 2023
 *      Author: Jeremy Cote
 */

#ifndef TASKS_BATTERYTASK_H_
#define TASKS_BATTERYTASK_H_

// STM headers
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"

// Our headers
#include "ApplicationTypes.h"

PUBLIC void InitBatteryTask(void);
PRIVATE void BatteryTask(void *argument);

#endif /* TASKS_BATTERYTASK_H_ */
