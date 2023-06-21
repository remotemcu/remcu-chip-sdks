/**
 * \file
 *
 * \brief QTouch debug settings.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

//---------- Do not edit --------------------
// Project Constants
// Values from 0xF000->0xFFFF are reserved for Atmel Kits
// values from 0x0000->0xEFFF are available for other projects
#define    QT8        0xF001
#define    QT16        0xF002
#define    QM64        0xF003
#define  ATSAM3S_EK     0xF006
#define  ATSAM3U_QTVB   0xF007
#define  ATSAM3N_EK     0xF008
#define  ATSAM4S        0xF0FF

// Interface constants
#define    TWI        1
#define    SPI1W        2
#define    SPI2W        3
#define    UART        4
#define  BitBangSPI     5

//---------- Edit Project Info -------------

// Select the type of interface to use for the debug protocol.
// Comment out the interface not used.
// Only one interface should be active.
//#define	QDEBUG_SPI
//#define QDEBUG_TWI
#define QDEBUG_SPI_BB

// Set up project info
//#define        PROJECT_ID        QT16
#define        PROJECT_ID        ATSAM4S


#if defined(QDEBUG_SPI)
#define        INTERFACE           SPI2W
#elif defined(QDEBUG_TWI)
#define        INTERFACE           TWI
#elif defined(QDEBUG_SPI_BB)
#define     INTERFACE           BitBangSPI
#endif
