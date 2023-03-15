/*
 * SDCardDriver.c
 *
 *  Created on: Mar 13, 2023
 *      Author: jeremycote
 */

#include "SDCardDriver.h"

#include "SerialDebugDriver.h"

#include "ff.h"
#include <stdlib.h>

#define DebugPrint(...) SerialPrintln(__VA_ARGS__)
static const char TAG[] = "#SCD";

static char lineBuffer[MAX_LINE_LENGTH];

static volatile FATFS fs;
static char _filename[32] = "log.csv";

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

	return RESULT_OK;
}

PUBLIC const char* SDGetFreeFilename() {
//	DIR dir;
//	f_opendir(&dir, "/");
//
//	FILINFO fno;
//
//	int32_t largest_num = 0;
//	// Iterate through the files in the directory
//	while (f_readdir(&dir, &fno) == FR_OK && fno.fname[0] != '\0') {
//	    // Parse the filename to extract the number
//	    int num = atoi(fno.fname + strlen("log"));
//
//	    // Update the largest number seen so far
//	    if (num > largest_num) {
//	        largest_num = num;
//	    }
//	}
//
//	f_closedir(&dir);
//
//	// Save filename of next file
//	sprintf(_filename, "log%ld.csv", largest_num + 1);
//
//	DebugPrint("Logs will be written to: %s", _filename);

	return _filename;
}

PUBLIC result_t SDAppend(const char* filename, const char* line, ...) {

	DebugPrint("%s Appending to %s", TAG, filename);

	va_list args;
	va_start(args, line);
	length_t len = vsprintf(lineBuffer, line, args);
	lineBuffer[len] = '\n';
	lineBuffer[len+1] = '\r';
	va_end(args);

	FIL file;
	FRESULT res;

	res = f_open(&file, filename, FA_OPEN_APPEND | FA_WRITE);

	DebugPrint("%s Opened %s", TAG, filename);

	if (res != FR_OK) {
		DebugPrint("%s Failed to write to %s", TAG, filename);
		return RESULT_FAIL;
	} else {
		DebugPrint("%s Opened %s", TAG, filename);
	}

	f_puts(lineBuffer, &file);

	DebugPrint("%s Putting to %s", TAG, filename);

	res = f_close(&file);

	DebugPrint("%s Closing %s", TAG, filename);

	if (res != FR_OK) {
		DebugPrint("%s Failed to close %s", TAG, filename);
		return RESULT_FAIL;
	} else {
		DebugPrint("%s Closed %s", TAG, filename);
	}

	return RESULT_OK;
}
