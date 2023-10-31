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
#define THREE_DATA_ON       (1U<<6)
#define THREE_CLOCK_ON      (1U<<7)
#define THREE_LATCH_ON      (1U<<8)

/* BSRR PIN RESET VALUES */
#define ONE_DATA_OFF        (1U<<16)
#define ONE_CLOCK_OFF       (1U<<17)
#define ONE_LATCH_OFF       (1U<<18)
#define TWO_DATA_OFF		(1U<<19)
#define TWO_CLOCK_OFF		(1U<<20)
#define TWO_LATCH_OFF		(1U<<21)
#define THREE_DATA_OFF      (1U<<22)
#define THREE_CLOCK_OFF     (1U<<23)
#define THREE_LATCH_OFF     (1U<<24)

/* Define Digits */
#define D1                  1
#define D2                  2
#define D3                  3
#define D4                  4
#define D5                  5
#define D6                  6

void shift_reg_init() {
    // initialize GPIO pins
    RCC->AHB1ENR |= GPIOAEN;

    /* Enable output for PA0 - PA8 */
    GPIOA->MODER |= ( 1U<<16 | 1U<<14 | 1U<<12 | 1U<<10 | 1U<<8 | 1U<<6 | 1U<<4 | 1U<<2 | 1U<<0 );

}

void display_handler(int h, int m, int s) {
    display_hours(h);
    display_minutes(m);
    display_seconds(s);
}

void display_hours(int h) {

    //if h > 9
    //  digit1 = h // 10
    //else
    //  digit1 = 0
    //digit2 = h % 10

	int bit_array[16] = { 0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0};

	if (h > 9) {
		set_time_array(&bit_array[8], (int)(h / 10));
	} else {
		set_time_array(&bit_array[8], 0);
	}

	set_digit_array(bit_array, D1);
	send_bits(bit_array, THREE_DATA_ON, THREE_DATA_OFF, D1, 16);

	set_time_array(&bit_array[8], (h % 10));
	set_digit_array(bit_array, D2);
	send_bits(bit_array, THREE_DATA_ON, THREE_DATA_OFF, D2, 16);
}

void display_minutes(int m) {
    //if m > 9
    //  digit3 = m // 10
    //else
    //  digit3 = 0
    //digit4 = m % 10
	int bit_array[16] = { 0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0};
	if (m > 9) {
		set_time_array(&bit_array[8], (int)(m / 10));
	} else {
		set_time_array(&bit_array[8], 0);
	}

	set_digit_array(bit_array, D3);
	send_bits(bit_array, THREE_DATA_ON, THREE_DATA_OFF, D3, 16);

	set_time_array(&bit_array[8], (m % 10));
	set_digit_array(bit_array, D4);
	send_bits(bit_array, THREE_DATA_ON, THREE_DATA_OFF, D4, 16);
}

void display_seconds(int s){

	int bit_array[8] = {0, 0, 0, 0, 0, 0, 0, 0};


	/* CHECK FOR TENS PLACE DIGIT */
	if (s > 9) {
		set_time_array(bit_array, ((int)(s / 10)));
	} else {
		set_time_array(bit_array, 0);
	}
	send_bits(bit_array, ONE_DATA_ON, ONE_DATA_OFF, D5, 8);

	/* SET FOR ONES PLACE DIGIT */
	set_time_array(bit_array, (s % 10));
	send_bits(bit_array, TWO_DATA_ON, TWO_DATA_OFF, D6, 8);

}

void set_time_array(int* p, int time) {
    // sets bit_array for digit in switch statement, according
    // to 7 segment display segments.

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
}

void set_digit_array(int* p, int digit) {
	for (int i = 0; i < 8; i++){
		p[i] = 1;
	}
	switch(digit){
	case D1:
		p[0] = 0;
		break;
	case D2:
		p[2] = 0;
		break;
	case D3:
		p[4] = 0;
		break;
	case D4:
		p[6] = 0;
		break;
	}
}

void send_bits(int bit_array[], uint32_t DATA_PIN_ON, uint32_t DATA_PIN_OFF, int digit, int length) {
    for(int i = length - 1; i >= 0; i--) {
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
    switch(digit) {
		case D5: // seconds D5
			GPIOA->BSRR = ONE_CLOCK_ON;
			GPIOA->BSRR = ONE_CLOCK_OFF;
			break;
        case D6: // seconds D6
	    	GPIOA->BSRR = TWO_CLOCK_ON;
	    	GPIOA->BSRR = TWO_CLOCK_OFF; 
            break;
        default: // hour - minute case
            GPIOA->BSRR = THREE_CLOCK_ON;
            GPIOA->BSRR = THREE_CLOCK_OFF;
    }
}

void pulse_latch(int digit) {
    // latch on / latch off
    switch(digit) {
    	case D5: // seconds D5
    		GPIOA->BSRR = ONE_LATCH_ON;
    		GPIOA->BSRR = ONE_LATCH_OFF;
    		break;
        case D6: // seconds D6
	    	GPIOA->BSRR = TWO_LATCH_ON;
	    	GPIOA->BSRR = TWO_LATCH_OFF; 
            break;
        default: // hour - minute case
            GPIOA->BSRR = THREE_LATCH_ON;
            GPIOA->BSRR = THREE_LATCH_OFF;
    }
}
