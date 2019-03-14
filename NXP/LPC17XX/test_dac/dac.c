/*
 * @brief DAC example
 * This example show how to use the D/A Conversion in 2 modes: Polling and DMA
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include <unistd.h>
#include <stdio.h>

//#define CHIP_LPC175X_6X
//#define CORE_M3

#include "board.h"


#include "remcu.h"

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

 #define DATA_SIZE 0x400
static const char WelcomeMenu[] =
	"Hello NXP Semiconductors \r\n"
	"DAC DEMO \r\n"
	"Press \'c\' to continue or \'x\' to quit\r\n";
static const char SelectMenu[] =
	"Press number 1-2 to choose DAC running mode:\r\n"
	"\t1: Polling Mode \r\n"
	"\t2: DMA Mode \r\n";
static const char DirectionMenu[] =
	"Press \'o\' or \'p\' to change sound frequency\r\n";

/* Work variables */
static volatile uint8_t channelTC, dmaChannelNum;
static volatile uint8_t DAC_Interrupt_Done_Flag, Interrupt_Continue_Flag;
static uint32_t DMAbuffer;

/* DAC sample rate request time */
#define DAC_TIMEOUT 0x3FF

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/
#if 0
/* DMA routine for DAC example */
static void App_DMA_Test(void)
{
	uint32_t tmp = 0;
	uint8_t freq_sound = 0xFF;
	uint8_t uart_buffer = 0;

	DEBUGOUT("DMA mode selected\r\n");
	DEBUGOUT(DirectionMenu);

	/* Initialize GPDMA controller */
	Chip_GPDMA_Init(LPC_GPDMA);

	/* Setup GPDMA interrupt */
	NVIC_DisableIRQ(DMA_IRQn);
	NVIC_SetPriority(DMA_IRQn, ((0x01 << 3) | 0x01));
	NVIC_EnableIRQ(DMA_IRQn);

	/* Get the free channel for DMA transfer */
	dmaChannelNum = Chip_GPDMA_GetFreeChannel(LPC_GPDMA, GPDMA_CONN_DAC);

	/* Output DAC value until get 'x' character */
	while (uart_buffer != 'x') {
		uart_buffer = DEBUGIN();
		if (uart_buffer == 'p') {
			freq_sound++;
		}
		else if (uart_buffer == 'o') {
			freq_sound--;
		}

		/* Start D/A conversion */
		tmp += (freq_sound % DATA_SIZE);
		if (tmp == (DATA_SIZE - 1)) {
			tmp = 0;
		}

		/* pre-format the data to DACR register */
		DMAbuffer = (uint32_t) (DAC_VALUE(tmp) | DAC_BIAS_EN);
		channelTC = 0;
		Chip_GPDMA_Transfer(LPC_GPDMA, dmaChannelNum,
						  (uint32_t) &DMAbuffer,
						  GPDMA_CONN_DAC,
						  GPDMA_TRANSFERTYPE_M2P_CONTROLLER_DMA,
						  1);

		/* Waiting for writing DAC value completed */
		while (channelTC == 0) {}
	}

	/* Disable interrupts, release DMA channel */
	Chip_GPDMA_Stop(LPC_GPDMA, dmaChannelNum);
	NVIC_DisableIRQ(DMA_IRQn);
}
#endif
/* Polling routine for DAC example */
static void App_Polling_Test(void)
{
	uint32_t tmp = 0;
	uint8_t freq_sound = 0xFF;
	uint8_t uart_buffer = 0;

	printf("Select Polling mode\r\n");
	//DEBUGOUT(DirectionMenu);
	while(1){
/*
	while (uart_buffer != 'x') {
		
		uart_buffer = DEBUGIN();
		if (uart_buffer == 'p') {
			freq_sound++;
		}
		else if (uart_buffer == 'o') {
			freq_sound--;
		}

		tmp += (freq_sound % DATA_SIZE);
		if (tmp == (DATA_SIZE - 1)) {
			tmp = 0;
		}
		*/
		Chip_DAC_UpdateValue(LPC_DAC, tmp);

		tmp += 0x99;
		tmp = (tmp % DATA_SIZE);

		printf("dac %x\r\n", tmp);

		/* Wait for DAC (DMA) interrupt request */
		while (!(Chip_DAC_GetIntStatus(LPC_DAC))) {}
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/
#if 0
/**
 * @brief	DMA interrupt handler sub-routine
 * @return	Nothing
 */
void DMA_IRQHandler(void)
{
	if (Chip_GPDMA_Interrupt(LPC_GPDMA, dmaChannelNum) == SUCCESS) {
		channelTC++;
	}
	else {
		/* Error, do nothing */
	}
}
#endif
/**
 * @brief	Main routine for DAC example
 * @return	Nothing
 */

extern void SystemInit(void);

int main(void)
{

		remcu_connect2OpenOCD("localhost", 6666);
remcu_resetRemoteUnit(ResetType::__HALT);
remcu_setVerboseLevel(LevelDebug::__INFO);

	uint8_t bufferUART;
	uint32_t dacClk;
	bool end_Flag = false;

	SystemInit();

	SystemCoreClockUpdate();
	Board_Init();

	/* Setup DAC pins for board and common CHIP code */
	Chip_DAC_Init(LPC_DAC);

	/* Setup DAC timeout for polled and DMA modes to 0x3FF */
#if defined(CHIP_LPC175X_6X)
	/* 175x/6x devices have a DAC divider, set it to 1 */
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_1);
#endif
	Chip_DAC_SetDMATimeOut(LPC_DAC, DAC_TIMEOUT);

	/* Compute and show estimated DAC request time */
#if defined(CHIP_LPC175X_6X)
	dacClk = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_DAC);
#else
	dacClk = Chip_Clock_GetPeripheralClockRate();
#endif
	DEBUGOUT("DAC base clock rate = %dHz, DAC request rate = %dHz\r\n",
		dacClk, (dacClk / DAC_TIMEOUT));

	/* Enable count and DMA support */
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_CNT_ENA | DAC_DMA_ENA);

	App_Polling_Test();
#if 0
	while (!end_Flag) {
		DEBUGOUT(WelcomeMenu);
		while (!end_Flag) {
			bufferUART = 0xFF;
			bufferUART = DEBUGIN();
			if (bufferUART == 'c') {
				DEBUGOUT(SelectMenu);
				bufferUART = 0xFF;
				while (bufferUART == 0xFF) {
					bufferUART = DEBUGIN();
					if ((bufferUART != '1') && (bufferUART != '2') && (bufferUART != '3')) {
						bufferUART = 0xFF;
					}
				}
				switch (bufferUART) {
				case '1':		/* Polling Mode */
					App_Polling_Test();
					break;

				case '2':		/* DMA mode */
					App_DMA_Test();
					break;
				}
				break;
			}
			else if (bufferUART == 'x') {
				end_Flag = true;
				DEBUGOUT("DAC demo terminated!\r\n");
			}
		}
	}
#endif
	return 0;
}

/**
 * @}
 */
