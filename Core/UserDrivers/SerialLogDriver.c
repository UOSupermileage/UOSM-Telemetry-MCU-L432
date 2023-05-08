/*
 * SerialLogDriver.c
 *
 *  Created on: Sep. 5, 2022
 *      Author: mingy
 */

#include "SerialLogDriver.h"

extern UART_HandleTypeDef huart1;
static char messageBuf[MAX_LOG_PRINT_LENGTH];

void SerialLog(const char *message, ...) {
    va_list args;
    va_start(args, message);
    uint16_t len = vsprintf(messageBuf, message, args);
    HAL_UART_Transmit(&huart1, (uint8_t *)messageBuf, len, HAL_MAX_DELAY);
    va_end(args);
}
void SerialLogln(const char *message, ...) {
    va_list args;
    va_start(args, message);
    uint16_t len = vsprintf(messageBuf, message, args);
    messageBuf[len] = '\n';
    messageBuf[len + 1] = '\r';
    HAL_UART_Transmit(&huart1, (uint8_t *)messageBuf, len + 2, HAL_MAX_DELAY);
    va_end(args);
}
