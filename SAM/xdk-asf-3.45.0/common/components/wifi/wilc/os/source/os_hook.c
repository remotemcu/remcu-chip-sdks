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

#include <os/include/os_hook.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>
#include <lwip/tcpip.h>

extern void wilc_netif_tx_from_queue(hif_msg_t *msg);
extern uint8_t m2m_wifi_handle_events(void *p);

/* HIF thread. */
xTaskHandle hif_thread;

/* HIF thread queue. */
xQueueHandle hif_queue = NULL;

/* HIF thread binary semaphore. */
static xSemaphoreHandle hif_notify_sem;

/* HIF initialized. */
static uint8_t has_init = 0;

/**
 * \brief HIF thread entry function.
 */
static void os_hif_task(void *pv)
{
	while(1) {
		hif_msg_t msg;
		
		if (xQueueReceive(hif_queue, (void *)&msg, portMAX_DELAY) != pdFALSE) {
			/* WiFi init. */
			if (msg.id == MSG_START) {
				if (msg.handler) 
					msg.handler(msg.priv);				
			}
			
			/* Incoming data packet. */
			else if (msg.id == MSG_RX) {
				m2m_wifi_handle_events(NULL);
				vTaskDelay(1);
			} 
#ifndef WILC_SERIAL_BRIDGE_INTERFACE
			/* Outgoing data packet. */
			else if ((msg.id == MSG_TX_STA) || (msg.id == MSG_TX_AP)) {
				wilc_netif_tx_from_queue(&msg);
			}
#endif			
			/* WiFi command. */
			else if (msg.id == MSG_CMD) {

				if (msg.handler) 
					msg.handler(msg.priv);
			} 
			/* Error. */
			else {
#ifndef WILC_SERIAL_BRIDGE_INTERFACE				
				osprintf("Warning: Wrong id  msg id %lu \r\n", msg.id);
#endif				
			}
		}
	}
}

/**
 * \brief Put interrupt request in netif queue for later processing.
 */
void os_hook_isr(void)
{
	signed portBASE_TYPE woken = pdFALSE;
	hif_msg_t msg;

	msg.id = MSG_RX;
	msg.pbuf = NULL;
	msg.payload_size = 0;
	msg.payload = NULL;
	if (xQueueSendFromISR(hif_queue, &msg, &woken) != pdTRUE) {
#ifndef WILC_SERIAL_BRIDGE_INTERFACE		
		osprintf("os_hook_isr: queue full error!\n");
#endif		
	}
	else {
		portEND_SWITCHING_ISR(woken);
	}
}

/**
 * \brief Initialize netif thread.
 */
void os_hook_init(void)
{
	if (!has_init) {
		vSemaphoreCreateBinary(hif_notify_sem);
		xSemaphoreTake(hif_notify_sem, portMAX_DELAY);
		hif_queue = xQueueCreate(32, sizeof(hif_msg_t));
		
		xTaskCreate(os_hif_task, (const signed char *)"WiFiHIF", 1024, NULL, (configMAX_PRIORITIES - 1), &hif_thread);			
		has_init = 1;
	}
}

void os_hook_set_handle(void *task)
{
	hif_thread = task;
}

/**
 * \brief Run handler function in the netif thread context and return immediately.
 */
uint8_t os_hook_dispatch_no_wait(wifi_task_cb handler, void *p)
{
	hif_msg_t msg;
	if (hif_thread == xTaskGetCurrentTaskHandle()) {
		handler(p);
	} 
	else {
		msg.id = MSG_CMD;
		msg.handler = handler;
		msg.priv = p;
		return xQueueSend(hif_queue, (void *)&msg, portMAX_DELAY);
	}
	return 0;
}

/**
 * \brief Run handler function in the netif thread context and wait for function return.
 */
void os_hook_dispatch_wait(wifi_task_cb handler, struct params_dispatch *p, void* pv)
{
	hif_msg_t msg;
	if (hif_thread == xTaskGetCurrentTaskHandle()) {
		p->signal_semaphore = 0;
		handler(pv);
	}
	else {
		p->signal_semaphore = 1;
		msg.id = MSG_CMD;
		msg.handler = handler;
		msg.priv = pv;
		xQueueSend(hif_queue, (void *)&msg, portMAX_DELAY);
		
		xSemaphoreTake(hif_notify_sem, portMAX_DELAY);
	}
}

/**
 * \brief Start WiFi in the netif thread context and wait for function return.
 */
void os_hook_send_start(wifi_task_cb handler, struct params_dispatch *p, void* pv)
{
	hif_msg_t msg;
 
	p->signal_semaphore = 1;
	msg.id = MSG_START;
	msg.handler = handler;
	msg.priv = pv;
	xQueueSend(hif_queue, (void *)&msg, portMAX_DELAY);
	xSemaphoreTake(hif_notify_sem, portMAX_DELAY);
}

/**
 * \brief Release lock to notify calling thread that netif job is done.
 */
void os_hook_notify(void)
{
	xSemaphoreGive(hif_notify_sem);
}
