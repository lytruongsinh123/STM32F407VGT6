/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: July 24, 2026
 *      Author: HUNG
 */
#ifndef DRIVERS_INC_STM32F407XX_SPI_DRIVER_H_
#define DRIVERS_INC_STM32F407XX_SPI_DRIVER_H_
#include "stm32f407xx.h"
/*
 * @SPI_DeviceMode
 * SPI Device Mode
 */
#define SPI_DEVICE_MODE_MASTER 1
#define SPI_DEVICE_MODE_SLAVE  0
/*
 * @SPI_BusConfig
 * SPI Bus Config
 */
#define SPI_BUS_CONFIG_FULL_DUPLEX    1
#define SPI_BUS_CONFIG_HALF_DUPLEX    2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 3
/*
 * @SPI_SclkSpeed
 * SPI Clock Speed
 */
#define SPI_SCLK_SPEED_DIVIDE_2   0
#define SPI_SCLK_SPEED_DIVIDE_4   1
#define SPI_SCLK_SPEED_DIVIDE_8   2
#define SPI_SCLK_SPEED_DIVIDE_16  3
#define SPI_SCLK_SPEED_DIVIDE_32  4
#define SPI_SCLK_SPEED_DIVIDE_64  5
#define SPI_SCLK_SPEED_DIVIDE_128 6
#define SPI_SCLK_SPEED_DIVIDE_256 7
/*
 * @SPI_DFF
 * SPI Data Frame Format
 */
#define SPI_DFF_8BITS  0
#define SPI_DFF_16BITS 1
/*
 * @SPI_CPOL
 * SPI Clock Polarity
 */
#define SPI_CPOL_LOW  0
#define SPI_CPOL_HIGH 1
/*
 * @SPI_CPHA
 * SPI Clock Phase
 */
#define SPI_CPHA_LOW  0
#define SPI_CPHA_HIGH 1
/*
 * @SPI_SSM
 * SPI Software Slave Management
 */
#define SPI_SSM_DI 0
#define SPI_SSM_EN 1
/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG  (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG (1 << SPI_SR_BSY)
/*
 * Configuration structure for SPIx peripheral
 */
typedef struct
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
} SPI_Config_t;
/*
 * Handle structure for SPIx peripheral
 */
typedef struct
{
    SPI_RegDef_t* pSPIx;
    SPI_Config_t  SPIConfig;
} SPI_Handle_t;

/********************************************************************************************
 *                               APIs supported by this driver
 *             For more information about the APIs check the function definitions
 ********************************************************************************************/

/*
 * Peripheral Clock Setup
 */
void SPI_PCLKControl(SPI_RegDef_t* pSPIx, uint8_t EnorDi);

/*
 * Init and Deinit
 */
void    SPI_Init(SPI_Handle_t* pSPIHandle);
void    SPI_DeInit(SPI_RegDef_t* pSPIx);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t* pSPIx, uint32_t FlagName);
/*
 * Data Send and Receive
 */
void SPI_TransmitData(SPI_RegDef_t* pSPIx, uint8_t* pTxBuffer, uint32_t len);
void SPI_ReceiveData(SPI_RegDef_t* pSPIx, uint8_t* pRxBuffer, uint32_t len);
/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t* pSPIHandle);
/*
 * Other Peripheral Control APIs
 */
void SPI_PeripheralControl(SPI_RegDef_t* pSPIx, uint8_t EnorDi);

#endif /* DRIVERS_INC_STM32F407XX_SPI_DRIVER_H_ */
