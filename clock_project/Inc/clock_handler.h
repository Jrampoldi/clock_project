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

/* Function Declarations*/
int calculate_min(int s);
// Description: takes in seconds as an argument then
// returns calculated minutes.
int calculate_hour(int s);
// Description: takes in seconds as an argument then
// returns calculated hours
int calculate_seconds_rem(int s);
// Description: takes in seconds as an argument then
// returns the calculated remaining seconds 
// after breaking them down into hours and minutes

void set_time(int h, int m, int s);

#endif
