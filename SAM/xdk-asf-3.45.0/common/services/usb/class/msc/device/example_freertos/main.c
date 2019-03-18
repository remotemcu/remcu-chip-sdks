/**
 * \file
 *
 * \brief FreeRTOS configuration
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
#include <asf.h>
#include "conf_usb.h"
#include "conf_board.h"
#include "ui.h"

static volatile bool main_b_msc_enable = false;

static void main_memories_trans_task(void *pvParameters);

//! Handle to the semaphore protecting memories transfer.
static xSemaphoreHandle main_trans_semphr = NULL;

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	sysclk_init();
	board_init();
	ui_init();
	ui_powerdown();

	ctrl_access_init(); // Required with FreeRTOS
	memories_initialization();

	// Create a semaphore to manage the memories data transfer
	vSemaphoreCreateBinary(main_trans_semphr);
	Assert( main_trans_semphr != NULL );
	
	// Start USB stack to authorize VBus monitoring
	udc_start();
	
	// Create a task to process data transfer
	xTaskCreate(main_memories_trans_task,
			((const signed portCHAR *)"DATA TRANSFER"),
#if defined(CONF_BOARD_NAND)
			3072/sizeof(portSTACK_TYPE), // NF require large stack
#else
			256,
#endif
			NULL,
			tskIDLE_PRIORITY + 1,
			NULL);

	// Uncomment the following line, if you want FreeRTOS to always run 
	// when USB cable is unplugged.
	//  IDLE is the sleep level required by the Timer counter used by FreeRTOS.
	// sleepmgr_lock_mode(SLEEPMGR_IDLE);

	// Start OS scheduler
	vTaskStartScheduler();
	return 0;
}

void vApplicationIdleHook( void );
void vApplicationIdleHook( void )
{
	// Management of sleep mode in Idle Hook from FreeRTOS
	sleepmgr_enter_sleep();
}

static void main_memories_trans_task(void *pvParameters)
{
	UNUSED(pvParameters);
	while (true) {
		// Wait for a semaphore which signals that a transfer is requested
		if( xSemaphoreTake( main_trans_semphr, portMAX_DELAY ) == pdTRUE ) {
			udi_msc_process_trans();
		}
	}
}

void main_msc_notify_trans(void)
{
	static signed portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	// One transfer is requested 
	// It is now time for main_memories_trans_task() to run
	xSemaphoreGiveFromISR( main_trans_semphr, &xHigherPriorityTaskWoken );
}

void main_suspend_action(void)
{
	ui_powerdown();
}

void main_resume_action(void)
{
	ui_wakeup();
}

void main_sof_action(void)
{
	if (!main_b_msc_enable)
		return;
	ui_process(udd_get_frame_number());
}

bool main_msc_enable(void)
{
	main_b_msc_enable = true;
	return true;
}

void main_msc_disable(void)
{
	main_b_msc_enable = false;
}

/**
 * \mainpage ASF USB Device MSC
 *
 * \section intro Introduction
 * This example shows how to implement a USB Device Mass Storage
 * on Atmel MCU products with USB module.
 *
 * \section startup Startup
 * The example uses all memories available on the board and connects these to
 * USB Device Mass Storage stack. After loading firmware, connect hardware board
 * (EVKxx,Xplain,...) to the USB Host. When connected to a USB host system
 * this application allows to display all available memories as a
 * removable disks in the Unix/Mac/Windows operating systems.
 * \note
 * This example uses the native MSC driver on Unix/Mac/Windows OS, except for Win98.
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB Device stack and MSC modules:
 *   <br>services/usb/
 *   <br>services/usb/udc/
 *   <br>services/usb/class/msc/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h   configuration of each module
 *       - ui.c        implement of user's interface (leds)
 *
 * \subsection freertos FreeRTOS
 * \paragraph tasks Task required
 * The USB device stack is fully interrupt driven and uses the USB DMA to transfer
 * data from/to the internal RAM. Thus, the USB does not require task creation.
 * However, the data memory transfer is done without DMA and requires a specific task
 * (called main_memories_trans_task).
 * 
 * \paragraph sync Task synchronization
 * The memory transfer task is synchronized (wakeup) by a mutex
 * (main_trans_semphr) which is given by a USB notification callback
 * (main_msc_notify_trans()). The callback is called by the USB interrupt which
 * is FreeRTOS compliant (See ISR_FREERTOS() macro).
 *
 * \paragraph power Sleep mode in FreeRTOS
 * The USB stack supports the sleepmgr module which allows to easily use the
 * CPU sleep mode and reduce the power consumption. To use sleepmgr modules 
 * in FreeRTOS, the best option is to enable configUSE_IDLE_HOOK and define
 * vApplicationIdleHook() which calls sleepmgr_enter_sleep().
 *
 * However, the IDLE sleep level must be locked in sleepmgr module, if you want
 * that FreeRTOS runs when USB cable is unplugged. In fact, the Timer counter
 * used by FreeRTOS runs only when sleep level is > IDLE.
 */
