/**
 * \file
 *
 * \brief Management of the virtual memory.
 *
 * This file manages the virtual memory.
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

#ifndef _VIRTUAL_MEM_H_
#define _VIRTUAL_MEM_H_


#include "conf_access.h"

#if VIRTUAL_MEM == ENABLE

#include "ctrl_access.h"

#ifdef __cplusplus
extern "C" {
#endif

//_____ D E F I N I T I O N S ______________________________________________

#define VMEM_SECTOR_SIZE   512


//---- CONTROL FUNCTIONS ----

extern Ctrl_status  virtual_test_unit_ready(void);
extern Ctrl_status  virtual_read_capacity(uint32_t *u32_nb_sector);
extern bool         virtual_wr_protect(void);
extern bool         virtual_removal(void);
extern bool         virtual_unload(bool unload);


//---- ACCESS DATA FUNCTIONS ----

// USB interface
#if ACCESS_USB == true
extern Ctrl_status  virtual_usb_read_10 (uint32_t addr, uint16_t nb_sector);
extern Ctrl_status  virtual_usb_write_10(uint32_t addr, uint16_t nb_sector);
#endif

// RAM interface
#if ACCESS_MEM_TO_RAM == true
extern Ctrl_status  virtual_mem_2_ram(uint32_t addr,       void *ram);
extern Ctrl_status  virtual_ram_2_mem(uint32_t addr, const void *ram);
#endif

#ifdef __cplusplus
}
#endif

#endif

#endif  // _VIRTUAL_MEM_H_
