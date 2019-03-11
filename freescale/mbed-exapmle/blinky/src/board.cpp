#include "board.hpp"

static const gpio_pin_config_t ledRedConfig   = {kGPIO_DigitalOutput, 1};
static const gpio_pin_config_t ledGreenConfig = {kGPIO_DigitalOutput, 1};
static const gpio_pin_config_t ledBlueConfig  = {kGPIO_DigitalOutput, 1};

static const uint32_t debugUartRxPin       = 16;
static const uint32_t debugUartTxPin       = 17;
static const uint32_t debugUartBaseAddress = UART0_BASE;
static const uint32_t debugUartBaudRate    = 115200;
static const uint8_t debugUartDevice       = DEBUG_CONSOLE_DEVICE_TYPE_UART;

void board::initLeds() {
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortE);

    PORT_SetPinMux(LED_RED_GPIO_PORT, LED_RED_GPIO_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(LED_GREEN_GPIO_PORT, LED_GREEN_GPIO_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(LED_BLUE_GPIO_PORT, LED_BLUE_GPIO_PIN, kPORT_MuxAsGpio);

    GPIO_PinInit(LED_RED_GPIO, LED_RED_GPIO_PIN, &ledRedConfig);
    GPIO_PinInit(LED_GREEN_GPIO, LED_GREEN_GPIO_PIN, &ledGreenConfig);
    GPIO_PinInit(LED_BLUE_GPIO, LED_BLUE_GPIO_PIN, &ledBlueConfig);
}

void board::initDebugConsole() {
    uint32_t uartClockSourceFrequency = CLOCK_GetCoreSysClkFreq();

    CLOCK_EnableClock(kCLOCK_PortB);

    PORT_SetPinMux(PORTB, debugUartRxPin, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTB, debugUartTxPin, kPORT_MuxAlt3);

    DbgConsole_Init(debugUartBaseAddress, debugUartBaudRate, debugUartDevice, uartClockSourceFrequency);
}
