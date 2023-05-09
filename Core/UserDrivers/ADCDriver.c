/*
 * ADCDriver.c
 *
 *  Created on: May 9, 2023
 *      Author: Jeremy Cote
 */
#include "ADCDriver.h"

extern ADC_HandleTypeDef hadc1;

#define SCALE 60000 / 3128

PUBLIC result_t ADCGetBatteryVoltage(voltage_t* voltage)
{
	uint32_t voltageRaw;
	HAL_StatusTypeDef returnStatus;
	returnStatus = HAL_ADC_Start(&hadc1);
	if(returnStatus != HAL_OK)
	{
		return RESULT_FAIL;
	}

	returnStatus = HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	if(returnStatus != HAL_OK)
	{
		return RESULT_FAIL;
	}

	voltageRaw = HAL_ADC_GetValue(&hadc1);

	*voltage = voltageRaw * SCALE;

	return RESULT_OK;
}
