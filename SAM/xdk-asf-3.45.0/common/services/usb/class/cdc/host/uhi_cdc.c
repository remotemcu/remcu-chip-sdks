/**
 * \file
 *
 * \brief USB host Communication Device Class interface.
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

#include "conf_usb_host.h"
#include "usb_protocol.h"
#include "uhd.h"
#include "uhc.h"
#include "uhi_cdc.h"
#include <string.h>

#ifdef USB_HOST_HUB_SUPPORT
#  error USB HUB support is not implemented on UHI CDC
#endif

#ifndef UHI_CDC_RX_NOTIFY
#  define UHI_CDC_RX_NOTIFY()
#endif

//! Define the minimum internal buffer size
#ifdef UHI_CDC_LOW_RATE
#  define UHI_CDC_BUFFER_SIZE  (1*64)
#else
#  define UHI_CDC_BUFFER_SIZE  (5*64)
#endif

/**
 * \ingroup uhi_cdc_group
 * \defgroup uhi_cdc_group_internal Implementation of UHI Communication Device Class
 *
 * Class internal implementation
 * @{
 */

/**
 * \name Internal defines and variables to manage CDC device
 */
//@{

//! Internal buffer information
typedef struct {
	//! Position of consumer in this buffer
	uint16_t pos;
	//! Number of data available in buffer
	uint16_t nb;
	//! Pointer on internal buffer
	uint8_t* ptr;
} uhi_cdc_buf_t;

//! Communication line information
typedef struct {
	//! Bulk endpoint number used to transfer data
	usb_ep_t ep_data;
	//! True, if a transfer is on-going on endpoint
	bool b_trans_ongoing;
	//! Frame number of last transfer
	uint16_t sof;
	//! Current internal buffer used to store data
	volatile uint8_t buf_sel;
	//! Size of internal buffer (unit Byte)
	uint16_t buffer_size;
	//! Internal buffer information
	uhi_cdc_buf_t buffer[2];
} uhi_cdc_line_t;

//! Communication port information
typedef struct {
	//! Current port configuration (baudrate,...)
	usb_cdc_line_coding_t conf;
	//! USB CDC-COMM interface number
	uint8_t  iface_comm;
	//! USB CDC-DATA interface number
	uint8_t  iface_data;
	//! Interrupt IN endpoint from CDC-COMM interface
	usb_ep_t ep_comm_in;
	//! RX line information
	uhi_cdc_line_t line_rx;
	//! TX line information
	uhi_cdc_line_t line_tx;
} uhi_cdc_port_t;

//! USB CDC device information
typedef struct {
	//! Pointer on USB Device information
	uhc_device_t *dev;
	//! True, if a CDC Device has been enumerated
	bool b_enabled;
	//! Pointer on communication port(s) information
	uhi_cdc_port_t *port;
	//! Number of port available on this USB device
	uint8_t nb_port;
} uhi_cdc_dev_t;

//! Information about the enumerated USB CDC device
static uhi_cdc_dev_t uhi_cdc_dev = {
	.dev = NULL,
	.nb_port = 0,
};
//@}

/**
 * \name Internal routines
 */
//@{

/**
 * \brief Free all CDC device structures
 */
static void uhi_cdc_free_device(void);

/**
 * \brief Returns a port structure information
 *
 * \param port_num  Number of port
 *
 * \return pointer on port structure
 */
static uhi_cdc_port_t* uhi_cdc_get_port(uint8_t port_num);

/**
 * \brief Changes the port configuration
 *
 * \param port_num       Number of port
 * \param configuration  Pointer on new configuration
 *
 * \return True, if success
 */
static bool uhi_cdc_set_conf(uint8_t port, usb_cdc_line_coding_t *configuration);

/**
 * \brief Sends a control line command on the port
 *
 * \param port_num       Number of port
 * \param wValue         USB CDC control line word
 *
 * \return True, if success
 */
static bool uhi_cdc_set_ctrl_line(uint8_t port, le16_t wValue);

/**
 * \brief Update the transfer endpoint IN (RX)
 * Valid the reception of the previous transfer.
 * Start a new transfer on endpoint IN, if a RX buffer is free
 * and a new USB frame is occurred since last transfer.
 *
 * \param line        RX communication line to manage
 *
 * \return True, if a new transfer has been started
 */
static bool uhi_cdc_rx_update(uhi_cdc_line_t *line);

/**
 * \brief Manage the end of RX transfer.
 * Registered by uhd_ep_run()
 * Callback called by USB interrupt after data transfer or abort (reset,...).
 *
 * \param add            USB address used by the transfer
 * \param status         Transfer status
 * \param nb_transferred Number of data transfered
 */
static void uhi_cdc_rx_received(usb_add_t add, usb_ep_t ep,
		uhd_trans_status_t status, iram_size_t nb_transferred);

/**
 * \brief Update the transfer endpoint OUT (TX)
 * Start a new transfer on endpoint OUT, if a data must be send
 * and a new USB frame is occurred since last transfer.
 *
 * \param line        TX communication line to manage
 *
 * \return True, if a new transfer has been started
 */
static bool uhi_cdc_tx_update(uhi_cdc_line_t *line);

/**
 * \brief Manage the end of TX transfer.
 * Registered by uhd_ep_run()
 * Callback called by USB interrupt after data transfer or abort (reset,...).
 *
 * \param add            USB address used by the transfer
 * \param status         Transfer status
 * \param nb_transferred Number of data transfered
 */
static void uhi_cdc_tx_send(usb_add_t add, usb_ep_t ep,
		uhd_trans_status_t status, iram_size_t nb_transferred);
//@}

//@}


/**
 * \name Interface used by UHC module
 */
//@{

uhc_enum_status_t uhi_cdc_install(uhc_device_t* dev)
{
	bool b_iface_comm, b_iface_data;
	uint16_t conf_desc_lgt;
	uint8_t port_num, i;
	usb_iface_desc_t *ptr_iface;
	uhi_cdc_port_t *ptr_port = NULL;
	uhi_cdc_line_t *ptr_line;

	if (uhi_cdc_dev.dev != NULL) {
		return UHC_ENUM_SOFTWARE_LIMIT; // Device already allocated
	}

	// Compute the number of port
	conf_desc_lgt = le16_to_cpu(dev->conf_desc->wTotalLength);
	ptr_iface = (usb_iface_desc_t*)dev->conf_desc;
	uhi_cdc_dev.nb_port = 0;
	while (conf_desc_lgt) {
		if ((ptr_iface->bDescriptorType == USB_DT_INTERFACE)
				&& (ptr_iface->bInterfaceClass == CDC_CLASS_COMM)
				&& (ptr_iface->bInterfaceSubClass == CDC_SUBCLASS_ACM)
				&& (ptr_iface->bInterfaceProtocol <= CDC_PROTOCOL_V25TER)) {
			// New COM port has been found
			uhi_cdc_dev.nb_port++;
		}
		Assert(conf_desc_lgt>=ptr_iface->bLength);
		conf_desc_lgt -= ptr_iface->bLength;
		ptr_iface = (usb_iface_desc_t*)((uint8_t*)ptr_iface + ptr_iface->bLength);
	}
	if (uhi_cdc_dev.nb_port == 0) {
		return UHC_ENUM_UNSUPPORTED; // No interface supported
	}

	// Alloc port structures
	uhi_cdc_dev.port = malloc(uhi_cdc_dev.nb_port * sizeof(uhi_cdc_port_t));
	if (uhi_cdc_dev.port == NULL) {
		Assert(false);
		return UHC_ENUM_SOFTWARE_LIMIT;
	}
	// Initialize structure
	for (i = 0; i<uhi_cdc_dev.nb_port; i++) {
		uhi_cdc_dev.port[i].ep_comm_in = 0;
		uhi_cdc_dev.port[i].iface_data = 0xFF;
		uhi_cdc_dev.port[i].line_rx.ep_data = 0;
		uhi_cdc_dev.port[i].line_rx.buffer[0].ptr = NULL;
		uhi_cdc_dev.port[i].line_rx.buffer[1].ptr = NULL;
		uhi_cdc_dev.port[i].line_tx.ep_data = 0;
		uhi_cdc_dev.port[i].line_tx.buffer[0].ptr = NULL;
		uhi_cdc_dev.port[i].line_tx.buffer[1].ptr = NULL;
	}

	// Fill port structures
	conf_desc_lgt = le16_to_cpu(dev->conf_desc->wTotalLength);
	ptr_iface = (usb_iface_desc_t*)dev->conf_desc;
	b_iface_comm = false;
	b_iface_data = false;
	port_num = 0;
	while (conf_desc_lgt) {
		switch (ptr_iface->bDescriptorType) {

		case USB_DT_INTERFACE:
			if ((ptr_iface->bInterfaceClass == CDC_CLASS_COMM)
					&& (ptr_iface->bInterfaceSubClass == CDC_SUBCLASS_ACM)
					&& (ptr_iface->bInterfaceProtocol <= CDC_PROTOCOL_V25TER) ) {
				// New Communication Class COM port has been found
				b_iface_comm = true;
				ptr_port = &uhi_cdc_dev.port[port_num++];
				ptr_port->iface_comm = ptr_iface->bInterfaceNumber;
			} else {
				// Stop allocation endpoint(s)
				b_iface_comm = false;
			}
			if ((ptr_iface->bInterfaceClass == CDC_CLASS_DATA)
					&& (ptr_iface->bInterfaceSubClass == 0)
					&& (ptr_iface->bInterfaceProtocol == 0) ) {
				for (i = 0; i<uhi_cdc_dev.nb_port; i++) {
					ptr_port = &uhi_cdc_dev.port[i];
					if (ptr_port->iface_data == 0xFF) {
						b_iface_data = true;
						break;
					}
					else if (ptr_port->iface_data == ptr_iface->bInterfaceNumber) {
						// New CDC DATA Class has been found
						// and correspond at a CDC COMM Class
						b_iface_data = true;
						break;
					}
				}
			} else {
				// Stop allocation endpoint(s)
				b_iface_data = false;
			}
			break;

		case CDC_CS_INTERFACE:
			if (!b_iface_comm) {
				break;
			}
			if (((usb_cdc_call_mgmt_desc_t*)ptr_iface)->bDescriptorSubtype == CDC_SCS_CALL_MGMT) {
				ptr_port->iface_data = ((usb_cdc_call_mgmt_desc_t*)ptr_iface)->bDataInterface;
			}
			break;

		case USB_DT_ENDPOINT:
			//  Allocation of the endpoint
			if (b_iface_comm) {
				Assert (((usb_ep_desc_t*)ptr_iface)->bmAttributes == USB_EP_TYPE_INTERRUPT);
				Assert (((usb_ep_desc_t*)ptr_iface)->bEndpointAddress & USB_EP_DIR_IN);
				if (!uhd_ep_alloc(dev->address, (usb_ep_desc_t*)ptr_iface, dev->speed)) {
					uhi_cdc_free_device();
					return UHC_ENUM_HARDWARE_LIMIT; // Endpoint allocation fail
				}
				ptr_port->ep_comm_in = ((usb_ep_desc_t*)ptr_iface)->bEndpointAddress;
			}
			if (b_iface_data) {
				Assert (((usb_ep_desc_t*)ptr_iface)->bmAttributes == USB_EP_TYPE_BULK);
				if (!uhd_ep_alloc(dev->address, (usb_ep_desc_t*)ptr_iface, dev->speed)) {
					uhi_cdc_free_device();
					return UHC_ENUM_HARDWARE_LIMIT; // Endpoint allocation fail
				}

				if (((usb_ep_desc_t*)ptr_iface)->bEndpointAddress & USB_EP_DIR_IN) {
					ptr_line = &ptr_port->line_rx;
				} else {
					ptr_line = &ptr_port->line_tx;
				}
				ptr_line->ep_data = ((usb_ep_desc_t*)ptr_iface)->bEndpointAddress;
				ptr_line->b_trans_ongoing = false;
				ptr_line->buf_sel = 0;

				// Allocate and initialize buffers
				uint16_t buf_size = Max( le16_to_cpu(
						((usb_ep_desc_t*)ptr_iface)->wMaxPacketSize),
						UHI_CDC_BUFFER_SIZE );
				ptr_line->buffer_size = buf_size;
				ptr_line->buffer[0].pos = 0;
				ptr_line->buffer[0].nb = 0;
				ptr_line->buffer[0].ptr = malloc(buf_size);
				if (ptr_line->buffer[0].ptr == NULL) {
					Assert(false);
					uhi_cdc_free_device();
					return UHC_ENUM_SOFTWARE_LIMIT;
				}
				ptr_line->buffer[1].pos = 0;
				ptr_line->buffer[1].nb = 0;
				ptr_line->buffer[1].ptr = malloc(buf_size);
				if (ptr_line->buffer[1].ptr == NULL) {
					Assert(false);
					uhi_cdc_free_device();
					return UHC_ENUM_SOFTWARE_LIMIT;
				}

			}
			break;

		}
		Assert(conf_desc_lgt >= ptr_iface->bLength);
		conf_desc_lgt -= ptr_iface->bLength;
		ptr_iface = (usb_iface_desc_t*)((uint8_t*)ptr_iface + ptr_iface->bLength);
	}

	// Check installed ports
	for (i = 0; i<uhi_cdc_dev.nb_port; i++) {
		if ((uhi_cdc_dev.port[i].ep_comm_in == 0)
				|| (uhi_cdc_dev.port[i].line_rx.ep_data == 0)
				|| (uhi_cdc_dev.port[i].line_tx.ep_data == 0)) {
			// Install is not complete
			uhi_cdc_free_device();
			return UHC_ENUM_UNSUPPORTED;
		}
	}
	uhi_cdc_dev.b_enabled = false;
	uhi_cdc_dev.dev = dev;
	return UHC_ENUM_SUCCESS;
}

void uhi_cdc_enable(uhc_device_t* dev)
{
	if (uhi_cdc_dev.dev != dev) {
		return; // No interface to enable
	}
	uhi_cdc_dev.b_enabled = true;

	// Start all data transfers
	uhi_cdc_sof(false);
	UHI_CDC_CHANGE(dev,true);
}

void uhi_cdc_uninstall(uhc_device_t* dev)
{
	if (uhi_cdc_dev.dev != dev) {
		return; // Device not enabled in this interface
	}
	uhi_cdc_dev.dev = NULL;
	uhi_cdc_free_device();
	UHI_CDC_CHANGE(dev,false);
}

void uhi_cdc_sof(bool b_micro)
{
	uint8_t port = 0;
	uhi_cdc_port_t *ptr_port;
	UNUSED(b_micro);

	if (uhi_cdc_dev.dev == NULL) {
		return; // No interface to installed
	}
	if (!uhi_cdc_dev.b_enabled) {
		return; // Interface not enabled
	}

	// Update transfers on each port
	while (1) {
		ptr_port = uhi_cdc_get_port(port++);
		if (ptr_port == NULL) {
			break;
		}
		uhi_cdc_rx_update(&ptr_port->line_rx);
		uhi_cdc_tx_update(&ptr_port->line_tx);
	}
}
//@}


/**
 * \name Internal routines
 */
//@{

static void uhi_cdc_free_device(void)
{
	if (uhi_cdc_dev.port == NULL) {
		return;
	}

	for (uint8_t i = 0; i<uhi_cdc_dev.nb_port; i++) {
		if (uhi_cdc_dev.port[i].line_rx.buffer[0].ptr) {
			free(uhi_cdc_dev.port[i].line_rx.buffer[0].ptr);
		}
		if (uhi_cdc_dev.port[i].line_rx.buffer[1].ptr) {
			free(uhi_cdc_dev.port[i].line_rx.buffer[1].ptr);
		}
		if (uhi_cdc_dev.port[i].line_tx.buffer[0].ptr) {
			free(uhi_cdc_dev.port[i].line_tx.buffer[0].ptr);
		}
		if (uhi_cdc_dev.port[i].line_tx.buffer[1].ptr) {
			free(uhi_cdc_dev.port[i].line_tx.buffer[1].ptr);
		}
	}
	free(uhi_cdc_dev.port);
}

static uhi_cdc_port_t* uhi_cdc_get_port(uint8_t port_num)
{
	if (uhi_cdc_dev.dev == NULL) {
		return NULL;
	}
	if (port_num >= uhi_cdc_dev.nb_port) {
		return NULL;
	}
	return &uhi_cdc_dev.port[port_num];
}

static bool uhi_cdc_set_conf(uint8_t port, usb_cdc_line_coding_t *configuration)
{
	uhi_cdc_port_t *ptr_port;
	usb_setup_req_t req;

	// Select port
	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}
	memcpy(&ptr_port->conf, configuration, sizeof(usb_cdc_line_coding_t));

	// Enable configuration
	req.bmRequestType = USB_REQ_RECIP_INTERFACE | USB_REQ_TYPE_CLASS | USB_REQ_DIR_OUT;
	req.bRequest = USB_REQ_CDC_SET_LINE_CODING;
	req.wValue = 0;
	req.wIndex = ptr_port->iface_comm;
	req.wLength = sizeof(usb_cdc_line_coding_t);
	if (!uhd_setup_request(uhi_cdc_dev.dev->address,
			&req,
			(uint8_t *) &ptr_port->conf,
			sizeof(usb_cdc_line_coding_t),
			NULL, NULL)) {
		return false;
	}
	return true;
}

static bool uhi_cdc_set_ctrl_line(uint8_t port, le16_t wValue)
{
	uhi_cdc_port_t *ptr_port;
	usb_setup_req_t req;

	// Select port
	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}

	// Enable configuration
	req.bmRequestType = USB_REQ_RECIP_INTERFACE | USB_REQ_TYPE_CLASS | USB_REQ_DIR_OUT;
	req.bRequest = USB_REQ_CDC_SET_CONTROL_LINE_STATE;
	req.wValue = wValue;
	req.wIndex = ptr_port->iface_comm;
	req.wLength = 0;
	if (!uhd_setup_request(uhi_cdc_dev.dev->address,
			&req,
			NULL,
			0,
			NULL, NULL)) {
		return false;
	}
	return true;
}

static bool uhi_cdc_rx_update(uhi_cdc_line_t *line)
{
	irqflags_t flags;
	uhi_cdc_buf_t *buf_nosel;
	uhi_cdc_buf_t *buf_sel;

	flags = cpu_irq_save();
	// Check if transfer is already on-going
	if (line->b_trans_ongoing) {
		cpu_irq_restore(flags);
		return false;
	}

	// Search a empty buffer to start a transfer
	buf_sel = &line->buffer[line->buf_sel];
	buf_nosel = &line->buffer[(line->buf_sel == 0)? 1 : 0];
	if (buf_sel->pos >= buf_sel->nb) {
		// The current buffer has been read
		// then reset it
		buf_sel->pos = 0;
		buf_sel->nb = 0;
	}
	if (!buf_sel->nb && buf_nosel->nb) {
		// New data available then change current buffer
		line->buf_sel = (line->buf_sel == 0)? 1 : 0;
		buf_nosel = buf_sel;
		UHI_CDC_RX_NOTIFY();
	}

	if (buf_nosel->nb) {
		// No empty buffer available to start a transfer
		cpu_irq_restore(flags);
		return false;
	}

	// Check if transfer must be delayed after the next SOF
	if (uhi_cdc_dev.dev->speed == UHD_SPEED_HIGH) {
		if (line->sof == uhd_get_microframe_number()) {
			cpu_irq_restore(flags);
			return false;
		}
	} else {
		if (line->sof == uhd_get_frame_number()) {
			cpu_irq_restore(flags);
			return false;
		}
	}

	// Start transfer on empty buffer
	line->b_trans_ongoing = true;
	cpu_irq_restore(flags);

	return uhd_ep_run(
		uhi_cdc_dev.dev->address,
		line->ep_data,
		true,
		buf_nosel->ptr,
		line->buffer_size,
		10,
		uhi_cdc_rx_received);
}

static void uhi_cdc_rx_received(
		usb_add_t add,
		usb_ep_t ep,
		uhd_trans_status_t status,
		iram_size_t nb_transferred)
{
	uint8_t port = 0;
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_line_t *line;
	uhi_cdc_buf_t *buf;
	UNUSED(add);

	// Search port corresponding at endpoint
	while (1) {
		ptr_port = uhi_cdc_get_port(port++);
		if (ptr_port == NULL) {
			return;
		}
		line = &ptr_port->line_rx;
		if (ep == line->ep_data) {
			break; // Port found
		}
	}

	if ((UHD_TRANS_TIMEOUT == status) && nb_transferred) {
		// Save transfered
	}
	else if (UHD_TRANS_NOERROR != status) {
		// Abort transfer
		line->b_trans_ongoing  = false;
		return;
	}

	// Update SOF tag, if it is a short packet
	if (nb_transferred != line->buffer_size) {
		if (uhi_cdc_dev.dev->speed == UHD_SPEED_HIGH) {
			line->sof = uhd_get_microframe_number();
		} else {
			line->sof = uhd_get_frame_number();
		}
	}

	// Update buffer structure
	buf = &line->buffer[(line->buf_sel == 0) ? 1 : 0];
	buf->pos = 0;
	buf->nb = nb_transferred;
	line->b_trans_ongoing  = false;

	// Manage new transfer
	uhi_cdc_rx_update(line);
}


static bool uhi_cdc_tx_update(uhi_cdc_line_t *line)
{
	irqflags_t flags;
	uhi_cdc_buf_t *buf;

	flags = cpu_irq_save();
	// Check if transfer is already on-going
	if (line->b_trans_ongoing) {
		cpu_irq_restore(flags);
		return false;
	}
	// Check if transfer must be delayed after the next SOF
	if (uhi_cdc_dev.dev->speed == UHD_SPEED_HIGH) {
		if (line->sof == uhd_get_microframe_number()) {
			cpu_irq_restore(flags);
			return false;
		}
	} else {
		if (line->sof == uhd_get_frame_number()) {
			cpu_irq_restore(flags);
			return false;
		}
	}

	// Send the current buffer if not empty
	buf = &line->buffer[line->buf_sel];
	if (buf->nb == 0) {
		cpu_irq_restore(flags);
		return false;
	}

	// Change current buffer to next buffer
	line->buf_sel = (line->buf_sel == 0)? 1 : 0;

	// Start transfer
	line->b_trans_ongoing = true;
	cpu_irq_restore(flags);

	return uhd_ep_run(
		uhi_cdc_dev.dev->address,
		line->ep_data,
		true,
		buf->ptr,
		buf->nb,
		1000,
		uhi_cdc_tx_send);
}


static void uhi_cdc_tx_send(
		usb_add_t add,
		usb_ep_t ep,
		uhd_trans_status_t status,
		iram_size_t nb_transferred)
{
	uint8_t port = 0;
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_line_t *line;
	uhi_cdc_buf_t *buf;
	irqflags_t flags;
	UNUSED(add);

	flags = cpu_irq_save();

	// Search port corresponding at endpoint
	while (1) {
		ptr_port = uhi_cdc_get_port(port++);
		if (ptr_port == NULL) {
			cpu_irq_restore(flags);
			return;
		}
		line = &ptr_port->line_tx;
		if (ep == line->ep_data) {
			break; // Port found
		}
	}

	if (UHD_TRANS_NOERROR != status) {
		// Abort transfer
		line->b_trans_ongoing  = false;
		cpu_irq_restore(flags);
		return;
	}

	// Update SOF tag, if it is a short packet
	if (nb_transferred != line->buffer_size) {
		if (uhi_cdc_dev.dev->speed == UHD_SPEED_HIGH) {
			line->sof = uhd_get_microframe_number();
		} else {
			line->sof = uhd_get_frame_number();
		}
	}

	// Update buffer structure
	buf = &line->buffer[(line->buf_sel == 0) ? 1 : 0 ];
	buf->nb = 0;
	line->b_trans_ongoing  = false;
	cpu_irq_restore(flags);

	// Manage new transfer
	uhi_cdc_tx_update(line);
}
//@}


bool uhi_cdc_open(uint8_t port, usb_cdc_line_coding_t *configuration)
{
	// Send configuration
	if (!uhi_cdc_set_conf(port, configuration)) {
		return false;
	}
	// Send DTR
	if (!uhi_cdc_set_ctrl_line(port, CDC_CTRL_SIGNAL_DTE_PRESENT)) {
		return false;
	}
	return true;
}

void uhi_cdc_close(uint8_t port)
{
	// Clear DTR
	uhi_cdc_set_ctrl_line(port, 0);
}

bool uhi_cdc_is_rx_ready(uint8_t port)
{
	return (0 != uhi_cdc_get_nb_received(port));
}

iram_size_t uhi_cdc_get_nb_received(uint8_t port)
{
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_buf_t *buf;

	// Select port
	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}

	// Check available data
	buf = &ptr_port->line_rx.buffer[ ptr_port->line_rx.buf_sel ];
	return (buf->nb - buf->pos);
}

int uhi_cdc_getc(uint8_t port)
{
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_line_t *line;
	uhi_cdc_buf_t *buf;
	int rx_data = 0;
	bool b_databit_9;

	// Select port
	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}
	line = &ptr_port->line_rx;

	b_databit_9 = (9 == ptr_port->conf.bDataBits);

uhi_cdc_getc_process_one_byte:
	// Check available data
	buf = &line->buffer[line->buf_sel];
	while (buf->pos >= buf->nb) {
		if (NULL == uhi_cdc_get_port(port)) {
			return 0;
		}
		uhi_cdc_rx_update(line);
		goto uhi_cdc_getc_process_one_byte;
	}

	// Read data
	rx_data |= buf->ptr[buf->pos];
	buf->pos++;

	uhi_cdc_rx_update(line);

	if (b_databit_9) {
		// Receive MSB
		b_databit_9 = false;
		rx_data = rx_data << 8;
		goto uhi_cdc_getc_process_one_byte;
	}
	return rx_data;
}

iram_size_t uhi_cdc_read_buf(uint8_t port, void* buf, iram_size_t size)
{
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_line_t *line;
	uhi_cdc_buf_t *cdc_buf;
	iram_size_t copy_nb;

	// Select port
	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}
	line = &ptr_port->line_rx;


uhi_cdc_read_buf_loop_wait:
	// Check available data
	cdc_buf = &line->buffer[line->buf_sel];
	while (cdc_buf->pos >= cdc_buf->nb) {
		if (NULL == uhi_cdc_get_port(port)) {
			return 0;
		}
		uhi_cdc_rx_update(line);
		goto uhi_cdc_read_buf_loop_wait;
	}

	// Read data
	copy_nb = cdc_buf->nb - cdc_buf->pos;
	if (copy_nb > size) {
		copy_nb = size;
	}
	memcpy(buf, &cdc_buf->ptr[cdc_buf->pos], copy_nb);
	cdc_buf->pos += copy_nb;
	buf = (uint8_t*)buf + copy_nb;
	size -= copy_nb;

	uhi_cdc_rx_update(line);

	if (size) {
		goto uhi_cdc_read_buf_loop_wait;
	}
	return 0;
}


bool uhi_cdc_is_tx_ready(uint8_t port)
{
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_line_t *line;

	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}
	line = &ptr_port->line_tx;

	return (line->buffer_size != line->buffer[line->buf_sel].nb);
}


int uhi_cdc_putc(uint8_t port, int value)
{
	irqflags_t flags;
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_line_t *line;
	uhi_cdc_buf_t *buf;
	bool b_databit_9;

	// Select port
	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}
	line = &ptr_port->line_tx;

	b_databit_9 = (9 == ptr_port->conf.bDataBits);

uhi_cdc_putc_process_one_byte:
	// Check available space
	buf = &line->buffer[line->buf_sel];
	while (line->buffer_size == buf->nb) {
		if (NULL == uhi_cdc_get_port(port)) {
			return false;
		}
		goto uhi_cdc_putc_process_one_byte;
	}

	// Write value
	flags = cpu_irq_save();
	buf = &line->buffer[line->buf_sel];
	buf->ptr[buf->nb++] = value;
	cpu_irq_restore(flags);

	if (b_databit_9) {
		// Send MSB
		b_databit_9 = false;
		value = value >> 8;
		goto uhi_cdc_putc_process_one_byte;
	}
	return true;
}

iram_size_t uhi_cdc_write_buf(uint8_t port, const void* buf, iram_size_t size)
{
	irqflags_t flags;
	uhi_cdc_port_t *ptr_port;
	uhi_cdc_line_t *line;
	uhi_cdc_buf_t *cdc_buf;
	iram_size_t copy_nb;

	// Select port
	ptr_port = uhi_cdc_get_port(port);
	if (ptr_port == NULL) {
		return false;
	}
	line = &ptr_port->line_tx;

	if (9 == ptr_port->conf.bDataBits) {
		size *=2;
	}

uhi_cdc_write_buf_loop_wait:
	// Check available space
	cdc_buf = &line->buffer[line->buf_sel];
	while (line->buffer_size == cdc_buf->nb) {
		if (NULL == uhi_cdc_get_port(port)) {
			return 0;
		}
		goto uhi_cdc_write_buf_loop_wait;
	}

	// Write value
	flags = cpu_irq_save();
	cdc_buf = &line->buffer[line->buf_sel];
	copy_nb = line->buffer_size - cdc_buf->nb;
	if (copy_nb>size) {
		copy_nb = size;
	}
	memcpy(&cdc_buf->ptr[cdc_buf->nb], buf, copy_nb);
	cdc_buf->nb += copy_nb;
	cpu_irq_restore(flags);

	// Update buffer pointer
	buf = (uint8_t*)buf + copy_nb;
	size -= copy_nb;

	if (size) {
		goto uhi_cdc_write_buf_loop_wait;
	}

	return 0;
}

//@}
