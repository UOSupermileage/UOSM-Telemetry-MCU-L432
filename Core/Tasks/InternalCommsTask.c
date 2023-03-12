/*
 * InternalCommsTask.c
 *
 *  Created on: Sep 10, 2022
 *      Author: mingy
 */


//#include "CANMessageLookUpModule.h"
#include "InternalCommsTask.h"
#include "InternalCommsModule.h"
#include "CANMessageLookUpModule.h"
#include "DataAggregation.h"
#include "SerialDebugDriver.h"

// Function alias - replace with the driver api
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define STACK_SIZE 128*8
#define INTERNAL_COMMS_TASK_PRIORITY (osPriority_t) osPriorityRealtime
#define TIMER_INTERNAL_COMMS_TASK 50UL

#define THROTTLE_RATE 4

const char ICT_TAG[] = "#ICT:";

PUBLIC void InitInternalCommsTask(void);
PRIVATE void InternalCommsTask(void *argument);

osThreadId_t InternalCommsTaskHandle;
const osThreadAttr_t InternalCommsTask_attributes = {
	.name = "InternalCommunications",
	.stack_size = STACK_SIZE,
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
	//ICommsInit();
//	uint8_t testTxCounter = 0;

	const ICommsMessageInfo* throttleInfo = CANMessageLookUpGetInfo(THROTTLE_DATA_ID);
	uint8_t throttleTxCounter = 0;

	IComms_Init();
	for(;;)
	{
		cycleTick += TIMER_INTERNAL_COMMS_TASK;
		osDelayUntil(cycleTick);
		//DebugPrint("icomms loop");
//		iCommsMessage_t txMsg;
//		txMsg.standardMessageID = 0x08;
//		txMsg.dataLength = 4;
//		txMsg.data[0] = 0;
//		txMsg.data[1] = 0;
//		txMsg.data[2] = 0;
//		txMsg.data[3] = 4;
		/*txMsg.data[4] = 5;
		txMsg.data[5] = 6;
		txMsg.data[6] = 7;
		txMsg.data[7] = 8;*/
//		testTxCounter++;
//		if(testTxCounter == 25)
//		{
//			DebugPrint("#ICT: Sending!");
//			IComms_Transmit(&txMsg);
//			testTxCounter =0;
//		}

		throttleTxCounter++;
		if (throttleTxCounter == THROTTLE_RATE) {
			DebugPrint("%s Sending Throttle!", ICT_TAG);
			iCommsMessage_t throttleTxMsg = IComms_CreatePercentageMessage(throttleInfo->messageID, SystemGetThrottlePercentage());
			IComms_Transmit(&throttleTxMsg);
			throttleTxCounter = 0;
		}

		IComms_Update();
		uint16_t lookupTableIndex = 0;
		while(IComms_HasRxMessage())
		{
			iCommsMessage_t rxMsg;
			result_t ret = IComms_ReceiveNextMessage(&rxMsg);
			if(ret == RESULT_FAIL)
			{
				DebugPrint("%s Error Retrieving next message", ICT_TAG);
			}
			else{
				DebugPrint("%s Standard ID: %d", rxMsg.standardMessageID, ICT_TAG);
				DebugPrint("%s: DLC: %d", rxMsg.dataLength, ICT_TAG);
				for(uint8_t i=0; i<rxMsg.dataLength; i++) DebugPrint("%s Data[%d]: %d", ICT_TAG, i, rxMsg.data[i]);

				// NOTE: with the current polling, new messages incoming while processing this batch of messages will not be processed until the next cycle.
				// lookup can message in table
				// Exit if message found or if end of table reached
				while(rxMsg.standardMessageID != CANMessageLookUpTable[lookupTableIndex].messageID && lookupTableIndex < NUMBER_CAN_MESSAGE_IDS)
				{
					lookupTableIndex++;

				}
				// handle the case where the message is no recognized by the look up table
				if(lookupTableIndex < NUMBER_CAN_MESSAGE_IDS)
				{
					CANMessageLookUpTable[lookupTableIndex].canMessageCallback(rxMsg);
				}


			}

		}
	}
}
