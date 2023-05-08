/*
 * DataAggregation.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Jeremy Cote
 */

#ifndef MODULES_DATAAGGREGATION_H_
#define MODULES_DATAAGGREGATION_H_

#include "ApplicationTypes.h"

typedef union {
	uint32_t all;
	struct {
		uint32_t throttleTooHigh:1;
		uint32_t motorInitializing:1;
		uint32_t clockState:2;
		uint32_t reserved;
	};
} telemetry_status_t;

PUBLIC void InitDataAggregator();

PUBLIC void SystemSetThrottle(percentage_t throttle);
PUBLIC percentage_t SystemGetThrottle();

PUBLIC void SystemSetSpeed(speed_t speed);
PUBLIC speed_t SystemGetSpeed();

PUBLIC void SystemSetCurrent(current_t current);
PUBLIC current_t SystemGetCurrent();

PUBLIC void SystemSetThrottleTooHigh(flag_status_t state);
PUBLIC flag_status_t SystemGetThrottleTooHigh();

PUBLIC void SystemSetMotorInitializing(flag_status_t state);
PUBLIC flag_status_t SystemGetMotorInitializing();

PUBLIC void SystemSetClockState(uint8_t state);
PUBLIC uint8_t SystemGetClockState();

PUBLIC void SystemSetDeadmanTimestamp();
PUBLIC uint8_t SystemGetDeadmanTimestampHours();
PUBLIC uint8_t SystemGetDeadmanTimestampMinutes();
PUBLIC uint8_t SystemGetDeadmanTimestampSeconds();



#endif /* MODULES_DATAAGGREGATION_H_ */
