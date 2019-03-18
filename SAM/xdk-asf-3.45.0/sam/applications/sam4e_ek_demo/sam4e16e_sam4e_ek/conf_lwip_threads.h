/**
 * \file
 *
 * \brief lwIP core & application threads configuration file.
 *
 * This file contains the possible external configuration of the Ethernet module.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
 ***************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_LWIP_THREADS_H_INCLUDED
#define CONF_LWIP_THREADS_H_INCLUDED

#include "board.h"
#if 0
/** define stack size for WEB server task */
#define lwipBASIC_WEB_SERVER_STACK_SIZE   256

/** define stack size for TFTP server task */
#define lwipBASIC_TFTP_SERVER_STACK_SIZE  2048

/** define stack size for SMTP Client task */
#define lwipBASIC_SMTP_CLIENT_STACK_SIZE  256

/** define stack size for lwIP task */
#define lwipINTERFACE_STACK_SIZE         2048

/** define stack size for netif task */
#define netifINTERFACE_TASK_STACK_SIZE    2048

/** define WEB server priority */
#define lwipBASIC_WEB_SERVER_PRIORITY     (tskIDLE_PRIORITY + 2)

/** define TFTP server priority */
#define lwipBASIC_TFTP_SERVER_PRIORITY    (tskIDLE_PRIORITY + 3)

/** define SMTP Client priority */
#define lwipBASIC_SMTP_CLIENT_PRIORITY    (tskIDLE_PRIORITY + 5)

/** define lwIP task priority */
#define lwipINTERFACE_TASK_PRIORITY       (configMAX_PRIORITIES - 1)

/** define netif task priority */
#define netifINTERFACE_TASK_PRIORITY      (configMAX_PRIORITIES - 1)

/** Number of threads that can be started with sys_thread_new() */
#define SYS_THREAD_MAX                    8

/** LED used by the ethernet task, toggled on each activation */
#define webCONN_LED                       LED1_GPIO
#endif
#endif /* #ifndef CONF_LWIP_THREADS_H_INCLUDED */
