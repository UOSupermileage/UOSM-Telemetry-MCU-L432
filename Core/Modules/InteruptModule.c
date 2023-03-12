/*
 * InteruptModule.c
 *
 *  Created on: Jan 23, 2023
 *      Author: jeremycote
 */

#include "InteruptModule.h"
#include "SerialDebugDriver.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#define DEBOUNCE

const char ITM_TAG[] = "#ITM:";

/*********************************************************************************
 *
 * 		Look up table for Interupts and their callbacks
 *
 **********************************************************************************/

static InteruptInfo interuptLookUpTable[NUMBER_INTERUPT_IDS] =
	{
			// Message Index			Callback	Debounce	Last Triggered
			{INTERUPT_GPIO_0_ID,			NULL, 	0,			0},
			{INTERUPT_GPIO_1_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_2_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_3_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_4_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_5_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_6_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_7_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_8_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_9_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_10_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_11_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_12_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_13_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_14_ID,			NULL,	0,			0},
			{INTERUPT_GPIO_15_ID,			NULL,	0,			0}
	};

PUBLIC void InteruptRegisterCallback(InteruptLookUpIndex id, InteruptCallback callback, uint16_t debounce)
{
	interuptLookUpTable[id].callback = callback;
	interuptLookUpTable[id].debounce = debounce;
	interuptLookUpTable[id].lastTriggered = 0;
}


PRIVATE void InteruptTriggerCallback(InteruptLookUpIndex id) {

	if (interuptLookUpTable[id].callback == NULL) {
		DebugPrint("%s No interupt register for GPIO [%d]", ITM_TAG, id);
		return;
	}

	interuptLookUpTable[id].callback();
}

/*********************************************************************************
 *
 * 		STM32 Interupt Callback
 *
 **********************************************************************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	InteruptLookUpIndex index = ConvertPinToLookupIndex(GPIO_Pin);

#ifdef DEBOUNCE

	// If debouncing is enabled for interupt
	if (interuptLookUpTable[index].debounce > 0) {

		// DebugPrint("%s Checking for debounce on GPIO [%d]", ITM_TAG, GPIO_Pin);
		// DebugPrint("%s Time since last triggered [%d]", ITM_TAG, osKernelGetTickCount() - interuptLookUpTable[GPIO_Pin].lastTriggered);

		// If time since last triggered is greater than debounce, update last triggered. Else, do not call interupt
		if (osKernelGetTickCount() -  interuptLookUpTable[index].lastTriggered >= interuptLookUpTable[index].debounce) {
			interuptLookUpTable[index].lastTriggered = osKernelGetTickCount();
		} else {
			return;
		}
	} else {
		DebugPrint("%s Debounce disabled for GPIO [%d]", ITM_TAG, index);
	}

#endif

	InteruptTriggerCallback(index);
}

PRIVATE InteruptLookUpIndex ConvertPinToLookupIndex(uint16_t pin) {
	switch (pin) {
			case GPIO_PIN_0:
				return INTERUPT_GPIO_0_ID;
			case GPIO_PIN_1:
				return INTERUPT_GPIO_1_ID;
			case GPIO_PIN_2:
				return INTERUPT_GPIO_2_ID;
			case GPIO_PIN_3:
				return INTERUPT_GPIO_3_ID;
			case GPIO_PIN_4:
				return INTERUPT_GPIO_4_ID;
			case GPIO_PIN_5:
				return INTERUPT_GPIO_5_ID;
			case GPIO_PIN_6:
				return INTERUPT_GPIO_6_ID;
			case GPIO_PIN_7:
				return INTERUPT_GPIO_7_ID;
			case GPIO_PIN_8:
				return INTERUPT_GPIO_8_ID;
			case GPIO_PIN_9:
				return INTERUPT_GPIO_9_ID;
			case GPIO_PIN_10:
				return INTERUPT_GPIO_10_ID;
			case GPIO_PIN_11:
				return INTERUPT_GPIO_11_ID;
			case GPIO_PIN_12:
				return INTERUPT_GPIO_12_ID;
			case GPIO_PIN_13:
				return INTERUPT_GPIO_13_ID;
			case GPIO_PIN_14:
				return INTERUPT_GPIO_14_ID;
			case GPIO_PIN_15:
				return INTERUPT_GPIO_15_ID;
			default:
				DebugPrint("%s GPIO Pin [%d] Invalid Interupt Index.", ITM_TAG, pin);
				return 0;
	}
}
