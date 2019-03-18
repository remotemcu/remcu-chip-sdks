/**
 * \file
 *
 * \brief maXTouch component.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
#include <twihs_master.h>
#include <ioport.h>

#include "mxt_device_1.h"

#define  OBJECT_TABLE_ELEMENT_SIZE  6
#define  OBJECT_TABLE_START_ADDRESS 7
#define  MXT_ID_BLOCK_SIZE          7
#define  MXT_MEM_ADDR               0x00
#define  MXT_FAMILY_143E            0x81
#define  MXT_VARIANT_143E           0x07

/**
 * \internal
 * \brief Total number of report ids available
 *        in the maXTouch device.
 *
 * \param *device Pointer to mxt_device instance
 * \return Total number of report ids
 */
static uint8_t mxt_get_tot_report_ids(struct mxt_device *device)
{
	uint8_t i;
	uint8_t tot_report_ids = 0;
	/* Figure out how many report id's to allocate memory for */
	for (i = 0; i < device->info_object->obj_count; ++i) {
		tot_report_ids += (device->object_list[i].num_report_ids);
	}

	return tot_report_ids;
}

/**
 * \internal
 * \brief Read out the id information from the maXTouch device and
 *        put it into the info_object struct in the device instance.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t mxt_read_id_block(struct mxt_device *device)
{
	device->info_object = (struct mxt_info_object *)
			malloc(sizeof(struct mxt_info_object));

	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = MXT_MEM_ADDR,
		.addr[1]      = MXT_MEM_ADDR >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = device->info_object,
		.length       = MXT_ID_BLOCK_SIZE
	};

	/* Read information from the slave */
	if (twihs_master_read(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return STATUS_OK;
	}
}

/**
 * \internal
 * \brief Read out the object table from the maXTouch device and
 *        put it into the object_list structs in the device instance.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t mxt_read_object_table(struct mxt_device *device)
{
	device->object_list = (struct mxt_object *)
			malloc(device->info_object->obj_count *
			sizeof(struct mxt_object));

	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = OBJECT_TABLE_START_ADDRESS,
		.addr[1]      = OBJECT_TABLE_START_ADDRESS >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = device->object_list,
		.length       = device->info_object->obj_count *
				sizeof(struct mxt_object)
	};

	/* Read information from the slave */
	if (twihs_master_read(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return STATUS_OK;
	}
}

/**
 * \internal
 * \brief Read info block from device
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t inline mxt_read_info_block(struct mxt_device *device)
{
	uint8_t status;

	if ((status = mxt_read_id_block(device)) != STATUS_OK) {
		return (status_code_t)status;
	}

	if ((status = mxt_read_object_table(device)) != STATUS_OK) {
		return (status_code_t)status;
	}

	return STATUS_OK;
}

/**
 * \internal
 * \brief Create report ID map from the object list in mxt_device
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
static status_code_t mxt_create_report_id_map(struct mxt_device *device)
{
	uint8_t i, j, k;
	uint8_t id_index = 1;
	uint8_t tot_report_ids = mxt_get_tot_report_ids(device);

	device->report_id_map = (struct mxt_report_id_map *)
			malloc(sizeof(struct mxt_report_id_map) *
			tot_report_ids);

	/* For every object */
	for (i = 0; i < device->info_object->obj_count; ++i) {
		/* For every instance of an object */
		for (j = 0; j <= device->object_list[i].instances; ++j) {
			/* Not all objects report messages */
			if (device->object_list[i].num_report_ids != 0) {
				/* Some object have more than one report_id */
				for (k = 0; k < device->object_list[i].num_report_ids; ++k) {
					device->report_id_map[id_index].object_type =
							device->object_list[i].type;
					device->report_id_map[id_index].instance = j;
					id_index++;
				} /* each report id */
			} /* if report id */
		} /* every instance */
	} /* every object */

	return STATUS_OK;
}

/**
 * \internal
 * \brief Calculates the next crc value of current crc value
 *        and the following two bytes.
 *
 * \param crc
 * \param byte1
 * \param byte2
 * \return crc
 */
static uint32_t inline mxt_crc_24(uint32_t crc, uint8_t byte1, uint8_t byte2)
{
	static const uint32_t crcpoly = 0x80001B;
	uint32_t result;
	uint16_t data_word;

	data_word = (uint16_t)((uint16_t)(byte2 << 8u) | byte1);
	result = ((crc << 1u) ^ (uint32_t)data_word);

	if (result & 0x1000000) {
		result ^= crcpoly;
	}

	return result;
}

/**
 * \internal
 * \brief Calculates the crc checksum of the data in the info block.
 *
 * \param *device Pointer to mxt_device instance
 * \param *crc    Pointer to the crc variable
 * \return Operation result status code
 */
static status_code_t mxt_calculate_infoblock_crc(struct mxt_device *device,
		uint32_t *crc)
{
	uint32_t crc_tmp = 0;
	uint16_t crc_area_size;
	uint16_t i;
	uint8_t *id_pointer = (uint8_t *)device->info_object;
	uint8_t *objects_pointer = (uint8_t *)device->object_list;

	/* Data to calculate crc value for */
	crc_area_size = MXT_ID_BLOCK_SIZE +
			(device->info_object->obj_count *
			OBJECT_TABLE_ELEMENT_SIZE);

	for (i = 0; i < MXT_ID_BLOCK_SIZE - 1; i += 2) {
		crc_tmp = mxt_crc_24(crc_tmp, id_pointer[i], id_pointer[i + 1]);
	}

	/* Calculate for the last byte (7th) byte in the info_id_t struct and */
	/* the first in the object table.*/
	crc_tmp = mxt_crc_24(crc_tmp, id_pointer[MXT_ID_BLOCK_SIZE - 1],
			objects_pointer[0]);

	for (i = 1; i < (crc_area_size - MXT_ID_BLOCK_SIZE - 1); i += 2) {
		crc_tmp = mxt_crc_24(crc_tmp, objects_pointer[i],
				objects_pointer[i + 1]);
	}

	crc_tmp = mxt_crc_24(crc_tmp,
			objects_pointer[crc_area_size - MXT_ID_BLOCK_SIZE - 1],
			0);

	/* Return only 24 bit CRC. */
	*crc = (crc_tmp & 0x00FFFFFF);
	return STATUS_OK;
}

/**
 * \internal
 * \brief Reads out the crc value stored in the mxt-device.
 *
 * \param *device Pointer to mxt_device instance
 * \return crc_value 24-bit value representing the crc.
 */
static uint32_t mxt_get_crc_value(struct mxt_device *device)
{
	uint8_t crc[3];
	uint16_t addr = MXT_ID_BLOCK_SIZE
		+ (OBJECT_TABLE_ELEMENT_SIZE * device->info_object->obj_count);

	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = addr,
		.addr[1]      = addr >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = crc,
		.length       = sizeof(crc)
	};

	/* Read information from the slave */
	if (twihs_master_read(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return ((uint32_t)crc[2] << 16) | ((uint16_t)crc[1] << 8) | crc[0];
	}
}

/**
 * \internal
 * \brief Validates the info block by comparing the calculated Compares the
 *        calculated and stored crc value.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code.
 */
static status_code_t mxt_validate_info_block(struct mxt_device *device)
{
	uint32_t crc_read;
	uint32_t crc_calculated;

	mxt_calculate_infoblock_crc(device, &crc_calculated);
	crc_read = mxt_get_crc_value(device);

	if (crc_calculated != crc_read) {
		return ERR_BAD_DATA;
	} else {
		return STATUS_OK;
	}
}

/**
 * \internal
 * \brief Returns the object size by using the object address
 *
 * \param *device Pointer to mxt_device instance
 * \param mem_adr Address of the object
 * \return uint8_t Size of the object
 */
static uint8_t mxt_get_object_size(struct mxt_device *device,
		mxt_memory_adr mem_adr)
{
	uint8_t i;

	for (i = 0; i < device->info_object->obj_count; ++i) {
		if (device->object_list[i].start_address == mem_adr) {
			return (device->object_list[i].size + 1);
		}
	}
	return 0;
}

/**
 * \internal
 * \brief Returns the report id offset for a object.
 *
 * \param *device Pointer to mxt_device instance
 * \param object_type ID of the object
 * \return int8_t Report ID offset
 */
static int8_t mxt_get_report_id_offset(struct mxt_device *device,
		enum mxt_object_type object_type)
{
	uint8_t i, tot_rpt_id = mxt_get_tot_report_ids(device);

	for (i = 0; i < tot_rpt_id; ++i) {
		if (device->report_id_map[i].object_type == object_type) {
			return i;
		}
	}

	return -1;
}

#if defined(CONF_VALIDATE_MESSAGES) || defined(__DOXYGEN__)
/**
 * \internal
 * \brief Calculates the next crc value of current crc value
 *        and the following byte.
 *
 * \param crc
 * \param data
 * \return crc
 */
static uint8_t inline mxt_crc_8(uint8_t crc, uint8_t data)
{
	static const uint8_t crcpoly = 0x8c;
	uint8_t index, fb;
	index = 8;

	do {
		fb = (crc ^ data) & 0x01;
		data >>= 1;
		crc >>= 1;
		if (fb) {
			crc ^= crcpoly;
		}
	} while (--index);

	return crc;
}

/**
 * \internal
 * \brief Validates the message received from the maXTouch device.
 *
 * \param packet  Message received from the maXTouch device
 * \return Operation result status code.
 */
static inline status_code_t mxt_validate_message(
		twihs_package_t *packet)
{
	uint8_t crc = 0;
	uint8_t i;

	for (i = 0; i < (MXT_TWI_MSG_SIZE_T5); ++i) {
		crc = mxt_crc_8(crc, ((uint8_t *)packet->buffer)[i]);
	}

	if (crc != 0) {
		return ERR_BAD_DATA;
	} else {
		return STATUS_OK;
	}
}
#endif

/**
 * \internal
 * \brief Do any potential endian conversions in info block.
 *
 * \param *device Pointer to mxt_device instance
 */
static void mxt_info_le_to_cpu(struct mxt_device *device)
{
	uint8_t i;

	for (i = 0; i < device->info_object->obj_count; ++i) {
		device->object_list[i].start_address =
			le16_to_cpu(device->object_list[i].start_address);
	}
}

/**
 * \brief Probe for a maXTouch connected to a specific TWI line
 *
 * \param interface Pointer to TWI register set
 * \param *chip_adr I2C address to maXTouch device
 * \return Operation result status code
 */
status_code_t mxt_probe_device(twihs_master_t interface, uint8_t chip_adr)
{
	struct mxt_info_object info;
	uint8_t status;

	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = MXT_MEM_ADDR,
		.addr[1]      = MXT_MEM_ADDR >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = chip_adr,
		.buffer       = &info,
		.length       = sizeof(info)
	};

	/* Read information from the slave */
	status = twihs_master_read(interface, &packet);
	if (status != TWIHS_SUCCESS) {
		return (status_code_t)status;
	}

	if ((info.family_ID != MXT_FAMILY_143E)
			|| (info.variant_ID != MXT_VARIANT_143E)) {
		return ERR_BAD_ADDRESS;
	}

	return STATUS_OK;
}

/**
 * \brief Initialize maXTouch device connected to TWIx module
 *
 * \param *interface Pointer to TWI register set
 * \param *device Pointer to mxt_device instance
 * \param chip_adr I2C address to maXTouch device
 * \param chgpin IOPORT pin instance attached to the maXTouch device's /CHG pin
 * \return Operation result status code
 */
status_code_t mxt_init_device(struct mxt_device *device,
		twihs_master_t interface, uint8_t chip_adr, uint32_t chgpin)
{
	int8_t status;

	/* Set TWI interface, TWI address and CHG-pin of the maXTouch device. */
	device->interface = interface;
	device->mxt_chip_adr = chip_adr;
	device->chgpin = chgpin;
	device->handler = NULL;

	/* Read the info block from the chip into the mxt_device struct */
	status = mxt_read_info_block(device);

	if (status != STATUS_OK) {
		return (status_code_t)status;
	}

	/* Validate the data read from the info block */
	status = mxt_validate_info_block(device);
	if (status != STATUS_OK) {
		return (status_code_t)status;
	}

	/* Fix possible endian issues between protocol and cpu */
	mxt_info_le_to_cpu(device);

	/* Create map of the report ID's and put it into mxt_device struct */
	status = mxt_create_report_id_map(device);
	if (status != STATUS_OK) {
		return (status_code_t)status;
	}

	/* Get the report id offset of the multi touch object*/
	status = mxt_get_report_id_offset(device,
			MXT_TOUCH_MULTITOUCHSCREEN_T9);
	if (status == -1) {
		return ERR_BAD_DATA;
	}

	device->multitouch_report_offset = status;

	return STATUS_OK;
}

/**
 * \brief Get memory address to object
 *
 * \param *device Pointer to mxt_device instance
 * \param object_id Object ID
 * \param instance Object instance
 * \return Object memory address on maXTouch device. 0 if object not found
 */
uint16_t mxt_get_object_address(struct mxt_device *device, uint8_t object_id,
		uint8_t instance)
{
	uint8_t i;

	for (i = 0; i < device->info_object->obj_count; i++) {
		if (object_id == device->object_list[i].type) {
			return device->object_list[i].start_address;
		}
	}

	return 0;
}

/**
 * \brief Read object configuration
 *
 * \param *device Pointer to mxt_device instance
 * \param memory_adr Memory address to the object
 * \param *obj_data Pointer to a large enough memory buffer
 * \return Operation result status code
 */
status_code_t mxt_read_config_object(struct mxt_device *device,
		mxt_memory_adr memory_adr, void *obj_data)
{
	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = memory_adr,
		.addr[1]      = memory_adr >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = obj_data,
		.length       = mxt_get_object_size(device, memory_adr)
	};

	if (twihs_master_read(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return STATUS_OK;
	}

}

/**
 * \brief Read object register
 *
 * \param *device Pointer to mxt_device instance
 * \param memory_adr Memory address to the register
 * \param *value Pointer to a 1 byte buffer to store the data in
 * \result Operation result status code
 */
status_code_t mxt_read_config_reg(struct mxt_device *device,
		mxt_memory_adr memory_adr, uint8_t *value)
{
	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = memory_adr,
		.addr[1]      = memory_adr >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = value,
		.length       = sizeof(uint8_t)
	};

	if (twihs_master_read(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return STATUS_OK;
	}
}

/**
 * \brief Write object configuration
 *
 * \param *device Pointer to mxt_device  instance
 * \param memory_adr Memory address to the object
 * \param *obj_data Pointer to memory buffer containing object data
 * \result Operation result status code
 */
status_code_t mxt_write_config_object(struct mxt_device *device,
		mxt_memory_adr memory_adr, void *obj_data)
{
	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = memory_adr,
		.addr[1]      = memory_adr >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = obj_data,
		.length       = mxt_get_object_size(device, memory_adr)
	};

	if (twihs_master_write(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return STATUS_OK;
	}

}

/**
 * \brief Write object register
 *
 * \param *device Pointer to mxt_device instance
 * \param memory_adr Memory address to register
 * \param value Value to be written to register
 * \result Operation result status code
 */
status_code_t mxt_write_config_reg(struct mxt_device *device,
		mxt_memory_adr memory_adr, uint8_t value)
{
	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = memory_adr,
		.addr[1]      = memory_adr >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = &value,
		.length       = sizeof(value)
	};

	if (twihs_master_write(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return STATUS_OK;
	}
}

/**
 * \brief Closes the twi connection and frees memory.
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
status_code_t mxt_close_device(struct mxt_device *device)
{
	/* Release all mallocs */
	free(device->info_object);
	free(device->object_list);
	free(device->report_id_map);

	return STATUS_OK;
}

/**
 * \brief Set message handler
 *
 * \param *device Pointer to mxt_device instance
 * \param handler Message handler function
 */
void mxt_set_message_handler(struct mxt_device *device,
		mxt_message_handler_t handler)
{
	device->handler = handler;
}

/**
 * \brief Report if there is any pending messages in the queue
 *
 * \param *device Pointer to mxt_device instance
 * \return Return /CHG pin status
 */
bool mxt_is_message_pending(struct mxt_device *device)
{
	if (ioport_get_pin_level(device->chgpin) == false) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Get pending message count
 *
 * \param *device Pointer to mxt_device instance
 * \return Number of pending messages in the queue
 */
int8_t mxt_get_message_count(struct mxt_device *device)
{
	uint8_t count_tmp = 0;
	uint16_t obj_adr = mxt_get_object_address(device,
			MXT_SPT_MESSAGECOUNT_T44, 0);

	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = obj_adr,
		.addr[1]      = obj_adr >> 8,
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = &count_tmp,
		.length       = sizeof(count_tmp)
	};

	/* Read information from the slave */
	if (twihs_master_read(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
		return count_tmp;
	}
}

/**
 * \brief Get next message in queue
 *
 * \param *device Pointer to mxt_device instance
 * \param *message Pointer to mxt_message instance
 * \return Operation result status code
 */
status_code_t mxt_read_message(struct mxt_device *device,
		struct mxt_conf_messageprocessor_t5 *message)
{
	uint16_t obj_adr = mxt_get_object_address(device,
			MXT_GEN_MESSAGEPROCESSOR_T5, 0);

	/* Initializing the TWI packet to send to the slave */
	twihs_package_t packet = {
		.addr[0]      = obj_adr,
#ifdef CONF_VALIDATE_MESSAGES
		.addr[1]      = (obj_adr >> 8) | 0x80,
#else
		.addr[1]      = obj_adr >> 8,
#endif
		.addr_length  = sizeof(mxt_memory_adr),
		.chip         = device->mxt_chip_adr,
		.buffer       = message,
		.length       = MXT_TWI_MSG_SIZE_T5
	};

	/* Read information from the slave */
	if (twihs_master_read(device->interface, &packet) != STATUS_OK) {
		return ERR_IO_ERROR;
	} else {
#ifdef CONF_VALIDATE_MESSAGES
		return mxt_validate_message(&packet);
#else
		return STATUS_OK;
#endif
	}
}

/**
 * \brief Read next touch event in queue, skip other events (other events are
 *        lost)
 *
 * \param *device Pointer to mxt_device instance
 * \param *touch_event Pointer to mxt_touch_event instance
 * \return Operation result status code
 */
status_code_t mxt_read_touch_event(struct mxt_device *device,
		struct mxt_touch_event *touch_event)
{
	uint8_t obj_type, status;
	struct mxt_conf_messageprocessor_t5 message;

	while (mxt_is_message_pending(device)) {
		if((status = mxt_read_message(device, &message)) != STATUS_OK) {
			return (status_code_t)status;
		}

		obj_type = mxt_get_object_type(device, &message);

		if (obj_type == MXT_TOUCH_MULTITOUCHSCREEN_T9) {
			touch_event->id = (message.reportid -
					device->multitouch_report_offset);

			touch_event->status = message.message[0];

			touch_event->x = (message.message[1] << 4) |
					((message.message[3] & 0xf0) >> 4);
			touch_event->y = (message.message[2] << 4) |
					(message.message[3] & 0x0f);

			touch_event->size = message.message[4];

			return STATUS_OK;
		}
	}

	return ERR_BAD_DATA;
}

/**
 * \brief Get object type from message
 *
 * \param *device Pointer to mxt_device instance
 * \param *message Message buffer
 * \return Operation
 */
enum mxt_object_type mxt_get_object_type(struct mxt_device *device,
		struct mxt_conf_messageprocessor_t5 *message)
{
	return (enum mxt_object_type)(device->report_id_map[message->reportid].object_type);
}

/**
 * \brief Process message queue on maXTouch device
 *
 * \param *device Pointer to mxt_device instance
 * \return Operation result status code
 */
status_code_t mxt_process_messages(struct mxt_device *device)
{
	struct mxt_conf_messageprocessor_t5 message;
	uint8_t status;

	mxt_message_handler_t mxt_message_handler;
	mxt_message_handler = (mxt_message_handler_t)device->handler;

	if (device->handler == NULL) {
		return ERR_BAD_ADDRESS;
	}

	while (mxt_is_message_pending(device)) {
		if ((status = mxt_read_message(device, &message)) != STATUS_OK) {
			return (status_code_t)status;
		} else {
			mxt_message_handler(device, &message);
		}
	}

	return STATUS_OK;
}
