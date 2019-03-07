#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "segmentlcd.h"

#include <unistd.h>
#include <stdio.h>

#include "remcu.h"

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{

	remcu_connect2OpenOCD("localhost", 6666);
remcu_resetRemoteUnit(ResetType::__HALT);
remcu_setVerboseLevel(LevelDebug::__INFO);
  /* Chip errata */
  CHIP_Init();

  /* Enable LCD without voltage boost */
  SegmentLCD_Init(false);

  /* Run Energy Mode with LCD demo, see lcdtest.c */
  int i, numberOfIterations = 0;

  SegmentLCD_AllOff();

  SegmentLCD_Symbol(LCD_SYMBOL_PAD0, 1);
  SegmentLCD_Symbol(LCD_SYMBOL_PAD1, 1);

  sleep(1);
  SegmentLCD_Symbol(LCD_SYMBOL_GECKO, 1);
      SegmentLCD_Symbol(LCD_SYMBOL_EFM32, 1);
      SegmentLCD_Write(" TINY  ");

      sleep(33);

  /* Never going to reach this statement. Infinte loop in Test(). */
  return 0;
}