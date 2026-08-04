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
 *                        1. Configure the device mode
 *                        2. Configure the bus
 *                        3. Configure the SPI Serial Clock Speed
 *                        4. Configure the DFF
 *                        5. Configure the CPOL
 *                        6. Configure the CPHA
 */
void SPI_Init(SPI_Handle_t* pSPIHandle)
{
    // First lets configure the SPI_CR1 register
    uint32_t tempreg = 0;
    // Enable peripheral the clock
    SPI_PCLKControl(pSPIHandle->pSPIx, ENABLE);

    // 1. Configure the Device Mode
    tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;
    // 2. Configure the Bus
    if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX)
    {
        // BIDIMODE should be cleared
        tempreg &= ~(1 << SPI_CR1_BIDIMODE);
    }
    else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HALF_DUPLEX)
    {
        // BIDIMODE should be set
        tempreg |= (1 << SPI_CR1_BIDIMODE);
    }
    else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        // BIDIMODE should be cleared
        tempreg &= ~(1 << SPI_CR1_BIDIMODE);
        // RXONLY must be set
        tempreg |= (1 << SPI_CR1_RXONLY);
    }
    // 3. Configure the SPI Serial Clock Speed
    tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
    // 4. Configure the DFF
    tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;
    // 5. Configure the CPOL
    tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
    // 6. Configure the CPHA
    tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

    pSPIHandle->pSPIx->CR1 = tempreg;
}
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
void SPI_DeInit(SPI_RegDef_t* pSPIx)
{
    if (pSPIx == SPI1)
    {
        SPI1_REG_RESET();
    }
    else if (pSPIx == SPI2)
    {
        SPI2_REG_RESET();
    }
    else if (pSPIx == SPI3)
    {
        SPI3_REG_RESET();
    }
    else if (pSPIx == SPI4)
    {
        SPI4_REG_RESET();
    }
}
uint8_t SPI_GetFlagStatus(SPI_RegDef_t* pSPIx, uint32_t FlagName)
{
    if (pSPIx->SR & (FlagName))
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}
/*
 * Data Send and Receive
 */
/****************************************************************************
 * @fn                  - SPI_TransmitData
 *
 * @brief               -
 *
 * @param[in]           -
 * @param[in]           -
 *
 * @return              -
 *
 * @Note                - This is blocking call
 *
 */
void SPI_TransmitData(SPI_RegDef_t* pSPIx, uint8_t* pTxBuffer, uint32_t len)
{
    while (len > 0)
    {
        // 1. Wait until TXE is set
        while (SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET)
            ;
        // 2. Check the DFF bit in CR1
        if (pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            // 16 bit DFF
            // 1. Load the data in to the DR
            pSPIx->DR = *((uint16_t*)pTxBuffer);
            // 2. Update the remaining data length (2 bytes transmitted)
            len--;
            len--;
            // 3. Move the transmit buffer pointer to the next 2 bytes
            (uint16_t*)pTxBuffer++;
        }
        else
        {
            // 8 bit DFF
            pSPIx->DR = *pTxBuffer;
            len--;
            pTxBuffer++;
        }
    }
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
