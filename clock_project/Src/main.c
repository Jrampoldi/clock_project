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


volatile int seconds = 3600;

int main(void)
{
    /*Initialize Modules*/
    uart1_tx_init();
    tim2_1hz_init();
    shift_reg_init();

    while(1)
    {
        /*Forever Loop*/
        while(!(TIM2->SR & SR_UIF)) {
        	display_handler(calculate_hour(seconds), calculate_min(seconds), calculate_seconds_rem(seconds));
        }
        TIM2->SR &= ~SR_UIF;

        seconds++;
    }
}
