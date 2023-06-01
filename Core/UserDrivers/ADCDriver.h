/*
 * ADCDriver.h
 *
 *  Created on: May 9, 2023
 *      Author: Jeremy Cote
 */

#ifndef USERDRIVERS_ADCDRIVER_H_
#define USERDRIVERS_ADCDRIVER_H_

#include "stm32l4xx_hal.h"
#include "ApplicationTypes.h"

PUBLIC result_t ADCBatteryPeriodicJob();
PUBLIC voltage_t ADCGetBatteryVoltage();
PUBLIC current_t ADCGetBatteryCurrent();

#endif /* USERDRIVERS_ADCDRIVER_H_ */
