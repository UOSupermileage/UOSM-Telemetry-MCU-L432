/*
 * InternalCommsTask.c
 *
 *  Created on: Sep 10, 2022
 *      Author: mingy
 */


#include "CANMessageLookUpModule.h"
#include "InternalCommsTask.h"
#include "InternalCommsModule.h"
#include "SerialDebugDriver.h"
#include "DataAggregation.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define ICOMMS_STACK_SIZE 128*8
#define INTERNAL_COMMS_TASK_PRIORITY (osPriority_t) osPriorityRealtime1
#define TIMER_INTERNAL_COMMS_TASK 200UL

//#define UNDERVOLTAGE_BROADCAST_RATE 3
#define VOLTAGE_BROADCAST_RATE 5

const char ICT_TAG[] = "#ICT:";

PUBLIC void InitInternalCommsTask(void);
PRIVATE void InternalCommsTask(void *argument);

osThreadId_t InternalCommsTaskHandle;
const osThreadAttr_t InternalCommsTask_attributes = {
	.name = "InternalCommunications",
	.stack_size = ICOMMS_STACK_SIZE,
	.priority = INTERNAL_COMMS_TASK_PRIORITY,
};

PUBLIC void InitInternalCommsTask(void)
{
	InternalCommsTaskHandle = osThreadNew(InternalCommsTask, NULL, &InternalCommsTask_attributes);

}
PRIVATE void InternalCommsTask(void *argument)
{
	uint32_t cycleTick = osKernelGetTickCount();
	DebugPrint("icomms");

//	const ICommsMessageInfo* eventInfo = CANMessageLookUpGetInfo(EVENT_DATA_ID);
//	uint8_t undervoltageTxCounter = 0;

	const ICommsMessageInfo* voltageInfo = CANMessageLookUpGetInfo(VOLTAGE_DATA_ID);
	uint8_t voltageTxCounter = 0;

	IComms_Init();
	for(;;)
	{
		cycleTick += TIMER_INTERNAL_COMMS_TASK;
		osDelayUntil(cycleTick);

		DebugPrint("Checking for icomms");
		IComms_PeriodicReceive();

//		undervoltageTxCounter++;
//		if (undervoltageTxCounter == UNDERVOLTAGE_BROADCAST_RATE) {
//			if (SystemGetUndervoltage()) {
//				DebugPrint("%s Sending Undervoltage!", ICT_TAG);
//			}
//
//			iCommsMessage_t undervoltageTxMsg = IComms_CreateEventMessage(eventInfo->messageID, UNDERVOLTAGE, SystemGetUndervoltage());
//			result_t r = IComms_Transmit(&undervoltageTxMsg);
//			undervoltageTxCounter = 0;
//		}

		voltageTxCounter++;
		if (voltageTxCounter == VOLTAGE_BROADCAST_RATE) {
			iCommsMessage_t voltageTxMsg = IComms_CreatePercentageMessage(voltageInfo->messageID, SystemGetBatteryVoltage());
			result_t r = IComms_Transmit(&voltageTxMsg);
			voltageTxCounter = 0;
		}
	}
}
