#include <stdio.h>
#include <xmc_uart.h>

#if defined(__GNUC__)
int _write(int fd, const void *buf, size_t count)
{
  (void)fd;

  for (int i = 0; i < count; ++i)
  {
    XMC_UART_CH_Transmit(XMC_UART0_CH0, *(const uint8_t *)buf);
    buf++;
  }
  return count;
}

int _read(int fd, void *buf, size_t count)
{
  int char_cnt = 0;
  (void)fd;

  while ((XMC_UART_CH_GetStatusFlag(XMC_UART0_CH0) & (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                                      XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION)) == 0);

  char_cnt++;
  *(uint8_t *)buf = XMC_UART_CH_GetReceivedData(XMC_UART0_CH0);

  XMC_UART_CH_ClearStatusFlag(XMC_UART0_CH0, XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                             XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION);

  return char_cnt;
}
#endif


#if defined(__CC_ARM)
int stdout_putchar(int ch, FILE *f)
{
  (void)f;
  XMC_UART_CH_Transmit(XMC_UART0_CH0, ch);
	return ch;
}

int stdin_getchar(FILE *f)
{
  (void)f;
	int result;
	
  while ((XMC_UART_CH_GetStatusFlag(XMC_UART0_CH0) & (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                                      XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION)) == 0);

  result = XMC_UART_CH_GetReceivedData(XMC_UART0_CH0);

  XMC_UART_CH_ClearStatusFlag(XMC_UART0_CH0, XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                             XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION);

  return result;
}
#endif

#if defined(__ICCARM__)
size_t __write(int handle, const unsigned char *buffer, size_t size)
{
  (void)handle;

  for (int i = 0; i < size; ++i)
  {
    XMC_UART_CH_Transmit(XMC_UART0_CH0, *(const uint8_t *)buffer);
    buffer++;
  }
  return size;
}

int __read(int fd, void *buf, size_t count)
{
  int char_cnt = 0;
  (void)fd;

  while ((XMC_UART_CH_GetStatusFlag(XMC_UART0_CH0) & (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                                      XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION)) == 0);

  char_cnt++;
  *(uint8_t *)buf = XMC_UART_CH_GetReceivedData(XMC_UART0_CH0);

  XMC_UART_CH_ClearStatusFlag(XMC_UART0_CH0, XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                             XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION);

  return char_cnt;
}
#endif

