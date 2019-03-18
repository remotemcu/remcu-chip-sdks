/* This source file is part of the ATMEL QTouch Library Release 5.1 */

/**
 * \file
 *
 * \brief QTouch debug settings.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef QDEBUG_SETTINGS_H
#define QDEBUG_SETTINGS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* ---------- Do not edit -------------------- */

/*! \name Project Constants.
 * \brief Values from 0xF000->0xFFFF are reserved for Atmel Kits.
 * Values from 0x0000->0xEFFF are available for other projects.
 */
/* ! @{ */

#define         QT8                                     0xF001
#define         QT16                                    0xF002
#define         QM64                                    0xF003
#define         UC3L_EK_REV2                            0xF005
#define         SAMD20_XPLAINED_PRO_SELFCAP_EXT         0xF010
#define         SAMD20_XPLAINED_PRO_MUTLCAP_EXT         0xF011

/* ! @} */

/*! \name Interface constants.
 */
/* ! @{ */

#define         TWI                             1
#define         SPI1W                           2
#define         SPI2W                           3
#define         UART                            4

/* ! @} */

/* ---------- Edit Project Info ------------- */

/*! \name Select the type of interface to use for the debug protocol.
 * \brief Comment out the interface not used.
 * Only one interface should be active.
 */
/* ! @{ */

/* #define QDEBUG_SPI */
/* #define QDEBUG_TWI */
/* #define QDEBUG_SERIAL */
#define QDEBUG_BITBANG_SPI
#define QDEBUG_SPI_BB

/* The definitions below should not clash with the SNS/SNSK port pins */
#define QDEBUG_SPI_BB_SS_PIN        31
#define QDEBUG_SPI_BB_SCK_PIN       23
#define QDEBUG_SPI_BB_MOSI_PIN      22
#define QDEBUG_SPI_BB_MISO_PIN      16

#define QDEBUG_SPI_BB_SS_PORT       B
#define QDEBUG_SPI_BB_SCK_PORT      B
#define QDEBUG_SPI_BB_MOSI_PORT     B
#define QDEBUG_SPI_BB_MISO_PORT     B

/* ! @} */

/*! \name Set up project info.
 */
/* ! @{ */

#define PROJECT_ID              SAMD20_XPLAINED_PRO_MUTLCAP_EXT
#define INTERFACE               SPI2W

/* ! @} */

#ifdef __cplusplus
}
#endif

#endif                          /* QDEBUG_SETTINGS_H */
