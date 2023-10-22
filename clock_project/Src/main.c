/************************************************************
 * File: main.c                                             *
 *                                                          *
 * Description: Utilizes uart_driver, timer_driver...etc    *
 *                                                          *
 * Author: Jourdan Rampoldi                                 *
 ***********************************************************/
#include "stm32f411xe.h"
#include "uart_driver.h"
#include "timer_driver.h"
#include "clock_handler.h"
#include "shift_reg_handler.h"


int seconds = 0;

int main()
{
    /*Initialize Modules*/
    uart1_tx_init();
    tim2_1hz_init();
    shift_reg_init();

    while (1)
    {
        /*Forever Loop*/
        while(!(TIM2->SR & SR_UIF)){}
        TIM2->SR &= ~SR_UIF;
        
        seconds++;
        display_handler(seconds);
    }
}
