/**
 *
 * \file
 *
 * \brief WiFi Settings.
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

#ifndef CONF_WILC_H_INCLUDED
#define CONF_WILC_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"
#include "osprintf.h"
#include <FreeRTOSConfig.h>

/*
   ---------------------------------
   --------- Chip settings ---------
   ---------------------------------
*/

/** Select WILC firmware to use. */
#define CONF_WILC_USE_3000_REV_A


/*
   ---------------------------------
   --------- Bluetooth ---------
   ---------------------------------
*/
#define CONF_BT_MODE_BLE_ONLY	/* BLE Only mode */

/*
   ---------------------------------
   ---------- PIN settings ---------
   ---------------------------------
*/

#define CONF_WILC_PIN_RESET              IOPORT_CREATE_PIN(PIOD, 26)
#define CONF_WILC_PIN_CHIP_ENABLE        IOPORT_CREATE_PIN(PIOC,13)
#define CONF_WILC_PIN_WAKE               IOPORT_CREATE_PIN(PIOB, 2)

/*
   ---------------------------------
   ---------- SPI settings ---------
   ---------------------------------
*/

#define CONF_WILC_USE_SPI				
//#define CONF_WILC_USE_SDIO				
//#define CONF_WILC_USE_SDIO_EXT_IRQ				

/** SPI pin and instance settings. */
#define CONF_WILC_SPI					SPI0
#define CONF_WILC_SPI_ID				ID_SPI0
#define CONF_WILC_SPI_MISO_GPIO			SPI0_MISO_GPIO
#define CONF_WILC_SPI_MISO_FLAGS		SPI0_MISO_FLAGS
#define CONF_WILC_SPI_MOSI_GPIO			SPI0_MOSI_GPIO
#define CONF_WILC_SPI_MOSI_FLAGS		SPI0_MOSI_FLAGS
#define CONF_WILC_SPI_CLK_GPIO			SPI0_SPCK_GPIO
#define CONF_WILC_SPI_CLK_FLAGS			SPI0_SPCK_FLAGS
#define CONF_WILC_SPI_CS_GPIO			SPI0_NPCS1_GPIO
#define CONF_WILC_SPI_CS_FLAGS			SPI0_NPCS1_FLAGS
#define CONF_WILC_SPI_NPCS				(1)

/** SPI delay before SPCK and between consecutive transfer. */
#define CONF_WILC_SPI_DLYBS				(0)
#define CONF_WILC_SPI_DLYBCT 			(0)

/** SPI interrupt pin. */
#if defined(CONF_WILC_USE_SPI) && defined(CONF_WILC_USE_3000_REV_A) 
/*Interrupt pin configuration is unique for WILC3000SHLD + SAMv71*/
#define CONF_WILC_SPI_INT_PIN               IOPORT_CREATE_PIN(PIOC, 31)
#define CONF_WILC_SPI_INT_PIO               PIOC
#define CONF_WILC_SPI_INT_PIO_ID            ID_PIOC
#define CONF_WILC_SPI_INT_MASK              (1 << 31)
#else
#define CONF_WILC_SPI_INT_PIN           IOPORT_CREATE_PIN(PIOD, 28)
#define CONF_WILC_SPI_INT_PIO           PIOD
#define CONF_WILC_SPI_INT_PIO_ID        ID_PIOD
#define CONF_WILC_SPI_INT_MASK          (1 << 28)
#endif

/** Highest INT priority that can call FreeRTOS FromISR() functions. */
#define CONF_WILC_SPI_INT_PRIORITY		(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY)

/** Clock polarity & phase. */
#define CONF_WILC_SPI_POL				(0)
#define CONF_WILC_SPI_PHA				(1)

/** SPI clock. */
#define CONF_WILC_SPI_CLOCK				(40000000)

/*
   ---------------------------------
   ----------- OS options ----------
   ---------------------------------
*/

#define CONF_DRIVER_LOCK				1
#if CONF_DRIVER_LOCK
#  include <os/include/os_hook.h>
#  define DRIVER_SIGNAL_ISR				os_hook_isr
#else
#  define DRIVER_SIGNAL_ISR()
#endif

/*
   ---------------------------------
   --------- Debug options ---------
   ---------------------------------
*/

#define CONF_WILC_DEBUG					(1)
#define CONF_WILC_PRINTF				osprintf

#ifdef __cplusplus
}
#endif

#endif /* CONF_WILC_H_INCLUDED */
