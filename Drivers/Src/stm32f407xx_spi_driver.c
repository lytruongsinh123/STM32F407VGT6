/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: July 25, 2026
 *      Author: HUNG
 */
#include "stm32f407xx_spi_driver.h"

#include "stm32f407xx.h"

/*
 * Peripheral Clock Setup
 */
/****************************************************************************
 * @fn                  - SPI_PCLKControl
 *
 * @brief               - This function enables or disables peripheral clock for given GPIO Port
 *
 * @param[in]           - Base address of the SPIx peripheral
 * @param[in]           - Enable or Disable macros
 * @param[in]           - None
 *
 * @return              - None
 *
 * @Note                - None
 */
void SPI_PCLKControl(SPI_RegDef_t* pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
        else if (pSPIx == SPI4)
        {
            SPI4_PCLK_EN();
        }
    }
    else
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_DI();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_DI();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_DI();
        }
        else if (pSPIx == SPI4)
        {
            SPI4_PCLK_DI();
        }
    }
}
/*
 * Init and Deinit
 */
/****************************************************************************
 * @fn                  - SPI_Init
 *
 * @brief               - Initializes the SPI peripheral according to the specified
 *                        configuration settings in SPI_Handle_t structure.
 *
 * @param[in]           - pSPIHandle : Pointer to SPI handle structure
 * @param[in]           - None
 * @param[in]           - None
 *
 * @return              - None
 *
 * @Note                - This function enables and configures:
 *                        1.
 *                        2.
 *                        3.
 *                        4.
 *                        5.
 */
void SPI_Init(SPI_Handle_t* pSPIHandle) {}
/****************************************************************************
 * @fn                  - SPI_DeInit
 *
 * @brief               - Resets the selected SPI peripheral registers
 *                        to their default reset values.
 *
 * @param[in]           - pSPIx : Pointer to SPI peripheral base address
 * @param[in]           - None
 * @param[in]           - None
 *
 * @return              - None
 *
 * @Note                -
 *
 *
 */
void SPI_DeInit(SPI_RegDef_t* pSPIx) {}
/*
 * Data Send and Receive
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

/*
 * IRQ Configuration and ISR handling
 */
/******************************************************************************
 * @fn            GPIO_IRQInterruptConfig
 *
 * @brief         -
 *
 * @param[in]     -
 * @param[in]     -
 * @param[in]     -
 *
 * @return        -
 *
 * @Note          -
 *
 ******************************************************************************/
// void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
// {
//     if (EnorDi == ENABLE)
//     {
//         // NVIC_ISER0 register
//         if (IRQNumber <= 31)
//         {
//             *NVIC_ISER0 |= (1 << IRQNumber);
//         }
//         // NVIC_ISER1 register
//         else if (IRQNumber > 31 && IRQNumber < 64)
//         {
//             *NVIC_ISER1 |= (1 << (IRQNumber % 32));
//         }
//         // NVIC_ISER2 register
//         else if (IRQNumber >= 64 && IRQNumber < 96)
//         {
//             *NVIC_ISER2 |= (1 << (IRQNumber % 64));
//         }
//     }
//     else
//     {
//         // NVIC_ICER0 register
//         if (IRQNumber <= 31)
//         {
//             *NVIC_ICER0 |= (1 << IRQNumber);
//         }
//         // NVIC_ICER1 register
//         else if (IRQNumber > 31 && IRQNumber < 64)
//         {
//             *NVIC_ICER1 |= (1 << (IRQNumber % 32));
//         }
//         // NVIC_ICER2 register
//         else if (IRQNumber >= 64 && IRQNumber < 96)
//         {
//             *NVIC_ICER2 |= (1 << (IRQNumber % 64));
//         }
//     }
// }
/******************************************************************************
 * @fn            GPIO_IRQPriorityConfig
 *
 * @brief         -
 *
 * @param[in]     -
 * @param[in]     -
 * @param[in]     -
 *
 * @return        -
 *
 * @Note          -
 *
 ******************************************************************************/
// void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
// {
//     // 1. Find out the IPRx register and PRI_x section in IPRx
//     uint8_t iprx         = IRQNumber / 4;
//     uint8_t iprx_section = IRQNumber % 4;
//     uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
//     *(NVIC_PR_BASE_ADDR + iprx) |= IRQPriority << shift_amount;
// }
// void GPIO_IRQHandling(uint8_t PinNumber)
// {
//     // Clear the EXTI PR (Pending Reg) corresponding to the Pin number
//     if (EXTI->PR & (1 << PinNumber))
//     {
//         EXTI->PR |= (1 << PinNumber);
//     }
// }
