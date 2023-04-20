#include "ApplicationTypes.h"

#include "CANMessageLookUpModule.h"

#include "LoggerModule.h"

#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

void SpeedDataCallback(iCommsMessage_t msg)
{
	DebugPrint("SpeedDataCallback! %d", msg.standardMessageID);
	LoggerEnqueue(&msg);
}
void MotorTemperatureCallback(iCommsMessage_t msg)
{
	DebugPrint("MotorTemperatureCallback! %d", msg.standardMessageID);
	LoggerEnqueue(&msg);
}

void ThrottleDataCallback(iCommsMessage_t* msg)
{
	DebugPrint("ThrottleDataCallback not implemented! %d", msg->standardMessageID);
	LoggerEnqueue(&msg);
}

void ErrorDataCallback(iCommsMessage_t* msg)
{
	DebugPrint("ErrorDataCallback not implemented! %d", msg->standardMessageID);
	LoggerEnqueue(&msg);
}

void SpeedDataCallback(iCommsMessage_t* msg)
{
	DebugPrint("SpeedDataCallback not implemented! %d", msg->standardMessageID);
}

void EventDataCallback(iCommsMessage_t* msg)
{
	DebugPrint("EventDataCallback not implemented! %d", msg->standardMessageID);
}