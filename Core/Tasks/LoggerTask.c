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
#define TIMER_LOGGER_TASK 100UL

const char TAG[] = "#LGT:";

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

	LoggerInit();

	const char* filename = "canLogs.csv";

	iCommsMessage_t msg;

	cycleTick += 1000;
	osDelayUntil(cycleTick);


	SDInit();

	DebugPrint("Logging: ID,Length,Data");
	SDAppend(filename, "ID,Length,Data\r\n");
	DebugPrint("Done append");

	for(;;)
	{
		cycleTick += TIMER_LOGGER_TASK;
		osDelayUntil(cycleTick);

//		if (LoggerDequeue(&msg) == RESULT_OK) {
//			DebugPrint("Logging: %d,%d,%x", msg.standardMessageID, msg.dataLength, msg.data);
//			SDAppend(filename, "%d,%d,%x/r/n", msg.standardMessageID, msg.dataLength, msg.data);
//		} else {
			DebugPrint("Nothing to write...");
//		}
	}
}
