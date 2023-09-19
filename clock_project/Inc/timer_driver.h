/************************************************
 * File: timer_driver.h                         *
 *                                              *
 * Description: Header file for timer set to    *
 * 1 Hz.                                        *
 *                                              *
 * Author: Jourdan Rampoldi                     *
 *                                              *
 *                                              *
 * *********************************************/

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include "stm32f411xe.h"

#define SR_UIF          (1<<0) 

// Header declerations go here
void tim2_1hz_init();


#endif
