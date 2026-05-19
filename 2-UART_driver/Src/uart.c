#include "uart.h"

#define SYS_CLK 16000000U 
#define APB1_CLK (SYS_CLK ) // APB1 clock is half of system clock
#define UART_BAUDRATE 115200U


static void UART_Bauderate_set(uint32_t periph_clk, uint32_t baudrate);

int _io_putchar(int ch)
{
    UART_Transmit_char((uint8_t)ch);
    return ch;
}

void UART_Tx_Init(void)
{
    /*********GPIO Configuration *********/
    /*Enable clock for GPIOA*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    /*Set PA2 as alternate function (AF7 for USART2_TX)*/
    GPIOA->MODER &= ~(0x3 << (2 * 2)); // Clear mode bits for PA2
    GPIOA->MODER |= (0x2 << (2 * 2)); // Set alternate function mode
    GPIOA->AFR[0] &= ~(0xF << (2 * 4)); // Clear alternate function bits for PA2
    GPIOA->AFR[0] |= (0x7 << (2 * 4)); // Set AF7 for USART2_TX

    /*********UART Configuration *********/
    /*Enable clock for USART2*/
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    /*Configure baud rate*/
    UART_Bauderate_set(APB1_CLK, UART_BAUDRATE);
    /*Enable USART2 transmitter*/
    USART2->CR1 |= USART_CR1_TE;
    /*Enable USART2*/
    USART2->CR1 |= USART_CR1_UE;

}

void UART_Transmit_char(uint8_t data)
{
    /*Wait until transmit data register is empty*/
    while (!(USART2->SR & USART_SR_TXE));
    /*Write data to transmit data register*/
    USART2->DR = data;
}

static uint16_t UART_BAUD_Icalculate(uint32_t periph_clk, uint32_t baudrate)
{
    return (periph_clk + (baudrate / 2U)) / baudrate;
}

static void UART_Bauderate_set(uint32_t periph_clk, uint32_t baudrate)
{
    USART2->BRR = UART_BAUD_Icalculate(periph_clk, baudrate);
}