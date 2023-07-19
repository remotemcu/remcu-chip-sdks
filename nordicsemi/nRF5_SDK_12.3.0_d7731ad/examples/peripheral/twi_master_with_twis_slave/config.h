/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/**
 * @ingroup twi_master_with_twis_slave_example
 * @defgroup twi_master_with_twis_slave_example_config Example code configuration
 *
 * Configuration for the code presenting TWIS and TWI functionality
 * @{
 */

#ifndef TWI_MASTER_WITH_TWIS_SLAVE_CONFIG_H__
#define TWI_MASTER_WITH_TWIS_SLAVE_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define UART_TX_BUF_SIZE         1024 //!< UART TX buffer size.
#define UART_RX_BUF_SIZE         32   //!< UART RX buffer size
#define EEPROM_SIM_SIZE          128  //!< Simulated EEPROM size
#define EEPROM_SIM_SEQ_WRITE_MAX 8    //!< Maximum number of bytes writable in one sequential access
#define EEPROM_SIM_ADDR          0x50 //!< Simulated EEPROM TWI address

#define TWI_SCL_M                3   //!< Master SCL pin
#define TWI_SDA_M                4   //!< Master SDA pin
#define EEPROM_SIM_SCL_S         31   //!< Slave SCL pin
#define EEPROM_SIM_SDA_S         30   //!< Slave SDA pin

#define EEPROM_SIM_TWIS_INST     1    //!< TWIS interface used by EEPROM simulator
#define MASTER_TWI_INST          0    //!< TWI interface used as a master accessing EEPROM memory

#define IN_LINE_PRINT_CNT        16  //<! Number of data bytes printed in single line

/** @} */

#ifdef __cplusplus
}
#endif

#endif // TWI_MASTER_WITH_TWIS_SLAVE_CONFIG_H__
