/**
 * \file
 *
 * \brief SAM D11 USB Mass Storage Class Driver
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


#include "usb_msc.h"
#include <stdbool.h>
#include <string.h>
#include <asf.h>
#include <sd_mmc_spi.h>
#include "scsi_commands.h"
#include "usb_descriptor.h"
static callback_t callback_sof = NULL;

#define OUT_BANK                           0
#define IN_BANK                            1
/* USB data Block size - 512 */
#define UDI_MSC_BLOCK_SIZE                 512L

#define NVM_SW_CALIB_DFLL48M_COARSE_VAL    58
#define NVM_SW_CALIB_DFLL48M_FINE_VAL      64

#define NVM_USB_PAD_TRANSN_POS             45
#define NVM_USB_PAD_TRANSN_SIZE            5
#define NVM_USB_PAD_TRANSP_POS             50
#define NVM_USB_PAD_TRANSP_SIZE            5
#define NVM_USB_PAD_TRIM_POS               55
#define NVM_USB_PAD_TRIM_SIZE              3

static void usb_pad_calibration(void);
static void USB_Setup_Send_ZLP(void);
static void USB_Setup_Send_Stall(bool direction_in);

/*Global variables */
volatile uint8_t loej, load_eject;
uint16_t CBWCB_transfer_length;
uint8_t CurrentConfig;
uint8_t csw_fail;
uint8_t slot = 0;
sd_mmc_err_t err;

COMPILER_WORD_ALIGNED UsbDeviceDescriptor usb_endpoint_table[TOTAL_EP];
COMPILER_WORD_ALIGNED uint8_t ctrl_ep_out_buffer[CTRL_EP_SIZE];
COMPILER_WORD_ALIGNED uint8_t ctrl_ep_in_buffer[CTRL_EP_SIZE];
COMPILER_WORD_ALIGNED uint8_t msc_bulk_ep_out_buffer[MSC_BULK_IN_EP_SIZE];
COMPILER_WORD_ALIGNED uint8_t msc_bulk_ep_in_buffer[MSC_BULK_OUT_EP_SIZE];

static volatile uint8_t bmRequestType, bRequest, dir;
static volatile uint16_t wValue, wIndex, wLength, wStatus;

struct sbc_read_capacity10_data {
	/* !< LBA of last logical block */
	be32_t max_lba;
	 /* !< Number of bytes in the last logical block */
	be32_t block_len;
};

struct command_block_wrapper {
	uint8_t dCBWSignature[4];
	uint8_t dCBWTag[4];
	uint8_t dCBWDataTransferLength[4];
	uint8_t bmCBWFlags;
	uint8_t bCBWLUN;
	uint8_t bCBWCBLength;
	uint8_t CBWCB[16];
}
cbw;

struct csw_signature {
	/* dCSWSignature Signature field contain 53425355h (little endian) */
	uint8_t dCSWSignature[4];
	uint8_t dCSWTag[4];
	uint8_t dCSWDataResidue[4];
	uint8_t bCSWStatus;
};

/* USB SOF callback */
#if defined (USB_CALLBACK_SOF)
void usb_set_callback(callback_t callback_func)
{
	callback_sof = (callback_t)callback_func;
}

#endif

/**
 * \brief   USB function to initialize the USB module
 */
void usb_init(void)
{
	/* Enable USB clock */
	PM->APBBMASK.reg |= PM_APBBMASK_USB;

	/* Set up the USB DM pin */
	PORT->Group[0].PINCFG[PIN_PA24G_USB_DM].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[PIN_PA24G_USB_DM / 2].reg
		&= ~(0xF << (4 * (PIN_PA24G_USB_DM & 0x01u)));
	PORT->Group[0].PMUX[PIN_PA24G_USB_DM / 2].reg
		|= MUX_PA24G_USB_DM << (4 * (PIN_PA24G_USB_DM & 0x01u));

	/* Set up the USB DP pin */
	PORT->Group[0].PINCFG[PIN_PA25G_USB_DP].bit.PMUXEN = 1;
	PORT->Group[0].PMUX[PIN_PA25G_USB_DP / 2].reg
		&= ~(0xF << (4 * (PIN_PA25G_USB_DP & 0x01u)));
	PORT->Group[0].PMUX[PIN_PA25G_USB_DP / 2].reg
		|= MUX_PA25G_USB_DP << (4 * (PIN_PA25G_USB_DP & 0x01u));

	/* GCLK_ID - USB - 0x06 */
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN |
			GCLK_CLKCTRL_GEN(USB_GCLK_GEN) |
			GCLK_CLKCTRL_ID(USB_GCLK_ID);

	/* Reset */
	USB->DEVICE.CTRLA.bit.SWRST = 1;
	while (USB->DEVICE.SYNCBUSY.reg & USB_SYNCBUSY_SWRST) {
		/* Sync wait */
	}

	/* USB Pad calibration */
	usb_pad_calibration();

	/* Set the configuration */
	/* Set mode to Device mode */
	USB->DEVICE.CTRLA.bit.MODE = 0;
	/* Enable Run in Standby */
	USB->DEVICE.CTRLA.bit.RUNSTDBY = true;
	/* Set the descriptor address */
	USB->DEVICE.DESCADD.reg = (uint32_t)(&usb_endpoint_table[0]);
	/* Set speed configuration to Full speed */
	USB->DEVICE.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_FS_Val;
	/* Attach to the USB host */
	USB->DEVICE.CTRLB.reg &= ~USB_DEVICE_CTRLB_DETACH;

	/* Initialize endpoint table RAM location to a known value 0 */
	memset((uint8_t *)(&usb_endpoint_table[0]), 0,
			sizeof(usb_endpoint_table));

	/* Enable needed interrupts */
	USB->DEVICE.INTENSET.reg = USB_DEVICE_INTENSET_SOF |
			USB_DEVICE_INTENSET_EORST;
	USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTENSET.reg = USB_DEVICE_EPINTENSET_RXSTP;
	USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRCPT1;
	USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRCPT1;
	USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
	USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;

	/* Set callback function to be called on a USB SOF interrupt */
	usb_set_callback(USB_CALLBACK_SOF);

	/* Enable USB Interrupt in NVIC */
	NVIC_EnableIRQ(USB_IRQn);

	/* Enable USB module */
	USB->DEVICE.CTRLA.reg |= USB_CTRLA_ENABLE;
}

/**
 * \brief   USB function to calibrate its DP/DM pads
 */
static void usb_pad_calibration()
{
	uint32_t pad_transn, pad_transp, pad_trim;
	/* Load DP/DM drivers pad calibration from NVM Software Calibration Area
	 **/
	pad_transn = (*((uint32_t *)(NVMCTRL_OTP4)
			+ (NVM_USB_PAD_TRANSN_POS / 32))
			>> (NVM_USB_PAD_TRANSN_POS % 32))
			& ((1 << NVM_USB_PAD_TRANSN_SIZE) - 1);
	if (pad_transn == 0x1F) {
		pad_transn = 5;
	}

	USB->DEVICE.PADCAL.bit.TRANSN = pad_transn;

	/* Load DP/DM drivers pad calibration from NVM Software Calibration Area
	 **/
	pad_transp = (*((uint32_t *)(NVMCTRL_OTP4)
			+ (NVM_USB_PAD_TRANSP_POS / 32))
			>> (NVM_USB_PAD_TRANSP_POS % 32))
			& ((1 << NVM_USB_PAD_TRANSP_SIZE) - 1);
	if (pad_transp == 0x1F) {
		pad_transp = 29;
	}

	USB->DEVICE.PADCAL.bit.TRANSP = pad_transp;

	/* Load DP/DM drivers pad calibration from NVM Software Calibration Area
	 **/
	pad_trim = (*((uint32_t *)(NVMCTRL_OTP4)
			+ (NVM_USB_PAD_TRIM_POS / 32))
			>> (NVM_USB_PAD_TRIM_POS % 32))
			& ((1 << NVM_USB_PAD_TRIM_SIZE) - 1);
	if (pad_trim == 0x7) {
		pad_trim = 3;
	}

	USB->DEVICE.PADCAL.bit.TRIM = pad_trim;
}


/**
 * \brief    USB function to send Zero Length Packet
 */
static void USB_Setup_Send_ZLP()
{
	/* Set the byte count as zero */
	usb_endpoint_table[CTRL_EP].DeviceDescBank[IN_BANK].PCKSIZE.bit.
	BYTE_COUNT = 0;
	/* Clear the transfer complete flag  */
	USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
	/* Set the bank as ready */
	USB->DEVICE.DeviceEndpoint[CTRL_EP].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK1RDY;
	/* Wait for transfer to complete */
	while (!(USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTFLAG.reg &
			USB_DEVICE_EPINTFLAG_TRCPT(2))) {
	}
}


/**
 * \brief   USB function to send stall request
 */
static void USB_Setup_Send_Stall(bool direction_in)
{
	/* Check the direction */
	if (direction_in) {
		/* Set STALL request on IN direction */
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPSTATUSSET.reg
			= USB_DEVICE_EPSTATUSSET_STALLRQ(2);
	} else {
		/* Set STALL request on OUT direction */
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPSTATUSSET.reg
			= USB_DEVICE_EPSTATUSSET_STALLRQ(1);
	}
}


/**
 * \brief   USB function to write data to host via endpoint
 *
 * \param pData    USB data
 * \param length   Length of data
 * \param ep_num   endpoint number
 */
int32_t USB_Write(uint8_t *pData, int32_t length, uint8_t ep_num)
{
	uint32_t data_address;
	uint8_t buf_index;

	/* Set buffer index */
	buf_index = (ep_num == 0) ? 0 : 1;

	/* Check for requirement for multi-packet or auto zlp */
	if (length >=
			(1 <<
			(usb_endpoint_table[ep_num].DeviceDescBank[IN_BANK].
			PCKSIZE.
			bit.SIZE + 3))) {
		/* Update the EP data address */
		data_address = (uint32_t)pData;
	} else {
		/* Copy to local buffer */
		if (buf_index) {
			memcpy(msc_bulk_ep_in_buffer, pData, length);
			/* Update the EP data address */
			data_address = (uint32_t)&msc_bulk_ep_in_buffer[0];
		} else {
			memcpy(ctrl_ep_in_buffer, pData, length);
			/* Update the EP data address */
			data_address = (uint32_t)&ctrl_ep_in_buffer[0];
		}
	}

	/* Set the buffer address for ep data */
	usb_endpoint_table[ep_num].DeviceDescBank[IN_BANK].ADDR.reg
		= data_address;
	/* Set the byte count as zero */
	usb_endpoint_table[ep_num].DeviceDescBank[IN_BANK].PCKSIZE.bit.
	BYTE_COUNT = length;

	/* Set the multi packet size as zero for multi-packet transfers where
	 * length > ep size */
	usb_endpoint_table[ep_num].DeviceDescBank[IN_BANK].PCKSIZE.bit.
	MULTI_PACKET_SIZE = 0;
	/* Clear the transfer complete flag  */
	USB->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
	/* Set the bank as ready */
	USB->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK1RDY;

	/* Wait for transfer to complete */
	while (!(USB->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg &
			USB_DEVICE_EPINTFLAG_TRCPT(2))) {
	}
	return length;
}


/**
 * \brief    USB interrupt handler
 */
void USB_Handler(void)
{
	struct csw_signature CSW_failed_unsupported_command = {
		.dCSWSignature[0] = 0x55,
		.dCSWSignature[1] = 0x53,
		.dCSWSignature[2] = 0x42,
		.dCSWSignature[3] = 0x53,
		.dCSWTag[0] = cbw.dCBWTag[0],
		.dCSWTag[1] = cbw.dCBWTag[1],
		.dCSWTag[2] = cbw.dCBWTag[2],
		.dCSWTag[3] = cbw.dCBWTag[3],
		.dCSWDataResidue[0] = cbw.dCBWDataTransferLength[0],
		.dCSWDataResidue[1] = cbw.dCBWDataTransferLength[1],
		.dCSWDataResidue[2] = cbw.dCBWDataTransferLength[2],
		.dCSWDataResidue[3] = cbw.dCBWDataTransferLength[3],
		 /* command failed */
		.bCSWStatus        = 0x01,
	};

	/* USB interrupt because of SOF token */
	if (USB->DEVICE.INTFLAG.reg & USB_DEVICE_INTFLAG_SOF) {
		/* Clear interrupt flag */
		USB->DEVICE.INTFLAG.reg = USB_DEVICE_INTFLAG_SOF;

		if (callback_sof) {
			callback_sof();
		}
	}

	/* USB interrupt because of end of reset signal */
	if (USB->DEVICE.INTFLAG.reg & USB_DEVICE_INTFLAG_EORST) {
		USB->DEVICE.INTFLAG.reg = USB_DEVICE_INTFLAG_EORST;
		/* Set Device address as 0 */
		USB->DEVICE.DADD.reg = USB_DEVICE_DADD_ADDEN | 0;
		/* Configure endpoint 0 */
		/* Configure Endpoint 0 for Control IN and Control OUT */
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPCFG.reg
			= USB_DEVICE_EPCFG_EPTYPE0(1) |
				USB_DEVICE_EPCFG_EPTYPE1(1);
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPSTATUSSET.reg
			= USB_DEVICE_EPSTATUSSET_BK0RDY;
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPSTATUSCLR.reg
			= USB_DEVICE_EPSTATUSCLR_BK1RDY;
		/* Configure control OUT Packet size to 64 bytes */
		usb_endpoint_table[CTRL_EP].DeviceDescBank[OUT_BANK].PCKSIZE.bit
		.SIZE = 3;
		/* Configure control IN Packet size to 64 bytes */
		usb_endpoint_table[CTRL_EP].DeviceDescBank[IN_BANK].PCKSIZE.bit.
		SIZE = 3;
		/* Configure the data buffer address for control OUT */
		usb_endpoint_table[CTRL_EP].DeviceDescBank[OUT_BANK].ADDR.reg
			= (uint32_t)&ctrl_ep_out_buffer[0];
		/* Configure the data buffer address for control IN */
		usb_endpoint_table[CTRL_EP].DeviceDescBank[IN_BANK].ADDR.reg
			= (uint32_t)&ctrl_ep_in_buffer[0];

		/* Set Multipacket size to 8 for control OUT and byte count to
		 * 0*/
		usb_endpoint_table[CTRL_EP].DeviceDescBank[OUT_BANK].PCKSIZE.bit
		.MULTI_PACKET_SIZE = 8;
		usb_endpoint_table[CTRL_EP].DeviceDescBank[OUT_BANK].PCKSIZE.bit
		.BYTE_COUNT = 0;
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPSTATUSCLR.reg
			= USB_DEVICE_EPSTATUSCLR_BK0RDY;
		USB->DEVICE.INTENSET.reg = USB_DEVICE_INTENSET_SOF |
				USB_DEVICE_INTENSET_EORST;
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTENSET.reg = USB_DEVICE_EPINTENSET_RXSTP;
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRCPT1;
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
		CurrentConfig = 0;
	}

	/* USB interrupt because of received setup signal from control endpoint
	**/
	if (USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_RXSTP) {
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_RXSTP;
		/* Read the USB request parameters */
		bmRequestType = ctrl_ep_out_buffer[0];
		bRequest      = ctrl_ep_out_buffer[1];
		wValue        = (ctrl_ep_out_buffer[2] & 0xFF);
		wValue       |= (ctrl_ep_out_buffer[3] << 8);
		wIndex        = (ctrl_ep_out_buffer[4] & 0xFF);
		wIndex       |= (ctrl_ep_out_buffer[5] << 8);
		wLength       = (ctrl_ep_out_buffer[6] & 0xFF);
		wLength      |= (ctrl_ep_out_buffer[7] << 8);

		/* Clear the Bank 0 ready flag on Control OUT */
		USB->DEVICE.DeviceEndpoint[CTRL_EP].EPSTATUSCLR.reg
			= USB_DEVICE_EPSTATUSCLR_BK0RDY;

		/* Handle supported standard device request */
		switch ((bRequest << 8) | bmRequestType) {
		case STD_GET_DESCRIPTOR:
			if (wValue == 0x100) {
				/* Return Device Descriptor */
				USB_Write(devDescriptor,
						MIN(sizeof(devDescriptor),
						wLength), CTRL_EP);
			} else if (wValue == 0x200) {
				/* Return Configuration Descriptor */
				USB_Write(cfgDescriptor,
						MIN(sizeof(cfgDescriptor),
						wLength), CTRL_EP);
			} else if (wValue == 0x300) {
				/*Return String Descriptor*/
				USB_Write(string_descriptor_lang_id,
						MIN(sizeof(
							string_descriptor_lang_id),
						wLength), CTRL_EP);
			} else if (wValue == 0x302) {
				/*Return String Descriptor*/
				USB_Write(string_descriptor_manufacture,
						MIN(sizeof(
							string_descriptor_manufacture),
						wLength), CTRL_EP);
			} else if (wValue == 0x303) {
				/*Return String Descriptor*/
				USB_Write(string_descriptor_serial_number,
						MIN(sizeof(
							string_descriptor_serial_number),
						wLength), CTRL_EP);
			} else {
				/* Stall the request */
				USB_Setup_Send_Stall(IN_BANK);
			}

			break;

		case STD_SET_ADDRESS:
			/* Send ZLP */
			USB_Setup_Send_ZLP();

			/* Set device address to the newly received address from
			 * host */
			USB->DEVICE.DADD.reg = USB_DEVICE_DADD_ADDEN | wValue;
			break;

		case STD_SET_CONFIGURATION:
			/* Store configuration */
			CurrentConfig = (uint8_t)wValue;
			/* Send ZLP */
			USB_Setup_Send_ZLP();
			/* Configure BULK OUT endpoint for MSC Data interface*/
			USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPCFG.reg
				= USB_DEVICE_EPCFG_EPTYPE0(3);
			/* Set maximum packet size as 64 bytes */
			usb_endpoint_table[MSC_BULK_OUT_EP].DeviceDescBank[
				OUT_BANK].PCKSIZE.bit.SIZE = 3;
			/* Configure the data buffer */
			usb_endpoint_table[MSC_BULK_OUT_EP].DeviceDescBank[
				OUT_BANK].ADDR.reg
				= (uint32_t)&msc_bulk_ep_out_buffer[0];

			/* Configure INTERRUPT IN endpoint for MSC Data
			 * interface */
			USB->DEVICE.DeviceEndpoint[MSC_BULK_IN_EP].EPCFG.reg
				|= USB_DEVICE_EPCFG_EPTYPE1(3);
			/* Set maximum packet size as 64 bytes 3*/
			usb_endpoint_table[MSC_BULK_IN_EP].DeviceDescBank[
				IN_BANK].PCKSIZE.bit.SIZE = 3;

			USB->DEVICE.DeviceEndpoint[MSC_BULK_IN_EP].EPSTATUSCLR.
			reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;
			/* Configure the data buffer */
			usb_endpoint_table[MSC_BULK_IN_EP].DeviceDescBank[
				IN_BANK].ADDR.reg
				= (uint32_t)&msc_bulk_ep_in_buffer[0];
			USB->DEVICE.INTENSET.reg = USB_DEVICE_INTENSET_SOF |
					USB_DEVICE_INTENSET_EORST;
			USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPINTENSET.reg = USB_DEVICE_EPINTENSET_TRCPT0;

			/*reset both Bulk IN and OUT data toggle bits*/
			USB->DEVICE.DeviceEndpoint[MSC_BULK_IN_EP].EPSTATUSCLR.
			reg = USB_DEVICE_EPSTATUSSET_DTGLIN;
			USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPSTATUSCLR.
			reg = USB_DEVICE_EPSTATUSSET_DTGLOUT;
			break;

		case STD_GET_CONFIGURATION:
			/* Return current configuration value */
			USB_Write((uint8_t *)&CurrentConfig,
					sizeof(CurrentConfig), CTRL_EP);
			break;

		case STD_GET_STATUS_ZERO:
			wStatus = 0;
			USB_Write((uint8_t *)&wStatus, sizeof(wStatus),
					CTRL_EP);
			break;

		case STD_GET_STATUS_INTERFACE:
			wStatus = 0;
			USB_Write((uint8_t *)&wStatus, sizeof(wStatus),
					CTRL_EP);
			break;

		case STD_GET_STATUS_ENDPOINT:
			wStatus = 0;
			dir = wIndex & 0x80;
			wIndex &= 0x0F;
			if (wIndex <= 3) {
				if (dir) {
					wStatus	= (USB->DEVICE.DeviceEndpoint[wIndex].EPSTATUS.reg
							   & USB_DEVICE_EPSTATUSSET_STALLRQ(2)) ? 1 : 0;
				} else {
					wStatus	= (USB->DEVICE.DeviceEndpoint[wIndex].EPSTATUS.reg
								& USB_DEVICE_EPSTATUSSET_STALLRQ(1)) ? 1 : 0;
				}

				/* Return current status of endpoint */
				USB_Write((uint8_t *)&wStatus, sizeof(wStatus),
						CTRL_EP);
			} else {
				/* Stall the request */
				USB_Setup_Send_Stall(IN_BANK);
			}

			break;

		case STD_SET_FEATURE_ZERO:
			/* Stall the request */
			USB_Setup_Send_Stall(IN_BANK);
			break;

		case STD_SET_FEATURE_INTERFACE:
			/* Send ZLP */
			USB_Setup_Send_ZLP();
			break;

		case STD_SET_FEATURE_ENDPOINT:
			dir = wIndex & 0x80;
			wIndex &= 0x0F;
			if ((wValue == 0) && wIndex && (wIndex <= 3)) {
				/* Set STALL request for the endpoint */
				if (dir) {
					USB->DEVICE.DeviceEndpoint[wIndex].
					EPSTATUSSET.reg
						= USB_DEVICE_EPSTATUSSET_STALLRQ(
							2);
				} else {
					USB->DEVICE.DeviceEndpoint[wIndex].
					EPSTATUSSET.reg
						= USB_DEVICE_EPSTATUSSET_STALLRQ(
							1);
				}

				/* Send ZLP */
				USB_Setup_Send_ZLP();
			} else {
				/* Stall the request */
				USB_Setup_Send_Stall(IN_BANK);
			}

			break;

		case STD_CLEAR_FEATURE_ZERO:
			/* Stall the request */
			USB_Setup_Send_Stall(IN_BANK);
			break;

		case STD_CLEAR_FEATURE_INTERFACE:
			/* Send ZLP */
			USB_Setup_Send_ZLP();
			break;

		case STD_CLEAR_FEATURE_ENDPOINT:
			dir = wIndex & 0x80;
			wIndex &= 0x0F;
			if ((wValue == 0) && wIndex && (wIndex <= 3)) {
				if (dir) {
					if (USB->DEVICE.DeviceEndpoint[wIndex].
							EPSTATUS.reg &
							USB_DEVICE_EPSTATUSSET_STALLRQ(
							2)) {
						/* Remove stall request */
						USB->DEVICE.DeviceEndpoint[
							wIndex].
						EPSTATUSCLR.reg
							=
								USB_DEVICE_EPSTATUSCLR_STALLRQ(
								2);
						if (USB->DEVICE.DeviceEndpoint[
									wIndex].
								EPINTFLAG.reg &
								USB_DEVICE_EPINTFLAG_STALL(
								2)) {
							USB->DEVICE.
							DeviceEndpoint
							[wIndex]
							.
							EPINTFLAG
							.reg
								=
									USB_DEVICE_EPINTFLAG_STALL(
									2);

							/* The Stall has
							* occurred, then reset
							* data toggle */
							USB->DEVICE.
							DeviceEndpoint
							[wIndex]
							.
							EPSTATUSCLR
							.reg
								=
									USB_DEVICE_EPSTATUSSET_DTGLIN;
						}
					}
				} else {
					if (USB->DEVICE.DeviceEndpoint[wIndex].
							EPSTATUS.reg &
							USB_DEVICE_EPSTATUSSET_STALLRQ(
							1)) {
						/* Remove stall request */
						USB->DEVICE.DeviceEndpoint[
							wIndex].
						EPSTATUSCLR.reg
							=
								USB_DEVICE_EPSTATUSCLR_STALLRQ(
								1);
						if (USB->DEVICE.DeviceEndpoint[
									wIndex].
								EPINTFLAG.reg &
								USB_DEVICE_EPINTFLAG_STALL(
								1)) {
							USB->DEVICE.
							DeviceEndpoint
							[wIndex]
							.
							EPINTFLAG
							.reg
								=
									USB_DEVICE_EPINTFLAG_STALL(
									1);

							/* The Stall has
							* occurred, then reset
							* data toggle */
							USB->DEVICE.
							DeviceEndpoint
							[wIndex]
							.
							EPSTATUSCLR
							.reg
								=
									USB_DEVICE_EPSTATUSSET_DTGLOUT;
						}
					}
				}

				/* Send ZLP */
				USB_Setup_Send_ZLP();
				/* Send CSW fail for unsupported SCSI command */
				if (csw_fail) {
					USB_Write((uint8_t *)&CSW_failed_unsupported_command,
							sizeof(CSW_failed_unsupported_command),
							MSC_BULK_IN_EP);
					csw_fail = 0;
					load_eject = 0;
				}
			} else {
				USB_Setup_Send_Stall(IN_BANK);
			}

			break;

		/*MSC class requests*/
		/*Get MaxLUN supported*/
		case GET_MAX_LUN:
			/*wIndex should be interface number*/
			if (wValue == 0 && wIndex == 0 && wLength == 1) {
				USB_Write(getmaxlun, sizeof(getmaxlun),
						CTRL_EP);
			} else {
				/* Stall the request */
				USB_Setup_Send_Stall(IN_BANK);
			}

			break;
		case MASS_STORAGE_RESET:
			/*wIndex should be interface number*/
			dir = wIndex & 0x80;
			if (wValue == 0 && wIndex == 0 && wLength == 0) {
				USB->DEVICE.DeviceEndpoint[MSC_BULK_IN_EP].
				EPSTATUSCLR.reg
					= USB_DEVICE_EPSTATUSSET_DTGLIN;
				USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].
				EPSTATUSCLR.reg
					= USB_DEVICE_EPSTATUSSET_DTGLOUT;
				USB_Setup_Send_ZLP();
			} else {
				/* Stall the request */
				USB_Setup_Send_Stall(IN_BANK);
			}

			break;

		default:
			/* Stall the request */
			USB_Setup_Send_Stall(IN_BANK);
			break;
		}
	}

	/* USB interrupt because of Transfer complete interrupt from bulk out
	 * endpoint */
	if ((USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPINTFLAG.vec.TRCPT & 1)) {
		/* Clear transfer complete flag*/
		USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT0;
		/* Clear BK0RDY bit otherwise incoming data will discard*/
		USB->DEVICE.DeviceEndpoint[MSC_BULK_OUT_EP].EPSTATUSCLR.reg
			= USB_DEVICE_EPSTATUSCLR_BK0RDY;
		/* Copy Command Block Signature to cbw.dCBWSignature*/
		memcpy_ram2ram(cbw.dCBWSignature, &msc_bulk_ep_out_buffer[0],
				4);
		/* Copy Command Block Wrapper Tag to cbw.dCBWTag*/
		memcpy_ram2ram(cbw.dCBWTag, &msc_bulk_ep_out_buffer[4], 4);
		/* Copy Data Transfer Length to cbw.dCBWDataTransferLength*/
		memcpy_ram2ram(cbw.dCBWDataTransferLength,
				&msc_bulk_ep_out_buffer[8], 4);

		/*		bmCBWFlags bit indicates whether the data is
		* from Host to device or from device or Host.
		* bit 7 : 0 -> Data Out from host to device,
		*          1 -> Data In from device to Host   */
		cbw.bmCBWFlags  = msc_bulk_ep_out_buffer[12];

		/*Copy LUN value to cbw.bCBWLUN*/
		cbw.bCBWLUN             = msc_bulk_ep_out_buffer[13];
		/* Copy BULK OUT data endpoint data to cbw.CBWCB*/
		memcpy_ram2ram(cbw.CBWCB, &msc_bulk_ep_out_buffer[15], 16);
		loej = msc_bulk_ep_out_buffer[19];

		/*Logical Block Address*/
		uint8_t lba[4];
		lba[3] = cbw.CBWCB[2];
		lba[2] = cbw.CBWCB[3];
		lba[1] = cbw.CBWCB[4];
		lba[0] = cbw.CBWCB[5];
		uint32_t logic_block_address =
			(lba[3]<<24) | (lba[2]<<16) | (lba[1]<<8) | lba[0];

		/*allocation length*/
		uint8_t allocation_len[2];
		allocation_len[1] = cbw.CBWCB[3];
		allocation_len[0] = cbw.CBWCB[4];
		uint16_t allocation_length =
			(allocation_len[1]<<8) | allocation_len[0];


		/*transfer length*/
		uint8_t tfl[2];
		tfl[1] = cbw.CBWCB[7];
		tfl[0] = cbw.CBWCB[8];

		/*The Transfer Length field specifies the number of contiguous
		 * logical blocks of data that are transferred.*/

		/*Transfer Length (in terms of 512 bytes). If Host send Transfer
		 * Length =1 & cbw.bmCBWFlags =1, Host expects 512 bytes of data
		 * from device */
		CBWCB_transfer_length = (tfl[1]<<8) | tfl[0];

		/*dCBW_Transger_Length = Number of bytes of data that Host
		 * expects to transfer on BULK IN/OUT endpoint*/
		uint32_t dCBW_Transfer_Length =
			(cbw.dCBWDataTransferLength[3]<<24) |
			(cbw.dCBWDataTransferLength[2]<<16) |
			(cbw.dCBWDataTransferLength[1]<<8) |
			(cbw.dCBWDataTransferLength[0]);

		/*Command Status Wrapper*/
		struct csw_signature CSW_data = {
			.dCSWSignature[0] = 0x55,
			.dCSWSignature[1] = 0x53,
			.dCSWSignature[2] = 0x42,
			.dCSWSignature[3] = 0x53,
			.dCSWTag[0] = cbw.dCBWTag[0],
			.dCSWTag[1] = cbw.dCBWTag[1],
			.dCSWTag[2] = cbw.dCBWTag[2],
			.dCSWTag[3] = cbw.dCBWTag[3],
			.dCSWDataResidue = {0x0,0x0,0x0,0x0},
			/* command passed */
			.bCSWStatus        = 0x00,
		};

		struct csw_signature CSW_failed = {
			.dCSWSignature[0] = 0x55,
			.dCSWSignature[1] = 0x53,
			.dCSWSignature[2] = 0x42,
			.dCSWSignature[3] = 0x53,
			.dCSWTag[0] = cbw.dCBWTag[0],
			.dCSWTag[1] = cbw.dCBWTag[1],
			.dCSWTag[2] = cbw.dCBWTag[2],
			.dCSWTag[3] = cbw.dCBWTag[3],
			.dCSWDataResidue = {0x0,0x0,0x0,0x0},
			 /* command failed */
			.bCSWStatus        = 0x01,
		};

		/*Check CBW signature whether the received CBW is valid */
		if (cbw.dCBWSignature[0] == 0x55 && cbw.dCBWSignature[1] ==
				0x53 && cbw.dCBWSignature[2] == 0x42 &&
				cbw.dCBWSignature[3] == 0x43) {
			struct sbc_read_capacity10_data capactiy_response;
			uint32_t capactiy = 0;
			uint8_t buffer[512];
			memset(buffer, 0, 512);
			switch (cbw.CBWCB[0]) {
			/*Inquiry command to obtain disk information*/
			case SBC_CMD_INQUIRY:

				/* Send inquiry data if the allocation length is
				 * 36 bytes otherwise stall the request*/
				if (allocation_length == 0x24) {
					USB_Write(msc_inquiry_data,
							sizeof(msc_inquiry_data),
							MSC_BULK_IN_EP);
					USB_Write((uint8_t *)&CSW_data,
							sizeof(CSW_data),
							MSC_BULK_IN_EP);
				} else {
					USB->DEVICE.DeviceEndpoint[
						MSC_BULK_IN_EP].
					EPSTATUSSET.reg
						= USB_DEVICE_EPSTATUSSET_STALLRQ(
							2);
					csw_fail = 1;
				}

				break;
			/*Get Capacity of the connected SD card*/
			case SBC_CMD_READ_CAPACITY_10:
				/*Check whether SD card is inserted in slot*/
				if (sd_mmc_check(slot) == SD_MMC_ERR_NO_CARD) {
					USB->DEVICE.DeviceEndpoint[
						MSC_BULK_IN_EP].
					EPSTATUSSET.reg
						= USB_DEVICE_EPSTATUSSET_STALLRQ(
							2);
					csw_fail = 1;
				}
				/*If SD card is inserted in slot, read the
				 * capacity of card, send it to Host*/
				else {
					capactiy = sd_mmc_get_capacity(0) *
							(1024 /
							SD_MMC_BLOCK_SIZE);
					capactiy_response.block_len
						= CPU_TO_BE32(
							UDI_MSC_BLOCK_SIZE);
					capactiy_response.max_lba = capactiy -
							1;
					capactiy_response.max_lba = cpu_to_be32(
							capactiy_response.max_lba);
					USB_Write((uint8_t *)&capactiy_response,
							sizeof(capactiy_response),
							MSC_BULK_IN_EP);
					USB_Write((uint8_t *)&CSW_data,
							sizeof(CSW_data),
							MSC_BULK_IN_EP);
				}

				break;
			/* Read USB data from SD card */
			case SBC_CMD_READ_10:

				/*Check whether the SD card is inserted in slot
				**/

				/*if dCBW_Transfer_Length= 0,no data transfer
				 * */

				/*if dCBW_Transfer_Length =1024 &
				 * CBWCB_transfer_length =1 means Host expects 1
				 * block(512 bytes) of data &
				 * dCBW_Transfer_Length =1024  which
				 * contradicts*/
				if ((sd_mmc_check(slot) == SD_MMC_ERR_NO_CARD) |
						(dCBW_Transfer_Length == 0x00) |
						(dCBW_Transfer_Length !=
						CBWCB_transfer_length *
						UDI_MSC_BLOCK_SIZE)) {
					USB->DEVICE.DeviceEndpoint[
						MSC_BULK_IN_EP].
					EPSTATUSSET.reg
						= USB_DEVICE_EPSTATUSSET_STALLRQ(
							2);
					csw_fail = 1;
				}
				/*When read command is triggered &
				 * cbw.bmCBWFlags=0, Host send data to device
				 * which is invalid. Get data from Host and
				 *stall
				 * the request*/
				else if (cbw.bmCBWFlags == 0x00) {
					for (int i = 0; i < 8; i++) {
						while (!(USB->DEVICE.
								DeviceEndpoint[
									MSC_BULK_OUT_EP
								]
								.EPSTATUS.reg & USB_DEVICE_EPSTATUS_BK0RDY)) {
						}
						for (int j = 0; j < 64; j++) {
							buffer[64 * i +
							j]
								=
									msc_bulk_ep_out_buffer
									[
								j];
							dCBW_Transfer_Length--;
						}
						USB->DEVICE.DeviceEndpoint[
							MSC_BULK_OUT_EP]
						.EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK0RDY;
					}
					USB_Write((uint8_t *)&CSW_failed,
							sizeof(CSW_failed),
							MSC_BULK_IN_EP);
				}
				/*Send data to Host*/
				else {
					if (SD_MMC_OK !=
							sd_mmc_init_read_blocks(
							slot,
							logic_block_address,
							CBWCB_transfer_length))
					{
						return;
					}

					for (uint16_t nb_trans
								= 0;
							nb_trans <
							CBWCB_transfer_length;
							nb_trans++) {
						if (SD_MMC_OK !=
								sd_mmc_start_read_blocks(
								buffer, 1)) {
							return;
						}

						if (SD_MMC_OK !=
								sd_mmc_wait_end_of_read_blocks(false))
						{
							return;
						}

						USB_Write(buffer,
								sizeof(buffer),
								MSC_BULK_IN_EP);
					}
					USB_Write((uint8_t *)&CSW_data,
							sizeof(CSW_data),
							MSC_BULK_IN_EP);
				}

				break;
			/* Test Unit Ready command is used to determine if a device is ready to transfer data */
			case SBC_CMD_TEST_UNIT_READY:         /* 0x00 -
				                               * Mandatory */

				/* if load_eject value is 2 (since Eject command
				 * is received from My Computer), fail Test Unit
				 * Ready */
				if ((load_eject ==
						2) |
						(sd_mmc_check(slot) ==
						SD_MMC_ERR_NO_CARD)) {
					USB_Write((uint8_t *)&CSW_failed,
							sizeof(CSW_failed),
							MSC_BULK_IN_EP);
				}
				/*dCBW_Transfer_Length!=0 is invalid for Test
				 * unit ready, Data transfer is not required for
				 * Test unit ready.
				 * receive data from Host and fail Test Unit
				 * ready command */
				else if (dCBW_Transfer_Length != 0x00) {
					for (int i = 0; i < 8; i++) {
						while (!(USB->DEVICE.
								DeviceEndpoint[
									MSC_BULK_OUT_EP
								]
								.EPSTATUS.reg & USB_DEVICE_EPSTATUS_BK0RDY)) {
						}
						for (int j = 0; j < 64; j++) {
							buffer[64 * i +
							j]
								=
									msc_bulk_ep_out_buffer
									[
								j];
							dCBW_Transfer_Length--;
						}
						USB->DEVICE.DeviceEndpoint[
							MSC_BULK_OUT_EP]
						.EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK0RDY;
					}
					USB_Write((uint8_t *)&CSW_failed,
							sizeof(CSW_failed),
							MSC_BULK_IN_EP);
				} else {
					USB_Write((uint8_t *)&CSW_data,
							sizeof(CSW_data),
							MSC_BULK_IN_EP);
				}

				break;
			/* Write a block of USB data to SD card */
			case SBC_CMD_WRITE_10:

				/*if write command is triggered and if the write
				 * direction is from device to
				 * Host(cbw.bmCBWFlags == 0x80), stall the
				 * request*/

				/*Data transfer is required for Write command.
				 * If dCBW_Transfer_Length ==0x00, the command
				 *is
				 * invalid. Stall the request*/
				if ((cbw.bmCBWFlags == 0x80) |
						(dCBW_Transfer_Length == 0x00)) {
					USB->DEVICE.DeviceEndpoint[
						MSC_BULK_IN_EP].
					EPSTATUSSET.reg
						= USB_DEVICE_EPSTATUSSET_STALLRQ(
							2);
					csw_fail = 1;
				}
				/*check whether the data transfer length is
				 * equal to CBWCB transfer length * block size*/
				else if (dCBW_Transfer_Length !=
						CBWCB_transfer_length *
						UDI_MSC_BLOCK_SIZE) {
					for (uint16_t nb_trans
								= 0;
							nb_trans <
							dCBW_Transfer_Length /
							512; nb_trans++) {
						for (int i = 0; i < 8; i++) {
							while (!(USB->DEVICE.
									DeviceEndpoint
									[
										MSC_BULK_OUT_EP
									].
									EPSTATUS.reg & USB_DEVICE_EPSTATUS_BK0RDY))
							{
							}
							for (int j = 0; j < 64;
									j++) {
								buffer[64 * i +
								j
								]
									=
										msc_bulk_ep_out_buffer
										[
									j
										];
							}
							USB->DEVICE.
							DeviceEndpoint
							[
								MSC_BULK_OUT_EP
							].
							EPSTATUSCLR
							.reg
								= USB_DEVICE_EPSTATUSCLR_BK0RDY;
						}
					}
					USB_Write((uint8_t *)&CSW_failed,
							sizeof(CSW_failed),
							MSC_BULK_IN_EP);
				}
				/* Receive data from Host and write it in SD
				 * card */
				else {
					if (SD_MMC_OK !=
							sd_mmc_init_write_blocks(
							slot,
							logic_block_address,
							CBWCB_transfer_length))
					{
						return;
					}

					usb_endpoint_table[MSC_BULK_OUT_EP].
					DeviceDescBank[OUT_BANK]
					.PCKSIZE.bit.
					MULTI_PACKET_SIZE = 0;
					for (uint16_t nb_trans
								= 0;
							nb_trans <
							CBWCB_transfer_length;
							nb_trans++) {
						for (int i = 0; i < 8; i++) {
							while (!(USB->DEVICE.
									DeviceEndpoint
									[
										MSC_BULK_OUT_EP
									].
									EPSTATUS.reg & USB_DEVICE_EPSTATUS_BK0RDY))
							{
							}
							for (int j = 0; j < 64;
									j++) {
								buffer[64 * i +
								j
								]
									=
										msc_bulk_ep_out_buffer
										[
									j
										];
							}
							USB->DEVICE.
							DeviceEndpoint
							[
								MSC_BULK_OUT_EP
							].
							EPSTATUSCLR
							.reg
								= USB_DEVICE_EPSTATUSCLR_BK0RDY;
						}

						if (SD_MMC_OK !=
								sd_mmc_start_write_blocks(
								buffer, 1)) {
							return;
						}

						if (SD_MMC_OK !=
								sd_mmc_wait_end_of_write_blocks(false))
						{
							return;
						}

						usb_endpoint_table[
							MSC_BULK_OUT_EP]
						.DeviceDescBank[
							OUT_BANK].
						PCKSIZE.bit.
						BYTE_COUNT = 0;
						memset(buffer, 0, 512);
					}
					USB_Write((uint8_t *)&CSW_data,
							sizeof(CSW_data),
							MSC_BULK_IN_EP);
				}

				break;

			case SBC_CMD_READ_12:
				/* Stall the request */
				USB->DEVICE.DeviceEndpoint[MSC_BULK_IN_EP].
				EPSTATUSSET.reg
					= USB_DEVICE_EPSTATUSSET_STALLRQ(
						2);
				csw_fail = 1;
				break;

			case SBC_CMD_WRITE_12:
				for (uint16_t nb_trans = 0;
						nb_trans <
						dCBW_Transfer_Length / 512;
						nb_trans++) {
					for (int i = 0; i < 8; i++) {
						while (!(USB->DEVICE.
								DeviceEndpoint[
									MSC_BULK_OUT_EP
								]
								.EPSTATUS.reg & USB_DEVICE_EPSTATUS_BK0RDY)) {
						}
						for (int j = 0; j < 64; j++) {
							buffer[64 * i +
							j]
								=
									msc_bulk_ep_out_buffer
									[
								j];
						}
						USB->DEVICE.DeviceEndpoint[
							MSC_BULK_OUT_EP]
						.EPSTATUSCLR.reg
						 = USB_DEVICE_EPSTATUSCLR_BK0RDY;
					}
					memset(buffer,0,512);
				}
				USB_Write((uint8_t *)&CSW_failed,
						sizeof(CSW_failed),
						MSC_BULK_IN_EP);
				break;

			case SBC_VERIFY10:
				/* Just send CSW signature */
				USB_Write((uint8_t *)&CSW_data,
						sizeof(CSW_data),
						MSC_BULK_IN_EP);
				break;

			/* request removable media to load/ unload its media*/
			case SBC_CMD_START_STOP_UNIT:

				/*loej value is 2 if the media is ejected from
				 * PC otherwise loej value will be 0*/
				load_eject = loej;
				USB_Write((uint8_t *)&CSW_data,
						sizeof(CSW_data),
						MSC_BULK_IN_EP);
				break;
			/* Allow Medium removal */
			case SBC_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL:
				USB_Write((uint8_t *)&CSW_data,
						sizeof(CSW_data),
						MSC_BULK_IN_EP);
				break;
			/* request sense data if CBW command failed */
			case SBC_CMD_REQUEST_SENSE:
				if ((load_eject == 2) | (sd_mmc_check(slot) ==
						SD_MMC_ERR_NO_CARD)) {
					/*No medium is present*/
					USB_Write(request_sense_medium_not_present,
							sizeof(request_sense_medium_not_present),
							MSC_BULK_IN_EP);
					USB_Write((uint8_t *)&CSW_data,
							sizeof(CSW_data),
							MSC_BULK_IN_EP);
				} else if (allocation_length == 0x12) {
					USB_Write(request_sense,
							sizeof(request_sense),
							MSC_BULK_IN_EP);
					USB_Write((uint8_t *)&CSW_data,
							sizeof(CSW_data),
							MSC_BULK_IN_EP);
				} else {
					USB->DEVICE.DeviceEndpoint[
						MSC_BULK_IN_EP].
					EPSTATUSSET.reg
						= USB_DEVICE_EPSTATUSSET_STALLRQ(
							2);
					csw_fail = 1;
				}

				break;
			default:
				/* Stall the request */
				USB->DEVICE.DeviceEndpoint[MSC_BULK_IN_EP].
				EPSTATUSSET.reg
					= USB_DEVICE_EPSTATUSSET_STALLRQ(
						2);
				csw_fail = 1;
				break;
			}
		} else {
		}
	}
}
