#include "TIME_IRQ_Handler.h"

uint16_t tim1_counter = 0;
static uint8_t dir = 1;


void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        
    }
}
