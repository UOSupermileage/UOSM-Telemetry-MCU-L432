/*
 * SDCardDriver.h
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 *
 *  Assumes FatFS Middleware + user_diskio_spi driver integration.
 *  https://01001000.xyz/2020-08-09-Tutorial-STM32CubeIDE-SD-card/
 *  https://github.com/kiwih/cubeide-sd-card
 */

#ifndef USERDRIVERS_SDCARDDRIVER_H_
#define USERDRIVERS_SDCARDDRIVER_H_

#include "ApplicationTypes.h"

#define MAX_LINE_LENGTH 256

PUBLIC result_t SDInit();

PUBLIC result_t SDAppend(const char* filename, const char* line, ...);

#endif /* USERDRIVERS_SDCARDDRIVER_H_ */
