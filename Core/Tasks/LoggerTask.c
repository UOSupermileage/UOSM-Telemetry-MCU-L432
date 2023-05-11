/*
 * LoggerTask.c
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 *
 *      https://mevihub.com/stm32-realtime-clock-example/
 */


#include "LoggerTask.h"

#include "SerialLogDriver.h"

#include "DataAggregation.h"

#define STACK_SIZE 128*8
#define LOGGER_TASK_PRIORITY (osPriority_t) osPriorityRealtime
#define TIMER_LOGGER_TASK 100UL

const char TAG[] = "#LGT:";

extern RTC_HandleTypeDef hrtc;

PUBLIC void InitLoggerTask(void);
PRIVATE void LoggerTask(void *argument);

osThreadId_t LoggerTaskHandle;
const osThreadAttr_t LoggerTask_attributes = {
	.name = "Logger",
	.stack_size = STACK_SIZE,
	.priority = LOGGER_TASK_PRIORITY,
};

PUBLIC void InitLoggerTask(void)
{

	LoggerTaskHandle = osThreadNew(LoggerTask, NULL, &LoggerTask_attributes);

}
PRIVATE void LoggerTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("logger");

	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

//	SerialLogln("timestamp,throttle,speed,rpm,current,voltage,throttleTooHigh,motorInitializing,clockState,lastDeadman");

	for(;;)
	{
		cycleTick += TIMER_LOGGER_TASK;
		osDelayUntil(cycleTick);

		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

		// Required for the time to be unlocked and continue incrementing
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		SerialLogln("%02d.%02d.%02d,%d,%d,%d,%d,%d,%d,%d,%d,%02d.%02d.%02d", sTime.Hours, sTime.Minutes ,sTime.Seconds, SystemGetThrottle(), SystemGetSpeed(), SystemGetMotorRPM(), SystemGetCurrent(), SystemGetBatteryVoltage(), SystemGetThrottleTooHigh(), SystemGetMotorInitializing(), SystemGetClockState(), SystemGetDeadmanTimestampHours(), SystemGetDeadmanTimestampMinutes(), SystemGetDeadmanTimestampSeconds());
		DebugPrint("%02d.%02d.%02d,%d,%d,%d,%d,%d,%d,%d,%d,%02d.%02d.%02d", sTime.Hours, sTime.Minutes ,sTime.Seconds, SystemGetThrottle(), SystemGetSpeed(), SystemGetMotorRPM(), SystemGetCurrent(), SystemGetBatteryVoltage(), SystemGetThrottleTooHigh(), SystemGetMotorInitializing(), SystemGetClockState(), SystemGetDeadmanTimestampHours(), SystemGetDeadmanTimestampMinutes(), SystemGetDeadmanTimestampSeconds());
	}

}
