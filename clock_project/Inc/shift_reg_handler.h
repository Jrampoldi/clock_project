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
// Description: initializes the gpio necessary
// to generate clock signals, latch, signals, and 
// bit_arrays
void display_handler(int h, int m, int s);
// Description: Calls appropriate functions
// to send data to shift_reg
void display_hours(int h);
void display_minutes(int m);
void display_seconds(int s);
void set_time_array(int* p, int time);
void set_digit_array(int* p, int digit);
void send_bits(int bit_array[], uint32_t DATA_PIN_ON, uint32_t DATA_PIN_OFF, int digit, int length);
// Description: Loops over bit_array, sending each bit
// with a clock pulse. After bit_array loops, with a 
// latch signal.
void pulse_clock(int digit);
// Desription: Turn on clock pin and turn
// off clock pin.
void pulse_latch(int digit);
// Description: Turn on latch pin and turn
// off latch pin


#endif
