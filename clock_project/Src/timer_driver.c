/****************************************
 * File: timer_driver.c                 *
 *                                      *
 * Description: Definition for timer    * 
 * init function.                       *
 *                                      *
 * Author: Jourdan Rampoldi             *
 *                                      *
 * *************************************/
#include "timer_driver.h"
           
#define TIM2EN              (1U<<0) // APB1ENR
#define CR1_CEN             (1U<<0)

void tim2_1hz_init()
{
    /*****Configure Timer to 1 Hz*****/
    RCC->APB1ENR |= TIM2EN;
    TIM2->PSC = 1600 - 1;
    TIM2->ARR = 10000 - 1;
    TIM2->CNT = 0;
    TIM2->CR1 |= CR1_CEN;
}
