#ifndef UART_H_
#define UART_H_
#include"stm32f4xx.h"
#include <stdint.h>
// Function prototypes
void UART_Tx_Init(void);
void UART_Transmit_char(uint8_t data);
void UART_Receive(uint8_t *data, uint16_t len);

#endif // UART_H_