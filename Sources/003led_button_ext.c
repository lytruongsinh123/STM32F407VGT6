#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#define HIGH        ENABLE
#define BTN_PRESSED HIGH
void delay(void)
{
    for (uint32_t i = 0; i < 500000 / 2; i++)
        ;
}
int main(void)
{
    GPIO_Handle_t gpioled, gpiobtn;
    gpioled.pGPIOx                             = GPIOA;
    gpioled.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_8;
    gpioled.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
    gpioled.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
    gpioled.GPIO_PinConfig.GPIO_PinOType       = GPIO_OP_TYPE_PP;
    gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_PCLKControl(GPIOD, ENABLE);
    GPIO_Init(&gpioled);

    gpiobtn.pGPIOx                             = GPIOB;
    gpiobtn.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_12;
    gpiobtn.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_IN;
    gpiobtn.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
    gpiobtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_PCLKControl(GPIOA, ENABLE);
    GPIO_Init(&gpiobtn);
    while (1)
    {
        if (GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_12) == BTN_PRESSED)
        {
            delay();
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8);
        }
    }
    return 0;
}