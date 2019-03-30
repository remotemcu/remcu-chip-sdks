#include "serial.h"

#include <xmc_uart.h>
#include <xmc_gpio.h>

void serial_init(void)
{
  XMC_UART_CH_CONFIG_t uart_config =
  {
    .baudrate = 115200,
    .data_bits = 8,
    .stop_bits = 1,
  };

  XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);

  XMC_GPIO_SetMode(UART_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH0, XMC_UART_CH_INPUT_RXD, USIC0_C0_DX0_P1_4);

  XMC_UART_CH_Start(XMC_UART0_CH0);

  XMC_GPIO_SetMode(UART_TX, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P1_5_AF_U0C0_DOUT0);
}
