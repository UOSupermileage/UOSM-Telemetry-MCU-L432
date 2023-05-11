/*
 * ADCDriver.c
 *
 *  Created on: May 9, 2023
 *      Author: Jeremy Cote
 */
#include "ADCDriver.h"
#include "DataAggregation.h"

extern ADC_HandleTypeDef hadc1;

uint16_t adcResult[2] = {0, 0};

PUBLIC result_t ADCBatteryPeriodicJob()
{
	HAL_StatusTypeDef returnStatus;

	// Size of buffer is one, only capture one point in time
	returnStatus = HAL_ADC_Start_DMA(&hadc1, adcResult, 2);

	if(returnStatus != HAL_OK)
	{
		return RESULT_FAIL;
	}

	return RESULT_OK;
}

PRIVATE void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    // Conversion Complete & DMA Transfer completed so The voltageADCResult Is Now Updated
    SystemSetBatteryVoltage(adcResult[0]);
    SystemSetCurrent(adcResult[1]);
}
