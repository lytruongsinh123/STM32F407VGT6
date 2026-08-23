
//
// PB14 -> SPI2_MISO
// PB15 -> SPI2_MOSI
// PB13 -> SPI2_SCLK
// PB12 -> SPI2_NSS
// ALT function mode : AF5
//
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"

// Command codes
#define COMMAND_LED_CTRL    0x50
#define COMMAND_SENSOR_READ 0x51
#define COMMAND_LED_READ    0x52
#define COMMAND_PRINT       0x53
#define COMMAND_ID_READ     0x54

#define LED_ON  1
#define LED_OFF 0

// Arduino analog pins
#define ANALOG_PINO 0
#define ANALOG_PIN1 1
#define ANALOG_PIN2 2
#define ANALOG_PIN3 3
#define ANALOG_PIN4 4

// Arduino Led
#define LED_PIN 9
void SPI2_GPIOInits(void)
{
    GPIO_Handle_t SPI2Pins;
    SPI2Pins.pGPIOx                             = GPIOB;
    SPI2Pins.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_ALT;
    SPI2Pins.GPIO_PinConfig.GPIO_PinAltFunMode  = 5;
    SPI2Pins.GPIO_PinConfig.GPIO_PinOType       = GPIO_OP_TYPE_PP;
    SPI2Pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPI2Pins.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;

    // SCLK
    SPI2Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&SPI2Pins);

    // MOSI
    SPI2Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&SPI2Pins);

    // MISO
    SPI2Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(&SPI2Pins);

    // NSS
    SPI2Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GPIO_Init(&SPI2Pins);
}
void SPI2_Inits(void)
{
    SPI_Handle_t SPI2handle;
    SPI2handle.pSPIx                    = SPI2;
    SPI2handle.SPIConfig.SPI_BusConfig  = SPI_BUS_CONFIG_FULL_DUPLEX;
    SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2handle.SPIConfig.SPI_SclkSpeed  = SPI_SCLK_SPEED_DIVIDE_8;
    SPI2handle.SPIConfig.SPI_DFF        = SPI_DFF_8BITS;
    SPI2handle.SPIConfig.SPI_CPOL       = SPI_CPOL_LOW;
    SPI2handle.SPIConfig.SPI_CPHA       = SPI_CPHA_LOW;
    SPI2handle.SPIConfig.SPI_SSM        = SPI_SSM_DI; // hardware slave management enabled for NSS pin

    SPI_Init(&SPI2handle);
}
void GPIO_ButtonInit()
{
    GPIO_Handle_t gpiobtn;
    gpiobtn.pGPIOx                             = GPIOA;
    gpiobtn.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_0;
    gpiobtn.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_IN;
    gpiobtn.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
    gpiobtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&gpiobtn);
}
uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
    if (ackbyte == 0xF5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void delay(void)
{
    for (uint32_t i = 0; i < 500000 / 2; i++)
        ;
}
int main(void)
{
    uint8_t dummy_write = 0xff;
    uint8_t dummy_read = 0xff;
    GPIO_ButtonInit();
    // Function is used to initialize the GPIO pins to behave as SPI2 pins
    SPI2_GPIOInits();
    // Function is used to initialize the SPI2 peripheral parameters
    SPI2_Inits();

    SPI_SSOEConfig(SPI2, ENABLE);
    while (1)
    {

        // Wait till button is pressed
        while (!GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0))
            ;
        delay();

        // Enable the SPI peripheral
        SPI_PeripheralControl(SPI2, ENABLE);

        // 1. Send CMD_LED_CTRL      <pin no(1)>       <value(1)>
        uint8_t commandcode = COMMAND_LED_CTRL;
        uint8_t ackbyte;
        uint8_t args[2];
        SPI_TransmitData(SPI2, &commandcode, 1);
        // Do dummy read to clear of the RXNE
        SPI_ReceiveData(SPI2, &dummy_read, 1);
        // Send some dummy bits (1 byte) to fetch the response from the slave
        SPI_TransmitData(SPI2, &dummy_write, 1);
        // Read ack byte received
        SPI_ReceiveData(SPI2, &ackbyte, 1);
        if (SPI_VerifyResponse(ackbyte))
        {
            // Send argument
            args[0] = LED_PIN;
            args[1] = LED_ON;
            SPI_TransmitData(SPI2, args, 2);
        }
        // Confirm SPI is not busy
        while (SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG))
            ;
        // Disable the SPI peripheral
        SPI_PeripheralControl(SPI2, DISABLE);
    }
    return 0;
}
