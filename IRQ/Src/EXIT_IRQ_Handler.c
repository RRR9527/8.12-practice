#include "EXIT_IRQ_Handler.h"

volatile uint8_t Beep_Trigger = 0;
// extern comprehensive_figures figures;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == INPUT_Pin){
        
    }
}
