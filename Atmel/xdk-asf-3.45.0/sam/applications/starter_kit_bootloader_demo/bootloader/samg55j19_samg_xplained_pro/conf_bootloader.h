/**
 * \file
 *
 * \brief Bootloader configuration.
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

#ifndef CONF_BOOTLOADER_H_INCLUDED
#define CONF_BOOTLOADER_H_INCLUDED

/*
 * Debug config
 * -> Debug console
 * -> Debug LED
 */
//#define DBG_USE_USART           /**< Define to Use UART (optional) */
#  define DBG_USART_NAME USART   /**< UART/USART */
#  define DBG_USART_NB   7      /**< UART/USART number (Nothing or 0, 1...) */
#  define DBG_USART_BAUDRATE    115200 /**< UART/USART baudrate */
//#  define DBG_USART_PIN_EN
//#    define DBG_USART_PIN_EN_LEVEL
#  define DBG_USART_PIN_RX      PIO_PA27_IDX      /**< USART RX pin IO index */
#  define DBG_USART_PIN_RX_MUX  IOPORT_MODE_MUX_B /**< USART RX periph Mux */
#  define DBG_USART_PIN_TX      PIO_PA28_IDX      /**< USART TX pin IO index */
#  define DBG_USART_PIN_TX_MUX  IOPORT_MODE_MUX_B /**< USART TX periph Mux */

//#define DBG_USE_LED             /**< Define to use LED0 for information */
#  define DBG_LED_PIN           LED_0_PIN    /**< LED pin IO index */
#  define DBG_LED_PIN_ON_LEVEL  LED_0_ACTIVE /**< Output level to make LED on */

/**
 * < Define to use DBG console to modify boot
 * information (Uses OLED1 BUTTON1).
 */
//#define DBG_USE_INFO_EDIT       
//#  define DBG_INFO_EDIT_TRIGGER_PIN        (PIO_PB2_IDX)
//#  define DBG_INFO_EDIT_TRIGGER_PIN_ACTIVE (0)

/*
 * Source media config
 * -> Update from SD card
 * -> File check list (in root dir)
 */
#define MEDIA_USE_SD /**< Define to use SD/MMC (must) */
/* Default file list (modify to customize default list) */
#  define MEDIA_FILE_LIST_DEFAULT  \
	"demo_en.bin"
#  define MEDIA_FILE_LIST_LEN      1

/*
 * Trigger config
 * -> Buttons
 * -> SW flag
 */
//#define TRIGGER_USE_BUTTONS     /**< Define to use button trigger */
//#  define TRIGGER_LOAD_BUTTON        (PIO_PA2_IDX)
//#  define TRIGGER_LOAD_BUTTON_ACTIVE (0)
//#  define TRIGGER_SWITCH_BUTTON /* reserved for dual bank with more btn */
//#  define TRIGGER_SWITCH_BUTTON_ACTIVE (0)

#define TRIGGER_USE_FLAG        /**< Define to use SW flag in INFO area */

/*
 * Memory config
 */
//#define MEM_LOCK_BOOT_REGION    /**< Define to lock boot region (optional) */

#define MEM_USE_FLASH           /**< Define to Use internal flash (must) */

/* Memory mapping
=====================================================================+
|<   128K   >|<                                       >|<    4 K    >|
+============+=========================================+=============+
| Bootloader | Application code                        | Information |
+=====================================================================
*/

#ifdef MEM_USE_FLASH
/** memory blank value */
#define MEM_BLANK_VALUE 0xFF
/** memory block size */
#define MEM_BLOCK_SIZE (IFLASH_PAGE_SIZE)
/** memory erase block size (4K) */
#define MEM_ERASE_SIZE (IFLASH_PAGE_SIZE * 16)
/* memory aligned (8 pages to erase) */
#define mem_align(addr) \
	(((addr) % MEM_ERASE_SIZE) ? ((addr) - ((addr) % MEM_ERASE_SIZE)) : (addr))
/** boot region size */
#define BOOT_SIZE      (128*1024)
/** application region size */
#define APP_SIZE       mem_align((IFLASH_SIZE - BOOT_SIZE) / 1)

/* memory address */
#define MEM0_ADDR      IFLASH_ADDR
/* MEM1_ADDR   is reserved for dual flash */

/* Boot region (single) */
#define BOOT_CODE_SIZE (BOOT_SIZE - MEM_BLOCK_SIZE) /* reserve last page */
#define BOOT0_START    mem_align(MEM0_ADDR)
#define BOOT0_END      (BOOT0_START + BOOT_SIZE - 1)
/* BOOT1_START is reserved for dual flash  */
/* BOOT1_END   is reserved for dual flash  */

/* Application region (single) */
#define APP_CODE_SIZE  (APP_SIZE - MEM_ERASE_SIZE) /* reserve last pages */
#define APP0_START     mem_align(MEM0_ADDR + BOOT_SIZE)
#define APP0_END       (APP0_START + APP_CODE_SIZE - 1)

/* boot: boot region number, always 0 */
#define APP_START(boot) (APP0_START) /* Always boot from 1st region */

/* Information page (follow app buffer) */
#define INFO_SIZE   (MEM_ERASE_SIZE) /**< Boot information size */
#define INFO0_ADDR  (APP0_END + 1)
/* INFO1_ADDR   is reserved for dual flash */

/* for_boot: purpose, true for boot, false for buffer */
#define INFO_ADDR(for_boot) (INFO0_ADDR) /* Info always save to last flash page */

#endif /* #ifdef MEM_USE_FLASH */

#endif /* CONF_BOOTLOADER_H_INCLUDED */

