#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

int main(void)
{
    
    return 0;
}

void EXTI0_IRQHandler(void)
{
    GPIO_IRQHandling(0);
}