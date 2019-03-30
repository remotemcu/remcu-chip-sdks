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
#include <xmc1_scu.h>

/*******************************************************************************
** MACRO DEFINITIONS:
*******************************************************************************/
/* Ticks are generated every 0.1s */
#define TICKS_PER_SECOND 10UL
/* Maximum number of characters supported for Seven segment display */
#define COUNT 51U

/*******************************************************************************
** GLOBAL VARIABLE DEFINITIONS:
*******************************************************************************/
/* Array containing display characters */
uint8_t symbol[8] = {'H','E','L','L','O','.','.','.'};

/*******************************************************************************
** FUNCTION DECLARATIONS:
*******************************************************************************/
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
const XMC_LEDTS_GLOBAL_CONFIG_t global_config_data =
{
  .suspend_response         = XMC_LEDTS_SUSPEND_ENABLE,
  .clock_generation         = XMC_LEDTS_CLOCK_TYPE_MASTER,
  .autoscan_synchronization = XMC_LEDTS_TP_SYNC_DISABLE
};

const XMC_LEDTS_LED_CONFIG_t led_config_data =
{
  .column_active_level = XMC_LEDTS_ACTIVE_LEVEL_LED_COL_LOW,
  .no_of_led_columns   = XMC_LEDTS_NUMBER_LED_COLUMNS_8,
};

/*******************************************************************************
** MAIN CODE:
*******************************************************************************/
int main(void)
{
  XMC_LEDTS_STATUS_t init_status;

  init_status = XMC_LEDTS_InitGlobal(XMC_LEDTS0, &global_config_data);
  init_status |= XMC_LEDTS_InitLED(XMC_LEDTS0, &led_config_data);
  
  XMC_ASSERT("Initialization sequence of LEDTS module failed\n", (init_status == XMC_LEDTS_STATUS_SUCCESS));

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

  /* Start LEDTS timer */
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
  static uint8_t uiCounter = 0 ;

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
