/**
 * \file
 *
 * \brief Sample of IEE11073 Communication Model
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

#include "asf.h"
#include "ieee11073_skeleton.h"

/* ! @defgroup IEEE11073_COM_MODEL_PHDC Structure used by Communication Model
 * to connect a USB PHDC Device
 * @{
 */
#define  IEEE11073_LGT_OPAQUEDATA_IN   10
#define  IEEE11073_LGT_OPAQUEDATA_OUT  10
#define  IEEE11073_LGT_METADATA_IN     80
#define  IEEE11073_LGT_METADATA_OUT    80
udi_phdc_metadata_t ieee11073_g_phdc_metadata_in;
udi_phdc_metadata_t ieee11073_g_phdc_metadata_out;
uint8_t ieee11073_g_opaquedata_in[IEEE11073_LGT_OPAQUEDATA_IN];
uint8_t ieee11073_g_opaquedata_out[IEEE11073_LGT_OPAQUEDATA_OUT];
uint8_t ieee11073_g_metadata_in[IEEE11073_LGT_METADATA_IN];
uint8_t ieee11073_g_metadata_out[IEEE11073_LGT_METADATA_OUT];
/* ! @} */

/* ! @defgroup IEEE11073_ASSOC_STATE Communication model association states
 * @{
 */
#define  IEEE11073_ASSOC_ABORT      0
#define  IEEE11073_ASSOC_RUNNING    1
#define  IEEE11073_ASSOC_VALIDED    2
static uint8_t udi_phdc_assoc_state;
/* ! @} */

/* ! @defgroup PHD_DATA Array with IEEE11073 data
 * @{
 */
/* ! Association Data Request */
uint8_t phd_assoc_req[] = {
	0xE2, 0x00,
	0x00, 0x32,
	0x80, 0x00, 0x00, 0x00,
	0x00, 0x01,
	0x00, 0x2A,
	0x50, 0x79,
	0x00, 0x26,
	0x80, 0x00, 0x00, 0x00,
	0x80, 0x00,
	0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00,
	0x00, 0x08,
	0x4C, 0x4E, 0x49, 0x41, 0x47, 0x45, 0x4E, 0x54,
	0x40, 0x00,
	0x00, 0x01, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00
};

/* ! Sample of measure */
uint8_t phd_measure[] = {
	0xE7, 0x00, 0x00, 0x5A, 0x00, 0x58, 0x12, 0x36, 0x01, 0x01, 0x00, 0x52,
	0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0D, 0x1D, 0x00, 0x48, 0xF0, 0x00, 0x00, 0x00,
	0x00, 0x04,
	0x00, 0x40, 0x00, 0x01, 0x00, 0x0C, 0xFF, 0x00, 0x02, 0xFA, 0x20, 0x07,
	0x12, 0x06,
	0x12, 0x10, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0C, 0xFF, 0x00, 0x00, 0xF3,
	0x20, 0x09, 0x06, 0x12,
	0x12, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0C, 0xFF, 0x00, 0x02, 0xF8,
	0x20, 0x09, 0x06, 0x12,
	0x20, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0C, 0xFF, 0x00, 0x00, 0xF2,
	0x20, 0x09, 0x06, 0x12,
	0x20, 0x05, 0x00, 0x00
};

/* ! Device Attributes */
uint8_t phd_attr[] = {
	0xE7, 0x00, 0x00, 0x6E, 0x00, 0x6C, 0x00, 0x02, 0x02, 0x03, 0x00, 0x66,
	0x00, 0x00, 0x00, 0x06,
	0x00, 0x60, 0x0A, 0x5A, 0x00, 0x08, 0x00, 0x01, 0x00, 0x04, 0x10, 0x0F,
	0x00, 0x01, 0x09, 0x28,
	0x00, 0x1A, 0x00, 0x0A, 0x46, 0x72, 0x65, 0x65, 0x73, 0x63, 0x61, 0x6C,
	0x65, 0x20, 0x00, 0x0C, 0x4D, 0x65,
	0x64, 0x69, 0x63, 0x61, 0x6C, 0x20, 0x43, 0x46, 0x56, 0x31, 0x09, 0x84,
	0x00, 0x0A,
	0x00, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x0a, 0x44,
	0x00, 0x02, 0x40, 0x00,
	0x09, 0x2D, 0x00, 0x12, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x08, 0x44, 0x45,
	0x31, 0x32, 0x34, 0x35, 0x36, 0x37, 0x09, 0x87, 0x00, 0x08, 0x20, 0x09,
	0x06, 0x12,
	0x12, 0x05, 0x00, 0x00
};

/* ! @} */

/* ! Internal routines */
static bool ieee11073_enable_reception(void);
static bool ieee11073_decode_metadata(void);
static bool ieee11073_send_association(void);
static bool ieee11073_send_mesure(uint8_t qos);
void ieee11073_received(bool status, uint16_t nb_received);
void ieee11073_sent(uint16_t nb_send);

/*! \brief Enable the communication model processing
 *
 * \retval true
 */
bool ieee11073_skeleton_enable(void)
{
	if (!ieee11073_enable_reception()) {
		return false;
	}

	return ieee11073_send_association();
}

/*! \brief Disable the communication model processing
 */
void ieee11073_skeleton_disable(void)
{
}

/*! \brief Send a measure on communication line
 */
void ieee11073_skeleton_send_measure_1(void)
{
	ieee11073_send_mesure(USB_PHDC_QOS_LOW_GOOD);
}

/*! \brief Send a measure on communication line
 */
void ieee11073_skeleton_send_measure_2(void)
{
	ieee11073_send_mesure(USB_PHDC_QOS_MEDIUM_BETTER);
}

/*! \brief Callback called when a data is received
 *
 * \param nb_received  Number of data received
 */
void ieee11073_received(bool status, uint16_t nb_received)
{
	if (!status) {
		return; /* Error or abort */
	}

	ieee11073_g_phdc_metadata_out.metadata_size = nb_received;
	ieee11073_decode_metadata();
	ieee11073_enable_reception();
}

/*! \brief Callback called when a data is sent
 *
 * \param nb_send  Number of data sent
 */
void ieee11073_sent(uint16_t nb_send)
{
	if (0 == nb_send) {
		if (udi_phdc_assoc_state == IEEE11073_ASSOC_RUNNING) {
			udi_phdc_assoc_state = IEEE11073_ASSOC_ABORT;
		}

		return;
	}
}

/*! \brief Function to process communication model
 * Must be scheduled by other process
 */
bool ieee11073_skeleton_process(void)
{
	return (udi_phdc_assoc_state == IEEE11073_ASSOC_VALIDED);
}

/*! \brief Start the reception of data on communication line
 *
 * \retval true   Reception started
 * \retval false  Impossible to start reception
 */
static bool ieee11073_enable_reception(void)
{
	ieee11073_g_phdc_metadata_out.opaquedata = ieee11073_g_opaquedata_out;
	ieee11073_g_phdc_metadata_out.opaque_size =
			IEEE11073_LGT_OPAQUEDATA_OUT;
	ieee11073_g_phdc_metadata_out.metadata = ieee11073_g_metadata_out;
	ieee11073_g_phdc_metadata_out.metadata_size =
			IEEE11073_LGT_METADATA_OUT;
	if (!udi_phdc_waitdata(&ieee11073_g_phdc_metadata_out,
			ieee11073_received)) {
		return false;
	}

	return true;
}

/*! \brief Start the data  reception on communication line
 *
 * \retval true   Metadata correct
 * \retval false  Metadata unknown
 */
static bool ieee11073_decode_metadata(void)
{
	uint16_t invoke_id;
	uint16_t choice;
	typedef struct {
		uint16_t choice;
		uint16_t length;
		uint8_t values[1];
	} Phd_t;

	Phd_t *phd = (Phd_t *)ieee11073_g_phdc_metadata_out.metadata;

	if (0 == ieee11073_g_phdc_metadata_out.metadata_size) {
		return false; /* Error reception */
	}

	if (ieee11073_g_phdc_metadata_out.metadata_size !=
			(4 + be16_to_cpu(phd->length))) {
		return false; /* Error on length */
	}

	switch (be16_to_cpu(phd->choice)) {
	case 0xE300:
		if (0 == be16_to_cpu(*((uint16_t *)&phd->values[0]))) {
			if (udi_phdc_assoc_state == IEEE11073_ASSOC_RUNNING) {
				udi_phdc_assoc_state = IEEE11073_ASSOC_VALIDED;
			}

			return true;
		}

		break;

	case 0xE600:
		if (0 == be16_to_cpu(*((uint16_t *)&phd->values[0]))) {
			if (udi_phdc_assoc_state == IEEE11073_ASSOC_RUNNING) {
				udi_phdc_assoc_state = IEEE11073_ASSOC_ABORT;
			}

			return true;
		}

		break;

	case 0xE700:
		if (ieee11073_g_phdc_metadata_out.metadata_size !=
				(6 + be16_to_cpu(*((uint16_t *)&phd->values[0])))) {
			return false; /* Error on length */
		}

		invoke_id = *((uint16_t *)&phd->values[2]);
		choice = *((uint16_t *)&phd->values[4]);

		if (be16_to_cpu(choice) == 0x0103) {
			invoke_id = be16_to_cpu(invoke_id);
			phd_attr[6] = (uint8_t)(invoke_id >> 8);
			phd_attr[7] = (uint8_t)(invoke_id & 0xFF);
			ieee11073_g_phdc_metadata_in.qos
					= USB_PHDC_QOS_MEDIUM_BEST;
			ieee11073_g_phdc_metadata_in.opaque_size = 0;
			ieee11073_g_phdc_metadata_in.metadata
					= phd_attr;
			ieee11073_g_phdc_metadata_in.metadata_size
					= sizeof(phd_attr);
			if (!udi_phdc_senddata(&ieee11073_g_phdc_metadata_in,
					ieee11073_sent)) {
				break;
			}
			return true;
		}
		break;
	}
	return false;
}

static bool ieee11073_send_association(void)
{
	ieee11073_g_phdc_metadata_in.qos = USB_PHDC_QOS_MEDIUM_BEST;
	ieee11073_g_phdc_metadata_in.opaque_size = 0;
	ieee11073_g_phdc_metadata_in.metadata = phd_assoc_req;
	ieee11073_g_phdc_metadata_in.metadata_size = sizeof(phd_assoc_req);
	if (!udi_phdc_senddata(&ieee11073_g_phdc_metadata_in, ieee11073_sent)) {
		return false;
	}

	udi_phdc_assoc_state = IEEE11073_ASSOC_RUNNING;
	return true;
}

static bool ieee11073_send_mesure(uint8_t qos)
{
	if (udi_phdc_assoc_state != IEEE11073_ASSOC_VALIDED) {
		return false;
	}

	ieee11073_g_phdc_metadata_in.opaque_size = 0;
	ieee11073_g_phdc_metadata_in.metadata = phd_measure;
	ieee11073_g_phdc_metadata_in.metadata_size = sizeof(phd_measure);
	ieee11073_g_phdc_metadata_in.qos = qos;
	return udi_phdc_senddata( &ieee11073_g_phdc_metadata_in,
			ieee11073_sent);
}
