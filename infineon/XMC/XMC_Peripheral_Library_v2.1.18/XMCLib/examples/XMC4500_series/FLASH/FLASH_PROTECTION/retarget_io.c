#include <stdio.h>
#include <xmc_uart.h>

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

#if 0
  for (int i = 0; i < count; ++i)
  {
#endif
    while ((XMC_UART_CH_GetStatusFlag(XMC_UART0_CH0) & (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                                        XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION)) == 0);

    char_cnt++;
    *(uint8_t *)buf = XMC_UART_CH_GetReceivedData(XMC_UART0_CH0);

    XMC_UART_CH_ClearStatusFlag(XMC_UART0_CH0, XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                               XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION);

#if 0
    /* Stop reading if CR (Ox0D) character is received */
    if (*(uint8_t *)buf == 0x0DU)
    {
      /* New line character (CR) received ? */
      *(uint8_t*)buf = '\n';           /* Yes, convert LF to '\n' char. */
      break;                           /* Stop loop and return received char(s) */
    }

    buf++;
  }
#endif

  return char_cnt;
}
