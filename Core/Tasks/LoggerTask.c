/*
 * LoggerTask.c
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 */


#include "LoggerTask.h"
#include "LoggerModule.h"
#include "SDCardDriver.h"
#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*8
#define LOGGER_TASK_PRIORITY (osPriority_t) osPriorityRealtime
#define TIMER_LOGGER_TASK 1000UL

const char TAG[] = "#LGT:";

PUBLIC void InitLoggerTask(void);
PRIVATE void LoggerTask(void *argument);

osThreadId_t LoggerTaskHandle;
const osThreadAttr_t LoggerTask_attributes = {
	.name = "Logger",
	.stack_size = STACK_SIZE,
	.priority = LOGGER_TASK_PRIORITY,
};

PUBLIC uint32_t readMsg(iCommsMessage_t *msg) {
	int32_t value = msg->data[msg->dataLength - 1];

	for (int i = msg->dataLength - 1; i > 0; i--) {
		value <<= 8;
		value |= msg->data[i -1];
	}

	return value;
}

PUBLIC void InitLoggerTask(void)
{

	LoggerTaskHandle = osThreadNew(LoggerTask, NULL, &LoggerTask_attributes);

}
PRIVATE void LoggerTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("logger");

	LoggerInit();

	iCommsMessage_t msg;

	cycleTick += 1000;
	osDelayUntil(cycleTick);


	SDInit();

	const char* filename = SDGetFreeFilename();

	DebugPrint("Logging: ID,Length,Data");
	SDAppend(filename, "ID,Data");
	DebugPrint("Done append");

	for(;;)
	{
		cycleTick += TIMER_LOGGER_TASK;
		osDelayUntil(cycleTick);
//
		if (LoggerDequeue(&msg) == RESULT_OK) {
			uint32_t d = readMsg(&msg);
			DebugPrint("%d,%d", msg.standardMessageID, d);
			SDAppend(filename, "%d,%d", msg.standardMessageID, d);
		} else {
			DebugPrint("Nothing to write...");
		}
	}

	// Demount the drive
//	res = f_mount(NULL, "/", 0);
//	if (res != FR_OK) {
//		DebugPrint("%s Failed to unmount drive", TAG);
//		return RESULT_FAIL;
//	} else {
//		DebugPrint("%s Unmounted drive", TAG);
//	}

}
