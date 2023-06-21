/**
 * \file
 *
 * \brief AT86RFX configuration
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
#ifndef CONF_AT86RFX_H
#define CONF_AT86RFX_H

#if defined(DOXYGEN)
/**
 * Attribute to apply to an enum declaration to force it into the smallest
 * type size required to represent all values.
 */
#define SHORTENUM
/**
 * Null operation: just waste one CPU cycle.
 */
#define nop()
#endif /* defined(DOXYGEN) */

#if defined(__ICCAVR32__)
#define SHORTENUM /**/
#define nop() __no_operation()
#endif /* defined(__ICCAVR32__) */
#if defined(__GNUC__)
#define SHORTENUM           __attribute__((packed))
#define nop() do { __asm__ __volatile__ ("nop"); } while (0)
#endif /* defined(__GNUC__) */

/*! \name Macros for IRQ and AT86RFX accessing GPIO
 */
//! @{
#define EXT_INT                         (AVR32_PIN_PA20)
#define EXT_INT_ISR_GROUP               2
#define EXT_INT_ISR_PRIORITY            1

 //! RESET pin of transceiver
#define TRX_RST                         (AVR32_PIN_PA17)
 //! Sleep Transceiver pin
#define SLP_TR                          (AVR32_PIN_PA19)
//! @}

/**
 * This macro saves the trx interrupt status and disables the trx interrupt.
 */
#define ENTER_TRX_REGION()              DISABLE_TRX_IRQ()
/**
 *  This macro restores the transceiver interrupt status
 */
#define LEAVE_TRX_REGION()              ENABLE_TRX_IRQ()

#if (UC3)
/* This macro saves the global interrupt status */
#define ENTER_CRITICAL_REGION()                 AVR32_ENTER_CRITICAL_REGION( )

/* This macro restores the global interrupt status */
#define LEAVE_CRITICAL_REGION()                 AVR32_LEAVE_CRITICAL_REGION( )

/* Wait for 65 ns. */
#define  WAIT_65_NS()  {nop(); nop();}

/* Wait for 1 us. Has to be provided based on the controller interfaced */
#define PAL_WAIT_1_US()      do {              \
} while (0)

/* Wait for 1 us. Has to be provided based on the controller interfaced */
#define DELAY_US(delay)      do {              \
} while (0)
#endif

/**
 * AT86RFX Module Callbacks definitions (Optional)
 * @{
 */
#define AT86RFX_RX_NOTIFY(frame)
#define AT86RFX_TX_STATUS_NOTIFY(status)
//@}

#if !defined(AT86RFX_SPI)              || \
    !defined(AT86RFX_SPI_NPCS)         || \
    !defined(AT86RFX_SPI_SCK_PIN)      || \
    !defined(AT86RFX_SPI_SCK_FUNCTION) || \
    !defined(AT86RFX_SPI_MISO_PIN)     || \
    !defined(AT86RFX_SPI_MISO_FUNCTION)|| \
    !defined(AT86RFX_SPI_MOSI_PIN)     || \
    !defined(AT86RFX_SPI_MOSI_FUNCTION)|| \
    !defined(AT86RFX_SPI_NPCS_PIN)     || \
    !defined(AT86RFX_SPI_NPCS_FUNCTION)|| \
    !defined(AT86RFX_SPI_MISO_PIN)     || \
    !defined(AT86RFX_SPI_BAUDRATE) 
#  warning The AT86RFX SPI setups configuration to use in the driver is missing. Default configuration is used.
#  define AT86RFX_SPI                  (&AVR32_SPI0)
#  define AT86RFX_SPI_NPCS             0
#  define AT86RFX_SPI_SCK_PIN          AVR32_SPI0_SCK_0_0_PIN
#  define AT86RFX_SPI_SCK_FUNCTION     AVR32_SPI0_SCK_0_0_FUNCTION
#  define AT86RFX_SPI_MISO_PIN         AVR32_SPI0_MISO_0_0_PIN
#  define AT86RFX_SPI_MISO_FUNCTION    AVR32_SPI0_MISO_0_0_FUNCTION
#  define AT86RFX_SPI_MOSI_PIN         AVR32_SPI0_MOSI_0_0_PIN
#  define AT86RFX_SPI_MOSI_FUNCTION    AVR32_SPI0_MOSI_0_0_FUNCTION
#  define AT86RFX_SPI_NPCS_PIN         AVR32_SPI0_NPCS_0_0_PIN
#  define AT86RFX_SPI_NPCS_FUNCTION    AVR32_SPI0_NPCS_0_0_FUNCTION
#  define AT86RFX_SPI_BAUDRATE         (48000)
#endif

#endif /* CONF_AT86RFX_H */
