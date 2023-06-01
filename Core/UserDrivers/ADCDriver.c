/*
 * ADCDriver.c
 *
 *  Created on: May 9, 2023
 *      Author: Jeremy Cote
 */
#include "ADCDriver.h"
#include "DataAggregation.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;

volatile uint16_t adcResult[2] = {0, 0};

PUBLIC result_t ADCBatteryPeriodicJob()
{
	HAL_StatusTypeDef returnStatus;

	// Size of buffer is one, only capture one point in time
	returnStatus = HAL_ADC_Start_DMA(&hadc1, adcResult, 2);

	if(returnStatus != HAL_OK)
	{
		return RESULT_FAIL;
	}

	HAL_TIM_Base_Start(&htim1);

	return RESULT_OK;
}


PUBLIC voltage_t ADCGetBatteryVoltage() {
	return adcResult[0];
}
PUBLIC current_t ADCGetBatteryCurrent() {
	return adcResult[1];
}
