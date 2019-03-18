/**
 * \file
 *
 * \brief FreeRTOS configuration
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "board.h"


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION                       1
#define configUSE_IDLE_HOOK                        1
#define configUSE_TICK_HOOK                        0
#define configCPU_CLOCK_HZ        ( CHIP_FREQ_CPU_MAX ) /* Hz clk gen */
#define configPBA_CLOCK_HZ        ( CHIP_FREQ_CPU_MAX )
#define configTICK_RATE_HZ        ( ( portTickType ) 1000 )
#define configMAX_PRIORITIES      ( 4 )
#define configMINIMAL_STACK_SIZE  ( ( unsigned portSHORT ) 128 )
/* configTOTAL_HEAP_SIZE is not used when heap_3.c is used. */
#define configTOTAL_HEAP_SIZE     ( ( size_t ) ( 0x2000 ) ) // 8K
#define configMAX_TASK_NAME_LEN   ( 20 )
#define configUSE_TRACE_FACILITY  0
#define configUSE_16_BIT_TICKS    0
#define configIDLE_SHOULD_YIELD   1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                      0
#define configMAX_CO_ROUTINE_PRIORITIES            (2)

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet                   1
#define INCLUDE_uxTaskPriorityGet                  0
#define INCLUDE_vTaskDelete                        0
#define INCLUDE_vTaskCleanUpResources              0
#define INCLUDE_vTaskSuspend                       1
#define INCLUDE_vTaskDelayUntil                    0
#define INCLUDE_vTaskDelay                         1
#define INCLUDE_xTaskGetCurrentTaskHandle          0
#define INCLUDE_xTaskGetSchedulerState             0

/* configTICK_USE_TC is a boolean indicating whether to use a Timer Counter or
   the CPU Cycle Counter for the tick generation.
   Both methods will generate an accurate tick.
   0: Use of the CPU Cycle Counter.
   1: Use of the Timer Counter (configTICK_TC_CHANNEL is the TC channel). */
#define configTICK_USE_TC             0
#define configTICK_TC_CHANNEL         2

/* configHEAP_INIT is a boolean indicating whether to initialize the heap with
   0xA5 in order to be able to determine the maximal heap consumption. */
#define configHEAP_INIT               0

// #define configUSE_MUTEXES                          1
// #define configUSE_RECURSIVE_MUTEXES                0
// #define configUSE_COUNTING_SEMAPHORES              0
// #define configUSE_ALTERNATIVE_API                  0
// #define configCHECK_FOR_STACK_OVERFLOW             2
// #define configQUEUE_REGISTRY_SIZE                  10
// #define configGENERATE_RUN_TIME_STATS              0

#define configKERNEL_INTERRUPT_PRIORITY            (0x0f << 4) /* Priority 15, or 255 as only the top four bits are implemented.  This is the lowest priority. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY       (0x05 << 4) /* Priority 5, or 80 as only the top four bits are implemented. */

// #define INCLUDE_vResumeFromISR                     1
// #define INCLUDE_uxTaskGetStackHighWaterMark        1

/* Debug trace configuration.
   configDBG is a boolean indicating whether to activate the debug trace. */
#define configDBG                     0

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define xPortPendSVHandler PendSV_Handler
#define vPortSVCHandler SVC_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
