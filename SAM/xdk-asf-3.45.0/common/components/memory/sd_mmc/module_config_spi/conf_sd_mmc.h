/**
 * \file
 *
 * \brief SD/MMC stack configuration file.
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

#ifndef CONF_SD_MMC_H_INCLUDED
#define CONF_SD_MMC_H_INCLUDED

// Define to enable the SPI mode instead of Multimedia Card interface mode
#define SD_MMC_SPI_MODE

// Define to enable the SDIO support
#define SDIO_SUPPORT_ENABLE

// Define to enable the debug trace to the current standard output (stdio)
//#define SD_MMC_DEBUG

/*! \name board SPI SD/MMC slot template definition
 *
 * The GPIO and SPI Connections of the SD/MMC Connector must be added
 * in board.h file.
 * Also do not forget to add the initialization of this GPIO in the init.c
 * from the board.
 * See below an example:
 */
//! @{
#ifndef SD_MMC_SPI_MEM_CNT
#  warning The GPIO and SPI connections of the SD/MMC connector must\
   be added in the board.h file and initialized in init.c board file.
// Add it when SD_MMC_SPI is a USART in SPI mode
//#define SD_MMC_SPI_USES_USART_SPI_SERVICE
#  if UC3 // Example from EVK1100
#    define SD_MMC_SPI_MEM_CNT          1
/* Optional card detect pin and write protection pin
#    define SD_MMC_0_CD_GPIO            AVR32_PIN_PA02
#    define SD_MMC_0_CD_DETECT_VALUE    1
#    define SD_MMC_0_WP_GPIO            AVR32_PIN_PA07
#    define SD_MMC_0_WP_DETECT_VALUE    0
*/
#    ifdef  AVR32_SPI
#      define SD_MMC_SPI_0_CS             0
#      define SD_MMC_SPI                  (&AVR32_SPI)
#      define SD_MMC_SPI_SCK_PIN          AVR32_SPI_SCK_0_1_PIN
#      define SD_MMC_SPI_SCK_FUNCTION     AVR32_SPI_SCK_0_1_FUNCTION
#      define SD_MMC_SPI_MISO_PIN         AVR32_SPI_MISO_0_1_PIN
#      define SD_MMC_SPI_MISO_FUNCTION    AVR32_SPI_MISO_0_1_FUNCTION
#      define SD_MMC_SPI_MOSI_PIN         AVR32_SPI_MOSI_0_1_PIN
#      define SD_MMC_SPI_MOSI_FUNCTION    AVR32_SPI_MOSI_0_1_FUNCTION
#      define SD_MMC_SPI_NPCS_PIN         AVR32_SPI_NPCS_0_0_PIN
#      define SD_MMC_SPI_NPCS_FUNCTION    AVR32_SPI_NPCS_0_0_FUNCTION
#    else
#      define SD_MMC_SPI_0_CS             1
#      define SD_MMC_SPI                  (&AVR32_SPI1)
#      define SD_MMC_SPI_SCK_PIN          AVR32_SPI1_SCK_0_0_PIN
#      define SD_MMC_SPI_SCK_FUNCTION     AVR32_SPI1_SCK_0_0_FUNCTION
#      define SD_MMC_SPI_MISO_PIN         AVR32_SPI1_MISO_0_0_PIN
#      define SD_MMC_SPI_MISO_FUNCTION    AVR32_SPI1_MISO_0_0_FUNCTION
#      define SD_MMC_SPI_MOSI_PIN         AVR32_SPI1_MOSI_0_0_PIN
#      define SD_MMC_SPI_MOSI_FUNCTION    AVR32_SPI1_MOSI_0_0_FUNCTION
#      define SD_MMC_SPI_NPCS_PIN         AVR32_SPI1_NPCS_1_0_PIN
#      define SD_MMC_SPI_NPCS_FUNCTION    AVR32_SPI1_NPCS_1_0_FUNCTION
#    endif
#  endif
#  if XMEGA
#    define SD_MMC_SPI_MEM_CNT          1
/* Optional card detect pin and write protection pin
#    define SD_MMC_0_CD_GPIO            IOPORT_CREATE_PIN(PORTE, 4)
#    define SD_MMC_0_CD_DETECT_VALUE    0
#    define SD_MMC_0_WP_GPIO            IOPORT_CREATE_PIN(PORTE, 6)
#    define SD_MMC_0_WP_DETECT_VALUE    0
*/
#    define SD_MMC_SPI                  &SPIC
#    define SD_MMC_SPI_SCK              IOPORT_CREATE_PIN(PORTC,7)
#    define SD_MMC_SPI_MISO             IOPORT_CREATE_PIN(PORTC,6)
#    define SD_MMC_SPI_MOSI             IOPORT_CREATE_PIN(PORTC,5)
#    define SD_MMC_SPI_0_CS             IOPORT_CREATE_PIN(PORTC,4)
/* Example XMEGA with a USART in SPI mode
#    define SD_MMC_SPI_USES_USART_SPI_SERVICE // To signal that is a USART in SPI mode
#    define SD_MMC_SPI                  &USARTD0
#    define SD_MMC_SPI_SCK              IOPORT_CREATE_PIN(PORTD, 1)
#    define SD_MMC_SPI_MISO             IOPORT_CREATE_PIN(PORTD, 2)
#    define SD_MMC_SPI_MOSI             IOPORT_CREATE_PIN(PORTD, 3)
#    define SD_MMC_SPI_0_CS             IOPORT_CREATE_PIN(PORTE, 5)
 */
#  endif
#  if SAM // Example from SAM3N-EK
#    define SD_MMC_SPI_MEM_CNT          1
/* Optional card detect pin and write protection pin
#    define SD_MMC_0_CD_GPIO            (PIO_PA19_IDX)
#    define SD_MMC_0_CD_PIO_ID          ID_PIOA
#    define SD_MMC_0_CD_FLAGS           (PIO_INPUT | PIO_PULLUP)
#    define SD_MMC_0_CD_DETECT_VALUE    0
*/
#    define SD_MMC_SPI_0_CS             0
#    ifdef  SPI
#      define SD_MMC_SPI                  SPI
#    else
#      define SD_MMC_SPI                  SPI0
#    endif
#    define SPI_NPCS0_GPIO              (PIO_PA11_IDX)
#    define SPI_NPCS0_FLAGS             (PIO_PERIPH_A | PIO_DEFAULT)
#    define SPI_MISO_GPIO               (PIO_PA12_IDX)
#    define SPI_MISO_FLAGS              (PIO_PERIPH_A | PIO_DEFAULT)
#    define SPI_MOSI_GPIO               (PIO_PA13_IDX)
#    define SPI_MOSI_FLAGS              (PIO_PERIPH_A | PIO_DEFAULT)
#    define SPI_SPCK_GPIO               (PIO_PA14_IDX)
#    define SPI_SPCK_FLAGS              (PIO_PERIPH_A | PIO_DEFAULT)
#  endif
#endif
//! @}

#endif /* CONF_SD_MMC_H_INCLUDED */

