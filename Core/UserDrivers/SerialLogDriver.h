/*
 * SerialLogDriver.h
 *
 *  Created on: Sep. 5, 2022
 *      Author: mingy
 */

#ifndef USERDRIVERS_SERIALLOGDRIVER_H_
#define USERDRIVERS_SERIALLOGDRIVER_H_

// STM headers
#include "stm32l4xx_hal.h"

// Standard Lib
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MAX_LOG_PRINT_LENGTH 512

// #define VERBOSE

/* NOTE:
 * Initalization of the serial peripheral is done in main.c
 * Auto generated init by the IOC file */

void SerialLog(const char *message, ...);
void SerialLogln(const char *message, ...);

#endif /* USERDRIVERS_SERIALLOGDRIVER_H_ */
