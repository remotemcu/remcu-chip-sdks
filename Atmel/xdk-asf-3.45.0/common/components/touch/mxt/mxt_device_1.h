/**
 * \file
 *
 * \brief maXTouch component.
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

#ifndef MXT_DEVICE_H
#define MXT_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <status_codes.h>
#include <twihs_master.h>
#include "conf_mxt.h"


#define MXT_MAX_MSG_SIZE       7
#define MXT_TWI_MSG_SIZE_T5    MXT_MAX_MSG_SIZE + 2
#define MXT_RESET_TIME         65

typedef uint16_t mxt_memory_adr;

/**
 * \defgroup mxt_group maXTouch low-level component
 *
 * See \ref mxt_device_quickstart.
 *
 * This component provides low-level read/write access to the configuration and
 * data registers on a maXTouch device. It has only been tested on
 * mxt143E parts, but it should be easy to add support for other maXTouch
 * devices. This is a common API for all supported architectures in ASF.
 * 
 * The component is not interrupt driven and the maXTouch device has to be
 * polled to see if there are any pending messages, and the mxt_read_message
 * function reads out the messages pending. For reading out only touch events,
 * the mxt_read_touch_event function can be used. As mentioned the component is
 * not interrupt driven, but by configuring a pin change interrupt on the CHG
 * pin, the application can receive interrupts when there are messages pending.
 *
 * @{
 */

/** \brief Object types */
enum mxt_object_type {

	MXT_GEN_MESSAGEPROCESSOR_T5             = 5,
	MXT_GEN_COMMANDPROCESSOR_T6             = 6,
	MXT_GEN_POWERCONFIG_T7                  = 7,
	MXT_GEN_ACQUISITIONCONFIG_T8            = 8,
	MXT_TOUCH_MULTITOUCHSCREEN_T9           = 9,
	MXT_SPT_COMMSCONFIG_T18                 = 18,
	MXT_SPT_MESSAGECOUNT_T44                = 44,
	MXT_SPT_CTE_CONFIGURATION_T46           = 46,
	MXT_PROCG_TOUCHSUPPRESSION_T48          = 48,
	MXT_PROCI_SHIELDLESS_T56                = 56,
};

/**
 * \name COMMSCONFIG T18 object control register bit positions
 * @{
 */
#define MXT_COMMSCONFIG_T18_CHG_MODE_bp       2
#define MXT_COMMSCONFIG_T18_DISMNTR_bp        7
/** @} */

/* Align struct members to bytes for communication objects */
COMPILER_PACK_SET(1)

/** \brief Identification header */
struct mxt_info_object {
	uint8_t family_ID;      /**< Family ID     */
	uint8_t variant_ID;     /**< Variant ID    */
	uint8_t version;        /**< Version       */
	uint8_t build;          /**< Build         */
	uint8_t matrix_x_size;  /**< Matrix x size */
	uint8_t matrix_y_size;  /**< Matrix y size */
	uint8_t obj_count;      /**< Object count  */
};

/** \brief Object table entry */
struct mxt_object {
	uint8_t type;                 /**< Object type                    */
	mxt_memory_adr start_address; /**< Object start address           */
	uint8_t size;                 /**< Object size                    */
	uint8_t instances;            /**< Maximum object instances       */
	uint8_t num_report_ids;       /**< Number of report IDs pr object */
};

/** \brief Object message */
struct mxt_conf_messageprocessor_t5 {
	uint8_t reportid;                  /**< Report ID */
	uint8_t message[MXT_MAX_MSG_SIZE]; /**< Message   */
	uint8_t checksum;                  /**< Checksum  */
};

/**
 * \name COMMANDPROCESSOR T6 object register offset
 * @{
 */
#define MXT_GEN_COMMANDPROCESSOR_RESET        0
#define MXT_GEN_COMMANDPROCESSOR_BACKUPNV     1
#define MXT_GEN_COMMANDPROCESSOR_CALIBRATE    2
#define MXT_GEN_COMMANDPROCESSOR_REPORTALL    3
#define MXT_GEN_COMMANDPROCESSOR_DIAGNOSTIC   5
/** @} */

/** \brief Commandprocessor T6 object */
struct mxt_gen_commandprocessor_t6 {
	uint8_t reset;
	uint8_t backupnv;
	uint8_t calibrate;
	uint8_t reportall;
	uint8_t reserved_0x04;
	uint8_t diagnostic;
};

/**
 * \name Touch event types
 * @{
 */
#define MXT_UNGRIP_EVENT   1
#define MXT_SUPPRESS_EVENT 2
#define MXT_AMP_EVENT      4
#define MXT_VECTOR_EVENT   8
#define MXT_MOVE_EVENT     16
#define MXT_RELEASE_EVENT  32
#define MXT_PRESS_EVENT    64
#define MXT_DETECT_EVENT   128
/* @} */

/** \brief Touch event struct */
struct mxt_touch_event {
	uint8_t id;
	uint8_t status;
	uint16_t x;
	uint16_t y;
	uint8_t size;
	int8_t deltax;
	int8_t deltay;
};

/* Reset struct member alignment */
COMPILER_PACK_RESET()

/** \brief Map of the report ID vs object type and instance */
struct mxt_report_id_map {
	uint8_t object_type;
	uint8_t instance;
};

/**
 * \brief Forward declaration of the mxt_device struct to avoid warnings
 *         in the mxt_message_handler_t typedef
 */
struct mxt_device;

/**
 * \brief Message handler prototype
 *
 * \param *device Pointer to mxt_device struct
 * \param *message Pointer to mxt_message struct
 */
typedef void (*mxt_message_handler_t)(struct mxt_device *device,
		struct mxt_conf_messageprocessor_t5 *message);

/**
 * \brief maXTouch device information data container struct
 */

struct mxt_device {
	struct mxt_info_object *info_object;
	struct mxt_object *object_list;

	twihs_master_t interface;

	uint8_t mxt_chip_adr;
	mxt_message_handler_t handler;

	struct mxt_report_id_map *report_id_map;

	uint32_t chgpin;
	int8_t multitouch_report_offset;
};

status_code_t mxt_probe_device(twihs_master_t interface, uint8_t chip_adr);

status_code_t mxt_init_device(struct mxt_device *device,
		twihs_master_t interface, uint8_t chip_adr, uint32_t chgpin);

status_code_t mxt_load_configuration(struct mxt_device *device,
		void *configuration_data);

uint16_t mxt_get_object_address(struct mxt_device *device, uint8_t object_id,
		uint8_t instance);

status_code_t mxt_read_config_object(struct mxt_device *device,
		mxt_memory_adr memory_adr, void *obj_data);

status_code_t mxt_read_config_reg(struct mxt_device *device,
		mxt_memory_adr memory_adr, uint8_t *value);

status_code_t mxt_write_config_object(struct mxt_device *device,
		mxt_memory_adr memory_adr, void *obj_data);

status_code_t mxt_write_config_reg(struct mxt_device *device,
		mxt_memory_adr memory_adr, uint8_t value);

status_code_t mxt_close_device(struct mxt_device *device);

void mxt_set_message_handler(struct mxt_device *device,
		mxt_message_handler_t handler);

bool mxt_is_message_pending(struct mxt_device *device);

int8_t mxt_get_message_count(struct mxt_device *device);

status_code_t mxt_read_message(struct mxt_device *device,
		struct mxt_conf_messageprocessor_t5 *message);

status_code_t mxt_read_touch_event(struct mxt_device *device,
		struct mxt_touch_event *touch_event);

enum mxt_object_type mxt_get_object_type(struct mxt_device *device,
		struct mxt_conf_messageprocessor_t5 *message);

status_code_t mxt_process_messages(struct mxt_device *device);

/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page mxt_device_quickstart Quick start guide for the maXTouch component
 *
 * This is the quick start guide for the \ref mxt_group "maXTouch component"
 * The guide will give you a step-by-step introduction on how to setup and
 * use the component to be able to read touch responses from the maXTouch
 * Xplained Pro kit.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section mxt_device_use_case Basic use case
 * In this basic use case, the maXTouch component is configured for:
 * - Checking the defined CHG pin is indicating messages in the queue
 * - Reading touch events from the device
 *
 * Note: In this basic use case the application code will check for new events
 * by polling of the CHG pin. The application code can be modified into 
 * receiving interrupts on touch events by configuring a pin change interrupt
 * on the CHG pin.
 *
 * \section mxt_device_use_case_setup Setup steps
 *
 * \subsection mxt_device_use_case_setup_prereq Prerequisites
 * For the setup code of this use csse to work, the following is
 * needed:
 * -# An empty SAME70 Xplained board project.
 * -# A SAME70 Xplained kit.
 * -# A maXTouch Xplained Pro top module with pre-loaded configuration mounted on
 *    the SAME70 Xplained kit.
 *
 * \subsection mxt_device_use_case_setup_code Example code
 * Add to the initialization code:
 * \code
	    struct mxt_device device

	    if(mxt_probe_device(&TWIF, 0x4a) != STATUS_OK)
	      Assert(false);

	    if(mxt_init_device(&device, &TWIF, 0x4a, IOPORT_CREATE_PIN(PORTF, 2))
	        != STATUS_OK)
	      Assert(false);

	    mxt_write_config_reg(&device, mxt_get_object_address(&device,-
	        MXT_GEN_COMMANDPROCESSOR_T6, 0) + MXT_GEN_COMMANDPROCESSOR_RESET, 1);

	    delay_ms(MXT_RESET_TIME);

	    mxt_write_config_reg(&device, mxt_get_object_address(&device,
	        MXT_SPT_COMMSCONFIG_T18, 0),
	        MXT_COMMSCONFIG_T18_CHG_MODE_bp << 1);
\endcode
 *
 * \subsection mxt_device_use_case_setup_flow Workflow
 * -# define a variable of type struct mxt_device, a pointer to this struct must
 *    be available to every function using the maXTouch component API:
 *    - \code struct mxt_device device \endcode
 * -# call the maXTouch component probe function to check if there is any maXTouch
 *    device on the defined bus and address:
 *   - \code mxt_probe_device(TWIF, 0x4a); \endcode
 * -# call the maXTouch component init function to initialize the component. On the
 *    XMEGA-A1 Xplained you have use the TWIF module for data communication and
 *    pin 2 on port F as CHG pin interface:
 *   - \code mxt_init_device(&device, &TWIF, 0x4a, IOPORT_CREATE_PIN(PORTF,
	     2)); \endcode
 * -# then we have to do a softreset of the maXTouch device to get it into a
 *    known state:
 *   -  \code mxt_write_config_reg(&device, mxt_get_object_address(&device,-
	MXT_GEN_COMMANDPROCESSOR_T6, 0) + MXT_GEN_COMMANDPROCESSOR_RESET, 1);
\endcode
 * -# We have to wait for the reset to complete:
 *   - \code delay_ms(MXT_RESET_TIME); \endcode
 * -# The last ting we have to do before the device is ready for use is to set
 *    the CHG pin modus to 1. Which means that the pin will stay low until the
 *    message queue is empty instead of strobing each time a new message is
 *    received. To achieve that we write 1 to the CHG_MODE bit position in the
 *    T18 objects control register:
 *   - \code
	mxt_write_config_reg(&device, mxt_get_object_address(&device,
	    MXT_SPT_COMMSCONFIG_T18, 0),
	    MXT_COMMSCONFIG_T18_CHG_MODE_bp << 1);
\endcode
 *
 * \subsection mxt_device_use_case_example_code Example code
 * \code
	 // Add to application:

	 #define LED_PORT  PORTE

	 int function read_touch(struct mxt_device &device,
	     struct mxt_touch_event *touch_event)
	 {
	   if(mxt_is_message_pending(device)
	     return mxt_read_touch_event(device, touch_event);

	   return ERR_TIMEOUT;
	 }
\endcode
 *
 * \subsection mxt_device_use_case_example_code_flow Workflow
 * -# check if there is any messages waiting in the queue:
 *   - \code mxt_is_message_pending(device) \endcode
 * -# if there is any messages pending, check if any of these messages is
 *    a touch event and store it in the touch_event variable. Return with
 *    the return value from the mxt_read_touch_event function:
 *   - \code mxt_read_touch_event(device, touch_event); \endcode
 * -# if no pending message was found, return with ERR_TIMEOUT code:
 *   - \code return ERR_TIMEOUT; \endcode
 */
 
#endif /*MXT_DEVICE_H*/
