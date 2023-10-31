/********************************************************
 *  File: clock_handler.h                               *
 *                                                      *
 *  Description: Header file for clock handler function *
 *  declerations.                                       *
 *                                                      *
 *                                                      *
 * *****************************************************/


#ifndef CLOCK_HANDLER_H_
#define CLOCK_HANDLER_H_

int calculate_min(int s);
int calculate_hour(int s);
int calculate_seconds_rem(int s);
void set_time(int h, int m, int s);

#endif
