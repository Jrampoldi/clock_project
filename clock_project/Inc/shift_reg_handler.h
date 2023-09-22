/********************************************************
 *  File: shift_reg_handler.h                           *
 *                                                      *
 *  Description: Declerations for 8 bit shift register  *
 *  handler functions.                                  *
 *                                                      *
 *  Author: Jourdan Rampoldi                            *
 * ******************************************************/

#ifndef SHIFT_REG_HANDLER_H_
#define SHIFT_REG_HANDLER_H_

#include "uart_driver.h"
#include "stm32f411xe.h"
#include <stdlib.h>


//provide logic here!
void shift_reg_init();
void display_handler(int m, int s);
void set_bit_array(int bit_array[], int time);
void send_8_bits(int bit_array[]);
void pulse_clock();
void pulse_latch();


#endif
