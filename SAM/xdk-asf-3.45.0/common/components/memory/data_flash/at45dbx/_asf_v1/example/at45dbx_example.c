/*****************************************************************************
 *
 * \file
 *
 * \brief Example application of the AT45DBX data flash controller.
 *
 * This software uses AT45DBX interfaces to check memory capacity.
 * Then it performs:
 *   - two byte accesses (write one byte at first address of a cluster);
 *   - two buffer accesses (write 512 bytes at a cluster).
 * In order to test addresses, the patterns used are 0x55 and 0xAA.
 * You have to set in conf_at45dbx.h what is your memory capacity.
 * For an example about FAT file-system accesses on DF components, see the
 * FAT module.
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
 ******************************************************************************/

/*! \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the AT45DBX driver.
 *
 * This example demonstrates how to use the AT45DBX low-level interface.
 *
 * This software uses data flash interfaces to check memory capacity.
 * Then it performs:
 *   - two byte accesses;
 *   - two sector accesses (512 bytes);
 *   - one multiple sector access.
 *
 * The patterns 0x55 and 0xAA are used to test addresses and data.
 *
 * The memory capacity has to be set up in conf_at45dbx.h.
 *
 * For an example about FAT file-system accesses on DF components, see the
 * <A href="../../../../../../SERVICES/FAT/EXAMPLES/FAT_EXAMPLE/readme.html">FAT example</A>.
 *
 * \section files Main Files
 * - at45dbx.c: management of the AT45DBX data flash controller through SPI;
 * - at45dbx.h: associated header file;
 * - at45dbx_mem.c: CTRL_ACCESS interface for the AT45DBX data flash controller;
 * - at45dbx_mem.h: associated header file;
 * - ctrl_access.c: abstraction layer for memory interfaces;
 * - ctrl_access.h: associated header file;
 * - at45dbx_example.c: AT45DBX example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC for AVR32 and for IAR Embedded Workbench
 * for Atmel AVR32. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All AVR32 devices with an SPI and a USART module can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following configuration:
 * - EVK1100, EVK1101, EVK1105, EVK1104, AT32UC3C-EK, AT32UC3L-EK evaluation kit;
 * - CPU clock:
*              -- 12 MHz: EVK1100, EVK1101, EVK1104, EVK1105, AT32UC3L-EK
*              -- 16 MHz: AT32UC3C-EK
 * - USART1 on EVK1100 and EVK1101 connected to a PC serial port via a standard RS232 DB9 cable;
 *   USART0 on EVK1105 connected to a PC via USB VCP;
 *   USART1 on EVK1104 connected to a PC via USB VCP;
 *   USART2 on AT32UC3C-EK connected to a PC via USB VCP;
 *   USART3 on AT32UC3L-EK connected to a PC via USB VCP;
 * - PC terminal settings:
 *   - 57600 bps,
 *   - 8 data bits,
 *   - no parity bit,
 *   - 1 stop bit,
 *   - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/design-centers/32-bit /">Atmel AVR32</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#include <string.h>
#include "compiler.h"
#include "preprocessor.h"
#include "board.h"
#include "power_clocks_lib.h"
#include "gpio.h"
#include "spi.h"
#include "print_funcs.h"
#include "conf_at45dbx.h"
#include "at45dbx.h"


//! Welcome message to display.
#define MSG_WELCOME "\r\n ---------- Welcome to AT45DBX example ---------- \r\n"
#define MSG_GOODBYE "\r\n ---------- End of AT45DBX example ---------- \r\n"


/*! \name Test Result Messages
 */
//! @{
#define TEST_SUCCESS "\t[PASS]\r\n"
#define TEST_FAIL    "\t[FAIL]\r\n"
//! @}

/*! \name Clock Settings
 */
//! @{
#  define EXAMPLE_TARGET_PBACLK_FREQ_HZ FOSC0  // PBA clock target frequency
#if BOARD == UC3L_EK
#undef EXAMPLE_TARGET_PBACLK_FREQ_HZ
#  define EXAMPLE_TARGET_PBACLK_FREQ_HZ 12000000  // PBA clock target frequency
#  define EXAMPLE_TARGET_DFLL_FREQ_HZ   96000000  // DFLL target frequency, in Hz.
#  define EXAMPLE_TARGET_MCUCLK_FREQ_HZ 12000000  // MCU clock target frequency, in Hz.
#endif
//! @}

//! Pattern to test the AT45DBX multiple-sector access functions with.
static const Union32 PATTERN_MULTIPLE_SECTOR = {0xDEADBEEF};

//! Number of erroneous bytes detected during the test of the AT45DBX multiple-
//! sector access functions.
static U32 at45dbx_example_error_cnt;


/*! \brief Performs a memory check on all DFs.
 */
static void at45dbx_example_check_mem(void)
{
  if (at45dbx_mem_check())
  {
    print_dbg("\tSize:\t");
    print_dbg_ulong(AT45DBX_MEM_CNT << (AT45DBX_MEM_SIZE - 20));
    print_dbg(" MB\t" TEST_SUCCESS);
  }
  else
  {
    print_dbg(TEST_FAIL);
  }
}


/*! \brief Tests single-byte access functions.
 */
static void at45dbx_example_test_byte_mem(void)
{
  U8 Pattern = 0x55;
  U8 j = 0xA5;
  print_dbg("\tUsing Pattern 0x55");
  // Perform write access.
  if (at45dbx_write_open(Pattern))
  {
    at45dbx_write_byte(Pattern);
    at45dbx_write_close();
  }
  // Perform read access.
  if (at45dbx_read_open(Pattern))
  {
    j = at45dbx_read_byte();
    at45dbx_read_close();
  }
  // Check read and write operations.
  if (j == Pattern)
  {
    print_dbg(TEST_SUCCESS);
  }
  else
  {
    print_dbg(TEST_FAIL);
  }

  // Change the pattern used.
  Pattern = 0xAA;
  j = 0xA5;
  print_dbg("\tUsing Pattern 0xAA");
  // Perform write access.
  if (at45dbx_write_open(Pattern))
  {
    at45dbx_write_byte(Pattern);
    at45dbx_write_close();
  }
  // Perform read access.
  if (at45dbx_read_open(Pattern))
  {
    j = at45dbx_read_byte();
    at45dbx_read_close();
  }
  // Check read and write operations.
  if (j == Pattern)
  {
    print_dbg(TEST_SUCCESS);
  }
  else
  {
    print_dbg(TEST_FAIL);
  }
}


/*! \brief Tests single-sector access functions.
 */
static void at45dbx_example_test_RAM_mem(void)
{
  static U8 PatternTable[AT45DBX_SECTOR_SIZE];
  static U8 ReceiveTable[AT45DBX_SECTOR_SIZE];

  U8 Pattern = 0x55;
  memset(PatternTable, Pattern, AT45DBX_SECTOR_SIZE);
  memset(ReceiveTable, 0xA5, AT45DBX_SECTOR_SIZE);
  print_dbg("\tUsing Pattern 0x55");
  // Perform write access.
  if (at45dbx_write_open(Pattern))
  {
    at45dbx_write_sector_from_ram(PatternTable);
    at45dbx_write_close();
  }
  // Perform read access.
  if (at45dbx_read_open(Pattern))
  {
    at45dbx_read_sector_2_ram(ReceiveTable);
    at45dbx_read_close();
  }
  // Check read and write operations.
  if (!memcmp(ReceiveTable, PatternTable, AT45DBX_SECTOR_SIZE))
  {
    print_dbg(TEST_SUCCESS);
  }
  else
  {
    print_dbg(TEST_FAIL);
  }

  // Change the pattern used.
  Pattern = 0xAA;
  memset(PatternTable, Pattern, AT45DBX_SECTOR_SIZE);
  memset(ReceiveTable, 0xA5, AT45DBX_SECTOR_SIZE);
  print_dbg("\tUsing Pattern 0xAA");
  // Perform write access.
  if (at45dbx_write_open(Pattern))
  {
    at45dbx_write_sector_from_ram(PatternTable);
    at45dbx_write_close();
  }
  // Perform read access.
  if (at45dbx_read_open(Pattern))
  {
    at45dbx_read_sector_2_ram(ReceiveTable);
    at45dbx_read_close();
  }
  // Check read and write operations.
  if (!memcmp(ReceiveTable, PatternTable, AT45DBX_SECTOR_SIZE))
  {
    print_dbg(TEST_SUCCESS);
  }
  else
  {
    print_dbg(TEST_FAIL);
  }
}


/*! \brief Tests multiple-sector access functions.
 */
static void at45dbx_example_test_multiple_sector(void)
{
  U32 position = 252;
  U32 nb_sector = 4;

  // Initialize counters.
  at45dbx_example_error_cnt = 0;

  // Write sectors.
  print_dbg("\tWriting sectors\r\n");
  at45dbx_write_open(position);
  at45dbx_write_multiple_sector(nb_sector);
  at45dbx_write_close();

  // Read written sectors.
  print_dbg("\tReading sectors\t");
  at45dbx_read_open(position);
  at45dbx_read_multiple_sector(nb_sector);
  at45dbx_read_close();

  if (!at45dbx_example_error_cnt)
  {
    print_dbg(TEST_SUCCESS);
  }
  else
  {
    print_dbg(TEST_FAIL "\t");
    print_dbg_ulong(at45dbx_example_error_cnt);
    print_dbg(" errors\r\n");
  }
}


void at45dbx_write_multiple_sector_callback(void *psector)
{
  U32 *pdata = psector;
  psector = (U8 *)psector + AT45DBX_SECTOR_SIZE;
  while ((void *)pdata < psector) *pdata++ = PATTERN_MULTIPLE_SECTOR.u32;
}


void at45dbx_read_multiple_sector_callback(const void *psector)
{
  const Union32 *pdata = psector;
  psector = (const U8 *)psector + AT45DBX_SECTOR_SIZE;
  while ((const void *)pdata < psector)
  {
    if (pdata->u32 != PATTERN_MULTIPLE_SECTOR.u32)
    {
      at45dbx_example_error_cnt += (pdata->u8[0] != PATTERN_MULTIPLE_SECTOR.u8[0]) +
                                   (pdata->u8[1] != PATTERN_MULTIPLE_SECTOR.u8[1]) +
                                   (pdata->u8[2] != PATTERN_MULTIPLE_SECTOR.u8[2]) +
                                   (pdata->u8[3] != PATTERN_MULTIPLE_SECTOR.u8[3]);
    }
    pdata++;
  }
}


/*! \brief Initializes AT45DBX resources: GPIO, SPI and AT45DBX.
 */
static void at45dbx_resources_init(void)
{
  static const gpio_map_t AT45DBX_SPI_GPIO_MAP =
  {
    {AT45DBX_SPI_SCK_PIN,          AT45DBX_SPI_SCK_FUNCTION         },  // SPI Clock.
    {AT45DBX_SPI_MISO_PIN,         AT45DBX_SPI_MISO_FUNCTION        },  // MISO.
    {AT45DBX_SPI_MOSI_PIN,         AT45DBX_SPI_MOSI_FUNCTION        },  // MOSI.
#define AT45DBX_ENABLE_NPCS_PIN(NPCS, unused) \
    {AT45DBX_SPI_NPCS##NPCS##_PIN, AT45DBX_SPI_NPCS##NPCS##_FUNCTION},  // Chip Select NPCS.
    MREPEAT(AT45DBX_MEM_CNT, AT45DBX_ENABLE_NPCS_PIN, ~)
#undef AT45DBX_ENABLE_NPCS_PIN
  };

  // SPI options.
  spi_options_t spiOptions =
  {
    .reg          = AT45DBX_SPI_FIRST_NPCS,   // Defined in conf_at45dbx.h.
    .baudrate     = AT45DBX_SPI_MASTER_SPEED, // Defined in conf_at45dbx.h.
    .bits         = AT45DBX_SPI_BITS,         // Defined in conf_at45dbx.h.
    .spck_delay   = 0,
    .trans_delay  = 0,
    .stay_act     = 1,
    .spi_mode     = 0,
    .modfdis      = 1
  };

  // Assign I/Os to SPI.
  gpio_enable_module(AT45DBX_SPI_GPIO_MAP,
                     sizeof(AT45DBX_SPI_GPIO_MAP) / sizeof(AT45DBX_SPI_GPIO_MAP[0]));

  // Initialize as master.
  spi_initMaster(AT45DBX_SPI, &spiOptions);

  // Set selection mode: variable_ps, pcs_decode, delay.
  spi_selectionMode(AT45DBX_SPI, 0, 0, 0);

  // Enable SPI.
  spi_enable(AT45DBX_SPI);

  // Initialize data flash with SPI clock Osc0.
  at45dbx_init(spiOptions, EXAMPLE_TARGET_PBACLK_FREQ_HZ);
}


#if BOARD == UC3L_EK
/*! \name Parameters to pcl_configure_clocks().
 */
//! @{
static scif_gclk_opt_t gc_dfllif_ref_opt = { SCIF_GCCTRL_SLOWCLOCK, 0, false};
static pcl_freq_param_t pcl_dfll_freq_param =
{
  .main_clk_src = PCL_MC_DFLL0,
  .cpu_f        = EXAMPLE_TARGET_MCUCLK_FREQ_HZ,
  .pba_f        = EXAMPLE_TARGET_PBACLK_FREQ_HZ,
  .pbb_f        = EXAMPLE_TARGET_PBACLK_FREQ_HZ,
  .dfll_f       = EXAMPLE_TARGET_DFLL_FREQ_HZ,
  .pextra_params = &gc_dfllif_ref_opt
};
//! @}
#endif

/*! \brief Main function. Execution starts here.
 */
int main(void)
{

#if BOARD == UC3L_EK
  // Note: on the AT32UC3L-EK board, there is no crystal/external clock connected
  // to the OSC0 pinout XIN0/XOUT0. We shall then program the DFLL and switch the
  // main clock source to the DFLL.
  pcl_configure_clocks(&pcl_dfll_freq_param);
  // Note: since it is dynamically computing the appropriate field values of the
  // configuration registers from the parameters structure, this function is not
  // optimal in terms of code size. For a code size optimal solution, it is better
  // to create a new function from pcl_configure_clocks_dfll0() and modify it
  // to use preprocessor computation from pre-defined target frequencies.
#else
  // Configure Osc0 in crystal mode (i.e. use of an external crystal source, with
  // frequency FOSC0) with an appropriate startup time then switch the main clock
  // source to Osc0.
  pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
#endif

  // Initialize RS232 debug text output.
  init_dbg_rs232(EXAMPLE_TARGET_PBACLK_FREQ_HZ);
  print_dbg(MSG_WELCOME);

  // Initialize AT45DBX resources: GPIO, SPI and AT45DBX.
  at45dbx_resources_init();

  // Perform a memory check on all DFs.
  print_dbg("Entering Memory Check:\r\n");
  at45dbx_example_check_mem();

  // Test single-byte access functions.
  print_dbg("Entering Memory Test (Byte Access):\r\n");
  at45dbx_example_test_byte_mem();

  // Test single-sector access functions.
  print_dbg("Entering Memory Test (RAM Access):\r\n");
  at45dbx_example_test_RAM_mem();

  // Test multiple-sector access functions.
  print_dbg("Entering Multiple Sector Test:\r\n");
  at45dbx_example_test_multiple_sector();

  print_dbg(MSG_GOODBYE);
  while (true);
}
