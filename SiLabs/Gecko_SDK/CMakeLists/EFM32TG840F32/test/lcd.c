#include <stdint.h>
#include <stdbool.h>

#include "device_defines.h"

#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"

#include <unistd.h>
#include <stdio.h>
#include <assert.h>

#include "remcu.h"

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(int argc, char** argv)
{
  printf("argc : %d\n", argc);

  if(argc < 3){
        printf("test requare 2 arguments: host and port\n");
        return -1;
    }
    const char * host = argv[1];
    printf("argv[1] : %s\n", argv[1]);
    printf("argv[2] : %s\n", argv[2]);
    const uint16_t port = (atoi(argv[2]) & 0xFFFF);
    printf("port : %d\n", port);

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

remcu_resetRemoteUnit(__HALT);
//remcu_setVerboseLevel(LevelDebug::__INFO);
remcu_setVerboseLevel(__ERROR);

  assert(remcu_is_connected());
  /* Chip errata */
  CHIP_Init();

  /* Enable LCD without voltage boost */
  SegmentLCD_Init(false);

  /* Run Energy Mode with LCD demo, see lcdtest.c */
  int i, numberOfIterations = 0;

  SegmentLCD_AllOff();

  //SegmentLCD_Symbol(LCD_SYMBOL_PAD0, 1);
  //SegmentLCD_Symbol(LCD_SYMBOL_PAD1, 1);

  sleep(1);
  SegmentLCD_Symbol(LCD_SYMBOL_GECKO, 1);
      SegmentLCD_Symbol(LCD_SYMBOL_EFM32, 1);

  while(1){
      sleep(1);
      SegmentLCD_Write("REMCU");

      sleep(1);
      SegmentLCD_Write("     ");
    }

  /* Never going to reach this statement. Infinte loop in Test(). */
  return 0;
}