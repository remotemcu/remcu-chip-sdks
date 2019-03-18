/**
 * \file
 *
 * \brief USB host driver
 * Compliance with common driver UHD
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

#include "conf_usb_host.h"
#include "sysclk.h"
#include "matrix.h"
#include "ohci/ohci_hcd.h"
#include <string.h>
#include <stdlib.h>

#if !(SAMG55)
# error The current UHP Driver supports only SAMG55.
#endif

#ifndef UHD_USB_INT_LEVEL
# define UHD_USB_INT_LEVEL 5 // By default USB interrupt have low priority
#endif

/* Optional UHC callbacks. */
#ifndef UHC_MODE_CHANGE
# define UHC_MODE_CHANGE(arg)
#endif
#ifndef UHC_SOF_EVENT
# define UHC_SOF_EVENT()
#endif
#ifndef UHC_VBUS_CHANGE
# define UHC_VBUS_CHANGE(b_present)
#endif
#ifndef UHC_VBUS_ERROR
# define UHC_VBUS_ERROR()
#endif

/**
 * \ingroup usb_host_group
 * \defgroup uhd_group USB Host Driver (UHD)
 *
 * \section uhp_conf UHP Custom configuration
 * The following UHP driver configuration must be defined in conf_usb_host.h
 * file of the application.
 *
 * USB_INT_LEVEL<br>
 * Option to change the interrupt priority (0 to 15) by default 5 (recommended).
 *
 * \section Callbacks management
 * The USB driver is fully managed by interrupt and does not request periodic
 * task. Thereby, the USB events use callbacks to transfer the information.
 * The callbacks can be declared in static during compilation
 * or dynamically during code execution.
 *
 * \section Power mode management
 * The driver uses the sleepmgr service to manage the different sleep modes.
 * The sleep mode depends on USB driver state (uhd_uhp_state_enum).
 * @{
 */

/**
 * \name Power management
 */
//@{
#ifndef UHP_NO_SLEEP_MGR

#include "sleepmgr.h"
/** States of UHP interface. */
enum uhd_uhp_state_enum {
	UHD_STATE_OFF = 0,
	UHD_STATE_WAIT_ID_HOST = 1,
	UHD_STATE_NO_VBUS = 2,
	UHD_STATE_DISCONNECT = 3,
	UHD_STATE_SUSPEND = 4,
	UHD_STATE_IDLE = 5,
};

/**
 * \brief Manages the sleep mode following the UHP state
 *
 * \param new_state  New UHP state
 */
static void uhd_sleep_mode(enum uhd_uhp_state_enum new_state)
{
	enum sleepmgr_mode sleep_mode[] = {
		SLEEPMGR_ACTIVE,    // UHD_STATE_OFF (not used)
		SLEEPMGR_ACTIVE, // UHD_STATE_WAIT_ID_HOST
		SLEEPMGR_ACTIVE, // UHD_STATE_NO_VBUS
		SLEEPMGR_ACTIVE, // UHD_STATE_DISCONNECT
		SLEEPMGR_ACTIVE, // UHD_STATE_SUSPEND
		SLEEPMGR_ACTIVE, // UHD_STATE_IDLE
	};

	static enum uhd_uhp_state_enum uhd_state = UHD_STATE_OFF;

	if (uhd_state == new_state) {
		return; // No change
	}
	if (new_state != UHD_STATE_OFF) {
		/* Lock new limit. */
		sleepmgr_lock_mode(sleep_mode[new_state]);
	}
	if (uhd_state != UHD_STATE_OFF) {
		/* Unlock old limit. */
		sleepmgr_unlock_mode(sleep_mode[uhd_state]);
	}
	uhd_state = new_state;
}

#else
#  define uhd_sleep_mode(arg)
#endif // UHP_NO_SLEEP_MGR
//@}

/** Store the callback to be call at the end of reset signal. */
static uhd_callback_reset_t uhd_reset_callback = NULL;

/** Store the callback to be call at the end of setup request. */
struct uhd_callback_setup_end_parameter {
	usb_add_t add;
	uhd_trans_status_t status;
	uint16_t payload_trans;
};
static struct uhd_callback_setup_end_parameter callback_setup_end_para;
static uhd_callback_setup_end_t callback_setup_end_func = NULL;

/** Store the callback to be call at the end of one transaction. */
struct uhd_callback_trans_end_parameter {
	usb_add_t add;
	usb_ep_t ep;
	uhd_trans_status_t status;
	iram_size_t nb_transfered;
	struct ohci_td_general *td_general_header;
	uhd_callback_trans_t callback_trans_end_func;
	bool flag;
};
static struct uhd_callback_trans_end_parameter callback_trans_end_para[8];

/** Variables to manage the suspend/resume sequence */
static uint8_t uhd_suspend_start;
static uint8_t uhd_resume_start;

/**
 * \internal
 * \brief Manages callback in transfer end
 */
static void uhd_transfer_end(void *pointer)
{
	uint32_t completion_code;
	uint32_t i;
	struct ohci_td_general *td_general_header;
	iram_size_t current_buffer_point;

	td_general_header = (struct ohci_td_general *)pointer;

	uint32_t *type = (uint32_t *)pointer;
	volatile uint32_t callback_type = *type;

	if (!(callback_type & 0x80000000)) {
		td_general_header = (struct ohci_td_general *)(callback_type & 0xFFFFFFF0);
		while (td_general_header != NULL) {
			/* Check if there is free callback resource. */
			for (i = 0; i < 8; i++) {
				if (callback_trans_end_para[i].td_general_header ==
							td_general_header) {
					break;
				}
			}
			if (i == 8) {
				return;
			}

			if (callback_trans_end_para[i].callback_trans_end_func != NULL) {
				current_buffer_point =
						(iram_size_t)td_general_header->pCurrentBufferPointer;
				if (!current_buffer_point) {
					current_buffer_point =
						(iram_size_t)td_general_header->pBufferEnd + 1;
				}

				completion_code = (callback_type & 0x0000000F);
				if (completion_code == TD_CONDITIONCODE_STALL) {
					callback_trans_end_para[i].status = UHD_TRANS_STALL;
					ohci_clear_ed_transfer_status(td_general_header);
				}

				callback_trans_end_para[i].callback_trans_end_func(
						callback_trans_end_para[i].add,
						callback_trans_end_para[i].ep,
						callback_trans_end_para[i].status,
						(current_buffer_point
						- callback_trans_end_para[i].nb_transfered));

				memset((void *)&callback_trans_end_para[i], 0,
						sizeof(callback_trans_end_para[i]));
			}

			td_general_header = td_general_header->p_next_td;
		}
	} else if (callback_type & 0x80000000) {
		if (callback_setup_end_func != NULL) {
			uhd_callback_setup_end_t callback_setup = callback_setup_end_func;
			callback_setup_end_func = NULL;

			callback_setup(callback_setup_end_para.add,
						callback_setup_end_para.status,
						callback_setup_end_para.payload_trans);

		}
	}
}

/**
 * \internal
 * \brief Manages timeouts and actions based on SOF events
 * - UHC user notification
 * - SOF user notification
 */
static void uhd_sof_interrupt(void *pointer)
{
	UNUSED(pointer);

	/* Manage a delay to enter in suspend */
	if (uhd_suspend_start) {
		if (--uhd_suspend_start == 0) {
			ohci_bus_suspend();
			uhd_sleep_mode(UHD_STATE_SUSPEND);
		}
		return; // Abort SOF events
	}

	/* Manage a delay to exit of suspend */
	if (uhd_resume_start) {
		if (--uhd_resume_start == 0) {
			// Notify the UHC
			uhc_notify_resume();
			uhd_sleep_mode(UHD_STATE_IDLE);
		}
		return; // Abort SOF events
	}

	/* Notify the UHC. */
	uhc_notify_sof(false);

	/* Notify the user application. */
	UHC_SOF_EVENT();
}

static void uhd_remote_wakeup(void *pointer)
{
	UNUSED(pointer);

	/* Wait 50ms before restarting transfer. */
	uhd_resume_start = 50;
}

static void uhd_status_change(void *pointer)
{
	uint32_t *bus_flag;

	bus_flag = (uint32_t *)pointer;

	if (*bus_flag == BUS_CONNECT) {
		uhc_notify_connection(true);
	} else if (*bus_flag == BUS_DISCONNECT) {
		uhc_notify_connection(false);
	} else if (*bus_flag == BUS_RESET) {
		if (uhd_reset_callback != NULL) {
			uhd_reset_callback();
			uhd_reset_callback = NULL;
		}
	}
}

void uhd_enable(void)
{
	irqflags_t flags;

	uhd_suspend_start = 0;
	uhd_resume_start = 0;

	uhd_sleep_mode(UHD_STATE_DISCONNECT);

#if SAMG55
	matrix_set_usb_host();
#endif

	/* Enable USB hardware clock. */
	sysclk_enable_usb();
	pmc_enable_periph_clk(ID_UHP);

	/**
	 * Always authorize asynchronous USB interrupts to exit of sleep mode
	 * For SAMG55 USB wake up device except BACKUP mode.
	 */
	NVIC_SetPriority((IRQn_Type)ID_UHP, UHD_USB_INT_LEVEL);
	NVIC_EnableIRQ((IRQn_Type)ID_UHP);
//	pmc_set_fast_startup_input(PMC_FSMR_USBAL);

	/* To avoid USB interrupt before end of initialization. */
	flags = cpu_irq_save();

	ohci_init();
	ohci_register_callback(OHCI_INTERRUPT_WDH, (void *)uhd_transfer_end);
	ohci_register_callback(OHCI_INTERRUPT_SF, (void *)uhd_sof_interrupt);
	ohci_register_callback(OHCI_INTERRUPT_RD, (void *)uhd_remote_wakeup);
	ohci_register_callback(OHCI_INTERRUPT_RHSC, (void *)uhd_status_change);

	cpu_irq_restore(flags);
}


void uhd_disable(bool b_id_stop)
{
	UNUSED(b_id_stop);

	irqflags_t flags;

	flags = cpu_irq_save();
	ohci_deinit();
	cpu_irq_restore(flags);

	/* Do not authorize asynchronous USB interrupts. */
//	pmc_clr_fast_startup_input(PMC_FSMR_USBAL);
	sysclk_disable_usb();
	pmc_disable_periph_clk(ID_UHP);
	uhd_sleep_mode(UHD_STATE_OFF);

}

uhd_speed_t uhd_get_speed(void)
{
	switch (ohci_get_device_speed()) {

	case 0:
		return UHD_SPEED_FULL;

	case 1:
		return UHD_SPEED_LOW;

	default:
		Assert(false);
		return UHD_SPEED_LOW;
	}
}

uint16_t uhd_get_frame_number(void)
{
	return ohci_get_frame_number();
}

uint16_t uhd_get_microframe_number(void)
{
	return 0; // Not supported
}

void uhd_send_reset(uhd_callback_reset_t callback)
{
	uhd_reset_callback = callback;
	ohci_bus_reset();
}

void uhd_suspend(void)
{
	/* Wait three SOFs before entering in suspend state. */
	uhd_suspend_start = 3;
}

bool uhd_is_suspend(void)
{
	if(ohci_is_suspend()) {
		return true;
	} else {
		return false;
	}
}

void uhd_resume(void)
{
	ohci_bus_resume();
	/* Wait 50ms before restarting transfer. */
	uhd_resume_start = 50;
}

bool uhd_ep0_alloc(usb_add_t add, uint8_t ep_size)
{
	ed_info_t ed_info_temp;

	if (ep_size < 8) {
		return false;
	}

	ed_info_temp.ed_info_s.bFunctionAddress = add;             // device address
	ed_info_temp.ed_info_s.bEndpointNumber = 0;                // endpoint 0
	ed_info_temp.ed_info_s.bDirection = 0;                     // in TD
	ed_info_temp.ed_info_s.bSpeed = ohci_get_device_speed();   // speed
	ed_info_temp.ed_info_s.bSkip = 0;                          // no skip
	ed_info_temp.ed_info_s.bFormat = 0;                        // General TD
	ed_info_temp.ed_info_s.bMaximumPacketSize = ep_size;       // max packet size

	ohci_add_ed_control(&ed_info_temp);

	return true;
}

bool uhd_ep_alloc(usb_add_t add, usb_ep_desc_t * ep_desc, uhd_speed_t speed)
{
	ed_info_t ed_info_temp;
	bool return_value;
	uint8_t ep_type;
	uint8_t ep_dir;
	(void)speed; // No high speed currently

	ep_type = ep_desc->bmAttributes&USB_EP_TYPE_MASK;
	if (ep_desc->bEndpointAddress & USB_EP_DIR_IN) {
		ep_dir = 2;
	} else {
		ep_dir = 1;
	}

	ed_info_temp.ed_info_s.bFunctionAddress = add;                        // device address=UHC_DEVICE_ENUM_ADD=1
	ed_info_temp.ed_info_s.bEndpointNumber = ep_desc->bEndpointAddress;   // endpoint number
	ed_info_temp.ed_info_s.bDirection = ep_dir;                           // Set direction
	ed_info_temp.ed_info_s.bSpeed = (speed == UHD_SPEED_LOW);             // speed
	ed_info_temp.ed_info_s.bSkip = 0;                                     // no skip
	ed_info_temp.ed_info_s.bFormat = 0;                                   // General TD
	ed_info_temp.ed_info_s.bMaximumPacketSize = ep_desc->wMaxPacketSize;  // max packet size

	switch(ep_type) {
	case USB_EP_TYPE_ISOCHRONOUS:
		ed_info_temp.ed_info_s.bFormat = 1;                // ISO TD
		return_value = ohci_add_ed_period(&ed_info_temp);
		break;
	case USB_EP_TYPE_INTERRUPT:
		return_value = ohci_add_ed_period(&ed_info_temp);
		break;
	case USB_EP_TYPE_BULK:
		return_value = ohci_add_ed_bulk(&ed_info_temp);
		break;
	default:
		Assert(false);
		return false;
	}

	return return_value;
}


void uhd_ep_free(usb_add_t add, usb_ep_t endp)
{
	UNUSED(add);

	ohci_remove_ed(endp);
}

bool uhd_setup_request(
		usb_add_t add,
		usb_setup_req_t *req,
		uint8_t *payload,
		uint16_t payload_size,
		uhd_callback_setup_run_t callback_run,
		uhd_callback_setup_end_t callback_end)
{
	UNUSED(callback_run);

	bool return_value;

	irqflags_t flags;
	flags = cpu_irq_save();

	/* Add setup TD. */
	return_value = ohci_add_td_control(TD_PID_SETUP, (uint8_t *)req, sizeof(usb_setup_req_t));
	if (return_value == false) {
		cpu_irq_restore(flags);
		return false;
	}

	if ((req->bmRequestType & USB_REQ_DIR_MASK) == USB_REQ_DIR_IN) {
		/* Add in TD. */
		return_value = ohci_add_td_control(TD_PID_IN, payload, payload_size);
		if (return_value == false) {
			cpu_irq_restore(flags);
			return false;
		}

		/* Add out TD. */
		return_value = ohci_add_td_control(TD_PID_OUT, payload, 0);
		if (return_value == false) {
			cpu_irq_restore(flags);
			return false;
		}
	} else {
		if (req->wLength) {
			/* Add out TD. */
			return_value = ohci_add_td_control(TD_PID_OUT, payload, payload_size);
			if (return_value == false) {
				cpu_irq_restore(flags);
				return false;
			}

			/* Add in TD. */
			return_value = ohci_add_td_control(TD_PID_IN, payload, 0);
			if (return_value == false) {
				cpu_irq_restore(flags);
				return false;
			}
		} else {
			/* No DATA phase */
			return_value = ohci_add_td_control(TD_PID_IN, payload, 0);
			if (return_value == false) {
				cpu_irq_restore(flags);
				return false;
			}
		}
	}

	callback_setup_end_para.add = add;
	callback_setup_end_para.status = UHD_TRANS_NOERROR;
	callback_setup_end_para.payload_trans = payload_size;
	callback_setup_end_func = callback_end;

	cpu_irq_restore(flags);

	return true;
}

bool uhd_ep_run(usb_add_t add,
		usb_ep_t endp,
		bool b_shortpacket,
		uint8_t *buf,
		iram_size_t buf_size,
		uint16_t timeout,
		uhd_callback_trans_t callback)
{
	UNUSED(b_shortpacket);
	UNUSED(timeout);

	uint32_t i;
	bool return_value = true;

	/* Check if there is free callback resource. */
	for (i = 0; i < 8; i++) {
		if (!callback_trans_end_para[i].flag) {
			memset((void *)&callback_trans_end_para[i], 0,
					sizeof(callback_trans_end_para[i]));
			break;
		}
	}
	if (i == 8) {
		return false;
	}

	irqflags_t flags;

	flags = cpu_irq_save();

	return_value = ohci_add_td_non_control(endp, buf, buf_size,
			&callback_trans_end_para[i].td_general_header);
	if (return_value == false) {
		cpu_irq_restore(flags);
		return false;
	}

	callback_trans_end_para[i].add = add;
	callback_trans_end_para[i].ep = endp;
	callback_trans_end_para[i].status = UHD_TRANS_NOERROR;
	callback_trans_end_para[i].nb_transfered = (iram_size_t)buf;
	callback_trans_end_para[i].callback_trans_end_func = callback;
	callback_trans_end_para[i].flag = 1;

	cpu_irq_restore(flags);

	return true;
}

void uhd_ep_abort(usb_add_t add, usb_ep_t endp)
{
	UNUSED(add);

	ohci_remove_td(endp);
}



//@}
