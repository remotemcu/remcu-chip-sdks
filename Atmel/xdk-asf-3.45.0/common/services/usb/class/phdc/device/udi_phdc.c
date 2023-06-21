/**
 * \file
 *
 * \brief USB Device Personal Healthcare Device Class (PHDC) interface.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "conf_usb.h"
#include "usb_protocol.h"
#include "usb_protocol_phdc.h"
#include "udd.h"
#include "udc.h"
#include "udi_phdc.h"
#include <string.h>

#if ((UDI_PHDC_QOS_OUT & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
#  error LOW-GOOD (latency-reliability) is not authorized on OUT bulk endpoint
#endif

/**
 * \ingroup udi_phdc_group
 * \defgroup udi_phdc_group_udc Interface with USB Device Core (UDC)
 *
 * Structures and functions required by UDC.
 *
 * @{
 */
bool udi_phdc_enable(void);
void udi_phdc_disable(void);
bool udi_phdc_setup(void);
uint8_t udi_phdc_getsetting(void);

/* ! Global structure which contains standard UDI API for UDC */
UDC_DESC_STORAGE udi_api_t udi_api_phdc = {
	.enable = udi_phdc_enable,
	.disable = udi_phdc_disable,
	.setup = udi_phdc_setup,
	.getsetting = udi_phdc_getsetting,
	.sof_notify = NULL,
};
/* @} */

/**
 * \ingroup udi_phdc_group
 * \defgroup udi_phdc_group_internal Implementation of UDI PHDC
 *
 * Class internal implementation
 * @{
 */

/**
 * \name Internal variables to manage PHDC
 * @{
 */

/* ! Variable to store the transfer pending flag */
COMPILER_WORD_ALIGNED
		static le16_t udi_phdc_holding_data;

#if (UDI_PHDC_PREAMBLE_FEATURE == true)
/* ! Flag to signal the state of preample feature */
static uint8_t udi_phdc_preample_feature;
#endif

COMPILER_PACK_SET(1)

/* ! Structure to manage the transfer on PHDC IN endpoints */
static struct {
	bool b_run;
	bool b_preample_run;
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
	usb_phdc_metadata_msg_t preample_header;
	uint8_t preample_opaque_data[UDI_PHDC_EP_SIZE_BULK_IN -
			sizeof(usb_phdc_metadata_msg_t)];
#endif
	udi_phdc_metadata_t *metadata;
	uint16_t metadata_pos;
	void (*callback)(uint16_t);
	void *cntx;
} udi_phdc_in_trans;

/* ! Structure to manage the transfer on PHDC OUT endpoint */
static struct {
	bool b_run;
	bool b_preample_run;
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
	usb_phdc_metadata_msg_t preample_header;
	uint8_t preample_opaque_data[UDI_PHDC_EP_SIZE_BULK_OUT -
			sizeof(usb_phdc_metadata_msg_t)];
#endif
	udi_phdc_metadata_t *metadata;
	uint16_t metadata_pos;
	void (*callback)(bool, uint16_t);
	void *cntx;
} udi_phdc_out_trans;

COMPILER_PACK_RESET()

/* @} */

/**
 * \name Internal routines
 * @{
 */

#if (UDI_PHDC_PREAMBLE_FEATURE == true)

/*! \brief This function sends a preample message
 *
 * \retval true when success
 */
static bool udi_phdc_send_preamplemsg(void);

/*! \brief Callback called when preample message is sent
 *
 * \retval status       Transfer state (UDD_EP_TRANSFER_ABORT/_OK)
 * \retval nb_send  Number of data sent
 */
static void udi_phdc_preamplemsg_ack(udd_ep_status_t status,
		iram_size_t nb_send, udd_ep_id_t ep);

#endif

/*! \brief This function sends a metadata
 *
 * \retval true when success
 */
static bool udi_phdc_send_metadata(void);

/*! \brief Callback called when metadata is sent
 *
 * \retval status       Transfer state (UDD_EP_TRANSFER_ABORT/_OK)
 * \retval nb_send  Number of data sent
 */
static void udi_phdc_metadata_ack(udd_ep_status_t status, iram_size_t nb_send,
		udd_ep_id_t ep);

#if (UDI_PHDC_PREAMBLE_FEATURE == true)

/*! \brief This function requests a preample message
 *
 * \retval true when success
 */
static bool udi_phdc_wait_preamplemsg(void);

/*! \brief Callback called when metadata is received
 *
 * \retval status       Transfer state (UDD_EP_TRANSFER_ABORT/_OK)
 * \retval nb_received  Number of data received
 */
static void udi_phdc_received_preample(udd_ep_status_t status,
		iram_size_t nb_received, udd_ep_id_t ep);

#endif

/*! \brief This function request metadata
 *
 * \retval true when success
 */
static bool udi_phdc_wait_metadata(uint8_t bNumTransfers);

/*! \brief Callback called when metadata is received
 *
 * \retval status       Transfer state (UDD_EP_TRANSFER_ABORT/_OK)
 * \retval nb_received  Number of data received
 */
static void udi_phdc_received_metadata(udd_ep_status_t status,
		iram_size_t nb_received, udd_ep_id_t ep);

/*! \brief Aborts all PHDC transfers on-going or pending
 */
static void udi_phdc_abort_all_transfers_ongoing(void);

/* @} */

/* ------------------------------- */
/* ------ Interface for UDC ------ */

bool udi_phdc_enable(void)
{
	/* Enable external component of PHDC interface */
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
	udi_phdc_preample_feature = false;
#endif
	udi_phdc_holding_data = 0;
	udi_phdc_in_trans.b_run = false;
	udi_phdc_out_trans.b_run = false;
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
	{
		uint8_t sig_tmp[] = METADATA_MESSAGE_SIG;
		/* Init struct signature */
		memcpy(udi_phdc_in_trans.preample_header.aSignature, sig_tmp,
				sizeof(sig_tmp));
		udi_phdc_in_trans.preample_header.bQoSEncodingVersion
			= USB_PHDC_QOS_ENCODING_VERSION_1;
	}
#endif
	return UDI_PHDC_ENABLE_EXT();
}

void udi_phdc_disable(void)
{
	udi_phdc_abort_all_transfers_ongoing();
	UDI_PHDC_DISABLE_EXT();
}

bool udi_phdc_setup(void)
{
	/* Interface requests */
	if (Udd_setup_is_in()) {
		/* Requests Interface GET */
		if (udd_g_ctrlreq.req.wLength == 0) {
			return false;   /* Error for USB host */
		}

		if (Udd_setup_type() == USB_REQ_TYPE_CLASS) {
			/* Requests Class Interface Get */
			switch (udd_g_ctrlreq.req.bRequest) {
			case USB_REQ_GET_STATUS:
				if (udd_g_ctrlreq.req.wValue != 0) {
					return false;
				}

				if (udd_g_ctrlreq.req.wLength !=
						sizeof(udi_phdc_holding_data)) {
					return false;
				}

				udd_g_ctrlreq.payload
						= (uint8_t *)&udi_phdc_holding_data;
				udd_g_ctrlreq.payload_size
						= sizeof(udi_phdc_holding_data);
				return true;
			}
		}
	}

	if (Udd_setup_is_out()) {
		/* Requests Interface SET */
		if (Udd_setup_type() == USB_REQ_TYPE_CLASS) {
			/* Requests Class Interface Set */
			switch (udd_g_ctrlreq.req.bRequest) {
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
			case USB_REQ_CLEAR_FEATURE:
				if ((udd_g_ctrlreq.req.wValue & 0xFF) !=
						USB_PHDC_FEATURE_METADATA) {
					return false;
				}

				if ((udd_g_ctrlreq.req.wValue >> 8) != 0) {
					return false;
				}

				udi_phdc_abort_all_transfers_ongoing();
				return true;

			case USB_REQ_SET_FEATURE:
				if (udd_g_ctrlreq.req.wLength != 0) {
					return false;
				}

				if ((udd_g_ctrlreq.req.wValue & 0xFF) !=
						USB_PHDC_FEATURE_METADATA) {
					return false;
				}

				if ((udd_g_ctrlreq.req.wValue >> 8) !=
						USB_PHDC_QOS_ENCODING_VERSION_1) {
					return false;
				}

				udi_phdc_abort_all_transfers_ongoing();
				return true;

#endif
			}
		}
	}

	return false; /* Not supported request */
}

uint8_t udi_phdc_getsetting(void)
{
	return 0; /* Always 0, no alternate setting on this interface */
}

/* -------------------------------------------- */
/* ------ Interface for application ----------- */

bool udi_phdc_senddata(udi_phdc_metadata_t *metadata,
		void (*callback)(uint16_t))
{
	bool b_status;
	irqflags_t flags;
	uint8_t qos = metadata->qos;

	/* Check qos: Only one bit must be set in qos */
	if ((0 == qos) || (0 != (qos & (qos - 1)))) {
		return false; /* bad qos value */
	}

	/* Check if qos is supported */
	if (0 == (qos & UDI_PHDC_QOS_IN)) {
		return false; /* qos not supported */
	}

	if (udi_phdc_in_trans.b_run) {
		return false; /* transfer already running */
	}

	/* Init transfer */
	udi_phdc_in_trans.metadata = metadata;
	udi_phdc_in_trans.metadata_pos = 0;
	udi_phdc_in_trans.callback = callback;
	udi_phdc_in_trans.b_preample_run = false;

	flags = cpu_irq_save();
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
	/* It is a bulk then check preample feature */
	if ((USB_PHDC_QOS_LOW_GOOD != qos) &&
			(udi_phdc_preample_feature)) {
		b_status = udi_phdc_send_preamplemsg();
	} else
#endif
	{
		b_status = udi_phdc_send_metadata();
	}
	cpu_irq_restore(flags);
	return b_status;
}

void udi_phdc_senddata_abort(void)
{
	if (udi_phdc_in_trans.b_run) {
		/* transfer running then abort */
#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
		if (USB_PHDC_QOS_LOW_GOOD == udi_phdc_in_trans.metadata->qos) {
			udd_ep_abort(UDI_PHDC_EP_INTERRUPT_IN);
		} else {
			udd_ep_abort(UDI_PHDC_EP_BULK_IN);
		}

#else
		udd_ep_abort(UDI_PHDC_EP_BULK_IN);
#endif
	}
}

bool udi_phdc_waitdata(udi_phdc_metadata_t *metadata,
		void (*callback)(bool, uint16_t))
{
	bool b_status;
	irqflags_t flags;

	if (udi_phdc_out_trans.b_run) {
		return false; /* transfer already running */
	}

	/* Init transfer */
	udi_phdc_out_trans.metadata = metadata;
	udi_phdc_out_trans.metadata_pos = 0;
	udi_phdc_out_trans.callback = callback;

	flags = cpu_irq_save();
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
	/* It is a bulk then check preample feature */
	if (udi_phdc_preample_feature) {
		b_status = udi_phdc_wait_preamplemsg();
	} else
#endif
	{
		/* Enable of wait data */
#if (UDI_PHDC_PREAMBLE_FEATURE == true)
		/* Qos cannot be determinated */
		udi_phdc_out_trans.metadata->qos = 0;

#else
		udi_phdc_out_trans.metadata->qos = UDI_PHDC_QOS_OUT;
#endif
		b_status = udi_phdc_wait_metadata(
				udi_phdc_out_trans.metadata->metadata_size
				/ UDI_PHDC_EP_SIZE_BULK_OUT);
	}

	cpu_irq_restore(flags);
	return b_status;
}

/* ------------------------------- */
/* ------ Internal routines ------ */

#if (UDI_PHDC_PREAMBLE_FEATURE == true)
static bool udi_phdc_send_preamplemsg(void)
{
	if ((UDI_PHDC_EP_SIZE_BULK_IN - 1 - sizeof(usb_phdc_metadata_msg_t))
			< udi_phdc_in_trans.metadata->opaque_size) {
		return false; /* Opaque data too large */
	}

	/* Fill preample message */
	udi_phdc_in_trans.preample_header.bNumTransfers
			= 1 + ((udi_phdc_in_trans.metadata->metadata_size - 1)
			/ UDI_PHDC_EP_SIZE_BULK_IN);
	udi_phdc_in_trans.preample_header.bmLatencyReliability
			= udi_phdc_in_trans.metadata->qos;
	udi_phdc_in_trans.preample_header.bOpaqueDataSize
			= udi_phdc_in_trans.metadata->opaque_size;
	memcpy(udi_phdc_in_trans.preample_opaque_data,
			udi_phdc_in_trans.metadata->opaquedata,
			udi_phdc_in_trans.metadata->opaque_size);
	/* Send preample message */
	if (!udd_ep_run(UDI_PHDC_EP_BULK_IN,
			true,
			(uint8_t *)&udi_phdc_in_trans.preample_header,
			udi_phdc_in_trans.
			preample_header.bOpaqueDataSize +
			sizeof(usb_phdc_metadata_msg_t),
			udi_phdc_preamplemsg_ack)) {
		return false;
	}

	udi_phdc_in_trans.b_run = true;
	udi_phdc_in_trans.b_preample_run = true;
	udi_phdc_holding_data |= cpu_to_le16(
			(1 <<(UDI_PHDC_EP_SIZE_BULK_IN & USB_EP_ADDR_MASK)));
	return true;
}

static void udi_phdc_preamplemsg_ack(udd_ep_status_t status,
		iram_size_t nb_send, udd_ep_id_t ep)
{
	/* Preample sending */
	udi_phdc_in_trans.b_run = false;
	udi_phdc_holding_data &= cpu_to_le16((~(1 <<
			(UDI_PHDC_EP_SIZE_BULK_IN & USB_EP_ADDR_MASK))));
	udi_phdc_in_trans.b_preample_run = false;
	if (UDD_EP_TRANSFER_ABORT == status) {
		/* Transfer abort */
		udi_phdc_in_trans.callback(0);
		return;
	}

	if (!udi_phdc_send_metadata()) {
		/* Transfer metadata impossible */
		udi_phdc_in_trans.callback(0);
	}
}

#endif /* (UDI_PHDC_PREAMBLE_FEATURE == true) */

static bool udi_phdc_send_metadata(void)
{
	udd_ep_id_t ep_num;

#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
	if (USB_PHDC_QOS_LOW_GOOD == udi_phdc_in_trans.metadata->qos) {
		ep_num = UDI_PHDC_EP_INTERRUPT_IN;
	} else
#endif
	{
		ep_num = UDI_PHDC_EP_BULK_IN;
	}

	/* Send data */
	if (!udd_ep_run(ep_num, true, udi_phdc_in_trans.metadata->metadata,
			udi_phdc_in_trans.
			metadata->metadata_size,
			udi_phdc_metadata_ack)) {
		/* Error then end of transfer */
		return false;
	}

	/* Uptade struct */
	udi_phdc_holding_data
			|= cpu_to_le16((1 << (ep_num & USB_EP_ADDR_MASK)));
	udi_phdc_in_trans.b_run = true;
	return true;
}

static void udi_phdc_metadata_ack(udd_ep_status_t status, iram_size_t nb_send,
		udd_ep_id_t ep)
{
	udd_ep_id_t ep_num;

#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
	if (USB_PHDC_QOS_LOW_GOOD == udi_phdc_in_trans.metadata->qos) {
		ep_num = UDI_PHDC_EP_INTERRUPT_IN;
	} else
#endif
	{
		ep_num = UDI_PHDC_EP_BULK_IN;
	}

	udi_phdc_in_trans.b_run = false;
	udi_phdc_holding_data
			&= cpu_to_le16((~(1 << (ep_num & USB_EP_ADDR_MASK))));
	udi_phdc_in_trans.callback(nb_send);
}

#if (UDI_PHDC_PREAMBLE_FEATURE == true)
static bool udi_phdc_wait_preamplemsg(void)
{
	/* Enable the reception of preample message */
	if (!udd_ep_run(UDI_PHDC_EP_BULK_OUT,
			false,
			(uint8_t *)&
			udi_phdc_out_trans.preample_header,
			UDI_PHDC_EP_SIZE_BULK_OUT,
			udi_phdc_received_preample)) {
		return false;
	}

	udi_phdc_out_trans.b_run = true;
	udi_phdc_out_trans.b_preample_run = true;
	return true;
}

static void udi_phdc_received_preample(udd_ep_status_t status,
		iram_size_t nb_received, udd_ep_id_t ep)
{
	uint8_t sig_tmp[] = METADATA_MESSAGE_SIG;

	udi_phdc_out_trans.b_preample_run = false;

	/* Check preample integrity */
	if (UDD_EP_TRANSFER_ABORT == status) {
		goto udi_phdc_received_preample_abort;
	}

	if (nb_received < sizeof(usb_phdc_metadata_msg_t)) {
		goto udi_phdc_received_preample_bad;
	}

	if (0 != memcmp(udi_phdc_out_trans.preample_header.aSignature, sig_tmp,
			sizeof(sig_tmp))) {
		goto udi_phdc_received_preample_bad;
	}

	if (0 == udi_phdc_out_trans.preample_header.bNumTransfers) {
		goto udi_phdc_received_preample_bad;
	}

	if (USB_PHDC_QOS_ENCODING_VERSION_1 !=
			udi_phdc_out_trans.preample_header.bQoSEncodingVersion) {
		goto udi_phdc_received_preample_bad;
	}

	if (0 != (udi_phdc_out_trans.preample_header.bmLatencyReliability
			& (udi_phdc_out_trans.
			preample_header.bmLatencyReliability
			- 1))) {
		goto udi_phdc_received_preample_bad;
	}

	if (0 == (UDI_PHDC_QOS_OUT & udi_phdc_out_trans.
			preample_header.bmLatencyReliability)) {
		goto udi_phdc_received_preample_bad;
	}

	if (nb_received !=
			(udi_phdc_out_trans.preample_header.bOpaqueDataSize +
			sizeof(usb_phdc_metadata_msg_t))) {
		goto udi_phdc_received_preample_bad;
	}

	udi_phdc_out_trans.metadata->qos
			= udi_phdc_out_trans.preample_header.bmLatencyReliability;
	udi_phdc_out_trans.metadata->opaque_size
			= udi_phdc_out_trans.preample_header.bOpaqueDataSize;
	udi_phdc_out_trans.metadata->opaquedata
			= udi_phdc_out_trans.preample_opaque_data;

	if (udi_phdc_out_trans.metadata->metadata_size <
			(udi_phdc_out_trans.preample_header.bNumTransfers
			* UDI_PHDC_EP_SIZE_BULK_OUT)) {
		goto udi_phdc_received_preample_bad;
	}

	if (!udi_phdc_wait_metadata(
			udi_phdc_out_trans.preample_header.bNumTransfers)) {
		goto udi_phdc_received_preample_bad;
	}

	return;

udi_phdc_received_preample_bad:
	/* Bad preample message then stall this endpoint */
	udd_ep_set_halt(UDI_PHDC_EP_BULK_OUT);
udi_phdc_received_preample_abort:
	udi_phdc_out_trans.b_run = false;
	udi_phdc_out_trans.callback(false, 0);
}

#endif /* (UDI_PHDC_PREAMBLE_FEATURE == true) */

static bool udi_phdc_wait_metadata(uint8_t bNumTransfers)
{
	/* Wait metadata */
	udi_phdc_out_trans.b_run =
			udd_ep_run(UDI_PHDC_EP_BULK_OUT,
			false,
			udi_phdc_out_trans.metadata->metadata,
			bNumTransfers * UDI_PHDC_EP_SIZE_BULK_OUT,
			udi_phdc_received_metadata);
	Assert(udi_phdc_out_trans.b_run);
	return udi_phdc_out_trans.b_run;
}

static void udi_phdc_received_metadata(udd_ep_status_t status,
		iram_size_t nb_received, udd_ep_id_t ep)
{
	udi_phdc_out_trans.b_run = false;
	if (UDD_EP_TRANSFER_OK != status) {
		udi_phdc_out_trans.callback(false, 0);
		return;
	}

	udi_phdc_out_trans.b_preample_run = false;
	udi_phdc_out_trans.callback(true, nb_received);
}

static void udi_phdc_abort_all_transfers_ongoing(void)
{
	if (0 != udi_phdc_holding_data) {
#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
		if (USB_PHDC_QOS_LOW_GOOD ==
				udi_phdc_in_trans.metadata->qos) {
			udd_ep_abort(UDI_PHDC_EP_INTERRUPT_IN);
		} else {
			udd_ep_abort(UDI_PHDC_EP_BULK_IN);
		}

#else
		udd_ep_abort(UDI_PHDC_EP_BULK_IN);
#endif
	}

#if (UDI_PHDC_PREAMBLE_FEATURE == true)
	udi_phdc_preample_feature = false;
#endif
	if (udi_phdc_out_trans.b_run) {
		/* Kill waiting transfer to start new one */
		udd_ep_abort(UDI_PHDC_EP_BULK_OUT);
	}
}

/* @} */
