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
** version 1.0.0 (Initial version)				                              **
**                                                                            **
********************************************************************************/

/*******************************************************************************
** Revision History:                                                          **
** Date       version       Details                                           **
** 03-Dec-2014   1.0.0    Initial version of Example project                  **
*******************************************************************************/

#include <XMC4500.h>		//SFR declarations of the selected device
#include <xmc_gpio.h>
#include <xmc_ledts.h>

/*******************************************************************************
** GLOBAL VARIABLE DEFINITIONS:
*******************************************************************************/
/* Touch-Sense Library Variables/Parameters */
uint8_t  LPFilterGain = 8U;
uint16_t SubM[8] = {0, 0, 0x4F, 0, 0, 0, 0, 0x4F};
uint16_t ShortCnt = 0xFFFCU;
uint16_t ErrorCnt = 0xFFEFU;
uint8_t  PADFLAG[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t  PADRESULT[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t  PADERROR[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint32_t LEDTS_Average[8];
uint32_t LEDTS_LowTripVal[8];
uint32_t LEDTS_PadDownCounter[8];
uint8_t  CurrentPadTurn = 0;

/* LED status tracker */
uint8_t  ledstatus = 0;

/*******************************************************************************
** FUNCTION DECLARATIONS:
*******************************************************************************/
void FindTouchedPad(void);

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
  .no_of_led_columns   = XMC_LEDTS_NUMBER_LED_COLUMNS_2,
};

const XMC_LEDTS_TS_CONFIG_BASIC_t ts_basic_config_data =
{
  .common_compare     = XMC_LEDTS_COMMON_COMPARE_ENABLE,
  .counter_auto_reset = XMC_LEDTS_TS_COUNTER_AUTO_RESET_ENABLE,
  .counter_saturation = XMC_LEDTS_TS_COUNTER_SATURATION_ENABLE,
  .no_of_accumulation = XMC_LEDTS_ACCUMULATION_COUNT_2_TIMES,
};

const XMC_LEDTS_TS_CONFIG_ADVANCED_t ts_adv_config_data =
{
  .first_pad_turn   = XMC_LEDTS_PAD_TURN_2,
  .pad_turn_control = XMC_LEDTS_SW_CONTROL_ENABLE,
};

/*******************************************************************************
** MAIN CODE:
*******************************************************************************/
int main(void)
{
	/* Initialize LEDTS features */
	XMC_LEDTS_InitGlobal(XMC_LEDTS0, &global_config_data);
	XMC_LEDTS_InitLED(XMC_LEDTS0, &led_config_data);
	XMC_LEDTS_InitTSBasic(XMC_LEDTS0, &ts_basic_config_data);
	XMC_LEDTS_InitTSAdvanced(XMC_LEDTS0, &ts_adv_config_data);

	/* Configure all LED columns for max brightness */
	XMC_LEDTS_SetColumnBrightness(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, 0xFF);

	/* LEDs are off at start */
	XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, 0x00);

	/* Configure common oscillation window size for touch pads */
	XMC_LEDTS_SetCommonOscillationWindow(XMC_LEDTS0, 0xF0);

    /* Initialize PORT Pins */
	XMC_GPIO_SetMode(XMC_GPIO_PORT5, 10, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4); /* LINE7 */
	XMC_GPIO_SetMode(XMC_GPIO_PORT2, 4, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4); /* LINE2 */
	XMC_GPIO_SetMode(XMC_GPIO_PORT0, 10, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4); /* COL1 */

	/* Initialize PORT Pins for Touch Sense Inputs */
	XMC_GPIO_SetHardwareControl(XMC_GPIO_PORT5, 10, XMC_GPIO_HWCTRL_PERIPHERAL1); /* TSIN7 HW Control Config */
	XMC_GPIO_SetHardwareControl(XMC_GPIO_PORT2, 4, XMC_GPIO_HWCTRL_PERIPHERAL1); /* TSIN2 HW Control Config */

	/* Configure LEDTS Interrupt */
	XMC_LEDTS_EnableInterrupt(XMC_LEDTS0, XMC_LEDTS_INTERRUPT_TIMEFRAME); /* Enable LEDTS Kernel 0 Time Frame Interrupt */
	NVIC_SetPriority(LEDTS0_0_IRQn, 0); /* Set Interrupt Priority for NVIC 30 Node App Instance 0 */
	NVIC_EnableIRQ(LEDTS0_0_IRQn); /* Enable LEDTS Kernel 1 Interrupt Request */

	/* Start LEDTS timer */
	XMC_LEDTS_StartCounter(XMC_LEDTS0, 0x01D5); /* time slice duration = 1ms */

	while(1)
	{

	}
}

/*******************************************************************************
** INTERRUPT HANDLERS:
*******************************************************************************/
void LEDTS0_0_IRQHandler()
{
  if((XMC_LEDTS_ReadInterruptFlag(XMC_LEDTS0) & XMC_LEDTS_INTERRUPT_FLAG_TIMEFRAME) == XMC_LEDTS_INTERRUPT_FLAG_TIMEFRAME)
  {
    /* Time Frame Interrupt has occured */
    /* Clear flag */
	XMC_LEDTS_ClearInterruptFlag(XMC_LEDTS0, XMC_LEDTS_INTERRUPT_FLAG_TIMEFRAME);

    CurrentPadTurn = RD_REG(LEDTS0->FNCTL, LEDTS_FNCTL_PADT_Msk, LEDTS_FNCTL_PADT_Pos);

    /* Call Find Touch Pad */
    FindTouchedPad();

	if(PADRESULT[2]) /* T1 touched */
	{
		if(ledstatus & 0x04) ledstatus &= ~(0x04);
		else ledstatus |= 0x04;
		PADRESULT[2] = 0;
	}
	if(PADRESULT[7]) /* T2 touched */
	{
		if(ledstatus & 0x80) ledstatus &= ~(0x80);
		else ledstatus |= 0x80;
		PADRESULT[7] = 0;
	}
	XMC_LEDTS_SetLEDLinePattern(XMC_LEDTS0, XMC_LEDTS_LED_COLUMN_1, ledstatus); /* update LEDs */
	if(PADERROR[2])
	{
		PADERROR[2] = 0; /* ignore long touch */
	}
	if(PADERROR[7])
	{
		PADERROR[7] = 0; /* ignore long touch */
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
	PadIndex = (uint8_t)RD_REG(LEDTS0->FNCTL, LEDTS_FNCTL_PADT_Msk, LEDTS_FNCTL_PADT_Pos);

	/* Take the accumulated TSCounter value */
	TotalTSCnt = XMC_LEDTS_ReadTSVAL(XMC_LEDTS0);

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
    if(1 == RD_REG(LEDTS0->FNCTL,LEDTS_FNCTL_PADTSW_Msk, LEDTS_FNCTL_PADTSW_Pos))
    {
      if(CurrentPadTurn == 2)
      {
    	  CurrentPadTurn = 7;
      }
      else if(CurrentPadTurn == 7)
      {
    	  CurrentPadTurn = 2;
      }
	  /* End of code portion where modification can be done for setting
	     the sequence of active pad turn in SW pad turn control  */

	  /* write next padt for SW pad turn */
	  WR_REG(LEDTS0->FNCTL, LEDTS_FNCTL_PADT_Msk, LEDTS_FNCTL_PADT_Pos, CurrentPadTurn);
    }
    else
    {
      /* Do Nothing - For HW pad turn HW automatically scans in Round Robin */
    }

}
