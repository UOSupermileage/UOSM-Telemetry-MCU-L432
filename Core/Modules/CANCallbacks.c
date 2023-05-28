#include "ApplicationTypes.h"

#include "CANDriver.h"
#include "CANMessageLookUpModule.h"
#include "DataAggregation.h"


void ThrottleDataCallback(iCommsMessage_t* msg)
{
	uint32_t throttle = readMsg(msg);
	DebugPrint("CAN Throttle percentage received: %d", throttle);
	SystemSetThrottle(throttle);
}

void ErrorDataCallback(iCommsMessage_t* msg)
{
    if (msg->dataLength == CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes) {
        ErrorCode code = msg->data[1];
        flag_status_t status = msg->data[0];

        DebugPrint("ErrorDataCallback, received code %d with status %d", code, status);
        switch (code) {
        case THROTTLE_TOO_HIGH:
            SystemSetThrottleTooHigh(status);
            break;
        }
    } else {
        DebugPrint("msg.dataLength does not match lookup table. %d != %d", msg->dataLength, CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes);
    }
}

void SpeedDataCallback(iCommsMessage_t* msg)
{
	uint32_t speed = readMsg(msg);
	DebugPrint("CAN speed received: %d", speed);
	SystemSetSpeed(speed);
}

void EventDataCallback(iCommsMessage_t* msg)
{
    if (msg->dataLength == CANMessageLookUpTable[EVENT_DATA_ID].numberOfBytes) {
        EventCode code = msg->data[1];
        uint8_t status = msg->data[0];

        DebugPrint("EventDataCallback, received code %d with status %d", code, status);
        switch (code) {
        case MOTOR_INITIALIZING:
            SystemSetMotorInitializing(status);
            break;
        case DEADMAN:
        	SystemSetDeadmanTimestamp();
        	break;
        case TIMER:
        	SystemSetClockState(status);
        	break;
        default:
            break;
        }
    } else {
        DebugPrint("msg.dataLength does not match lookup table. %d != %d", msg->dataLength, CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes);
    }
}

void MotorRPMDataCallback(iCommsMessage_t* msg) {
	int32_t rpm = readMsg(msg);
	DebugPrint("CAN rpm received: %d", rpm);
	SystemSetMotorRPM(rpm);
}
