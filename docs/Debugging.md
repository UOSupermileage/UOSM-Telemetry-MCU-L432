# SD Card Selection

STM32's FatFS implentation only supports SD Cards with a sector size of 512. You'll need to format the sd card in either Linux or Windows.

# FreeRTOS

## FreeRTOS Heap

If only a subset of the tasks are being executed. Increase the heap size.

## FreeRTOS priorities

Give each task a different priority level. FreeRTOS can get confused if tasks share a priority level.
