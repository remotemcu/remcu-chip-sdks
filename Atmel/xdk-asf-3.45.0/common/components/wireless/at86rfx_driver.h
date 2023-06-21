/**
 * \file
 *
 * \brief AT86RFx driver.
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

/**
 * \defgroup group_common_components_wireless_at86rfxdriver AT86RFx Driver
 *
 * Common driver for the AT86RF family transceivers. This layer provides Transceiver Abstraction Layer(TAL) for the application across AT86RF family.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "compiler.h"

/**
 * Default value of CCA mode
 */
#define CCA_MODE_DEFAULT                (0x01)

/**
 * Default value of minimum backoff exponent used while performing csma ca
 */
#define MINBE_DEFAULT                   (0x03)

/**
 * Default value of maximum backoff exponent used while performing csma ca
 */
#define MAXBE_DEFAULT                   (0x05)

/**
 * Default value of maximum csma ca backoffs
 */
#define MAX_CSMA_BACKOFFS_DEFAULT       (0x04)

/**
 * Value used for checking proper locking of PLL during switch from
 * TRX_PFF to PLL_ON.
 */
#define PLL_LOCK_ATTEMPTS           (3)


/**
 * Value in us used for delay between poll attempts for transceiver access.
 */
#define TRX_POLL_WAIT_TIME_US       (100)

/**
 * Ratio between max time to transceiver poll delay
 */
#define P_ON_TO_CLKM_ATTEMPTS       ((uint8_t) \
                                     (P_ON_TO_CLKM_AVAILABLE_MAX_US \
                                     / TRX_POLL_WAIT_TIME_US))

/**
 * Ratio between max time to transceiver poll delay
 */
#define SLEEP_TO_TRX_OFF_ATTEMPTS   ((uint8_t) \
                                     (SLEEP_TO_TRX_OFF_MAX_US \
                                     / TRX_POLL_WAIT_TIME_US))


/**
 * Size of the length parameter
 */
#define LENGTH_FIELD_LEN                    (1)

/**
 * Length (in octets) of FCS
 */
#define FCS_LEN                             (2)

/**
 * Write access command of the transceiver
 */
#define WRITE_ACCESS_COMMAND            (0xC0)

/**
 * Read access command to the transceiver
 */
#define READ_ACCESS_COMMAND             (0x80)

/**
 * Frame write command of transceiver
 */
#define TRX_CMD_FW                      (0x60)

/**
 * Frame read command of transceiver
 */
#define TRX_CMD_FR                      (0x20)

/**
 * SRAM write command of transceiver
 */
#define TRX_CMD_SW                      (0x40)

/**
 * SRAM read command of transceiver
 */
#define TRX_CMD_SR                      (0x00)

/**
 * Default interrupt configuration for transceiver
 */
#define TRX_IRQ_DEFAULT     TRX_IRQ_TRX_END

/**
 * Definition of a function pointer
 */
#define FUNC_PTR    void *

/**
 * Size of the buffer allocated for transceiver reception
 */
#define LARGE_BUFFER_SIZE               (130)

/**
 * Maximum length of a phy packet
 */
#define PHY_MAX_LENGTH                  (127)


/** Enables the transceiver interrupts */
#define ENABLE_TRX_IRQ()  do {                                     \
    gpio_enable_pin_interrupt(EXT_INT, GPIO_RISING_EDGE);\
}while(0)

/** Disable the transceiver interrupts */
#define DISABLE_TRX_IRQ() do {                                     \
    gpio_disable_pin_interrupt(EXT_INT);\
}while(0)

/** Clear the transceiver interrupts */
#define CLEAR_TRX_IRQ()   do {                                     \
    gpio_clear_pin_interrupt_flag(EXT_INT);\
}while(0)


/**
 * Reset pin low
 */
#define RST_LOW()                       do {      \
     gpio_set_pin_low(TRX_RST);                   \
} while (0);

/**
 * Reset pin high
 */
#define RST_HIGH()                      do {      \
      gpio_set_pin_high(TRX_RST);                 \
} while (0);

/**
 * Sleep pin low
 */
#define SLP_TR_LOW()                    do {   \
      gpio_set_pin_low(SLP_TR);                \
} while (0);

/**
 * Sleep pin high
 */
#define SLP_TR_HIGH()                      do {   \
      gpio_set_pin_high(SLP_TR);                  \
} while (0);

extern uint8_t at86rfx_rx_buffer[];

/**
 * These are the return values of the RF API.
 */
typedef enum
#if !defined(DOXYGEN)
 at86rfx_retval_tag
#endif
{
	AT86RFX_SUCCESS = 0x00,
	AT86RFX_FAILURE = 0x01,
	AT86RFX_CHANNEL_ACCESS_FAILURE = 0x02
} SHORTENUM at86rfx_retval_t;

//! \defgroup rf_api APIs to access RF module
//!
//! \{

/**
 * \brief Initializes the transceiver interface
 *
 * This function initializes the transceiver interface.
 */
at86rfx_retval_t at86rfx_init(void);

/**
 * \brief Transmits the frame
 *
 * This function configures the transceiver in TX mode and transmits
 * the frame
 *
 * \param[in] frame_tx Pointer to data to be transmitted
 */
void at86rfx_tx_frame(uint8_t * frame_tx);

/**
 * \brief RF task handling
 *
 * This function
 * - Checks and calls back with received packet.
 * - Processes the TAL incoming frame queue.
 * - Calls the TAL state machine handling.
 */
void at86rfx_task(void);

/**
 * \brief Initializes the SPI and GPIO pins for transceiver access
 *
 * This function configures the SPI in master mode and interrupt
 * capability of GPIO pin to handle the interrupts from transceiver
 */
void pal_trx_init(void);

/**
 * \brief Reads current value from a transceiver register
 *
 * This function reads the current value from a transceiver register.
 *
 * \param addr Specifies the address of the trx register
 * from which the data shall be read
 *
 * \return value of the register read
 */
uint8_t pal_trx_reg_read(uint8_t addr);

/**
 * \brief Writes data into a transceiver register
 *
 * This function writes a value into transceiver register.
 *
 * \param addr Address of the trx register
 * \param data Data to be written to trx register
 *
 */
void pal_trx_reg_write(uint8_t addr, uint8_t data);

/**
 * \brief Reads frame buffer of the transceiver
 *
 * This function reads the frame buffer of the transceiver.
 *
 * \param[out] data Pointer to the location to store frame
 * \param[in] length Number of bytes to be read from the frame
 * buffer.
 */
void pal_trx_frame_read(uint8_t * data, uint8_t length);

/**
 * \brief Writes data into frame buffer of the transceiver
 *
 * This function writes data into the frame buffer of the transceiver
 *
 * \param[in] data Pointer to data to be written into frame buffer
 * \param[in] length Number of bytes to be written into frame buffer
 */
void pal_trx_frame_write(uint8_t * data, uint8_t length);

/**
 * \brief Subregister read
 *
 * \param   addr  Offset of the register
 * \param   mask  Bit mask of the subregister
 * \param   pos   Bit position of the subregister
 * \return  Data  Value of the read bit(s)
 */
uint8_t pal_trx_bit_read(uint8_t addr, uint8_t mask, uint8_t pos);

/**
 * \brief Subregister write
 *
 * \param[in]   reg_addr  Offset of the register
 * \param[in]   mask      Bit mask of the subregister
 * \param[in]   pos       Bit position of the subregister
 * \param[out]  new_value Data, which is muxed into the register
 */
void pal_trx_bit_write(uint8_t reg_addr, uint8_t mask, uint8_t pos,
		uint8_t new_value);
    //! @}

/**
 * \}
 */
