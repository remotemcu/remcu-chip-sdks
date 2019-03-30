/*******************************************************************************
 Copyright (c) 2014, Infineon Technologies AG                                 **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its contributors **
 may be used to endorse or promote products derived from this software without**
 specific prior written permission.                                           **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
********************************************************************************
**                                                                            **
** PLATFORM : Infineon XMC1200 Series                                         **
**                                                                            **
** AUTHOR   : Application Engineering Team                                    **
**                                                                            **
** version 1.0.0 (Initial version)                                            **
**                                                                            **
********************************************************************************/

/*******************************************************************************
** Revision History:                                                          **
** Date       version       Details                                           **
** 03-Dec-2014   1.0.0    Initial version of Example project                  **
*******************************************************************************/

#include <xmc_gpio.h>
#include <xmc_ledts.h>

/*******************************************************************************
** MACRO DEFINITIONS:
*******************************************************************************/
/* Ticks are generated every 0.1s */
#define  TICKS_PER_SECOND 10UL
/* Maximum number of characters supported for Seven segment display */
#define  COUNT 51U

/*******************************************************************************
** GLOBAL VARIABLE DEFINITIONS:
*******************************************************************************/
/* Touch-Sense Library Variables/Parameters */
uint8_t  LPFilterGain = 4U;
uint16_t SubM[8] = {0x30, 0, 0, 0, 0x14, 0x14, 0, 0};
uint16_t ShortCnt = 0xFFF7U;
uint16_t ErrorCnt = 0xFF7FU;
uint8_t  PADFLAG[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t  PADRESULT[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t  PADERROR[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint32_t LEDTS_Average[8];
uint32_t LEDTS_LowTripVal[8];
uint32_t LEDTS_PadDownCounter[8];
uint8_t  CurrentPadTurn = 0;

/* Application mode: 0 (LED Display Mode), 1 (Touchpad Mode) */
uint8_t  touchmode = 0;

/* Counter for LED Display Mode */
uint8_t  uiCounter = 0 ;

/* Array containing display characters */
uint8_t  symbol[8] = {'H','E','L','L','O','.','.','.'};

/*******************************************************************************
** FUNCTION DECLARATIONS:
*******************************************************************************/
void FindTouchedPad(void);

/*******************************************************************************
 * @brief This function returns the Symbol pattern.
 *
 * @param[in]  val of type uint32_t
 *
 * @return  None <BR>
 *
 * <b>Reentrant: Yes </b><BR>
********************************************************************************/
uint8_t GetSymbolPattern(char Symbol)
{
  /* Look up table with pattern values for Seven Segment character display */
  uint8_t Look_Up_Table[COUNT][2U]={
                                     {0U,  0X0U},  /* NULL */
                                     {45U, 0X02U}, /* - */
                                     {46U, 0X01U}, /* . */ /**/
                                     {48U, 0XFCU}, /* 0 */
                                     {49U, 0X60U}, /* 1 */
                                     {50U, 0XDAU}, /* 2 */
                                     {51U, 0XF2U}, /* 3 */
                                     {52U, 0X66U}, /* 4 */
                                     {53U, 0XB6U}, /* 5 */
                                     {54U, 0XBEU}, /* 6 */
                                     {55U, 0XE0U}, /* 7 */
                                     {56U, 0XFEU}, /* 8 */
                                     {57U, 0XF6U}, /* 9 */ /**/
                                     {65U, 0XEEU}, /* A */
                                     {66U, 0XFEU}, /* B */
                                     {67U, 0X9CU}, /* C */
                                     {68U, 0XFCU}, /* D */
                                     {69U, 0X9EU}, /* E */
                                     {70U, 0X8EU}, /* F */
                                     {71U, 0XBCU}, /* G */
                                     {72U, 0X6EU}, /* H */
                                     {73U, 0X0CU}, /* I */
                                     {74U, 0X78U}, /* J */
                                                   /* K */
                                     {76U, 0X1CU}, /* L */
                                                   /* M */
                                                   /* N */
                                     {79U, 0XFCU}, /* O */
                                     {80U, 0XCEU}, /* P */
                                                   /* Q */
                                     {82U, 0XEEU}, /* R */
                                     {83U, 0XB6U}, /* S */
                                                   /* T */
                                     {85U, 0X7CU}, /* U */
                                                   /* V */
                                                   /* W */
                                                   /* X */
                                     {89U, 0X66U}, /* Y */
                                     {90U, 0XDAU}, /* Z */ /**/
                                     {91U, 0X9CU}, /* [ */
                                     {92U, 0XF0U}, /* ] */
                                     {95U, 0X10U}, /* _ */
                                     {97U, 0XFAU}, /* a */
                                     {98U, 0X3EU}, /* b */
                                     {99U, 0X1AU}, /* c */
                                     {100U, 0X7AU}, /* d */
                                     {101U, 0XDEU}, /* e */
                                                    /* f */
                                     {103U, 0XF6U}, /* g */
                                     {104U, 0X2EU}, /* h */
                                     {105U, 0X06U}, /* i */
                                     {106U, 0X07U}, /* j */
                                                    /* k */
                                     {108U, 0X0CU}, /* l */
                                                    /* m */
                                                    /* n */
                                     {111U, 0X3AU}, /* o */
                                                    /* p */
                                     {113U, 0XF6U}, /* q */
                                     {114U, 0XCCU}, /* r */
                                                    /* s */
                                     {116U, 0X1EU}, /* t */
                                     {117U, 0X38U}, /* u */
                                                    /* v */
                                                    /* w */
                                                    /* x */
                                     {121U, 0X76U}, /* y */
                                                    /* z */ /**/
                                     {124U, 0X60U}  /* | */
                                   };
  /* Loop counter */
  uint8_t i;

  /* This variable is used to store the pattern of Seven segment display */
  uint8_t Pattern = 0U;

  /* Loop and get the symbol pattern from Look Up Table */
  for (i=0U; i < COUNT; i++)
  {
    if ((uint8_t) Symbol == Look_Up_Table[i][0])
    {
      /* Assign the symbol pattern */
      Pattern = Look_Up_Table[i][1];
      i = COUNT; /* Break from 'for loop'. Equivalent to break statement. */
    }
  }

  /* Return the seven segment pattern */
  return (Pattern);
}

/*******************************************************************************
** LEDTS CONFIGURATION HANDLES:
*******************************************************************************/
const XMC_LEDTS_GLOBAL_CONFIG_t global_config_data0 =
{
  .suspend_response         = XMC_LEDTS_SUSPEND_ENABLE,
  .clock_generation         = XMC_LEDTS_CLOCK_TYPE_MASTER,
  .autoscan_synchronization = XMC_LEDTS_TP_SYNC_DISABLE
};

const XMC_LEDTS_LED_CONFIG_t led_config_data0 =
{
  .column_active_level = XMC_LEDTS_ACTIVE_LEVEL_LED_COL_LOW,
  .no_of_led_columns   = XMC_LEDTS_NUMBER_LED_COLUMNS_8,
};

const XMC_LEDTS_GLOBAL_CONFIG_t global_config_data1 =
{
  .suspend_response         = XMC_LEDTS_SUSPEND_ENABLE,
  .clock_generation         = XMC_LEDTS_CLOCK_TYPE_MASTER,
  .autoscan_synchronization = XMC_LEDTS_TP_SYNC_DISABLE
};

const XMC_LEDTS_TS_CONFIG_BASIC_t ts_basic_config_data1 =
{
  .common_compare     = XMC_LEDTS_COMMON_COMPARE_ENABLE,
  .counter_auto_reset = XMC_LEDTS_TS_COUNTER_AUTO_RESET_ENABLE,
  .counter_saturation = XMC_LEDTS_TS_COUNTER_SATURATION_ENABLE,
  .no_of_accumulation = XMC_LEDTS_ACCUMULATION_COUNT_2_TIMES,
  .no_of_touch_inputs = XMC_LEDTS_NUMBER_TS_INPUT_8
};

const XMC_LEDTS_TS_CONFIG_ADVANCED_t ts_adv_config_data1 =
{
  .first_pad_turn   = XMC_LEDTS_PAD_TURN_0,
  .pad_turn_control = XMC_LEDTS_SW_CONTROL_ENABLE,
};

/*******************************************************************************
** MAIN CODE:
*******************************************************************************/
int main(void)
{
  /* Initialize LEDTS features */
  XMC_LEDTS_InitGlobal(XMC_LEDTS0, &global_config_data0);
  XMC_LEDTS_InitLED(XMC_LEDTS0, &led_config_data0);
  XMC_LEDTS_InitGlobal(XMC_LEDTS1, &global_config_data1);
  XMC_LEDTS_InitTSBasic(XMC_LEDTS1, &ts_basic_config_data1);
  XMC_LEDTS_InitTSAdvanced(XMC_LEDTS1, &ts_adv_config_data1);

  /* Configure all LED columns for max brightness */
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, 0xFF);
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, 0xFF);
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, 0xFF);
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, 0xFF);
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, 0xFF);
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, 0xFF);
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, 0xFF);
  XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, 0xFF);

  /* Display nothing at start (clear display) */
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, GetSymbolPattern(' '));
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, GetSymbolPattern(' '));
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, GetSymbolPattern(' '));
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, GetSymbolPattern(' '));
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, GetSymbolPattern(' '));
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, GetSymbolPattern(' '));
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, GetSymbolPattern(' '));
  XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, GetSymbolPattern(' '));

  /* Configure common oscillation window size for touch pads */
  XMC_LEDTS_SetCommonOscillationWindow(XMC_LEDTS1, 0x10);

  /* Initialize PORT Pins */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 0, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE7 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE6 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE5 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE4 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE3 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE2 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 6, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE1 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 7, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2); /* LINE0 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 5, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COLA */
  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 0, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COL0 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COL1 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COL2 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 3, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COL3 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COL4 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 10, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COL5 */
  XMC_GPIO_SetMode(XMC_GPIO_PORT0, 9, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT3); /* COL6 */

  /* Initialize PORT Pins for Touch Sense Inputs */
  XMC_GPIO_SetHardwareControl(XMC_GPIO_PORT0, 8, XMC_GPIO_HWCTRL_PERIPHERAL1); /* TSIN7 HW Control Config */
  XMC_GPIO_SetInputHysteresis(XMC_GPIO_PORT0, 8, XMC_GPIO_INPUT_HYSTERESIS_LARGE); /* TSIN7 Hysteresis Config */
  XMC_GPIO_SetHardwareControl(XMC_GPIO_PORT0, 12, XMC_GPIO_HWCTRL_PERIPHERAL1); /* TSIN3 HW Control Config */
  XMC_GPIO_SetInputHysteresis(XMC_GPIO_PORT0, 12, XMC_GPIO_INPUT_HYSTERESIS_LARGE); /* TSIN3 Hysteresis Config */
  XMC_GPIO_SetHardwareControl(XMC_GPIO_PORT0, 13, XMC_GPIO_HWCTRL_PERIPHERAL1); /* TSIN2 HW Control Config */
  XMC_GPIO_SetInputHysteresis(XMC_GPIO_PORT0, 13, XMC_GPIO_INPUT_HYSTERESIS_LARGE); /* TSIN2 Hysteresis Config */

  /* Configure LEDTS Interrupt */
  XMC_LEDTS_EnableInterrupt(XMC_LEDTS1, XMC_LEDTS_INTERRUPT_TIMEFRAME); /* Enable LEDTS Kernel 1 Time Frame Interrupt */
  NVIC_SetPriority(LEDTS1_0_IRQn, 0); /* Set Interrupt Priority for NVIC 30 Node App Instance 0 */
  NVIC_EnableIRQ(LEDTS1_0_IRQn); /* Enable LEDTS Kernel 1 Interrupt Request */

  /* Start LEDTS timer */
  XMC_LEDTS_StartCounter(XMC_LEDTS1, 0x0080); /* time slice duration = 1.048ms */
  XMC_LEDTS_StartCounter(XMC_LEDTS0, 0x0020); /* time slice duration = 256us */

  /* System Timer initialization */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
  }
}

/*******************************************************************************
** INTERRUPT HANDLERS:
*******************************************************************************/
/* System Timer Handler */
void SysTick_Handler(void)
{
  if(++uiCounter == 10)
  {
    /*Display "HELLO..."*/
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, GetSymbolPattern(symbol[0]));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, GetSymbolPattern(symbol[1]));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, GetSymbolPattern(symbol[2]));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, GetSymbolPattern(symbol[3]));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, GetSymbolPattern(symbol[4]));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, GetSymbolPattern(symbol[5]));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, GetSymbolPattern(symbol[6]));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, GetSymbolPattern(symbol[7]));
  }
  else if(uiCounter == 20)
  {
    /*Display "12345678"*/
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, GetSymbolPattern('1'));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, GetSymbolPattern('2'));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, GetSymbolPattern('3'));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, GetSymbolPattern('4'));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, GetSymbolPattern('5'));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, GetSymbolPattern('6'));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, GetSymbolPattern('7'));
    XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, GetSymbolPattern('8'));
    uiCounter = 0;
  }
}

/* LEDTS Kernel 1 Handler */
void LEDTS1_0_IRQHandler()
{
  if((XMC_LEDTS_ReadInterruptFlag(XMC_LEDTS1) & XMC_LEDTS_INTERRUPT_FLAG_TIMEFRAME) == XMC_LEDTS_INTERRUPT_FLAG_TIMEFRAME)
  {
    /* Time Frame Interrupt has occured */
    /* Clear flag */
    XMC_LEDTS_ClearInterruptFlag(XMC_LEDTS1, XMC_LEDTS_INTERRUPT_FLAG_TIMEFRAME);

    CurrentPadTurn = RD_REG(LEDTS1->FNCTL, LEDTS_FNCTL_PADT_Msk, LEDTS_FNCTL_PADT_Pos);

    /* Call Find Touch Pad */
    FindTouchedPad();

    if(touchmode == 1)
    {
        if(PADRESULT[0]) /* TP_A touched */
        {
            /*Display "----tP_A"*/
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, GetSymbolPattern('t'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, GetSymbolPattern('P'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, GetSymbolPattern('_'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, GetSymbolPattern('A'));
            PADRESULT[0] = 0;
        }
        if(PADRESULT[4]) /* TP_B touched */
        {
            /*Display "--tP_b--"*/
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, GetSymbolPattern('t'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, GetSymbolPattern('P'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, GetSymbolPattern('_'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, GetSymbolPattern('b'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, GetSymbolPattern('-'));
            PADRESULT[4] = 0;
        }
        if(PADRESULT[5]) /* TP_C touched */
        {
            /*Display "tP_C----"*/
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, GetSymbolPattern('t'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, GetSymbolPattern('P'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, GetSymbolPattern('_'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, GetSymbolPattern('C'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, GetSymbolPattern('-'));
            XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, GetSymbolPattern('-'));
            PADRESULT[5] = 0;
        }
    }
    else /* touchmode = 0 */
    {
        PADRESULT[CurrentPadTurn] = 0;
        /* do nothing - LED display handled in SysTick_Handler(), all short touch ignored */
    }
    if(PADERROR[CurrentPadTurn] == 1) /* long touch */
    {
        touchmode ^= 1; /* switch mode */

        /*Clear Display*/
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_A, GetSymbolPattern(' '));
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_0, GetSymbolPattern(' '));
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, GetSymbolPattern(' '));
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_2, GetSymbolPattern(' '));
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_3, GetSymbolPattern(' '));
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_4, GetSymbolPattern(' '));
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_5, GetSymbolPattern(' '));
        XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_6, GetSymbolPattern(' '));

        PADERROR[CurrentPadTurn] = 0;

        if(touchmode == 0)
        {
            /* Reset counter to show display (handled by SysTick_Handler) */
            uiCounter = 0;
        }
        else
        {
            /* Ignore display commands by SysTick_Handler */
            uiCounter = 21;
        }
    }

  }
}

/*******************************************************************************
** TOUCH SENSE LIBRARY FUNCTION:
*******************************************************************************/
/* This function utilizes the TSVAL.TSCTRVALR value and calculates
 * average values. The average values are used to determine if any
 * of the touch pads are touched.
 */
void FindTouchedPad(void)
{
    uint8_t PadIndex = 0U;
    uint16_t TotalTSCnt = 0U;
    uint32_t CrrntComprsnVal = 0U;

    /* Get current PadTurnIndex */
    PadIndex = (uint8_t)RD_REG(LEDTS1->FNCTL, LEDTS_FNCTL_PADT_Msk, LEDTS_FNCTL_PADT_Pos);

    /* Take the accumulated TSCounter value */
    TotalTSCnt = XMC_LEDTS_ReadTSVAL(XMC_LEDTS1);

    if (0U == PADFLAG[PadIndex])
    {
        /* Calculate New Average */
        LEDTS_Average[PadIndex] = (LEDTS_Average[PadIndex] + \
                      TotalTSCnt) - (LEDTS_Average[PadIndex] / (uint32_t)LPFilterGain);

        if(LEDTS_Average[PadIndex] > SubM[PadIndex])
        /* check to avoid error if tscount sum is 0x0000 for 1st iteration */
        {
           LEDTS_LowTripVal[PadIndex] =  LEDTS_Average[PadIndex] -\
                                              (uint32_t)SubM[PadIndex];
        }
    }
    else
    {
    /* Do nothing - Only if PadFlag for the pad is 0,
    Calculate Average and LowTrip,else proceed to analyzing condition for Touch */
    }

    CrrntComprsnVal = (uint32_t)TotalTSCnt * (uint32_t)LPFilterGain;

    if(CrrntComprsnVal < LEDTS_LowTripVal[PadIndex])
    {
        if(0U == PADERROR[PadIndex])
        {
            if(0U == PADRESULT[PadIndex])
            {
                if(0U == PADFLAG[PadIndex])
                {
                    PADFLAG[PadIndex] = 1;
                    LEDTS_PadDownCounter[PadIndex] = 0xFFFFU;
                }
                else
                {
                    if(0U == LEDTS_PadDownCounter[PadIndex])
                    {
                        PADERROR[PadIndex] = 1;
                        PADFLAG[PadIndex] = 0;
                    }
                    else if(--LEDTS_PadDownCounter[PadIndex] == ErrorCnt)
                    {
                        LEDTS_PadDownCounter[PadIndex] = 0U;
                    }
                }
            }
        }
    }
    else
    {
        if(0 != PADFLAG[PadIndex]) // finger is released
        {
            if(LEDTS_PadDownCounter[PadIndex] < ShortCnt) PADRESULT[PadIndex] = 1;
            PADFLAG[PadIndex] = 0;
            LEDTS_PadDownCounter[PadIndex] = 0;
        }
    }

    /* For SW padturn next pad to be analyzed is to be set by SW
       Set this PADT value.....You can change the below portion
       of code to set the sequence of active pad turn........ */
    if(1 == RD_REG(LEDTS1->FNCTL,LEDTS_FNCTL_PADTSW_Msk, LEDTS_FNCTL_PADTSW_Pos))
    {
      if(CurrentPadTurn == 0)
      {
          CurrentPadTurn = 4;
      }
      else if(CurrentPadTurn == 4)
      {
          CurrentPadTurn = 5;
      }
      else if(CurrentPadTurn == 5)
      {
          CurrentPadTurn = 0;
      }
      /* End of code portion where modification can be done for setting
         the sequence of active pad turn in SW pad turn control  */

      /* write next padt for SW pad turn */
      WR_REG(LEDTS1->FNCTL, LEDTS_FNCTL_PADT_Msk, LEDTS_FNCTL_PADT_Pos, CurrentPadTurn);
    }
    else
    {
      /* Do Nothing - For HW pad turn HW automatically scans in Round Robin */
    }

}
