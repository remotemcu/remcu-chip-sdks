/**
 * \file
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

#ifndef BOOTLOADER_H_INCLUDED
#define BOOTLOADER_H_INCLUDED

#include <asf.h>
#include <string.h>
#include "conf_bootloader.h"

/* Check configuration */

/* -- Information editor --- */
#ifdef DBG_USE_INFO_EDIT

#  ifndef DBG_USE_USART
#    error DBG_USE_USART must be defined to enable DBG console for InfoEdit
#  endif

#  ifndef DBG_INFO_EDIT_TRIGGER_PIN
#    error DBG_INFO_EDIT_TRIGGER_PIN must be defined for InfoEdit trigger
#  endif

#  ifdef TRIGGER_USE_BUTTONS
#    ifdef TRIGGER_LOAD_BUTTON
#      if TRIGGER_LOAD_BUTTON == DBG_INFO_EDIT_TRIGGER_PIN
#        error TRIGGER_LOAD_BUTTON and DBG_INFO_EDIT_TRIGGER_PIN must be different
#      endif
#    endif

#    ifdef TRIGGER_SWITCH_BUTTON
#      if TRIGGER_SWITCH_BUTTON == DBG_INFO_EDIT_TRIGGER_PIN
#        error TRIGGER_SWITCH_BUTTON and DBG_INFO_EDIT_TRIGGER_PIN must be different
#      endif
#    endif
#  endif
#endif

/* -- medias (currently SD supported) --- */
#if (!defined(MEDIA_USE_COMM) && \
	!defined(MEDIA_USE_ETH)   && \
	!defined(MEDIA_USE_SD)    && \
	!defined(MEDIA_USE_MSD)   && \
	!defined(MEDIA_USE_NAND))
#  error MEDIA_USE_SD must be defined
#endif

#ifdef MEDIA_USE_COMM
/* -- communication    */
#  ifndef COMM_USE_USART
#    error COMM_USE_USART and USART options must be defined 
#  endif
#  ifndef COMM_USE_XON_XOFF
#    error COMM_USE_XON_XOFF must be defined
#  endif
#endif
/* -- trigger          */
/* -- memory           */
#ifndef MEM_USE_FLASH
#  error MEM_USE_FLASH must be defined
#endif
/* -- regions          */


/* All include files for bootloader */
#include "debug.h"
#include "memories.h"
#include "regions.h"
#include "trigger.h"
#include "media.h"

void jump_to_app(void * code_addr);

/* Global tick in ms */
extern volatile uint32_t tick_ms;

#endif /* #ifndef BOOTLOADER_H_INCLUDED */

