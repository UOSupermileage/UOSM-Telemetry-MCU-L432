/*
 * LoggerModule.c
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 */


#include "LoggerModule.h"

#include "queue.h"

static QueueHandle_t logsQueue = NULL;

PUBLIC void LoggerInit() {
	logsQueue = xQueueCreate(LOGGER_QUEUE_LENGTH, sizeof(iCommsMessage_t));
}

PUBLIC result_t LoggerEnqueue(iCommsMessage_t* msg) {
	if (xQueueSend(logsQueue, (void *)msg, LOGGER_BLOCKING_TIME) == pdTRUE) {
		return RESULT_OK;
	}

	return RESULT_FAIL;
}

PUBLIC result_t LoggerDequeue(iCommsMessage_t* msg) {
	if (logsQueue != NULL) {

		if (xQueueReceive(logsQueue, (void *)msg, LOGGER_BLOCKING_TIME) == pdTRUE) {
			return RESULT_OK;
		}
	}

	return RESULT_FAIL;
}
