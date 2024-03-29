/*
 * DataAggregation.c
 *
 *  Created on: Mar 11, 2023
 *      Author: Jeremy Cpte
 */
#include "DataAggregation.h"
#include "ADCDriver.h"

extern RTC_HandleTypeDef hrtc;

percentage_t throttle;
speed_t speed;

int32_t rpm;

telemetry_status_t status;
RTC_TimeTypeDef deadmanTimestamp;

PUBLIC void InitDataAggregator() {

}

PUBLIC void SystemSetThrottle(percentage_t t) {
	throttle = t;
}
PUBLIC percentage_t SystemGetThrottle() {
	return throttle;
}

PUBLIC void SystemSetSpeed(speed_t s) {
	speed = s;
}
PUBLIC speed_t SystemGetSpeed() {
	return speed;
}

PUBLIC current_t SystemGetCurrent() {
	return ADCGetBatteryCurrent();
}

PUBLIC void SystemSetThrottleTooHigh(flag_status_t s){
	status.throttleTooHigh = s;
}
PUBLIC flag_status_t SystemGetThrottleTooHigh() {
	return status.throttleTooHigh;
}

PUBLIC void SystemSetMotorInitializing(flag_status_t s) {
	status.motorInitializing = s;
}
PUBLIC flag_status_t SystemGetMotorInitializing() {
	return status.motorInitializing;
}

PUBLIC void SystemSetClockState(uint8_t s) {
	status.clockState = s;
}
PUBLIC uint8_t SystemGetClockState() {
	return status.clockState;
}

PUBLIC void SystemSetDeadmanTimestamp() {
	HAL_RTC_GetTime(&hrtc, &deadmanTimestamp, RTC_FORMAT_BIN);
}
PUBLIC uint8_t SystemGetDeadmanTimestampHours() {
	return deadmanTimestamp.Hours;
}
PUBLIC uint8_t SystemGetDeadmanTimestampMinutes() {
	return deadmanTimestamp.Minutes;
}
PUBLIC uint8_t SystemGetDeadmanTimestampSeconds() {
	return deadmanTimestamp.Seconds;
}

PUBLIC void SystemSetMotorRPM(int32_t r) {
	rpm = r;
}
PUBLIC int32_t SystemGetMotorRPM() {
	return rpm;
}

PUBLIC voltage_t SystemGetBatteryVoltage() {
	return ADCGetBatteryVoltage();
}

// 46V
PUBLIC flag_status_t SystemGetUndervoltage() {
	return SystemGetBatteryVoltage() < 3100 ? Set : Clear;
}
