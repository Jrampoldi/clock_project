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

/* BSRR PIN SET VALUES */
#define ONE_DATA_ON         (1U<<0)
#define ONE_CLOCK_ON        (1U<<1)
#define ONE_LATCH_ON        (1U<<2)
#define TWO_DATA_ON			(1U<<3)
#define TWO_CLOCK_ON		(1U<<4)
#define TWO_LATCH_ON		(1U<<5)

/* BSRR PIN RESET VALUES */
#define ONE_DATA_OFF        (1U<<16)
#define ONE_CLOCK_OFF       (1U<<17)
#define ONE_LATCH_OFF       (1U<<18)
#define TWO_DATA_OFF		(1U<<19)
#define TWO_CLOCK_OFF		(1U<<20)
#define TWO_LATCH_OFF		(1U<<21)


void shift_reg_init() {
    // initialize GPIO pins
    RCC->AHB1ENR |= GPIOAEN;

    /* Enable output for PA0, PA1, PA2, PA3, PA4, PA5 */
    GPIOA->MODER |= (1U<<10 | 1U<<8 | 1U<<6 |
    					1U<<4 | 1U<<2 | 1U<<0);


}
void display_handler(int s){


	int bit_array[8] = {0, 0, 0, 0, 0, 0, 0, 0};


	/* CHECK FOR TENS PLACE DIGIT */
	if (s > 10) {
		set_bit_array(bit_array, ((int)(s / 10)));
		printf("Calc Sec: %d", ((int)(s / 10)));
	} else {
		set_bit_array(bit_array, 0);
	}
	send_8_bits(bit_array, ONE_DATA_ON, ONE_DATA_OFF, 1);

	/* SET FOR ONES PLACE DIGIT */
	set_bit_array(bit_array, (s % 10));
	send_8_bits(bit_array, TWO_DATA_ON, TWO_DATA_OFF, 0);

}

void set_bit_array(int bit_array[], int time) {
    // sets bit_array for digit in switch statement, according
    // to 7 segment display segments.

	int* p = (int*)malloc(8 * sizeof(int));
    p = bit_array;

    switch(time) {
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
void send_8_bits(int bit_array[], uint32_t DATA_PIN_ON, uint32_t DATA_PIN_OFF, int digit) {
    for(int i = 7; i >= 0; i--) {
        //loop through and set pin data
        if (bit_array[i] == 1) {

        	GPIOA->BSRR = DATA_PIN_ON;

        } else {

        	GPIOA->BSRR = DATA_PIN_OFF;

        }
        //pulse clock
        pulse_clock(digit);
    }
    //pulse latch to catch
    pulse_latch(digit);
}

void pulse_clock(int digit) {
    // clock on / clock off
	if (digit == 1) {

		GPIOA->BSRR = ONE_CLOCK_ON;
		GPIOA->BSRR = ONE_CLOCK_OFF;

	} else {

		GPIOA->BSRR = TWO_CLOCK_ON;
		GPIOA->BSRR = TWO_CLOCK_OFF;

	}
}

void pulse_latch(int digit) {
    // latch on / latch off
	if (digit == 1) {

		GPIOA->BSRR = ONE_LATCH_ON;
		GPIOA->BSRR = ONE_LATCH_OFF;

	} else {

		GPIOA->BSRR = TWO_LATCH_ON;
		GPIOA->BSRR = TWO_LATCH_OFF;

	}
}
