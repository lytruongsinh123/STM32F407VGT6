/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: May 13, 2026
 *      Author: HUNG
 */

#ifndef DRIVERS_INC_STM32F407XX_GPIO_DRIVER_H_
#define DRIVERS_INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"
/*
 * @GPIO_PIN_NUMBER
 * GPIO Pin number
 */
#define GPIO_PIN_NO_0  0
#define GPIO_PIN_NO_1  1
#define GPIO_PIN_NO_2  2
#define GPIO_PIN_NO_3  3
#define GPIO_PIN_NO_4  4
#define GPIO_PIN_NO_5  5
#define GPIO_PIN_NO_6  6
#define GPIO_PIN_NO_7  7
#define GPIO_PIN_NO_8  8
#define GPIO_PIN_NO_9  9
#define GPIO_PIN_NO_10 10
#define GPIO_PIN_NO_11 11
#define GPIO_PIN_NO_12 12
#define GPIO_PIN_NO_13 13
#define GPIO_PIN_NO_14 14
#define GPIO_PIN_NO_15 15

/*
 * @GPIO_PIN_MODES
 * GPIO Pin possible modes
 */
#define GPIO_MODE_IN     0
#define GPIO_MODE_OUT    1
#define GPIO_MODE_ALT    2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODE_IT_FT  4
#define GPIO_MODE_IT_RT  5
#define GPIO_MODE_RFT    6
/*
 * @GPIO_PIN_OP_TYPE
 * GPIO Pin possible output types
 */
#define GPIO_OP_TYPE_PP 0
#define GPIO_OP_TYPE_OD 1
/*
 * @GPIO_PIN_SPEED
 * GPIO Pin possible output speeds
 */
#define GPIO_SPEED_LOW    0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_FAST   2
#define GPIO_SPEED_HIGH   3
/*
 * @GPIO_PIN_PUPD_CONTROL
 * GPIO Pin pull up and pull down configuration macros
 */
#define GPIO_NO_PUPD 0
#define GPIO_PIN_PU  1
#define GPIO_PIN_PD  2
typedef struct
{

    uint8_t GPIO_PinNumber;      /*!<possible values from @GPIO_PIN_NUMBER>*/
    uint8_t GPIO_PinMode;        /*!<possible values from @GPIO_PIN_MODES>*/
    uint8_t GPIO_PinSpeed;       /*!<possible values from @GPIO_PIN_SPEED>*/
    uint8_t GPIO_PinPuPdControl; /*!<possible values from @GPIO_PIN_PUPD_CONTROL>*/
    uint8_t GPIO_PinOType;       /*!<possible values from @GPIO_PIN_OP_TYPE>*/
    uint8_t GPIO_PinAltFunMode;
} GPIO_PinConfig_t;
/*
 * This is Handle structure for GPIO Pin
 */
typedef struct
{
    GPIO_RegDef_t*   pGPIOx;         /*!< This is holds the base address of the GPIO Port to which the pin belongs >*/
    GPIO_PinConfig_t GPIO_PinConfig; /*!< This is holds GPIO Pin Configuration settings >*/
} GPIO_Handle_t;

/********************************************************************************************
 *                               APIs supported by this driver
 *             For more information about the APIs check the function definitions
 ********************************************************************************************/

/*
 * Peripheral Clock Setup
 */
void GPIO_PCLKControl(GPIO_RegDef_t* pGIOx, uint8_t EnorDi);
/*
 * Init and Deinit
 */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t* pGIOx);
/*
 * Data read and write
 */
uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t* pGIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGIOx);
void     GPIO_WriteToOutputPin(GPIO_RegDef_t* pGIOx, uint8_t PinNumber, uint8_t value);
void     GPIO_WriteToOutputPort(GPIO_RegDef_t* pGIOx, uint16_t value);
void     GPIO_ToggleOutputPin(GPIO_RegDef_t* pGIOx, uint8_t PinNumber);
/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);
#endif /* DRIVERS_INC_STM32F407XX_GPIO_DRIVER_H_ */
