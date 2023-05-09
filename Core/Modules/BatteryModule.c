/*
 * BatteryModule.c
 *
 *  Created on: May 9, 2023
 *      Author: Jeremy Cote
 */

#include "BatteryModule.h"
#include "ADCDriver.h"

const char BAM_TAG[] = "#BAM:";

PUBLIC result_t Battery_UpdateVoltage() {

    voltage_t voltage;

    result_t resultStatus;
    resultStatus = ADCGetBatteryVoltage(&voltage);
    if (resultStatus == RESULT_FAIL) {
        DebugPrint("%s ERROR ADCGetVoltage", BAM_TAG);
        return RESULT_FAIL;
    }
    DebugPrint("%s ADC Battery Voltage value %d", BAM_TAG, voltage);
    SystemSetBatteryVoltage(voltage);
    return RESULT_OK;
}
