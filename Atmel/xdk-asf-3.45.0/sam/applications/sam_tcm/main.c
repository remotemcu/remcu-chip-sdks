/**
 * \file
 *
 * \brief Main application of SAM TCM Demo.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

/**
 *  \mainpage tcm TCM (Tightly Coupled Memory) Example
 *
 *  \section Purpose
 *
 *  The tcm example will help new users get familiar with Atmel's
 *  SAMV7 family of microcontroller's tcm memory and there are benefits to
 *  run code with low latency.
 *
 *  \section Requirements
 *
 *  This package can be used with SAM V71 Xplained Ultra board.
 *
 *  \section Description
 *
 *  The demonstration program compares the performance between normal 'memcpy'
 *  and 'TCM memcpy'.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the SAM V71 Xplained Ultra board.
 *     Please refer to the Getting Started with SAM V71 Microcontrollers.pdf
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 baud rates
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the following text should appear
 *  (values depend on the board and chip used):
 *     \code
 *      -- TCM memory Example xxx --
 *      -- xxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *
 *  \section References
 *  - tcm/main.c
 *  - board.h
 */

/**
 *  Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "asf.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE       0x1000

#define RESET_CYCLE_COUNTER()  do { \
	CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; \
	__DSB(); DWT->LAR = 0xC5ACCE55; __DSB(); \
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; \
	DWT->CYCCNT = 0; \
	DWT->CTRL = DWT_CTRL_CYCCNTENA_Msk; \
}while(0)

#define GET_CYCLE_COUNTER(x)                x=DWT->CYCCNT;

/* IAR Ewarm */
#if defined ( __ICCARM__ ) 
#pragma location = ".data_TCM"
 /* GCC || MDK */
#elif defined (  __GNUC__  ) || defined (__CC_ARM) 
__attribute__((__section__(".data_TCM")))
#endif
uint8_t tcm_destbuff[3*BUFF_SIZE];

/* IAR Ewarm */
#if defined ( __ICCARM__ ) 
#pragma location = ".data_TCM"
/* GCC || MDK */
#elif defined (  __GNUC__  ) || defined (__CC_ARM)  
__attribute__((__section__(".data_TCM")))
#endif
uint8_t tcm_srcbuff[BUFF_SIZE];

const char *pBuffer = "The ARM architecture is defined in a hierarchical manner,\
where the features are described in Chapter A2\
Application Level Programmers?Model at the application level,\
with underlying system support. What features are available and how they are \
supported is defined in the architecture profiles, making the system \
level support profile specific. Deprecated features can be found in an \
appendix to this manual. See page. As stated in Privileged execution on page \
A2-13, programs can execute in a privileged or unprivileged manner. System \
level support requires privileged access, allowing it the access permissions \
to configure and control the resources. This is typically supported by an \
operating system, which provides system services to the applications, either \
transparently, or through application initiated service calls. The operating \
system is also responsible for servicing interrupts and other system events, \
making exceptions a key component of the system level programmers?model.";

uint8_t destbuff[3*BUFF_SIZE], srcbuff[BUFF_SIZE];

static uint32_t cyclecounter;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/* IAR Ewarm */
#if defined ( __ICCARM__ )
#pragma default_function_attributes = @ ".code_TCM"
/* GCC || MDK */
#elif defined (  __GNUC__  ) || defined (__CC_ARM)  
__attribute__((__section__(".code_TCM")))
#endif
static uint32_t tcm_memcpy(uint8_t *pDest, uint8_t *pSrc, uint16_t len)
{
	/* clean destination and source buffer */
	memset(tcm_srcbuff, 0, len);
	__DSB();
	__ISB();
	memset(tcm_destbuff, 0, len);
	__DSB();
	__ISB();

	/* copy buffer to TCM source buffer */
	memcpy(pSrc, pBuffer,len);
	__DSB();
	__ISB();

	/* Disable and reset DWT cycle counter */
	RESET_CYCLE_COUNTER();
	/* Copy from DTCM source buffer to DTCM destination buffer */
	{
		uint32_t i;
		uint8_t * pTmpD = pDest;
		uint8_t * pTmpS;
		for(i=0, pTmpS = pSrc; i<len; i++) {
			*pTmpD++ = *pTmpS++;
		}
		for(i=0, pTmpS = pSrc; i<len; i++) {
			*pTmpD++ = *pTmpS++;
		}
		for(i=0, pTmpS = pSrc; i<len; i++) {
			*pTmpD++ = *pTmpS++;
		}
	}
	GET_CYCLE_COUNTER(cyclecounter);
	return cyclecounter ;
}


static uint32_t normal_memcpy(uint8_t *pDest, uint8_t *pSrc, uint16_t len)
{
	memset(srcbuff, 0, len);
	__DSB();
	__ISB();
	memset(destbuff, 0, len);
	__DSB();
	__ISB();
	memcpy(srcbuff, pBuffer,len);
	__DSB();
	__ISB();

	/* Disable and reset DWT cycle counter */
	RESET_CYCLE_COUNTER();
	/* Copy from DTCM source buffer to DTCM destination buffer */
	{
		uint32_t i;
		uint8_t * pTmpD = pDest;
		uint8_t * pTmpS;
		for(i=0, pTmpS = pSrc; i<len; i++) {
			*pTmpD++ = *pTmpS++;
		}
		for(i=0, pTmpS = pSrc; i<len; i++) {
			*pTmpD++ = *pTmpS++;
		}
		for(i=0, pTmpS = pSrc; i<len; i++) {
			*pTmpD++ = *pTmpS++;
		}
	}
	GET_CYCLE_COUNTER(cyclecounter);
	return cyclecounter ;
}

static uint32_t recursive(uint32_t n)
{
	volatile uint32_t tmp = n;
	if(0 == tmp) {
		return 0;
	}
	else {
		return n + recursive(tmp - 1);
	}
}

static uint32_t stack_test(uint32_t n)
{
	uint32_t sum;
	RESET_CYCLE_COUNTER();
	sum = recursive(n);
	GET_CYCLE_COUNTER(cyclecounter);
	printf("\r\n Sum of 1 to %u is %u, ", (unsigned)n, (unsigned)sum);
	return cyclecounter;
}

/* IAR Ewarm */
#if defined ( __ICCARM__ )
#pragma section = "CSTACK"
#pragma section = "CSTACK_DTCM"
	#define SRAM_STACK_BASE     (__section_begin("CSTACK"))
	#define DTCM_STACK_BASE     (__section_begin("CSTACK_DTCM"))
	#define SRAM_STACK_LIMIT    (__section_end("CSTACK"))
	#define DTCM_STACK_LIMIT    (__section_end("CSTACK_DTCM"))
/* MDK */
#elif defined (__CC_ARM)
	extern uint32_t Image$$ARM_LIB_STACK$$Base;
	extern uint32_t Image$$ARM_LIB_STACK$$ZI$$Limit;
	extern uint32_t Image$$DTCM_STACK$$Base;
	extern uint32_t Image$$DTCM_STACK$$ZI$$Limit;
	#define SRAM_STACK_BASE     (&Image$$ARM_LIB_STACK$$Base)
	#define DTCM_STACK_BASE     (&Image$$DTCM_STACK$$Base)
	#define SRAM_STACK_LIMIT    (&Image$$ARM_LIB_STACK$$ZI$$Limit)
	#define DTCM_STACK_LIMIT    (&Image$$DTCM_STACK$$ZI$$Limit)
/* GCC */
#elif defined (  __GNUC__  )  
	extern char _sdtcm_stack, _edtcm_stack, _sstack, _estack;
	#define SRAM_STACK_BASE     ((void *)(&_sstack))
	#define DTCM_STACK_BASE     ((void *)(&_sdtcm_stack))
	#define SRAM_STACK_LIMIT    ((void *)(&_estack))
	#define DTCM_STACK_LIMIT    ((void *)(&_edtcm_stack))
#endif

/** \brief  Change stack's location to DTCM
*
* The function changes the stack's location from SRAM to DTCM
*/
static void tcm_stackinit(void)
{
	uint32_t offset = (uint32_t)SRAM_STACK_LIMIT - (uint32_t)DTCM_STACK_LIMIT;
	volatile char *dst = (volatile char *)DTCM_STACK_LIMIT;
	volatile char *src = (volatile char *)SRAM_STACK_LIMIT;
	/* copy stack data from SRAM to DTCM */
	while(src > (volatile char *)SRAM_STACK_BASE){
		*--dst = *--src;
	}
	__set_MSP(__get_MSP() - offset);
}

/**
*  Configure UART console.
*/
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  \brief Application entry point for TCM example.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main( void )
{
	uint32_t cyclecounteroffset = 0;
	uint32_t cycles=0;

	sysclk_init();
	board_init();

	SCB_DisableICache();
	SCB_DisableDCache();

	/* Initialize debug console */
	configure_console();

	/* Output example information */
	printf( "\n\r-- TCM memory Example --\n\r");
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s --\n\r", __DATE__, __TIME__);


	RESET_CYCLE_COUNTER();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	cyclecounteroffset = DWT->CYCCNT;
	__DMB();
	cyclecounteroffset -=10;

	printf("\n\r");
	printf(" ------ ICache & DCache Disabled ------\n\r");
	printf(" ------ Stack In SRAM ------\n\r");

	/* stack test: in SRAM vs in DTCM */
	cycles = stack_test(100);
	printf("Inst cycles passed is %u\r\n", (unsigned)(cyclecounter - cyclecounteroffset));

	cycles = stack_test(100);
	printf("Inst cycles passed is %u\r\n", (unsigned)(cyclecounter - cyclecounteroffset));

	printf("\n\r");
	printf(" ------ Stack In DTCM ------\n\r");
	tcm_stackinit();

	cycles = stack_test(100);
	printf("Inst cycles passed is %u\r\n", (unsigned)(cyclecounter - cyclecounteroffset));

	cycles = stack_test(100);
	printf("Inst cycles passed is %u\r\n", (unsigned)(cyclecounter - cyclecounteroffset));

	/* memory copy test */
	cycles = normal_memcpy(destbuff, srcbuff, BUFF_SIZE);
	printf("\n\r Number of Inst cycles passed without TCM is %u  \n\r",
			(unsigned)(cycles - cyclecounteroffset)  );


	cycles = tcm_memcpy(tcm_destbuff, tcm_srcbuff, BUFF_SIZE);
	printf("\n\r Number of Inst cycles passed with TCM is %u \n\r",
			(unsigned)(cycles - cyclecounteroffset)  );


	SCB_EnableICache();
	SCB_EnableDCache();

	printf("\n\r");
	printf(" ------ ICache & DCache Enabled ------\n\r");

	cycles = normal_memcpy(destbuff, srcbuff, BUFF_SIZE);
	printf("\n\r Number of Inst cycles passed without TCM is %u  \n\r",
			(unsigned)(cycles - cyclecounteroffset));


	cycles = tcm_memcpy(tcm_destbuff, tcm_srcbuff, BUFF_SIZE);
	printf("\n\r Number of Inst cycles passed with TCM is %u  \n\r",
			(unsigned)(cycles - cyclecounteroffset));

	while (1) {
	}
}
