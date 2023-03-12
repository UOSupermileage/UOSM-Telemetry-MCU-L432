/*
 * CANMessageLookUpModule.c
 *
 *  Created on: Dec 4, 2022
 *      Author: mingy
 */

#include "CANMessageLookUpModule.h"
#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

const char CLM_TAG[] = "#CLM:";

// Callbacks
void ThrottleDataCallback(iCommsMessage_t msg);
void SpeedDataCallback(iCommsMessage_t msg);
void MotorTemperatureCallback(iCommsMessage_t msg);

/*********************************************************************************
 *
 * 		Look up table for CAN ID and meta data about its payload
 *
 **********************************************************************************/
const ICommsMessageInfo CANMessageLookUpTable[NUMBER_CAN_MESSAGE_IDS] =
	{
			// Message Index			CAN ID		Num of Bytes		Callback
			{THROTTLE_DATA_ID,			0x0001, 			2,		&ThrottleDataCallback},
			{SPEED_DATA_ID,				0x0400,				2,		&SpeedDataCallback},
			{MOTOR_TEMPERATURE_ID, 		0x0401,				2,		&MotorTemperatureCallback}
	};

void ThrottleDataCallback(iCommsMessage_t msg)
{
	DebugPrint("ThrottleDataCallback! %d", msg.standardMessageID);
}
void SpeedDataCallback(iCommsMessage_t msg)
{
	DebugPrint("SpeedDataCallback! %d", msg.standardMessageID);
}
void MotorTemperatureCallback(iCommsMessage_t msg)
{
	DebugPrint("MotorTemperatureCallback! %d", msg.standardMessageID);
}

PUBLIC const ICommsMessageInfo* CANMessageLookUpGetInfo(ICommsMessageLookUpIndex id) {
	return &CANMessageLookUpTable[id];
}
