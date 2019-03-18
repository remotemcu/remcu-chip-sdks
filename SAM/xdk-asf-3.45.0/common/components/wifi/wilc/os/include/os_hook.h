/**
 *
 * \file
 *
 * \brief
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef OS_HOOK_H_INCLUDED
#define OS_HOOK_H_INCLUDED

#include "compiler.h"

typedef void (*wifi_task_cb)(void *arg);

struct params_dispatch {
	uint8_t signal_semaphore;
	int8_t retval;
	void * param;
};

#define MSG_RX 1
#define MSG_TX_STA 2
#define MSG_TX_AP 3
#define MSG_QUIT 4
#define MSG_CMD 5
#define MSG_START 6

typedef struct {
	uint32_t id;
	void *pbuf;
	void * payload;
	uint32_t payload_size;
	wifi_task_cb	handler;
	void * priv;
} hif_msg_t ;

void os_hook_isr(void);
void os_hook_init(void);
void os_hook_set_handle(void *task);
uint8_t os_hook_dispatch_no_wait(wifi_task_cb handler, void *p);
void os_hook_dispatch_wait(wifi_task_cb handler, struct params_dispatch *p,void* pv);
void os_hook_notify(void);
void os_hook_deinit(void);
void os_hook_send_start(wifi_task_cb handler, struct params_dispatch *p, void* pv);
void os_hook_send_stop(wifi_task_cb handler, struct params_dispatch *p, void* pv);

#endif /* OS_HOOK_H_INCLUDED */
