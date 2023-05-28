/*
 * BatteryTask.c
 *
 *  Created on: May 9, 2023
 *      Author: Jeremy Cote
 *
 *
 */

#include "BatteryTask.h"
#include "ADCDriver.h"

#define STACK_SIZE 128 * 4
#define BATTERY_TASK_PRIORITY (osPriority_t) osPriorityHigh1
#define TIMER_BATTERY_TASK 100UL

const char BAT_TAG[] = "#BAT:";

PUBLIC void InitBatteryTask(void);
PRIVATE void BatteryTask(void *argument);

osThreadId_t BatteryTaskHandle;
const osThreadAttr_t BatteryTask_attributes = {
    .name = "BatteryTask",
    .stack_size = STACK_SIZE,
    .priority = BATTERY_TASK_PRIORITY,
};

PUBLIC void InitBatteryTask(void) { BatteryTaskHandle = osThreadNew(BatteryTask, NULL, &BatteryTask_attributes); }
PRIVATE void BatteryTask(void *argument) {
    uint32_t cycleTick = osKernelGetTickCount();
    DebugPrint("battery");

    for (;;) {
        cycleTick += TIMER_BATTERY_TASK;
        osDelayUntil(cycleTick);

        DebugPrint("%s battery loop", BAT_TAG);
        ADCBatteryPeriodicJob();
    }
}
