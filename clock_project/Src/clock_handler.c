/************************************************
 *  File: clock_handler.c                       *
 *                                              *
 *  Description: Definitions for clock handling *
 *  headers found here.                         *
 *                                              *
 *  Author: Jourdan Rampoldi                    *
 *                                              *
 * *********************************************/

#include "clock_handler.h"

int calculate_seconds_rem(int s)
{
    //logic for remainder of seconds
    return ((int)(s % 60));
}

int calculate_min(int s)
{
    //logic for calculating minutes
    return ((int)(s / 60) % 60);
}

int calculate_hour(int s)
{
    //logic for calculating hours
    return ((int)(s / 3600));
}
