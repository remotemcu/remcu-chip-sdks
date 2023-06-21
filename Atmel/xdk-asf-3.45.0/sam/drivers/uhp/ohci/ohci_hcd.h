/**
 * \file
 *
 * \brief OHCI Host Controller Driver header file with APIs for UHD interface.
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

#include "compiler.h"
#include "ohci.h"

/* Bus status. */
#define BUS_CONNECT     0
#define BUS_DISCONNECT  1
#define BUS_RESET       2

/* PID type. */
enum pid {
	TD_PID_SETUP = 0,
	TD_PID_OUT   = 1,
	TD_PID_IN    = 2,
};

/* OHCI interrupt source. */
enum ohci_interrupt_source {
	OHCI_INTERRUPT_SO = 0,
	OHCI_INTERRUPT_WDH,
	OHCI_INTERRUPT_SF,
	OHCI_INTERRUPT_RD,
	OHCI_INTERRUPT_UE,
	OHCI_INTERRUPT_FNO,
	OHCI_INTERRUPT_RHSC,
	OHCI_INTERRUPT_OC,
	OHCI_NUM_OF_INTERRUPT_SOURCE,
};

typedef void (*ohci_callback_t)(void *pointer);

void ohci_init(void);
void ohci_deinit(void);
bool ohci_get_device_speed (void);
uint16_t ohci_get_frame_number (void);
void ohci_bus_reset(void);
void ohci_bus_suspend(void);
bool ohci_is_suspend(void);
void ohci_bus_resume(void);
bool ohci_add_ed_control(ed_info_t *ed_info);
bool ohci_add_ed_bulk(ed_info_t *ed_info);
bool ohci_add_ed_period(ed_info_t *ed_info);
void ohci_remove_ed(uint8_t ep_number);
void ohci_clear_ed_transfer_status(struct ohci_td_general *td_general_header);
bool ohci_add_td_control(enum pid pid, uint8_t *buf, uint16_t buf_size);
bool ohci_add_td_non_control(uint8_t ep_number, uint8_t *buf,
		uint32_t buf_size, struct ohci_td_general **td_general_header);
void ohci_remove_td(uint8_t ep_number);
void ohci_enable_interrupt(enum ohci_interrupt_source int_source);
void ohci_disable_interrupt(enum ohci_interrupt_source int_source);
void ohci_register_callback(enum ohci_interrupt_source int_source, void *call_back);
void ohci_unregister_callback(enum ohci_interrupt_source int_source);

