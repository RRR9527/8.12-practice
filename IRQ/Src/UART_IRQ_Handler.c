#include "UART_IRQ_Handler.h"

uint8_t rx_buffer[5] = {0};  // 接收到的信息
uint8_t tx_buffer[5] = {0};  // 发送出去的信息
uint8_t Beep_Trigger;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  // 接收指定长度的数据。提前规定好了接收5个字节。第一个字节用于校验
{
   if (huart->Instance == USART1)
   {
        if (rx_buffer[0] == 0xFF)
        {
            // Process the received datag
            for (uint8_t i = 1; i < 5; i++)
            {
                if (rx_buffer[i] == 1){
                    Beep_Trigger ++;  
                }
            }
            HAL_UART_Transmit(&huart1, tx_buffer, sizeof(tx_buffer), HAL_MAX_DELAY);
        }
        // HAL_UART_Receive_IT(&huart1, rx_buffer, 5);  // 结束要来这样重启接收（定长的中断）
        // HAL_UART_Receive_DMA(&huart1, rx_buffer, 5);  // 重启接收（DMA定定长中断）
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer)); // DMA，空闲中断
    }
}

void UART_Start_Receive(void)
{
    // HAL_UART_Receive_IT(&huart1, rx_buffer, 5);  // 对于接收指定长度数据情况下的初始化
    // HAL_UART_ReceiveToIdle_IT(&huart1, rx_buffer, sizeof(rx_buffer));   // 空闲中断的接收的初始化
    // HAL_UART_Receive_DMA(&huart1, rx_buffer, 5);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));
} 

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){   // 空闲中断。这个size是自动获取并传入的，所以可以不定长度
    if (huart->Instance == USART1){
        if (rx_buffer[0] == 0xFF)
        {
            // Process the received data
            for (uint8_t i = 1; i < Size; i++)
            {
                if (rx_buffer[i] == 1){
                    Beep_Trigger ++;  
                }
            }
            HAL_UART_Transmit_DMA(&huart1, tx_buffer, sizeof(tx_buffer));
        }
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, sizeof(rx_buffer));  // 重启接收（空闲中断）
    }
}

// HAL_UART_Transmit(&huart1, tx_buffer, sizeof(tx_buffer), HAL_MAX_DELAY)  // 阻塞式发送消息，要预先指定发送的消息的大小。IT改成DMA就可以DMA发消息了
// 参数分别是(发送过去的窗口，发送的信息，发送的信息的大小，最大的延迟时间)超过最大延迟时间则停止，显示超时
// HAL_UART_Transmit_IT(&huart1, tx_buffer, size)  // 中断式发送消息。发一次中断一次。效率低
