/****************************************************
 * File: shift_reg_handler.c                        *
 *                                                  *
 * Description: Definitions for 8 bit shift         *
 * register handler can be found here.              *
 *                                                  *
 * Author: Jourdan Rampoldi                         *
 * *************************************************/
#include "shift_reg_handler.h"

#define GPIOAEN             (1U<<0)

#define DIGIT_ONE           (1U<<20 | 1U<<19 | 1U<<18 | 1U<<1)
#define DIGIT_TWO           (1U<<20 | 1U<<19 | 1U<<2 | 1U<<17)
#define DIGIT_THREE         (1U<<20 | 1U<<3 | 1U<<18 | 1U<<17)
#define DIGIT_FOUR          (1U<<4 | 1U<<19 | 1U<<18 | 1U<<17)

#define SR_CLOCK_ON         (1U<<11)
#define SR_CLOCK_OFF        (1U<<27)
#define LATCH_ON            (1U<<7)
#define LATCH_OFF           (1U<<23)

#define DATA_PIN_ON         (1U<<5)
#define DATA_PIN_OFF        (1U<<21)

#define ENABLE_PIN          (1U<<23)
#define SR_CLR              (1U<<12)


// Probably should try to use timer interrupts to 
// program all of these. 


void shift_reg_init()
{
    // initialize GPIO pins
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |= (1U<<24 | 1U<<22 | 1U<<14 | 
                    1U<<12 | 1U<<10 | 1U<<8 | 
                    1U<<6 | 1U<<4 | 1U<<2); 
    GPIOA->BSRR = (ENABLE_PIN | SR_CLR); 
    //sn74hc595n
}
void display_handler(int m, int s)
{
    int bit_array[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    
    // Program Digit1
    if (m > 9)
    {
        GPIOA->BSRR = DIGIT_ONE;
        set_bit_array(bit_array, ((int)(m / 10)));
        send_8_bits(bit_array);
    }

    // Program Digit2
    GPIOA->BSRR = DIGIT_TWO;
    set_bit_array(bit_array, (m % 10));
    send_8_bits(bit_array);

    // Program Digit3
    if(s > 9)
    {
        GPIOA->BSRR = DIGIT_THREE;
        set_bit_array(bit_array, ((int)(s / 10)));
        send_8_bits(bit_array);
    }

    // Program Digit4
    GPIOA->BSRR = DIGIT_FOUR;
    set_bit_array(bit_array, (s % 10));
    send_8_bits(bit_array);

}

void set_bit_array(int bit_array[],int time)
{
    // sets bit_array for digit in switch statement, according
    // to 7 segment display segments.
    int* p = (int*)malloc(8 * sizeof(int));
    p = bit_array;
    switch(time)
    {
        case 0:
            *p++ = 1; *p++ = 1; *p++ = 1; *p++ = 1;
            *p++ = 1; *p++ = 1; *p++ = 0; *p = 0;
            break;
        case 1:
            *p++ = 0; *p++ = 1; *p++ = 1; *p++ = 0; 
            *p++ = 0; *p++ = 0; *p++ = 0; *p = 0;
            break;
        case 2:
            *p++ = 1; *p++ = 1; *p++ = 0; *p++ = 1;
            *p++ = 1; *p++ = 0; *p++ = 1; *p = 0;
            break;
        case 3:
            *p++ = 1; *p++ = 1; *p++ = 1; *p++ = 1;
            *p++ = 0; *p++ = 0; *p++ = 1; *p = 0;
            break;
        case 4:
            *p++ = 0; *p++ = 1; *p++ = 1; *p++ = 0;
            *p++ = 0; *p++ = 1; *p++ = 1; *p = 0;
            break;
        case 5:
            *p++ = 1; *p++ = 0; *p++ = 1; *p++ = 1;
            *p++ = 0; *p++ = 1; *p++ = 1; *p = 0;
            break;
        case 6:
            *p++ = 1; *p++ = 0; *p++ = 1; *p++ = 1;
            *p++ = 1; *p++ = 1; *p++ = 1; *p = 0;
            break;
        case 7:
            *p++ = 1; *p++ = 1; *p++ = 1; *p++ = 0;
            *p++ = 0; *p++ = 0; *p++ = 0; *p = 0;
            break;
        case 8:
            *p++ = 1; *p++ = 1; *p++ = 1; *p++ = 1;
            *p++ = 1; *p++ = 1; *p++ = 1; *p = 0;
            break;
        case 9:
            *p++ = 1; *p++ = 1; *p++ = 1; *p++ = 0;
            *p++ = 0; *p++ = 1; *p++ = 1; *p = 0;
            break;
    }
    free(p); //deallocate pointer
}
void send_8_bits(int bit_array[])
{
    for(int i = 0; i < 8; i++)
    {
        //loop through and set pin data
        if (bit_array[i] == 1)
        {
            GPIOA->BSRR = DATA_PIN_ON;
        }
        else
        {
            GPIOA->BSRR = DATA_PIN_OFF;
        }
        //pulse clock
        pulse_clock();
    }
    //pulse latch to catch
    pulse_latch();
}

void pulse_clock()
{
    // clock on / clock off
    GPIOA->BSRR = SR_CLOCK_ON;
    GPIOA->BSRR = SR_CLOCK_OFF;
}

void pulse_latch()
{
    // latch on / latch off
    GPIOA->BSRR = LATCH_ON;
    GPIOA->BSRR = LATCH_OFF;
}








