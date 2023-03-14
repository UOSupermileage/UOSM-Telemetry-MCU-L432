/*
 * SDCardDriver.c
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 */

#include "SDCardDriver.h"

#include "SerialDebugDriver.h"

#include "ff.h"

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)
static const char TAG[] = "#SCD";

static char lineBuffer[MAX_LINE_LENGTH];

static volatile FATFS fs;

PUBLIC result_t SDInit() {
	DebugPrint("%s Init SD Card Driver", TAG);

	FRESULT res;

	// Mount the file system
	res = f_mount(&fs, "", 1);

	if (res != FR_OK) {
		DebugPrint("%s Failed to mount file system: %i", TAG, res);
		return RESULT_FAIL;
	}

	//Let's get some statistics from the SD card
	DWORD free_clusters, free_sectors, total_sectors;

	FATFS* getFreeFs;

	res = f_getfree("", &free_clusters, &getFreeFs);
	if (res != FR_OK) {
		DebugPrint("%s Failed to get free space %i", TAG, res);
		return RESULT_FAIL;
	}

	//Formula comes from ChaN's documentation
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;

	DebugPrint("%s SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", TAG, total_sectors / 2, free_sectors / 2);

//	res = f_mount(NULL, "/", 0);
//	if (res != FR_OK) {
//		DebugPrint("%s Failed to unmount drive", TAG);
//		return RESULT_FAIL;
//	} else {
//		DebugPrint("%s Unmounted drive", TAG);
//	}

	return RESULT_OK;
}

PUBLIC result_t SDAppend(const char* filename, const char* line, ...) {

	FIL file;
	FRESULT res;

//	res = f_mount(&fs, "", 1);
//
//	if (res != FR_OK) {
//		DebugPrint("%s Failed to mount file system: %i", TAG, res);
//		return RESULT_FAIL;
//	}

	va_list args;
	va_start(args, line);
	length_t len = vsprintf(lineBuffer, line, args);
	va_end(args);

	DebugPrint("%s Starting SDAppend", TAG);



	DebugPrint("%s Created variables", TAG);

	res = f_open(&file, filename, FA_OPEN_APPEND | FA_WRITE);

	if (res != FR_OK) {
		DebugPrint("%s Failed to write to %s", TAG, filename);
		return RESULT_FAIL;
	} else {
		DebugPrint("%s Opened %s", TAG, filename);
	}

	f_puts(lineBuffer, &file);

	res = f_close(&file);

	if (res != FR_OK) {
		DebugPrint("%s Failed to close %s", TAG, filename);
		return RESULT_FAIL;
	} else {
		DebugPrint("%s Closed %s", TAG, filename);
	}

//	res = f_mount(NULL, "/", 0);
//	if (res != FR_OK) {
//		DebugPrint("%s Failed to unmount drive", TAG);
//		return RESULT_FAIL;
//	} else {
//		DebugPrint("%s Unmounted drive", TAG);
//	}

	return RESULT_OK;
}
