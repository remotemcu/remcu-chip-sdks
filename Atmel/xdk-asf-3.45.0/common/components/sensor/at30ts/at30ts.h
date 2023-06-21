/**
 * \file
 *
 * \brief Management of the AT30TS Temperature Sensor component.
 *
 * This file contains definitions and services related to the features of the
 * AT30TS Temperature Sensor.
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

#ifndef AT30TS_H_
#define AT30TS_H_

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \defgroup sensor_at30ts_group AT30TS Temperature Sensor Library
 * This module contains different routines that can be 
 * used for interfacing AT30TS series of 
 * Digital Temperature Sensors. These devices are interfaced via
 * an I2C/SMBus compatible interface. 
 * @{
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * \ref twi_group for interfacing with a TWI Master.
 * \section apiinfo APIs for interfacing AT30TSxx Temperature Sensor
 * AT30TSxx Temperature Sensor API can be found 
 * \ref sensor_at30ts_api_group "here"
 *
 * @{
 */

#include "compiler.h"
#include "string.h"
#include "twi_master.h"
#include "conf_at30ts.h"

/* Error codes */
#define AT30TS_SUCCESS                  (0)
#define AT30TS_GENERAL_ERROR            (-1)
#define AT30TS_TWI_WRITE_NACK           (-2)
#define AT30TS_TWI_READ_NACK            (-3)
#define AT30TS_REG_LOCKED               (-4)
#define AT30TS_INVALID_EEPROM_ADDRESS   (-5)
#define AT30TS_INVALID_SIZE             (-6)
#define AT30TS_OUT_OF_BOUNDS            (-7)
#define AT30TS_NVRBSY_BUSY              (-8)

/**
 * \brief Configuration Reg Options for the for AT30TSE002B device
 */
enum config_options_002b{
        AT30TS_002B_CONF_OPT_MODE_CMP                = 0, /* !< */
	AT30TS_002B_CONF_OPT_MODE_INT                = 1, /* !< */
	AT30TS_002B_CONF_OPT_POL_LOW                 = 0, /* !< */
	AT30TS_002B_CONF_OPT_POL_HIGH                = 1, /* !< */
	AT30TS_002B_CONF_OPT_CRIT_ALL_ALM            = 0, /* !< */
	AT30TS_002B_CONF_OPT_CRIT_ALM_ONLY           = 1, /* !< */
	AT30TS_002B_CONF_OPT_EVTOUT_DIS              = 0, /* !< */
	AT30TS_002B_CONF_OPT_EVTOUT_EN               = 1, /* !< */
	AT30TS_002B_CONF_OPT_EVTSTS_DIS              = 0, /* !< */
	AT30TS_002B_CONF_OPT_EVTSTS_EN               = 1, /* !< */
	AT30TS_002B_CONF_OPT_EVTCLR_DIS              = 0, /* !< */
	AT30TS_002B_CONF_OPT_EVTCLR_EN               = 1, /* !< */
	AT30TS_002B_CONF_OPT_WINLOCK_DIS             = 0, /* !< */
	AT30TS_002B_CONF_OPT_WINLOCK_EN              = 1, /* !< */
	AT30TS_002B_CONF_OPT_CRTALML_DIS             = 0, /* !< */
	AT30TS_002B_CONF_OPT_CRTALML_EN              = 0, /* !< */
	AT30TS_002B_CONF_OPT_SHTDWN_EN               = 0, /* !< */
	AT30TS_002B_CONF_OPT_SHTDWN_DIS              = 1, /* !< */
	AT30TS_002B_CONF_OPT_HYSTENB_00C             = 0, /* !< */
	AT30TS_002B_CONF_OPT_HYSTENB_15C             = 1, /* !< */
	AT30TS_002B_CONF_OPT_HYSTENB_30C             = 2, /* !< */
	AT30TS_002B_CONF_OPT_HYSTENB_60C             = 3, /* !< */
};
typedef enum config_options_002b config_options_002b_t;

/**
 * \brief Configuration Reg Bits for the AT30TSE002B device
 */
enum opt_flag_002b{
	AT30TS_002B_CONFBIT_EVTMOD,
	AT30TS_002B_CONFBIT_EVTPOL,
	AT30TS_002B_CONFBIT_CRITEVT,
	AT30TS_002B_CONFBIT_EVTOUT,
	AT30TS_002B_CONFBIT_EVTSTS,
	AT30TS_002B_CONFBIT_EVTCLR,
	AT30TS_002B_CONFBIT_WINLOCK,
	AT30TS_002B_CONFBIT_CRTALML,
	AT30TS_002B_CONFBIT_SHTDWN,
	AT30TS_002B_CONFBIT_HYSTENB
};
typedef enum opt_flag_002b opt_flag_002b_t;

/**
 * \brief Configuration Reg Options for the AT30TS7x/TSE7x
 */
enum  config_options{
	AT30TS7_SD_DISABLE              = 0, /* !< */
	AT30TS7_SD_ENABLE               = 1, /* !< */
	AT30TS7_CMP                     = 0, /* !< */
	AT30TS7_INT                     = 1, /* !< */
	AT30TS7_POL_ACTIVE_LOW          = 0, /* !< */
	AT30TS7_POL_ACTIVE_HIGH         = 1, /* !< */
	AT30TS7_FAULT1                  = 0, /* !< */
	AT30TS7_FAULT2                  = 1, /* !< */
	AT30TS7_FAULT4                  = 2, /* !< */
	AT30TS7_FAULT6                  = 3, /* !< */
	AT30TS7_RES09                   = 0, /* !< */
	AT30TS7_RES10                   = 1, /* !< */
	AT30TS7_RES11                   = 2, /* !< */
	AT30TS7_RES12                   = 3, /* !< */
	AT30TS7_OS_DISABLE              = 0, /* !< */
	AT30TS7_OS_ENABLE               = 1 /* !< */
};
typedef enum config_options config_options_t;

/**
 * \brief Nonvolatile Configuration Reg Options
 */
enum nvconfig_options{
	AT30TS7_RLCK_UNLOCK             = 0, /* !< */
	AT30TS7_RLCK_LOCK               = 1, /* !< */
	AT30TS7_RLCKDWN_UNLOCK          = 0, /* !< */
	AT30TS7_RLCKDWN_LOCK            = 1, /* !< */
	AT30TS7_NVSD_DISABLE            = 0, /* !< */
	AT30TS7_NVSD_ENABLE             = 1, /* !< */
	AT30TS7_NVCMP                   = 0, /* !< */
	AT30TS7_NVINT                   = 1, /* !< */
	AT30TS7_NVPOL_ACTIVE_LOW        = 0, /* !< */
	AT30TS7_NVPOL_ACTIVE_HIGH       = 1, /* !< */
	AT30TS7_NVFAULT1                = 0, /* !< */
	AT30TS7_NVFAULT2                = 1, /* !< */
	AT30TS7_NVFAULT4                = 2, /* !< */
	AT30TS7_NVFAULT6                = 3, /* !< */
	AT30TS7_NVRES09                 = 0, /* !< */
	AT30TS7_NVRES10                 = 1, /* !< */
	AT30TS7_NVRES11                 = 2, /* !< */
	AT30TS7_NVRES12                 = 3 /* !< */
};
typedef enum nvconfig_options nvconfig_options_t;

/**
 * \brief Configuration Options
 */
enum opt_flag{
	AT30TS_RES,
	AT30TS_FAULT,
	AT30TS_POL,
	AT30TS_CMP_INT_MODE,
	AT30TS_SD,
	AT30TS_OS,
	AT30TS_RLCK,
	AT30TS_RLCKDWN
};
typedef enum opt_flag opt_flag_t;

/**
 * \brief AT30TS Family device types
 */
enum device_type{
	AT30TSE002B,
	AT30TS75,
	AT30TS750,
	AT30TSE752,
	AT30TSE754,
	AT30TSE758
};
typedef enum device_type device_type_t;

/**
 * \brief Qualifier for the temperature reading
 */
typedef enum {
	pos,
	neg,
	cel,
	farh,
	raw
} data_types;

/**
 * \brief Register types in AT30TS device
 */
typedef enum {
	vol,
	nonvol
} reg_type;

/* ! \brief Information about a AT30TS device */
#if defined(__GNUC__)
typedef struct _sensor_data {
	/* Volatile configuration register */
	/* ! \brief volatile configuration register */
	union {
		uint16_t value;
		struct {
#ifdef  _BIG_ENDIAN_    /* AVR32 mcu Big Endian */
			uint8_t OS       : 1; /* !< OS */
			uint8_t RES      : 2; /* !< Conversion Resolution */
			uint8_t FAULT    : 2; /* !< Fault Tolerance Queue */
			uint8_t POL      : 1; /* !< ALERT Pin Polarity */
			uint8_t CMP_INT  : 1; /* !< Alarm Thermostat Mode */
			uint8_t SD       : 1; /* !< Shutdown Mode */
			uint8_t RFU      : 7; /* !< RFU */
			uint8_t NVRBSY   : 1; /* !< Nonvolatile Registers
			                       *Busy */

#else                    /* AVR8 mcu Little Endian */
			uint8_t NVRBSY   : 1; /* !< Nonvolatile Registers
			                       *Busy */
			uint8_t RFU      : 7; /* !< RFU */
			uint8_t SD       : 1; /* !< Shutdown Mode */
			uint8_t CMP_INT  : 1; /* !< Alarm Thermostat Mode */
			uint8_t POL      : 1; /* !< ALERT Pin Polarity */
			uint8_t FAULT    : 2; /* !< Fault Tolerance Queue */
			uint8_t RES      : 2; /* !< Conversion Resolution */
			uint8_t OS       : 1; /* !< OS */
#endif
		} option;
	} config_reg;

	/* Volatile configuration register */
	/* ! \brief volatile configuration register */
	union {
		uint16_t value;
		struct {
#ifdef  _BIG_ENDIAN_    /* AVR32 mcu Big Endian */
			uint8_t RFU        : 5; /* !< RFU (Reserved for future
			                         *Use) */
			uint8_t HYSTENB    : 2; /* !< Hysteresis Enable */
			uint8_t SHTDWN     : 1; /* !< Shutdown Mode */
			uint8_t CRTALML    : 1; /* !< Crit_Alarm Trip Lock bit
			                        **/
			uint8_t WINLOCK    : 1; /* !< Alarm Window Lock bit */
			uint8_t EVTCLR     : 1; /* !< EVENT Clear(active low) */
			uint8_t EVTSTS     : 1; /* !< Pin Output Status (active
			                         *low) */
			uint8_t EVTOUT     : 1; /* !< Output Control */
			uint8_t CRITEVT    : 1; /* !< Critical Temperature only
			                        **/
			uint8_t EVTPOL     : 1; /* !< Polarity */
			uint8_t EVTMOD     : 1; /* !< Mode */

#else                           /* AVR8 mcu Little Endian */
			uint8_t EVTMOD     : 1; /* !< Mode */
			uint8_t EVTPOL     : 1; /* !< Polarity */
			uint8_t CRITEVT    : 1; /* !< Critical Temperature only
			                        **/
			uint8_t EVTOUT     : 1; /* !< Output Control */
			uint8_t EVTSTS     : 1; /* !< Pin Output Status (active
			                         *low) */
			uint8_t EVTCLR     : 1; /* !< EVENT Clear(active low) */
			uint8_t WINLOCK    : 1; /* !< Alarm Window Lock bit */
			uint8_t CRTALML    : 1; /* !< Crit_Alarm Trip Lock bit
			                        **/
			uint8_t SHTDWN     : 1; /* !< Shutdown Mode */
			uint8_t HYSTENB    : 2; /* !< Hysteresis Enable */
			uint8_t RFU                : 5; /* !< RFU (Reserved for
			                                 * Future Use) */
#endif
		} option;
	} config_reg_002b;

	/* ! \brief nonvolatile configuration register */
	union {
		uint16_t value;

		struct {
#ifdef  _BIG_ENDIAN_    /* AVR32 mcu Big Endian */
			uint8_t NU         : 1; /* !< Nonvolatile Not used */
			uint8_t NVRES      : 2; /* !< Nonvolatile Conversion
			                         * Resolution */
			uint8_t NVFT       : 2; /* !< Nonvolatile Fault
			                         * Tolerance Queue */
			uint8_t NVPOL      : 1; /* !< Nonvolatile ALERT Pin
			                         * Polarity */
			uint8_t NVCMP_INT  : 1; /* !< Nonvolatile Alarm
			                         * Thermostat Mode */
			uint8_t NVSD       : 1; /* !< Nonvolatile Shutdown Mode
			                        **/
			uint8_t RFU_       : 5; /* !< Bits 7:3 reserved for
			                         * future use */
			uint8_t RLCKDWN    : 1; /* !< Nonvolatile Register
			                         * Lockdown */
			uint8_t RLCK       : 1; /* !< Nonvolatile Register Lock
			                        **/
			uint8_t RFU        : 1; /* !< RFU */

#else                           /* AVR8 mcu Little Endian */
			uint8_t RFU        : 1; /* !< RFU */
			uint8_t RLCK       : 1; /* !< Nonvolatile Register Lock
			                        **/
			uint8_t RLCKDWN    : 1; /* !< Nonvolatile Register
			                         * Lockdown */
			uint8_t RFU_       : 5; /* !< Bits 7:3 reserved for
			                         * future use */
			uint8_t NVSD       : 1; /* !< Nonvolatile Shutdown Mode
			                        **/
			uint8_t NVCMP_INT  : 1; /* !< Nonvolatile Alarm
			                         * Thermostat Mode */
			uint8_t NVPOL      : 1; /* !< Nonvolatile ALERT Pin
			                         * Polarity */
			uint8_t NVFT       : 2; /* !< Nonvolatile Fault
			                         * Tolerance Queue */
			uint8_t NVRES      : 2; /* !< Nonvolatile Conversion
			                         * Resolution */
			uint8_t NU         : 1; /* !< Nonvolatile Not used */
#endif
		} option;
	} nvconfig_reg;

	/* ! \brief Information temperature */
	struct _temperature {
		uint8_t itemp;                  /* !<Integer part of the
		                                 * temperature data */
		uint16_t ftemp;                 /* !< Fractional part of the
		                                 * temperature data */
		uint8_t sign;                   /* !< Sign indicator */
		uint16_t raw_value;             /* !< Raw data */
	} temperature;

	struct _limits {
		uint16_t low;                   /* !< Low limit */
		uint16_t high;                  /* !< High limit */
		uint16_t critical;              /* !< Critical limit,
		                                 * AT30TSE002B device only */
	} limits;

	struct _nvlimits {
		uint16_t low;                   /* !< Low limit */
		uint16_t high;                  /* !< High limit */
	} nv_limits;

	struct {
		uint16_t smbus;                 /* !< 002b smbus */
		uint16_t device_id;     /* !< 002b device id */
		uint16_t manf_id;               /* !< 002b manufaucter id */
		uint16_t capability;    /* !< 002b capability */
	} _002b;
} __attribute__ ((packed)) sensor_data_t;

#elif defined(__ICCAVR__)
#pragma pack(1)
typedef struct _sensor_data {
	/* Volatile configuration register */
	/* ! \brief volatile configuration register */
	union {
		uint16_t value;
		struct {
#ifdef  _BIG_ENDIAN_    /* AVR32 mcu Big Endian */
			uint8_t OS       : 1; /* !< OS */
			uint8_t RES      : 2; /* !< Conversion Resolution */
			uint8_t FAULT    : 2; /* !< Fault Tolerance Queue */
			uint8_t POL      : 1; /* !< ALERT Pin Polarity */
			uint8_t CMP_INT  : 1; /* !< Alarm Thermostat Mode */
			uint8_t SD       : 1; /* !< Shutdown Mode */
			uint8_t RFU      : 7; /* !< RFU */
			uint8_t NVRBSY   : 1; /* !< Nonvolatile Registers
			                       *Busy */

#else                    /* AVR8 mcu Little Endian */
			uint8_t NVRBSY   : 1; /* !< Nonvolatile Registers
			                       *Busy */
			uint8_t RFU      : 7; /* !< RFU */
			uint8_t SD       : 1; /* !< Shutdown Mode */
			uint8_t CMP_INT  : 1; /* !< Alarm Thermostat Mode */
			uint8_t POL      : 1; /* !< ALERT Pin Polarity */
			uint8_t FAULT    : 2; /* !< Fault Tolerance Queue */
			uint8_t RES      : 2; /* !< Conversion Resolution */
			uint8_t OS       : 1; /* !< OS */
#endif
		} option;
	} config_reg;

	/* Volatile configuration register */
	/* ! \brief volatile configuration register */
	union {
		uint16_t value;
		struct {
#ifdef  _BIG_ENDIAN_    /* AVR32 mcu Big Endian */
			uint8_t RFU        : 5; /* !< RFU (Reserved for future
			                         *Use) */
			uint8_t HYSTENB    : 2; /* !< Hysteresis Enable */
			uint8_t SHTDWN     : 1; /* !< Shutdown Mode */
			uint8_t CRTALML    : 1; /* !< Crit_Alarm Trip Lock bit
			                        **/
			uint8_t WINLOCK    : 1; /* !< Alarm Window Lock bit */
			uint8_t EVTCLR     : 1; /* !< EVENT Clear(active low) */
			uint8_t EVTSTS     : 1; /* !< Pin Output Status (active
			                         *low) */
			uint8_t EVTOUT     : 1; /* !< Output Control */
			uint8_t CRITEVT    : 1; /* !< Critical Temperature only
			                        **/
			uint8_t EVTPOL     : 1; /* !< Polarity */
			uint8_t EVTMOD     : 1; /* !< Mode */

#else                           /* AVR8 mcu Little Endian */
			uint8_t EVTMOD     : 1; /* !< Mode */
			uint8_t EVTPOL     : 1; /* !< Polarity */
			uint8_t CRITEVT    : 1; /* !< Critical Temperature only
			                        **/
			uint8_t EVTOUT     : 1; /* !< Output Control */
			uint8_t EVTSTS     : 1; /* !< Pin Output Status (active
			                         *low) */
			uint8_t EVTCLR     : 1; /* !< EVENT Clear(active low) */
			uint8_t WINLOCK    : 1; /* !< Alarm Window Lock bit */
			uint8_t CRTALML    : 1; /* !< Crit_Alarm Trip Lock bit
			                        **/
			uint8_t SHTDWN     : 1; /* !< Shutdown Mode */
			uint8_t HYSTENB    : 2; /* !< Hysteresis Enable */
			uint8_t RFU                : 5; /* !< RFU (Reserved for
			                                 * Future Use) */
#endif
		} option;
	} config_reg_002b;

	/* ! \brief nonvolatile configuration register */
	union {
		uint16_t value;

		struct {
#ifdef  _BIG_ENDIAN_    /* AVR32 mcu Big Endian */
			uint8_t NU         : 1; /* !< Nonvolatile Not used */
			uint8_t NVRES      : 2; /* !< Nonvolatile Conversion
			                         * Resolution */
			uint8_t NVFT       : 2; /* !< Nonvolatile Fault
			                         * Tolerance Queue */
			uint8_t NVPOL      : 1; /* !< Nonvolatile ALERT Pin
			                         * Polarity */
			uint8_t NVCMP_INT  : 1; /* !< Nonvolatile Alarm
			                         * Thermostat Mode */
			uint8_t NVSD       : 1; /* !< Nonvolatile Shutdown Mode
			                        **/
			uint8_t RFU_       : 5; /* !< Bits 7:3 reserved for
			                         * future use */
			uint8_t RLCKDWN    : 1; /* !< Nonvolatile Register
			                         * Lockdown */
			uint8_t RLCK       : 1; /* !< Nonvolatile Register Lock
			                        **/
			uint8_t RFU        : 1; /* !< RFU */

#else                           /* AVR8 mcu Little Endian */
			uint8_t RFU        : 1; /* !< RFU */
			uint8_t RLCK       : 1; /* !< Nonvolatile Register Lock
			                        **/
			uint8_t RLCKDWN    : 1; /* !< Nonvolatile Register
			                         * Lockdown */
			uint8_t RFU_       : 5; /* !< Bits 7:3 reserved for
			                         * future use */
			uint8_t NVSD       : 1; /* !< Nonvolatile Shutdown Mode
			                        **/
			uint8_t NVCMP_INT  : 1; /* !< Nonvolatile Alarm
			                         * Thermostat Mode */
			uint8_t NVPOL      : 1; /* !< Nonvolatile ALERT Pin
			                         * Polarity */
			uint8_t NVFT       : 2; /* !< Nonvolatile Fault
			                         * Tolerance Queue */
			uint8_t NVRES      : 2; /* !< Nonvolatile Conversion
			                         * Resolution */
			uint8_t NU         : 1; /* !< Nonvolatile Not used */
#endif
		} option;
	} nvconfig_reg;

	/* ! \brief Information temperature */
	struct _temperature {
		uint8_t itemp;                  /* !<Integer part of the
		                                 * temperature data */
		uint16_t ftemp;                 /* !< Fractional part of the
		                                 * temperature data */
		uint8_t sign;                   /* !< Sign indicator */
		uint16_t raw_value;             /* !< Raw data */
	} temperature;

	struct _limits {
		uint16_t low;                   /* !< Low limit */
		uint16_t high;                  /* !< High limit */
		uint16_t critical;              /* !< Critical limit,
		                                 * AT30TSE002B device only */
	} limits;

	struct _nvlimits {
		uint16_t low;                   /* !< Low limit */
		uint16_t high;                  /* !< High limit */
	} nv_limits;

	struct {
		uint16_t smbus;                 /* !< 002b smbus */
		uint16_t device_id;     /* !< 002b device id */
		uint16_t manf_id;               /* !< 002b manufaucter id */
		uint16_t capability;    /* !< 002b capability */
	} _002b;
} sensor_data_t;  /* Packed Structure for IAR Compilation */
#pragma pack ()
#endif

/**
 * \brief Information about a AT30TS device
 */
#if defined(__GNUC__)
typedef struct _ts_device {
	/* ! Device address */
	uint8_t ts_reg_addr;

	/* ! Device id */
	uint8_t device_type;

	/* ! EEPROM size */
	uint16_t eeprom_size;
}
__attribute__ ((packed)) ts_device_t;

#elif defined(__ICCAVR__)
#pragma pack(1)
typedef struct _ts_device {
	/* ! Device address */
	uint8_t ts_reg_addr;

	/* ! Device id */
	uint8_t device_type;

	/* ! EEPROM size */
	uint16_t eeprom_size;
} ts_device_t; /* Packed Structure for IAR Compilation */
#pragma pack()
#endif

#define TPROG               5 /* !< NV Register Program Time (ms), max */
#define TCOPYW              5 /* !< Volatile to Nonvolatile Reg Copy Time (ms),
	                       * max */
#define TCOPYR              200 /* !< Nonvolatile to Volatile Reg Copy Time
	                         * (us), max */
#define EEPROM_WP_ADDRESS   0x60 /* !< EEPROM's WP TWI-address */
#define PAGE_SIZE           0x10 /* !< EEPROM page size */

/* AT30TS75x Pointer register address */
#define TEMPER_REG          0x00 /* !< Temperature Data (R) Default = 0x0000 */
#define CONFIG_REG          0x01 /* !< Vol Config (R/W) Default = N/A */
#define TLOLIM_REG          0x02 /* !< Vol Lo Lim (R/W) Default = N/A */
#define THILIM_REG          0x03 /* !< Vol Hi Lim (R/W) Default = N/A */
#define NV_CONFIG_REG       0x11 /* !< NonVol Config (R/W) Default = 0x0000 */
#define NV_TLOLIM_REG       0x12 /* !< NonVol Lo Lim (R/W) Default = 0x04B0 */
#define NV_THILIM_REG       0x13 /* !< NonVol Hi Lim (R/W) Default = 0x0500 */

/* AT30TSE002B Pointer register address */
#define CAPABIL_REG         0x00 /* !< Capability (R) Default = 0x00D7 */
#define CONFIGUR_REG        0x01 /* !< Configuration (R/W) Default = 0x0000 */
#define TRIP_UPR_REG        0x02 /* !< Upper Alarm (R/W) Default = 0x0000 */
#define TRIP_LWR_REG        0x03 /* !< Lower Alarm (R/W) Default = 0x0000 */
#define TRIP_CRT_REG        0x04 /* !< Critical Alarm (R/W) Default = 0x0000 */
#define TEMP_DATA_REG       0x05 /* !< Temperature Data (R) Default = N/A */
#define MANF_ID_REG         0x06 /* !< Manufacturer ID (R) Default = 0x001F */
#define DEV_ID_REG          0x07 /* !< Dev ID/Revision (R) Default = 0x8201 */
#define SMBUS_TO_REG        0x22 /* !< SMBus Timeout (R/W) Default = 0x0000 */

/* Register commands */
#define CPY_VOL_NVOL_REG    0x48 /* !< Copy Volatile Registers to Nonvolatile
	                          * Registers */
#define CPY_NVOL_VOL_REG    0xB8 /* !< Copy Nonvolatile Registers to Volatile
	                          * Registers */

/* Register configuration bits */
#define NVRBSY              0x01 /* !< Nonvolatile Registers Busy */
#define RLCK_MSK            0x02 /* !< Nonvolatile Register Lock */
#define RLCKDWN_MSK         0x04 /* !< Nonvolatile Register Lockdown */

/**
 * \defgroup sensor_at30ts_api_group AT30TS API listing
 * @{
 */
int8_t ts_read_register(const uint8_t pointer_reg, uint8_t *ibuf);
int8_t ts_write_register(uint8_t *obuf);
int8_t ts_read_eeprom(uint16_t address, uint16_t size, uint8_t *buf);
int8_t ts_write_eeprom(uint16_t address, uint16_t size, uint8_t *buf);
int8_t ts75_copy_vol_nonvol_register(void);
int8_t ts75_copy_nonvol_vol_register(void);
int8_t ts75_probe_nonvol_register(uint8_t device_addr);

uint8_t write_config(uint16_t val);
uint8_t write_temperature_low(uint8_t sign, uint8_t itemp,
                              uint16_t ftemp);
uint8_t write_temperature_high(uint8_t sign, uint8_t itemp,
                              uint16_t ftemp);
uint8_t read_temperature_high(sensor_data_t *data);
uint8_t read_temperature_low(sensor_data_t *data);
uint8_t read_config(sensor_data_t *data);
int8_t read_temperature(sensor_data_t *data);
uint8_t set_config_option(sensor_data_t *data, opt_flag_t flag,
                              config_options_t opt);
uint8_t write_nvconfig(uint16_t val);
uint8_t write_nvtlow(uint8_t sign, uint8_t itemp, uint16_t ftemp);
uint8_t write_nvthigh(uint8_t sign, uint8_t itemp, uint16_t ftemp);
uint8_t read_nvthigh(sensor_data_t *data);
uint8_t read_nvtlow(sensor_data_t *data);
uint8_t read_nvconfig(sensor_data_t *data);
uint8_t set_nvconfig_option(sensor_data_t *data, opt_flag_t flag,
                            nvconfig_options_t opt);
int8_t ts_ack_polling(uint8_t addr);
void parse_temp_reading(sensor_data_t *sensor_data);
int8_t check_NVRBSY(void);
void attach_device(uint8_t device_addr, device_type_t type);
uint8_t ts_write_memory(uint16_t address, uint16_t size, uint8_t *buf);
void ts_construct_eeprom_address(twi_package_t *packet, 
                                  uint16_t address);

/* Use for compatibility */
uint8_t twi_write(twi_package_t *packet);
uint8_t twi_read(twi_package_t *packet);
uint8_t twi_probe_device(uint8_t addr);

/* At30tse002b device only */
uint8_t read_smbus(sensor_data_t *sensor_data);
uint8_t read_devid(sensor_data_t *sensor_data);
uint8_t read_manfid(sensor_data_t *sensor_data);
uint8_t read_capability(sensor_data_t *sensor_data);
uint8_t read_tcrit(sensor_data_t *sensor_data);
uint8_t write_tcrit(uint8_t sign, uint8_t itemp, uint16_t ftemp);

/** @} */

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page sensor_at30ts_quickstart Quick start guide for the AT30TS
 *
 * This is the quick start guide for the \ref
 * sensor_at30ts_group, with step-by-step instructions
 * on how to configure and use the driver.
 *
 * \section at30ts_basic_use_case Basic use case
 * In the basic use case, the below setup is used:
 * -# The type of the AT30TS component - AT30TSE758
 * -# The development board used is Temperature Sensor Xplained
 * -# Defined two corresponding symbols in the project properties 
 *  _ATAVRTEMPSENSORX_, _AT30TSE758_ 
 * -# The AT30TSE758 is connected to the TWIC of an Xmega256A3BU
 * -# Temperature Sensor Xplained kit is plugged onto the 
 *  Xmega-A3BU Xplained Development Kit
 * -# TWI is configured as master
 * -# 10 bytes of data is written to the device. This is read back 
 *  and verified
 * -# Temperature is read at defined intervals and displayed
 *
 * \section at30ts_basic_use_case_setup Setup steps
 *
 * \subsection at30ts_basic_use_case_setup_prereq Prerequisites
 * -# AT30TSxx temperature sensor is interfaced via TWI
 * -# So, we need to add TWI Master driver and define the 
 * - TWI module to be used.
 *
 * \subsection at30ts_basic_use_case_setup_code Example code
 * The device addresses given below are defined 
 * for _ATAVRTEMPSENSORX_ development board
 * \code
 * #define TWI_MODULE               &TWIC
 * #define TWI_SPEED                50000
 * #define EXAMPLE_TS_DEVICE        AT30TSE758
 * #define EXAMPLE_TS_DEVICE_ADDR   AT30TSE758_ADDR_LOCAL
 * #define AT30TSE758_ADDR_LOCAL    0x48
 * \endcode
 *
 * The application will be somewhat similar to the below
 * \code
 * uint8_t ibuf[16] = {0};
 * static uint8_t test_pattern[PATTERN_TEST_LENGTH];
 * sensor_data_t sensor_data;
 * twi_master_options_t opt;
 * static uint8_t ret = 0;
 * uint8_t i = 0;
 *
 * irq_initialize_vectors();
 * sysclk_init();
 * board_init();
 * attach_device(EXAMPLE_TS_DEVICE_ADDR, EXAMPLE_TS_DEVICE);
 * opt.chip = EXAMPLE_TS_DEVICE_ADDR;
 * opt.speed = TWI_SPEED;
 * twi_master_setup(TWI_MODULE, &opt);
 *  
 * sensor_data.config_reg.value = 0;
 * sensor_data.config_reg.option.RES  = RES12;
 * if (write_config(sensor_data.config_reg.value) != TWI_SUCCESS) {
 *     test_fail_indication();
 * 	}
 * char senseData[50] = {0};	
 * read_temperature(&sensor_data);
 * sprintf(senseData, "%d.%04d DegC",
 *         sensor_data.temperature.itemp,
 *         sensor_data.temperature.ftemp);
 * 
 * // Perform a write access & check write result
 * if ((ret = ts_write_memory(EE_TEST_ADDR, PATTERN_TEST_LENGTH,
 *                (void *)test_pattern)) != TWI_SUCCESS) {
 * 	test_fail_indication();
 * }
 * 
 * // Allow time for EEPROM to settle
 * delay_ms(5);
 * // Clear test_pattern
 * memset(ibuf, 0, sizeof(ibuf));
 * 
 * // Perform a read access & check read result
 * if (ts_read_eeprom(EE_TEST_ADDR, PATTERN_TEST_LENGTH,
 * 		ibuf) != TWI_SUCCESS) {
 * 	test_fail_indication();
 * }
 * // Check received data against sent data
 * for (i = 0; i < PATTERN_TEST_LENGTH; i++) {
 * 	if (ibuf[i] != test_pattern[i]) {
 * 		test_fail_indication();
 * 	}
 * }
 * 
 * \endcode
 *
 * \subsection at30ts_basic_use_case_setup_flow Workflow
 * The TWI module to be used in the application can be 
 * defined in 'conf_twim.h'
 * \code #define TWI_MODULE               &TWIC \endcode
 * -# Make sure that the required preprocessor symbols for the selected 
 * sensor device and the development board (if any) are defined
 * in the project options eg: _ATAVRTEMPSENSORX_ , _AT30TSE758_
 * -# Enable the system clock and initialize TWI as Master
 * \code 
 * sysclk_init();
 * board_init();
 * attach_device(EXAMPLE_TS_DEVICE_ADDR, EXAMPLE_TS_DEVICE);
 * opt.chip = EXAMPLE_TS_DEVICE_ADDR;
 * opt.speed = TWI_SPEED;
 * twi_master_setup(TWI_MODULE, &opt);
 * 
 * \endcode

 * \section at30ts_basic_use_case_usage Usage steps
 * \subsection at30ts_basic_use_case_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
 *	read_temperature(&sensor_data);
 *  sprintf(senseData, "%d.%04d DegC",
 *  					sensor_data.temperature.itemp,
 * 						sensor_data.temperature.ftemp);
 *  status = ts_write_eeprom(address, write_size, buf);
 *  status = ts_read_eeprom(EE_TEST_ADDR, PATTERN_TEST_LENGTH, ibuf);
 * \endcode
 */
 
#endif  /* AT30TS_H_ */
