/**
 * \file
 *
 * \brief SAM USB SCSI commands
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
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifndef SCSI_COMMANDS_H_
#define SCSI_COMMANDS_H_


/****************************************************************************/
/* Command for all SCSI device types                                        */
/****************************************************************************/

// Mandatory Command set list from SBC-2
// (subclass 6, peripheral device type 0, version 5)
// FORMAT UNIT
// INQUIRY
// READ (6)
// READ (10)
// READ (16)
// READ CAPACITY (10)
// READ CAPACITY (16)
// REQUEST SENSE
// SEND DIAGNOSTIC
// TEST UNIT READY

#define SBC_CMD_TEST_UNIT_READY                   (0x00)
#define SBC_CMD_REQUEST_SENSE                     (0x03)
#define SBC_CMD_FORMAT_UNIT                       (0x04)
#define SBC_CMD_READ_6                            (0x08)
#define SBC_CMD_INQUIRY                           (0x12)
#define SBC_CMD_MODE_SELECT_6                     (0x15)
#define SBC_CMD_READ_FORMAT_CAPACITY              (0x23)
#define SBC_CMD_MODE_SENSE_6                      (0x1A)
#define SBC_CMD_START_STOP_UNIT                   (0x1B)
#define SBC_CMD_RECEIVE_DIAGNOSTICS               (0x1C)
#define SBC_CMD_SEND_DIAGNOSTIC                   (0x1D)
#define SBC_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL      (0x1E)
#define SBC_CMD_READ_LONG                         (0x23)
#define SBC_CMD_READ_CAPACITY_10                  (0x25)
#define SBC_CMD_READ_CD_ROM_CAPACITY              (0x25)
#define SBC_CMD_READ_10                           (0x28)
#define SBC_CMD_WRITE_10                          (0x2A)
#define SBC_CMD_READ_12							  (0xA8)	
#define SBC_CMD_WRITE_12						  (0xAA)
#define SBC_VERIFY10							   0x2F

#define SBC_CMD_SEEK                              (0x2B)
#define SBC_CMD_WRITE_VERIFY_10                   (0x2E)
#define SBC_CMD_VERIFY_10                         (0x2F)
#define SBC_CMD_SYNCHRONIZE_CACHE                 (0x35)
#define SBC_CMD_WRITE_BUFFER                      (0x3B)
#define SBC_CMD_CHANGE_DEFINITION                 (0x40)
#define SBC_CMD_READ_TOC                          (0x43)
#define SBC_CMD_MODE_SELECT_10                    (0x55)
#define SBC_CMD_RESERVE_10                        (0x56)
#define SBC_CMD_RELEASE_10                        (0x57)
#define SBC_CMD_MODE_SENSE_10                     (0x5A)

#define SBC_CONTROL_BYTE                          (0x00)
#define SBC_CMD_DIR_IN                            (0x80)
#define SBC_CMD_DIR_OUT                           (0x00)



#endif /* SCSI_COMMANDS_H_ */
