/*
 * CANDriver.h
 *
 *  Created on: Aug 6, 2022
 *      Author: mingye chen
 *      Forked from
 */

#ifndef USERDRIVERS_CANDRIVER_H_
#define USERDRIVERS_CANDRIVER_H_

#include "stm32l4xx_hal.h"
#include "stdbool.h"
#include "ApplicationTypes.h"

typedef union {
  struct {
    uint8_t idType;
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];
  } frame;
  uint8_t array[14];
} uCAN_MSG;

#define dSTANDARD_CAN_MSG_ID_2_0B 1
#define dEXTENDED_CAN_MSG_ID_2_0B 2

PUBLIC bool CANSPI_Initialize(void);
PUBLIC void CANSPI_Sleep(void);
PUBLIC uint8_t CANSPI_Transmit(iCommsMessage_t * txMsg);
PUBLIC uint8_t CANSPI_Receive(iCommsMessage_t * rxMsg);
PUBLIC uint8_t CANSPI_messagesInBuffer(void);
PUBLIC uint8_t CANSPI_isBussOff(void);
PUBLIC uint8_t CANSPI_isRxErrorPassive(void);
PUBLIC uint8_t CANSPI_isTxErrorPassive(void);

#endif /* USERDRIVERS_CANDRIVER_H_ */
