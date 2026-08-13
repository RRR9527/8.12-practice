#ifndef UART_IRQ_HANDLER_H
#define UART_IRQ_HANDLER_H

#include "main.h"
#include "usart.h"

void UART_Start_Receive(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif