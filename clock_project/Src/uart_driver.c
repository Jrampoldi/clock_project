/****************************************
 *  File: uart_driver.c                 *
 *                                      *
 *  Description: Holds definitions for  *
 *  uart_driver.h header file.          *
 *                                      *
 *  Author: Jourdan Rampoldi            *
 ***************************************/
#include "uart_driver.h"

/*System Definitions*/
#define SYSFREQ                 16000000
#define APB2CLK                 SYSFREQ
#define BAUDRATE                115200

/*GPIO Definitions*/
#define GPIOAEN                 (1U<<0)
#define PIN9_MODE               (1U<<19)
#define UART_AF                 (1U<<6 | 1U<<5 | 1U<<4)

/*USART Definitions*/
#define USART1EN                (1U<<4)
#define CR1_UE                  (1U<<13)
#define CR1_TE                  (1U<<3)
#define SR_TXE                  (1U<<7)

/* Function Declerations */
void uart1_set_brr(uint32_t periphClk, uint32_t baud);
void uart1_write(int ch);

void uart1_tx_init()
{
    /***** Configure GPIOA PIN9 *****/
    RCC->AHB1ENR |= GPIOAEN;
    GPIOA->MODER |= PIN9_MODE;
    GPIOA->AFR[1] |= UART_AF;

    /***** Configure USART1 *****/
    RCC->APB2ENR |= USART1EN;
    USART1->CR1 &= ~CR1_UE; // disable usart 
    USART1->CR1 |= CR1_TE; // enable TX
    uart1_set_brr(APB2CLK, BAUDRATE);
    USART1->CR1 |= CR1_UE;
    
}

int __io_putchar(int ch)
{ 
    /*Overwrite printf*/
    uart1_write(ch);
    return ch;
}

void uart1_set_brr(uint32_t periphClk, uint32_t baud)
{
    uint16_t uartdiv = periphClk / baud;
    USART1->BRR = (((uartdiv / 16) << 4) | (uartdiv % 16));
}

void uart1_write(int ch)
{
    while(!(USART1->SR & SR_TXE)){}
    USART1->DR = (ch & 0xFF);
}
