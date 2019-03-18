/**
 * \file
 *
 * \brief OHCI Host Controller Driver.
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

#include "ohci_hcd.h"
#include "delay.h"
#include <string.h>

#define OHCI         ((Ohci      *)0x20400000U) /**< \brief (OHCI) Base Address */

/* HCCA strcture. */
COMPILER_ALIGNED(256)
static volatile struct ohci_hcca hcca;

/* Control endpoint related. */
COMPILER_ALIGNED(16)
static volatile struct ohci_ed control_ed;
COMPILER_ALIGNED(16)
static volatile struct ohci_td_general control_td_head;
COMPILER_ALIGNED(16)
static volatile struct ohci_td_general control_td_tail;

/* Bulk endpoint related. */
COMPILER_ALIGNED(16)
static volatile struct ohci_ed bulk_ed[8];
static volatile uint8_t bulk_ed_status = 0;
COMPILER_ALIGNED(16)
static volatile struct ohci_td_general bulk_td_head[8];
COMPILER_ALIGNED(16)
static volatile struct ohci_td_general bulk_td_tail[8];

/* Interrupt endpoint related. */
COMPILER_ALIGNED(16)
static volatile struct ohci_ed interrupt_ed[8];
static volatile uint8_t interrupt_ed_status = 0;
COMPILER_ALIGNED(16)
static volatile struct ohci_td_general interrupt_td_head[8];
COMPILER_ALIGNED(16)
static volatile struct ohci_td_general interrupt_td_tail[8];

/* Isochronous endpoint related. */
COMPILER_ALIGNED(16)
static volatile struct ohci_ed isochronous_ed[8];
static volatile uint8_t isochronous_ed_status = 0;
COMPILER_ALIGNED(32)
static volatile struct ohci_td_iso isochronous_td_head[8];
COMPILER_ALIGNED(32)
static volatile struct ohci_td_iso isochronous_td_tail[8];

/* Callback related. */
static ohci_callback_t ohci_callback_pointer[OHCI_NUM_OF_INTERRUPT_SOURCE];
static uint32_t callback_para;

/* Reset flag. */
static volatile uint32_t bus_reset_flag;

/* Temp variable to store the TD head and tail. */
static volatile uint32_t p_td_head, p_td_tail;

/**
 * \brief Initialize the OHCI module.
 *
 */
void ohci_init(void)
{
	uint32_t i, temp_value;

	for (i = 0; i < OHCI_NUM_OF_INTERRUPT_SOURCE; i++) {
		ohci_callback_pointer[i] = 0;
	}

	memset((void *)&hcca, 0, sizeof(hcca));
	memset((void *)&control_ed, 0, sizeof(control_ed));
	for (i = 0; i < 8; i++) {
		memset((void *)&bulk_ed[i], 0, sizeof(bulk_ed[i]));
		memset((void *)&interrupt_ed[i], 0, sizeof(interrupt_ed[i]));
		memset((void *)&isochronous_ed[i], 0, sizeof(isochronous_ed[i]));
		memset((void *)&bulk_td_head[i], 0, sizeof(bulk_td_head[i]));
		memset((void *)&bulk_td_tail[i], 0, sizeof(bulk_td_tail[i]));
	}
	memset((void *)&control_td_head, 0, sizeof(control_td_head));
	memset((void *)&control_td_tail, 0, sizeof(control_td_tail));
	memset((void *)&interrupt_td_head, 0, sizeof(interrupt_td_head));
	memset((void *)&interrupt_td_tail, 0, sizeof(interrupt_td_tail));
	memset((void *)&isochronous_td_head, 0, sizeof(isochronous_td_head));
	memset((void *)&isochronous_td_tail, 0, sizeof(isochronous_td_tail));

	/* Setup Host Controller to issue a software reset. */
	OHCI->HcCommandStatus = HC_COMMANDSTATUS_HCR;
	while (OHCI->HcCommandStatus & HC_COMMANDSTATUS_HCR);

    /* Write Fm Interval and Largest Data Packet Counter. */
	OHCI->HcFmInterval    = FIT | (FSMP(FI)<< 16) | FI;
	OHCI->HcPeriodicStart = FI * 90 / 100;

	/* Begin sending SOF. */
	temp_value = OHCI->HcControl;
	temp_value &= ~HC_CONTROL_HCFS;
	temp_value |= HC_CONTROL_HCFS_USBOPERATIONAL;
	OHCI->HcControl = temp_value;

	OHCI->HcControl |= HC_CONTROL_PLE;
	OHCI->HcControl |= HC_CONTROL_IE;

	OHCI->HcHCCA = (uint32_t)&hcca;

	/* Clear Interrrupt Status. */
	OHCI->HcInterruptStatus |= OHCI->HcInterruptStatus;

	/* Enable some interrupts. */
	OHCI->HcInterruptEnable = HC_INTERRUPT_WDH | HC_INTERRUPT_SF
				| HC_INTERRUPT_RD | HC_INTERRUPT_RHSC | HC_INTERRUPT_MIE;

	/* Delay some time to access the port. */
	delay_ms(50);

	/* Set Global Power. */
	OHCI->HcRhStatus = RH_HS_LPSC;

	/* Initiate port reset. */
	OHCI->HcRhPortStatus = RH_PS_PRS;
	while (OHCI->HcRhPortStatus & RH_PS_PRS);
	delay_ms(100);
    /* Clear port reset signal. */
    OHCI->HcRhPortStatus = RH_PS_PRSC;
}

/**
 * \brief De-initialize the OHCI module.
 *
 */
void ohci_deinit(void)
{
	uint32_t i;
	struct ohci_td_general *td_general_header;
	struct ohci_td_general *td_general_free_header;
	struct ohci_ed *ed_header;
	struct ohci_ed *ed_free_header;

	/* Change to reset state. */
	OHCI->HcControl &= ~HC_CONTROL_HCFS;;
	
	/* Free all allocated EDs and TDs. */

	/* TDs in control endpoint. */
	control_ed.p_td_head = NULL;
	control_ed.p_td_tail = NULL; 

	/* TDs in Bulk endpoints. */
	ed_header = (struct ohci_ed *)OHCI->HcBulkHeadED;
	while (ed_header != NULL) {
		if (ed_header->p_td_head != ed_header->p_td_tail) {
			td_general_free_header = (struct ohci_td_general *)ed_header->p_td_head;
			while (td_general_free_header != NULL) {
				td_general_header = td_general_free_header->p_next_td;
				free(td_general_free_header);
				td_general_free_header = td_general_header;
			}
		}
	}

	/* TDs in Int/ISO endpoints. */
	for (i = 0; i < 32; i++) {
		ed_header = (struct ohci_ed *)hcca.InterruptTable[i];
		while (ed_header != NULL) {
			if (ed_header->p_td_head != ed_header->p_td_tail) {
				td_general_free_header = (struct ohci_td_general *)ed_header->p_td_head;
				while (td_general_free_header != NULL) {
					td_general_header = td_general_free_header->p_next_td;
					free(td_general_free_header);
					td_general_free_header = td_general_header;
				}
			}
			ed_header = ed_header->p_next_ed;
		}
	}

	/* control endpoint. */	
	memset((void *)&control_ed, 0, sizeof(control_ed));


	/* Bulk endpoints. */
	ed_header = (struct ohci_ed *)OHCI->HcBulkHeadED;
	while (ed_header != NULL) {
		ed_free_header = ed_header;
		ed_header = ed_header->p_next_ed;
		free(ed_free_header);
	}

	/* Int/ISO endpoints. */
	for (i = 0; i < 32; i++) {
		ed_header = (struct ohci_ed *)hcca.InterruptTable[i];
		while (ed_header != NULL) {
			ed_free_header = ed_header;
			ed_header = ed_header->p_next_ed;
			free(ed_free_header);
		}
	}
}

/**
 * \brief Gets the speed of connected device.
 *
 * \return Device speed, true for low speed, false for full speed.
 */
bool ohci_get_device_speed (void)
{
	if (OHCI->HcRhPortStatus & RH_PS_LSDA) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Gets the current Start Of Frame (SOF) number
 *
 * \return current start of frame number.
 */
uint16_t ohci_get_frame_number (void)
{
	return hcca.FrameNumber;
}

/**
 * \brief Enables the Reset state on the USB line.
 *
 */
void ohci_bus_reset(void)
{
	Assert(!(OHCI->HcRhPortStatus & RH_PS_CCS));

	/* Initiate port reset. */
	OHCI->HcRhPortStatus = RH_PS_PRS;
	while (OHCI->HcRhPortStatus & RH_PS_PRS);
	delay_ms(100);
    /* Clear port reset signal. */
    OHCI->HcRhPortStatus = RH_PS_PRSC;

	bus_reset_flag = true;
}

/**
 * \brief Enables the suspend state on the USB line.
 *
 */
void ohci_bus_suspend(void)
{
	uint32_t temp_value;

	OHCI->HcControl |= HC_CONTROL_RWE;

	/**
	 * Suspend hub ... this is the "global (to this bus) suspend" mode,
	 * which doesn't imply ports will first be individually suspended.
	 */
	temp_value = OHCI->HcControl;
	temp_value &= ~HC_CONTROL_HCFS;
	temp_value |= HC_CONTROL_HCFS_USBSUSPEND;
	OHCI->HcControl = temp_value;

	/* Device remote wakeup enable. */
	OHCI->HcRhStatus = RH_HS_DRWE;
}

/**
 * \brief Test if the suspend state is enabled on the USB line.
 * \return USB line in SUSPEND state, if true
 */
bool ohci_is_suspend(void)
{
	return ((OHCI->HcControl & HC_CONTROL_HCFS) == HC_CONTROL_HCFS_USBSUSPEND);
}

/**
 * \brief Enables the IDLE state on the USB line.
 * The IDLE state is enable when SOF are present on USB line.
 * A Downstream Resume signal can be sent.
 */
void ohci_bus_resume(void)
{
	uint32_t temp_value;

	/* Device remote wakeup disable. */
	OHCI->HcRhStatus = RH_HS_CRWE;

	temp_value = OHCI->HcControl;
	temp_value &= ~HC_CONTROL_HCFS;
	temp_value |= HC_CONTROL_HCFS_USBRESUME;
	OHCI->HcControl = temp_value;

	delay_ms(50);

	/* Then re-enable operations */
	temp_value = OHCI->HcControl;
	temp_value &= ~HC_CONTROL_HCFS;
	temp_value |= HC_CONTROL_HCFS_USBOPERATIONAL;
	OHCI->HcControl = temp_value;


	OHCI->HcControl &= ~HC_CONTROL_RWE;
}

/**
 * \brief Add a control endpoint.
 * \return true for success.
 */
bool ohci_add_ed_control(ed_info_t *ed_info)
{
	/* control endpoint. */	
	memset((void *)&control_ed, 0, sizeof(control_ed));
	OHCI->HcControlHeadED = (uint32_t)&control_ed;
	control_ed.ed_info.ul_ed_info = ed_info->ul_ed_info;
	return true;
}

/**
 * \brief Add a bulk endpoint.
 * \return true for success.
 */
bool ohci_add_ed_bulk(ed_info_t *ed_info)
{
	uint32_t i;

	struct ohci_ed *bulk_ed_head;
	struct ohci_ed *bulk_ed_add;

	/* Check if there is free bulk endpoint. */
	for (i = 0; i < 8; i++) {
		if (!(bulk_ed_status & (1 << i))) {
			bulk_ed_status |= (1 << i);
			memset((void *)&bulk_ed[i], 0, sizeof(bulk_ed[i]));
			bulk_ed_add = (struct ohci_ed *)&bulk_ed[i];
			break;
		}
	}
	if (i == 8) {
		return false;
	}

	bulk_ed_head = (struct ohci_ed *)OHCI->HcBulkHeadED;

	if (bulk_ed_head == NULL) {
		bulk_ed_add->ed_info.ul_ed_info = ed_info->ul_ed_info;
		OHCI->HcBulkHeadED = (uint32_t)bulk_ed_add;
	} else {
		/* Check if the endpoint has been allocated */
		while (bulk_ed_head->p_next_ed != NULL) {
			if (bulk_ed_head->ed_info.ed_info_s.bEndpointNumber ==
					ed_info->ed_info_s.bEndpointNumber) {
				return false;
			}
			bulk_ed_head = bulk_ed_head->p_next_ed;
		};

		bulk_ed_head->p_next_ed = bulk_ed_add;
		bulk_ed_add->ed_info.ul_ed_info = ed_info->ul_ed_info;
	}
	return true;
}

/**
 * \brief Add a control endpoint.
 *
 * Simplify the management, only 32 interrupt ED support, no list on each entry.
 *
 * \return true for success.
 */
bool ohci_add_ed_period(ed_info_t *ed_info)
{
	uint32_t i, j;
	struct ohci_ed *period_ed_add;
	struct ohci_ed *period_ed_header;

	if (ed_info->ed_info_s.bFormat) {
		/* isochronous ED */

		/* Check if there is free isochronous endpoint. */
		for (j = 0; j < 8; j++) {
			if (!(isochronous_ed_status & (1 << j))) {
				isochronous_ed_status |= (1 << j);
				memset((void *)&isochronous_ed[j], 0, sizeof(isochronous_ed[j]));
				period_ed_add = (struct ohci_ed *)&isochronous_ed[j];
				break;
			}
		}
		if (j == 8) {
			return false;
		}

		period_ed_add->ed_info.ul_ed_info = ed_info->ul_ed_info;
		for (i = 0; i < 32; i++) {
			period_ed_header = (struct ohci_ed *)hcca.InterruptTable[i];
			if (period_ed_header == NULL) {
				hcca.InterruptTable[i] = (uint32_t)period_ed_add;
			} else {
				period_ed_header->p_next_ed = period_ed_add;
			}
		}
		return true;
	} else {
		/* interrupt ED */

		/* Check if there is free interrupt endpoint. */
		for (j = 0; j < 8; j++) {
			if (!(interrupt_ed_status & (1 << j))) {
				interrupt_ed_status |= (1 << j);
				memset((void *)&interrupt_ed[j], 0, sizeof(interrupt_ed[j]));
				period_ed_add = (struct ohci_ed *)&interrupt_ed[j];
				break;
			}
		}
		if (j == 8) {
			return false;
		}

		for (i = 0; i < 8; i++) {
			period_ed_header = (struct ohci_ed *)hcca.InterruptTable[i];
			if (period_ed_header == NULL) {
				period_ed_add->ed_info.ul_ed_info = ed_info->ul_ed_info;
				hcca.InterruptTable[i] = (uint32_t)period_ed_add;
				hcca.InterruptTable[i + 8] = (uint32_t)period_ed_add;
				hcca.InterruptTable[i + 16] = (uint32_t)period_ed_add;
				hcca.InterruptTable[i + 24] = (uint32_t)period_ed_add;
				return true;
			} else {
				if (period_ed_header->ed_info.ed_info_s.bEndpointNumber
						== ed_info->ed_info_s.bEndpointNumber) {
					return false;
				}
			}
		}
	}
	return false;
}

/**
 * \brief Remove an endpoint.
 *
 * \param ep_number endpoint number.
 */
void ohci_remove_ed(uint8_t ep_number)
{
	uint32_t i, j;
	struct ohci_ed *ed_header = 0;
	struct ohci_ed *ed_free_header = 0;

	/* Control endpoints. */
	if (ep_number == 0) {
		memset((void *)&control_ed, 0, sizeof(control_ed));
	} 

	/* Bulk/Int/ISO endpoints. */
	if (ep_number != 0xFF) {
		/* Bulk endpoints. */
		ed_header = (struct ohci_ed *)OHCI->HcBulkHeadED;
		if (ed_header != NULL) {
			if (ed_header->ed_info.ed_info_s.bEndpointNumber == ep_number) {
				OHCI->HcBulkHeadED = (uint32_t)ed_header->p_next_ed;
				ed_free_header = ed_header;
			} else {
				/* Check the list */
				while ((ed_header != NULL) && (ed_header->p_next_ed != NULL)) {
					if (ed_header->p_next_ed->ed_info.ed_info_s.bEndpointNumber
							==	ep_number) {
						ed_free_header = ed_header->p_next_ed;
						ed_header->p_next_ed = ed_header->p_next_ed->p_next_ed;
						break;
					}
					ed_header = ed_header->p_next_ed;
				};
			}
		}

		/* Int/ISO endpoints. */
		for (i = 0; i < 32; i++) {
			ed_header = (struct ohci_ed *)hcca.InterruptTable[i];
			while (ed_header != NULL) {
				if (ed_header->ed_info.ed_info_s.bEndpointNumber == ep_number) {
					ed_free_header = ed_header;
					break;
				}
				ed_header = ed_header->p_next_ed;
			}
		}

		for (j = 0; j < 8; j++) {
			if (ed_free_header == &bulk_ed[j]) {
				bulk_ed_status &= ~(1 << j);
				break;
			}
			if (ed_free_header == &interrupt_ed[j]) {
				interrupt_ed_status &= ~(1 << j);
				break;
			}
			if (ed_free_header == &isochronous_ed[j]) {
				isochronous_ed_status &= ~(1 << j);
				break;
			}
		}

	}

	/* All endpoints. */
	if (ep_number == 0xFF) {
		/* Bulk endpoints. */
		OHCI->HcBulkHeadED = 0;

		/* Int/ISO endpoints. */
		for (i = 0; i < 32; i++) {
			hcca.InterruptTable[i] = 0;
		}

		bulk_ed_status = 0;
		interrupt_ed_status = 0;
		isochronous_ed_status = 0;
	};
}

/**
 * \brief Remove an endpoint transfer status.
 *
 * \param td_general_header TD used by the endpoint.
 */
void ohci_clear_ed_transfer_status(struct ohci_td_general *td_general_header)
{
	uint32_t i;
	uint32_t temp_head;

	if (td_general_header == &control_td_head) {
		temp_head = (uint32_t)control_ed.p_td_head;
		temp_head &= 0xFFFFFFF0;
		control_ed.p_td_head = (void *)temp_head;
	}

	for (i = 0; i < 8; i++) {
		if (td_general_header == &bulk_td_head[i]) {
			temp_head = (uint32_t)bulk_ed[i].p_td_head;
			temp_head &= 0xFFFFFFF0;
			bulk_ed[i].p_td_head = (void *)temp_head;
		}
	}
	for (i = 0; i < 8; i++) {
		if (td_general_header == &interrupt_td_head[i]) {
			temp_head = (uint32_t)interrupt_ed[i].p_td_head;
			temp_head &= 0xFFFFFFF0;
			interrupt_ed[i].p_td_head = (void *)temp_head;
		}
	}
	for (i = 0; i < 8; i++) {
		if (td_general_header ==
					(struct ohci_td_general *)&isochronous_td_head[i]) {
			temp_head = (uint32_t)isochronous_ed[i].p_td_head;
			temp_head &= 0xFFFFFFF0;
			isochronous_ed[i].p_td_head = (void *)temp_head;
		}
	}
}

/**
 * \brief Add a transfer descriptor to control endpoint.
 *
 * \param pid PID type.
 * \param buf Point to the data buffer.
 * \param buf_size Length of the data buffer.
 *
 * \return true for success.
 */
bool ohci_add_td_control(enum pid pid, uint8_t *buf, uint16_t buf_size)
{
	OHCI->HcControl &= ~HC_CONTROL_CLE;

	memset((void *)&control_td_head, 0, sizeof(control_td_head));
	memset((void *)&control_td_tail, 0, sizeof(control_td_tail));

	control_td_head.td_info.bBufferRounding = 1;
	control_td_head.td_info.bDirectionPID = pid;
	control_td_head.td_info.bDelayInterrupt = 0;
	if (pid == TD_PID_SETUP) {
		control_td_head.td_info.bDataToggle = 2;
	} else {
		control_td_head.td_info.bDataToggle = 3;
	}
	control_td_head.td_info.bErrorCount = 0;
	control_td_head.td_info.bConditionCode = 0xf;
	control_td_head.pCurrentBufferPointer= buf;
	control_td_head.p_next_td = NULL;
	control_td_head.pBufferEnd = buf + buf_size - 1;

	/* Check the halt status. */
	if ((uint32_t)control_ed.p_td_head & 0x01) {
		return false;
	}

	control_ed.p_td_head = (void *)&control_td_head;
	control_ed.p_td_tail = NULL;

	OHCI->HcCommandStatus = HC_COMMANDSTATUS_CLF;
	OHCI->HcControl |= HC_CONTROL_CLE;

	/* Wait for transfer done. */
	do {
		p_td_head = ((uint32_t)(control_ed.p_td_head)) & 0xFFFFFFF0;
		p_td_tail = ((uint32_t)(control_ed.p_td_tail)) & 0xFFFFFFF0;
	} while(p_td_head != p_td_tail);

	return true;
}

/**
 * \brief Add a transfer descriptor to non-control endpoint.
 *
 * \param ep_number endpoint number.
 * \param buf Point to the data buffer.
 * \param buf_size Length of the data buffer.
 *
 * \return true for success.
 */
bool ohci_add_td_non_control(uint8_t ep_number, uint8_t *buf,
		uint32_t buf_size, struct ohci_td_general **td_general_header)
{
	struct ohci_ed *ed_header;
	uint32_t i;
	uint8_t ep_dir;

	if (ep_number & 0x80) {
		ep_dir = 2;
	} else {
		ep_dir = 1;
	}
	ep_number = ep_number & 0xF;

	/* Bulk endpoints. */
	i = 0;
	ed_header = (struct ohci_ed *)OHCI->HcBulkHeadED;
	while (ed_header != NULL) {
		if ((ed_header->ed_info.ed_info_s.bEndpointNumber == ep_number) &&
				(ed_header->ed_info.ed_info_s.bDirection == ep_dir)) {
			/* Wait for transfer done. */
			do {
				p_td_head = ((uint32_t)(ed_header->p_td_head)) & 0xFFFFFFF0;
				p_td_tail = ((uint32_t)(ed_header->p_td_tail)) & 0xFFFFFFF0;
			} while(p_td_head != p_td_tail);

			memset((void *)&bulk_td_head[i], 0, sizeof(bulk_td_head[i]));
			memset((void *)&bulk_td_tail[i], 0, sizeof(bulk_td_tail[i]));

			bulk_td_head[i].td_info.bBufferRounding = 1;
			bulk_td_head[i].td_info.bDirectionPID = 3;
			bulk_td_head[i].td_info.bDelayInterrupt = 0;
			bulk_td_head[i].td_info.bDataToggle = 0;
			bulk_td_head[i].td_info.bErrorCount = 0;
			bulk_td_head[i].td_info.bConditionCode = 0;
			bulk_td_head[i].pCurrentBufferPointer= buf;
			bulk_td_head[i].p_next_td = NULL;
			bulk_td_head[i].pBufferEnd = buf + buf_size - 1;

			/* Check the halt status. */
			if ((uint32_t)ed_header->p_td_head & 0x01) {
				return false;
			}

			p_td_head = (uint32_t)(&bulk_td_head[i]);
			p_td_head &= 0xFFFFFFF0;
			*td_general_header = (struct ohci_td_general *)p_td_head;
			p_td_tail = (uint32_t)(ed_header->p_td_head);
			p_td_tail &= 0x0000000F;
			p_td_head |= p_td_tail;

			ed_header->p_td_head = (void *)p_td_head;
			ed_header->p_td_tail = NULL;

			OHCI->HcCommandStatus = HC_COMMANDSTATUS_BLF;
			OHCI->HcControl |= HC_CONTROL_BLE;
				
			return true;
		} else {
			ed_header = ed_header->p_next_ed;
			i++;
		}
	}

	/* Int/ISO endpoints. */
	for (i = 0; i < 8; i++) {
		ed_header = (struct ohci_ed *)hcca.InterruptTable[i];
		if ((ed_header->ed_info.ed_info_s.bEndpointNumber == ep_number) &&
				(ed_header->ed_info.ed_info_s.bDirection == ep_dir)) {
			if (ed_header->ed_info.ed_info_s.bFormat == 0) {
				/* Wait for transfer done. */
				do {
					p_td_head = ((uint32_t)(ed_header->p_td_head)) & 0xFFFFFFF0;
					p_td_tail = ((uint32_t)(ed_header->p_td_tail)) & 0xFFFFFFF0;
				} while(p_td_head != p_td_tail);

				OHCI->HcControl &= ~HC_CONTROL_PLE;
				OHCI->HcControl &= ~HC_CONTROL_IE;
				
				memset((void *)&interrupt_td_head[i], 0, sizeof(interrupt_td_head[i]));
				memset((void *)&interrupt_td_tail[i], 0, sizeof(interrupt_td_tail[i]));

				interrupt_td_head[i].td_info.bBufferRounding = 1;
				interrupt_td_head[i].td_info.bDirectionPID = 3;
				interrupt_td_head[i].td_info.bDelayInterrupt = 0;
				interrupt_td_head[i].td_info.bDataToggle = 0;
				interrupt_td_head[i].td_info.bErrorCount = 0;
				interrupt_td_head[i].td_info.bConditionCode = 0;
				interrupt_td_head[i].pCurrentBufferPointer= buf;
				interrupt_td_head[i].p_next_td = NULL;
				interrupt_td_head[i].pBufferEnd = buf + buf_size - 1;

				/* Check the halt status. */
				if ((uint32_t)ed_header->p_td_head & 0x01) {
					return false;
				}

				p_td_head = (uint32_t)(&interrupt_td_head[i]);
				p_td_head &= 0xFFFFFFF0;
				*td_general_header = (struct ohci_td_general *)p_td_head;
				p_td_tail = (uint32_t)(ed_header->p_td_head);
				p_td_tail &= 0x0000000F;
				p_td_head |= p_td_tail;
				ed_header->p_td_head = (void *)p_td_head;
				ed_header->p_td_tail = NULL;

				OHCI->HcControl |= HC_CONTROL_PLE;
				OHCI->HcControl |= HC_CONTROL_IE;

				return true;
			} else {
				/* Wait for transfer done. */
				do {
					p_td_head = ((uint32_t)(ed_header->p_td_head)) & 0xFFFFFFF0;
					p_td_tail = ((uint32_t)(ed_header->p_td_tail)) & 0xFFFFFFF0;
				} while(p_td_head != p_td_tail);

				OHCI->HcControl &= ~HC_CONTROL_PLE;
				OHCI->HcControl &= ~HC_CONTROL_IE;
				
				memset((void *)&isochronous_td_head[i], 0, sizeof(isochronous_td_head[i]));
				memset((void *)&isochronous_td_tail[i], 0, sizeof(isochronous_td_tail[i]));

				/* Start after 3 frame. */
				isochronous_td_head[i].td_info.bStartingFrame = ohci_get_frame_number() + 3;
				isochronous_td_head[i].td_info.bDelayInterrupt = 0;
				isochronous_td_head[i].td_info.FrameCount = 0;				// one frame transaction
				isochronous_td_head[i].td_info.bConditionCode = 0;
				isochronous_td_head[i].pBufferPage0= buf;
				isochronous_td_head[i].p_next_td = NULL;
				isochronous_td_head[i].pBufferEnd = buf + buf_size - 1;
				isochronous_td_head[i].offset_psw[0] = 0;

				/* Check the halt status. */
//				if ((uint32_t)ed_header->p_td_head & 0x01) {
//					return false;
//				}

				// set the skip
//				ed_header->ed_info.ed_info_s.bSkip = 1;

				ed_header->p_td_head = (void *)&isochronous_td_head[i];
				ed_header->p_td_tail = NULL;

				// clear the skip
//				ed_header->ed_info.ed_info_s.bSkip = 0;

				OHCI->HcControl |= HC_CONTROL_PLE;
				OHCI->HcControl |= HC_CONTROL_IE;
					
				return true;
			}
		}
	}
	return false;
}

/**
 * \brief Remove an transfer descriptor.
 *
 * \param ep_number endpoint number.
 */
void ohci_remove_td(uint8_t ep_number)
{
	uint32_t i;
	struct ohci_ed *ed_header;
	struct ohci_td_general *td_general_header;
	struct ohci_td_general *td_general_free_header;

	/* Control endpoints. */
	if (ep_number == 0) {
		control_ed.p_td_head = NULL;
		control_ed.p_td_tail = NULL; 
		return;
	} 

	/* Bulk endpoints. */
	ed_header = (struct ohci_ed *)OHCI->HcBulkHeadED;
	while (ed_header != NULL) {
		if (ed_header->ed_info.ed_info_s.bEndpointNumber ==	ep_number) {
			if (ed_header->p_td_head != ed_header->p_td_tail) {
				td_general_free_header = (struct ohci_td_general *)ed_header->p_td_head;
				while (td_general_free_header != NULL) {
					td_general_header = td_general_free_header->p_next_td;
					free(td_general_free_header);
					td_general_free_header = td_general_header;
				}
			}
			return;
		}
	}

	/* Int/ISO endpoints. */
	for (i = 0; i < 32; i++) {
		ed_header = (struct ohci_ed *)hcca.InterruptTable[i];
		while (ed_header != NULL) {
			if (ed_header->ed_info.ed_info_s.bEndpointNumber == ep_number) {
				ed_header->p_td_head = NULL;
				ed_header->p_td_tail = NULL;
				return;
			}
			ed_header = ed_header->p_next_ed;
		}
	}
}

/**
 * \brief Enable interrupt.
 *
 * \param int_source interrupt source type.
 */
void ohci_enable_interrupt(enum ohci_interrupt_source int_source)
{
	if (int_source == OHCI_INTERRUPT_SO) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_SO;
	}
	if (int_source == OHCI_INTERRUPT_WDH) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_WDH;
	}
	if (int_source == OHCI_INTERRUPT_SF) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_SF;
	}
	if (int_source == OHCI_INTERRUPT_RD) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_RD;
	}
	if (int_source == OHCI_INTERRUPT_UE) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_UE;
	}
	if (int_source == OHCI_INTERRUPT_FNO) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_FNO;
	}
	if (int_source == OHCI_INTERRUPT_RHSC) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_RHSC;
	}
	if (int_source == OHCI_INTERRUPT_OC) {
		OHCI->HcInterruptEnable = HC_INTERRUPT_OC;
	}
}

/**
 * \brief Disable interrupt.
 *
 * \param int_source interrupt source type.
 */
void ohci_disable_interrupt(enum ohci_interrupt_source int_source)
{
	if (int_source == OHCI_INTERRUPT_SO) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_SO;
	}
	if (int_source == OHCI_INTERRUPT_WDH) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_WDH;
	}
	if (int_source == OHCI_INTERRUPT_SF) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_SF;
	}
	if (int_source == OHCI_INTERRUPT_RD) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_RD;
	}
	if (int_source == OHCI_INTERRUPT_UE) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_UE;
	}
	if (int_source == OHCI_INTERRUPT_FNO) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_FNO;
	}
	if (int_source == OHCI_INTERRUPT_RHSC) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_RHSC;
	}
	if (int_source == OHCI_INTERRUPT_OC) {
		OHCI->HcInterruptDisable = HC_INTERRUPT_OC;
	}
}

/**
 * \brief Register interrupt callback function.
 *
 * \param int_source interrupt source type.
 * \param call_back Pointer to the callback function.
 */
void ohci_register_callback(enum ohci_interrupt_source int_source, void *call_back)
{
	ohci_callback_pointer[int_source] = (ohci_callback_t)call_back;
}

/**
 * \brief Unregister interrupt callback function.
 *
 * \param int_source interrupt source type.
 */
void ohci_unregister_callback(enum ohci_interrupt_source int_source)
{
	ohci_callback_pointer[int_source] = NULL;
}

/**
 * \brief USB host interrupt handler.
 */
void UHP_Handler()
{
	uint32_t int_status;
	uint32_t rh_status;
	uint32_t rh_port_status;
	struct ohci_td_general *td_general_header;

	rh_status = OHCI->HcRhStatus;
	rh_port_status = OHCI->HcRhPortStatus;

	/**
	 * Read interrupt status (and flush pending writes).  We ignore the
	 * optimization of checking the LSB of hcca->done_head; it doesn't
	 * work on all systems (edge triggering for OHCI can be a factor).
	 */
	int_status = OHCI->HcInterruptStatus;

	/* We only care about interrupts that are enabled */
	int_status &= OHCI->HcInterruptEnable;

	if (int_status & HC_INTERRUPT_WDH) {
		td_general_header = (struct ohci_td_general *)hcca.pDoneHead;
		OHCI->HcInterruptStatus = HC_INTERRUPT_WDH;
		callback_para = (uint32_t)td_general_header;
		callback_para &= 0xFFFFFFF0;
		if (callback_para == ((uint32_t)&control_td_head & 0xFFFFFFF0)) {
			callback_para |= 0x80000000;
		}
		callback_para |= td_general_header->td_info.bConditionCode;
		ohci_callback_pointer[OHCI_INTERRUPT_WDH](&callback_para);
	}

	/**
	 * For connect and disconnect events, we expect the controller
	 * to turn on RHSC along with RD.  But for remote wakeup events
	 * this might not happen.
	 */
	if (int_status & HC_INTERRUPT_RD) {
		/* Resume detected. */
		OHCI->HcInterruptStatus = HC_INTERRUPT_RD;
		ohci_bus_resume();
		ohci_callback_pointer[OHCI_INTERRUPT_RD](&callback_para);
	}

	if (int_status & HC_INTERRUPT_RHSC) {
		if (bus_reset_flag) {
			OHCI->HcRhPortStatus = RH_PS_PRSC;
			OHCI->HcInterruptStatus = HC_INTERRUPT_RHSC;
			bus_reset_flag = false;
			callback_para = BUS_RESET;
			ohci_callback_pointer[OHCI_INTERRUPT_RHSC](&callback_para);
		} else if (rh_port_status & RH_PS_CSC) {
			OHCI->HcRhPortStatus = RH_PS_CSC;
			OHCI->HcInterruptStatus = HC_INTERRUPT_RHSC;
			if (!(rh_status & RH_HS_DRWE)) {
				if (rh_port_status & RH_PS_CCS) {
					callback_para = BUS_CONNECT;
				} else {
					callback_para = BUS_DISCONNECT;
				}
				ohci_callback_pointer[OHCI_INTERRUPT_RHSC](&callback_para);
			}
		} else {
			OHCI->HcInterruptStatus = HC_INTERRUPT_RHSC;
			callback_para = 0xff;
		}
	}

	if (int_status & HC_INTERRUPT_SF) {
		OHCI->HcInterruptStatus = HC_INTERRUPT_SF;
		ohci_callback_pointer[OHCI_INTERRUPT_SF](&callback_para);
	}

	if (int_status & HC_INTERRUPT_SO) {
		OHCI->HcInterruptStatus = HC_INTERRUPT_SO;
		ohci_callback_pointer[OHCI_INTERRUPT_SO](&callback_para);
	}

	if (int_status & HC_INTERRUPT_UE) {
		OHCI->HcInterruptStatus = HC_INTERRUPT_UE;
		ohci_callback_pointer[OHCI_INTERRUPT_UE](&callback_para);
	}
}

