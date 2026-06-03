/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: May 13, 2026
 *      Author: HUNG
 */
#include "stm32f407xx_gpio_driver.h"

#include "stm32f407xx.h"

/*
 * Peripheral Clock Setup
 */
/****************************************************************************
 * @fn                  - GPIO_PCLKControl
 *
 * @brief               - This function enables or disables peripheral clock for given GPIO Port
 *
 * @param[in]           - Base address of the GPIOx peripheral
 * @param[in]           - Enable or Disable macros
 * @param[in]           - None
 *
 * @return              - None
 *
 * @Note                - None
 */
void GPIO_PCLKControl(GPIO_RegDef_t* pGIOx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pGIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if (pGIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if (pGIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if (pGIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if (pGIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if (pGIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if (pGIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if (pGIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
        else if (pGIOx == GPIOI)
        {
            GPIOI_PCLK_EN();
        }
    }
    else
    {
        if (pGIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if (pGIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if (pGIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if (pGIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if (pGIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if (pGIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }
        else if (pGIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }
        else if (pGIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
        else if (pGIOx == GPIOI)
        {
            GPIOI_PCLK_DI();
        }
    }
}
/*
 * Init and Deinit
 */
/****************************************************************************
 * @fn                  - GPIO_Init
 *
 * @brief               - Initializes the GPIO peripheral according to the specified
 *                        configuration settings in GPIO_Handle_t structure.
 *
 * @param[in]           - pGPIOHandle : Pointer to GPIO handle structure
 * @param[in]           - None
 * @param[in]           - None
 *
 * @return              - None
 *
 * @Note                - This function enables and configures:
 *                        1. GPIO pin modes
 *                        2. Output type
 *                        3. Output speed
 *                        4. Pull-up/Pull-down settings
 *                        5. Alternate function mode (if selected)
 */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle)
{
    uint32_t temp = 0;
    // 1. Configure the mode of gpio pin
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        // The non interrupt mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
        pGPIOHandle->pGPIOx->MODER |= temp;                                                 // set
    }
    else
    {
        // this part will code later (interrupt mode)
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            //1. Configure the FTSR
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            //1. Configure the RTSR
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            //1. Configure both FTSR and RTSR
        }
        // 2. Configure the GPIO Port selection in SYSCFG_EXTICR
        // 3. Enable the EXTI interrupt delivery using IMR
    }
    temp = 0;
    // 2. Configure the speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;                                                 // set
    temp = 0;
    // 3. Configure the pull up/pull down settings
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
    pGPIOHandle->pGPIOx->PUPDR |= temp;                                                 // set
    temp = 0;
    // 4. Configure the output type
    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
    pGPIOHandle->pGPIOx->OTYPER |= temp;                                                 // set
    temp = 0;
    // 5. Configure the alt functionality
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALT)
    {
        // Configure the alt function register
        uint32_t temp1 = 0, temp2 = 0;
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));                                           // clear
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2)); // set
    }
}
/****************************************************************************
 * @fn                  - GPIO_DeInit
 *
 * @brief               - Resets the selected GPIO peripheral registers
 *                        to their default reset values.
 *
 * @param[in]           - pGPIOx : Pointer to GPIO peripheral base address
 * @param[in]           - None
 * @param[in]           - None
 *
 * @return              - None
 *
 * @Note                - This function performs a peripheral reset using
 *                        the RCC reset register. All GPIO configuration
 *                        registers will be restored to their default state.
 */
void GPIO_DeInit(GPIO_RegDef_t* pGIOx)
{
    if (pGIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if (pGIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if (pGIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if (pGIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if (pGIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if (pGIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if (pGIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if (pGIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
    else if (pGIOx == GPIOI)
    {
        GPIOI_REG_RESET();
    }
}
/*
 * Data read and write
 */
/****************************************************************************
 * @fn                  - GPIO_ReadFromInputPin
 *
 * @brief               - Reads the logic level from the selected GPIO input pin.
 *
 * @param[in]           - pGPIOx     : Pointer to GPIO peripheral base address
 * @param[in]           - PinNumber : GPIO pin number to read
 *
 * @return              - uint8_t : Returns 0 or 1 depending on pin state
 *
 * @Note                - Reads the corresponding bit from the IDR
 *                        (Input Data Register).
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGIOx, uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t)((pGIOx->IDR >> PinNumber) & 0x00000001);
    return value;
}
/****************************************************************************
 * @fn                  - GPIO_ReadFromInputPort
 *
 * @brief               - Reads the current value of the GPIO input port.
 *
 * @param[in]           - pGPIOx : Pointer to GPIO peripheral base address
 *
 * @return              - uint16_t : Value of the GPIO input data register (IDR)
 *
 * @Note                - This function returns the logic states of all GPIO
 *                        pins in the selected port.
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGIOx)
{
    uint16_t value;
    value = (uint16_t)pGIOx->IDR;
    return value;
}
/****************************************************************************
 * @fn                  - GPIO_WriteToOutputPin
 *
 * @brief               - Writes a logic value to the selected GPIO output pin.
 *
 * @param[in]           - pGPIOx     : Pointer to GPIO peripheral base address
 * @param[in]           - PinNumber : GPIO pin number to write
 * @param[in]           - value     : Value to be written (GPIO_PIN_SET or GPIO_PIN_RESET)
 *
 * @return              - None
 *
 * @Note                - This function sets or clears the corresponding bit
 *                        in the ODR (Output Data Register).
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGIOx, uint8_t PinNumber, uint8_t value)
{
    if (value == GPIO_PIN_SET)
    {
        // write 1 to ODR at the bit field corresponding to the pin number
        pGIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        // write 0 to ODR at the bit field corresponding to the pin number
        pGIOx->ODR &= ~(1 << PinNumber);
    }
}
/****************************************************************************
 * @fn                  - GPIO_WriteToOutputPort
 *
 * @brief               - Writes a value to the GPIO output port.
 *
 * @param[in]           - pGPIOx : Pointer to GPIO peripheral base address
 * @param[in]           - value  : 16-bit value to be written to the output port
 *
 * @return              - None
 *
 * @Note                - This function updates the entire ODR
 *                        (Output Data Register) at once.
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t* pGIOx, uint16_t value)
{
    pGIOx->ODR = value;
}
/****************************************************************************
 * @fn                  - GPIO_ToggleOutputPin
 *
 * @brief               - Toggles the logic state of the selected GPIO output pin.
 *
 * @param[in]           - pGPIOx     : Pointer to GPIO peripheral base address
 * @param[in]           - PinNumber : GPIO pin number to toggle
 *
 * @return              - None
 *
 * @Note                - The corresponding bit in the ODR register is
 *                        inverted using XOR operation.
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGIOx, uint8_t PinNumber)
{
    pGIOx->ODR ^= (1 << PinNumber);
}
/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi) {}
void GPIO_IRQHandling(uint8_t PinNumber) {}
