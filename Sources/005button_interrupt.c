#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

#include <string.h>

#define HIGH        1
#define LOW         0
#define BTN_PRESSED LOW
void delay(void)
{
    for (uint32_t i = 0; i < 500000 / 2; i++)
        ;
}
int main(void)
{
    GPIO_Handle_t GpioLed, gpiobtn;
    memset(&GpioLed, 0, sizeof(GpioLed));
    memset(&gpiobtn, 0, sizeof(gpiobtn));
    // this is led gpio configuration
    GpioLed.pGPIOx                             = GPIOD;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_12;
    GpioLed.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_LOW;
    GpioLed.GPIO_PinConfig.GPIO_PinOType       = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_PCLKControl(GPIOD, ENABLE);
    GPIO_Init(&GpioLed);

    // this is btn gpio configuration
    gpiobtn.pGPIOx                             = GPIOD;
    gpiobtn.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_5;
    gpiobtn.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_IT_FT;
    gpiobtn.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
    gpiobtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_PCLKControl(GPIOD, ENABLE);
    GPIO_Init(&gpiobtn);

    // irq configuration
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRIO15);
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);
    while (1)
    {
    }

    return 0;
}
void EXTI9_5_IRQHandler(void)
{
    delay();
    GPIO_IRQHandling(GPIO_PIN_NO_5);
    GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}