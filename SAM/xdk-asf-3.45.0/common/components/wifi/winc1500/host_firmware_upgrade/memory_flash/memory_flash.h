/**
 *
 * \file
 *
 * \brief Flash Memory Access API's.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#include "flash_efc.h"

/* if dual bank flash */
#ifndef IFLASH_ADDR
#  define IFLASH_ADDR      IFLASH0_ADDR
#endif
/* if dual bank flash */
#ifndef IFLASH_PAGE_SIZE
#  define IFLASH_PAGE_SIZE IFLASH0_PAGE_SIZE
#endif

#define memory_init        mem_flash_init
#define memory_cleanup     mem_flash_cleanup
#define memory_erase       mem_flash_erase
#define memory_write       mem_flash_page_write
#define memory_next        mem_flash_page_next
#define memory_lock        mem_flash_lock
#define memory_unlock      mem_flash_unlock
#define memory_flush()

void mem_flash_init(void);
void mem_flash_cleanup(void);
uint32_t mem_flash_erase(void * addr,uint32_t size);
bool mem_flash_page_write(void * addr,void * data);
void *mem_flash_page_next(void * addr);
bool mem_flash_lock(void * start,void * end);
bool mem_flash_unlock(void * start,void * end);


#endif
