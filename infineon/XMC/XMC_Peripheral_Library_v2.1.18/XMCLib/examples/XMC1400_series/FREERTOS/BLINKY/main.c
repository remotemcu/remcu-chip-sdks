/*
 * Copyright (C) 2016-2017 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 20 Apr, 2017
 * @version 1.0.0
 *
 * @brief XMC1400 Bootkit FreeRTOS example
 *
 * Two threads are defined:
 * - one blinking a LED task which blink every 500ms after taking the semaphore
 * - another task waiting for 500ms and giving the semaphore
 *
 * History
 * =======
 *
 * Version 1.0.0 
 * - Initial
 *
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
 
#include "xmc_gpio.h"

#define LED1 P4_0

/* Global Variables */
xSemaphoreHandle xSemaphore;

static void blinkLED(void* pvParameters) 
{
  for (;;) 
  {
    XMC_GPIO_ToggleOutput(LED1);
    /* Block until the semaphore is given */
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
  }

}

static void mainThread(void* pvParameters) 
{
  for (;;) 
  {
    vTaskDelay(500);
    xSemaphoreGive(xSemaphore);
  }
}

int main(void)
{
  XMC_GPIO_CONFIG_t gpio_config;

  /* Initialize peripherals */
  gpio_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  XMC_GPIO_Init(LED1, &gpio_config);

  /* Create the Semaphore for synchronization between UART and LED task */
  vSemaphoreCreateBinary(xSemaphore);

  /* create threads */
  xTaskCreate(blinkLED, "Blink", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
  xTaskCreate(mainThread, "Main", configMINIMAL_STACK_SIZE, NULL, 1, NULL );

  /* Start the tasks and timer running. */
  vTaskStartScheduler();
}


void vApplicationMallocFailedHook( void )
{
  /* vApplicationMallocFailedHook() will only be called if
	 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	 function that will get called if a call to pvPortMalloc() fails.
	 pvPortMalloc() is called internally by the kernel whenever a task, queue,
	 timer or semaphore is created.  It is also called by various parts of the
	 demo application.  If heap_1.c or heap_2.c are used, then the size of the
	 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	 to query the size of free heap space that remains (although it does not
	 provide information on how the remaining heap might be fragmented). */
  taskDISABLE_INTERRUPTS();
  for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
  /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	 to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	 task.  It is essential that code added to this hook function never attempts
	 to block in any way (for example, call xQueueReceive() with a block time
	 specified, or call vTaskDelay()).  If the application makes use of the
	 vTaskDelete() API function (as this demo application does) then it is also
	 important that vApplicationIdleHook() is permitted to return to its calling
	 function, because it is the responsibility of the idle task to clean up
	 memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
  ( void ) pcTaskName;
  ( void ) pxTask;

  /* Run time stack overflow checking is performed if
	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	 function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
  /* This function will be called by each tick interrupt if
	 configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	 added here, but the tick hook is called from an interrupt context, so
	 code must not attempt to block, and only the interrupt safe FreeRTOS API
	 functions can be used (those that end in FromISR()). */
}

