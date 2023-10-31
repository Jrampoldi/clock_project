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



void shift_reg_init();
void display_handler(int h, int m, int s);
void display_hours(int h);
void display_minutes(int m);
void display_seconds(int s);
void set_time_array(int* p, int time);
void set_digit_array(int* p, int digit);
void send_bits(int bit_array[], uint32_t DATA_PIN_ON, uint32_t DATA_PIN_OFF, int digit, int length);
void pulse_clock(int digit);
void pulse_latch(int digit);


#endif
