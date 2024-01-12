/********************************************************************
 *  File: uart_driver.h                                             *
 *                                                                  *
 *  Description: Header file for handling uart communication        *
 *  on the STM32F411CEU6.                                           *
 *                                                                  *
 *  Author: Jourdan Rampoldi                                        *
 * *****************************************************************/
#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "stm32f411xe.h"
#include "stdint.h"
#include "stdio.h"

/* function declarations */
void uart1_tx_init();
// Description: configures uart to 
// transmit data at a 115200 baudrate

#endif
