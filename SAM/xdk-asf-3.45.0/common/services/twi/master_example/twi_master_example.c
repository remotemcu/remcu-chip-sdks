/*****************************************************************************
 *
 * \file
 *
 * \brief Example of usage of the TWI Master Mode Basic Services.
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
 ******************************************************************************/

/*! \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the TWI master mode basic services example.
 *
 * \section files Main Files
 * - twi_master_example.c: example application.
 * - conf_board.h: board configuration
 * - conf_twim.h: TWI master configuration used in this example
 * - twi_master.h: Part Specific TWI Master Mode Implementation
 *
 * \section twiapiinfo services/basic/twi API
 * The TWI API can be found \ref twi_master.h "here".
 *
 * \section deviceinfo Device Info
 * All AVR or SAM devices can be used. When use the example in Xplained Pro
 * Kits, we need connect an IO1 Xplained Pro board to the proper EXT port. For
 * information of the IO1Xplained Pro board, visit
 * <A href="http://www.microchip.com/tools/ATIO1-XPRO.aspx">IO1 web link.</A>
 * This example has been tested with the following setup:
 *   - access to the TWI signals.
 *
 * \section exampledescription Description of the example
 * The given example uses one kit as a TWI master:
 *    - the TWI master performs a write access to the TWI slave,
 *    - the TWI master performs a read access of what it just wrote to the TWI slave,
 *    - the read data are compared with the originally written data.
 *
 * LED0 gives the result of the test:
 *  If FAILED: LED0 is off.
 *  If PASS: LED0 is on at the end of the test.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR or SAM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "board.h"
#include "sysclk.h"
#include "twi_master.h"
#include "led.h"

#include "conf_board.h"

#if SAM
#include "conf_twi_master.h"
#include <string.h>
#endif

//! \name Local Configuration Constants
//@{
#ifndef EEPROM_BUS_ADDR
#define EEPROM_BUS_ADDR       0x50        //!< TWI slave bus address
#endif
#define EEPROM_MEM_ADDR       0xaa        //!< TWI slave memory address
#define TWI_SPEED             50000       //!< TWI data transfer rate

//@}


//! \name Slave EEPROM memory Test Pattern Constants
//@{

#define PATTERN_TEST_LENGTH     sizeof(test_pattern)
const uint8_t test_pattern[] = {
   0x55,
   0xA5,
   0x5A,
   0x77,
   0x99};

//@}


/*! \brief TWI Master Example Main
 *
 * The master example begins by initializing required board resources.  The
 * system clock, basic GPIO pin mapping, and interrupt vectors are established.
 *
 * A memory location on a TWI slave is written with a fixed test pattern which
 * is then read back into a separate buffer.  As a basic sanity check, the
 * original write-buffer values are compared with values read from the slave to
 * a separate buffer.  An LED on the development board is illuminated when there
 * is a match between the written and read data.
 *
 * \return Nothing.
 */
int main(void)
{
  /* Initialize the common clock service, board-specific initialization, and
   * interrupt vector support prior to using the TWI master interfaces.
   */
  sysclk_init();

  board_init();

#if (!SAM && !MEGA)
  irq_initialize_vectors();
#endif // SAM

  // TWI master initialization options.

  twi_master_options_t opt;
#if SAM
  memset((void *)&opt, 0, sizeof(opt));
#endif
  opt.speed = TWI_SPEED;
#if (!SAM4L)
  opt.chip  = EEPROM_BUS_ADDR;
#endif

  // Initialize the TWI master driver.

  twi_master_setup(TWI_EXAMPLE, &opt);

  // Initialize the platform LED's.
#if defined(sam4cek)
  LED_Off(LED0);
#elif defined(sam4cmpdb) || defined(sam4cmsdb)
  LED_Off(LED4);
#else
  LED_Off(LED0_GPIO);
#endif

  twi_package_t packet = {
/**
 * The SAM3X_EK, SAM3X Arduino board and SAM4C_EK use two bytes length internal
 * address EEPROM.
 */
#if defined(sam3xek) || defined(arduinoduex) || defined(sam4cek) || defined(sam4cmpdb) || defined(sam4cmsdb)
    .addr[0]      = EEPROM_MEM_ADDR >> 8, // TWI slave memory address data MSB
    .addr[1]      = EEPROM_MEM_ADDR,      // TWI slave memory address data LSB
    .addr_length  = sizeof (uint16_t),    // TWI slave memory address data size
#else
    .addr[0]      = EEPROM_MEM_ADDR,      // TWI slave memory address data MSB
    .addr_length  = sizeof (uint8_t),     // TWI slave memory address data size
#endif
    .chip         = EEPROM_BUS_ADDR,      // TWI slave bus address
    .buffer       = (void *)test_pattern, // transfer data source buffer
    .length       = PATTERN_TEST_LENGTH   // transfer data size (bytes)
  };

  // Perform a multi-byte write access then check the result.
  while (twi_master_write(TWI_EXAMPLE, &packet) != TWI_SUCCESS);

  uint8_t data_received[PATTERN_TEST_LENGTH] = {0};

  twi_package_t packet_received = {
#if defined(sam3xek) || defined(arduinoduex) || defined(sam4cek) || defined(sam4cmpdb) || defined(sam4cmsdb)
    .addr[0]      = EEPROM_MEM_ADDR >> 8, // TWI slave memory address data MSB
    .addr[1]      = EEPROM_MEM_ADDR,      // TWI slave memory address data LSB
    .addr_length  = sizeof (uint16_t),    // TWI slave memory address data size
#else
    .addr[0]      = EEPROM_MEM_ADDR,      // TWI slave memory address data MSB
    .addr_length  = sizeof (uint8_t),     // TWI slave memory address data size
#endif
    .chip         = EEPROM_BUS_ADDR,      // TWI slave bus address
    .buffer       = data_received,        // transfer data destination buffer
    .length       = PATTERN_TEST_LENGTH   // transfer data size (bytes)
  };

  // Perform a multi-byte read access then check the result.
  while (twi_master_read(TWI_EXAMPLE, &packet_received) != TWI_SUCCESS);

  // Verify that the received data matches the sent data.
  for (uint32_t i = 0 ; i < PATTERN_TEST_LENGTH; ++i) {

    if (data_received[i] != test_pattern[i]) {
      // Error
      while(1);
    }
  }

  //test PASS
#if SAM4C
  LED_On(LED0);
#elif defined(sam4cmpdb) || defined(sam4cmsdb)
  LED_On(LED4);
#else
  LED_On(LED0_GPIO);
#endif

  while(1);
}
