/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_crc.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
* @brief Init for CRC-16-CCIT.
* @details Init CRC peripheral module for CRC-16/CCIT-FALSE protocol:
*          width=16 poly=0x1021 init=0xffff refin=false refout=false xorout=0x0000 check=0x29b1
*          http://reveng.sourceforge.net/crc-catalogue/
* name="CRC-16/CCITT-FALSE"
*/
static void InitCrc16_CcitFalse(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    /*
     * config.polynomial = 0x1021;
     * config.seed = 0xFFFF;
     * config.reflectIn = false;
     * config.reflectOut = false;
     * config.complementChecksum = false;
     * config.crcBits = kCrcBits16;
     * config.crcResult = kCrcFinalChecksum;
     */
    CRC_GetDefaultConfig(&config);
    config.seed = seed;
    CRC_Init(base, &config);
}

/*!
 * @brief Init for CRC-16/MAXIM.
 * @details Init CRC peripheral module for CRC-16/MAXIM protocol.
 *          width=16 poly=0x8005 init=0x0000 refin=true refout=true xorout=0xffff check=0x44c2 name="CRC-16/MAXIM"
 *          http://reveng.sourceforge.net/crc-catalogue/
 */
static void InitCrc16(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial = 0x8005;
    config.seed = seed;
    config.reflectIn = true;
    config.reflectOut = true;
    config.complementChecksum = true;
    config.crcBits = kCrcBits16;
    config.crcResult = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

/*!
 * @brief Init for CRC-16/KERMIT.
 * @details Init CRC peripheral module for CRC-16/KERMIT protocol.
 *          width=16 poly=0x1021 init=0x0000 refin=true refout=true xorout=0x0000 check=0x2189 name="KERMIT"
 *          http://reveng.sourceforge.net/crc-catalogue/
 */
static void InitCrc16_Kermit(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial = 0x1021;
    config.seed = seed;
    config.reflectIn = true;
    config.reflectOut = true;
    config.complementChecksum = false;
    config.crcBits = kCrcBits16;
    config.crcResult = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

/*!
 * @brief Init for CRC-32.
 * @details Init CRC peripheral module for CRC-32 protocol.
 *          width=32 poly=0x04c11db7 init=0xffffffff refin=true refout=true xorout=0xffffffff check=0xcbf43926
 *          name="CRC-32"
 *          http://reveng.sourceforge.net/crc-catalogue/
 */
static void InitCrc32(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial = 0x04C11DB7U;
    config.seed = seed;
    config.reflectIn = true;
    config.reflectOut = true;
    config.complementChecksum = true;
    config.crcBits = kCrcBits32;
    config.crcResult = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

/*!
 * @brief Init for CRC-32/POSIX.
 * @details Init CRC peripheral module for CRC-32/POSIX protocol.
 *          width=32 poly=0x04c11db7 init=0x00000000 refin=false refout=false xorout=0xffffffff check=0x765e7680
 *          name="CRC-32/POSIX"
 *          http://reveng.sourceforge.net/crc-catalogue/
 */
static void InitCrc32_Posix(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    config.polynomial = 0x04c11db7u;
    config.seed = seed;
    config.reflectIn = false;
    config.reflectOut = false;
    config.complementChecksum = true;
    config.crcBits = kCrcBits32;
    config.crcResult = kCrcFinalChecksum;

    CRC_Init(base, &config);
}

/*!
 * @brief Main function
 */
int main(void)
{
    char testData[] = "123456789";
    const uint16_t checkCcitFalseCrc16 = 0x29b1u;
    const uint16_t checkMaximCrc16 = 0x44c2u;
    const uint16_t checkKermitCrc16 = 0x2189u;
    const uint32_t checkCrc32 = 0xcbf43926u;
    const uint32_t checkPosixCrc32 = 0x765e7680u;

    CRC_Type *base = CRC0;
    uint16_t checksum16;
    uint32_t checksum32;

    /* Init hardware*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("CRC Peripheral Driver Example\r\n\r\n");

    /* ***************
    * CRC-16/CCIT-FALSE *
    *************** */
    InitCrc16_CcitFalse(base, 0xFFFFU);
    CRC_WriteData(base, (uint8_t *)&testData[0], sizeof(testData) - 1);
    checksum16 = CRC_Get16bitResult(base);

    PRINTF("Test string: %s\r\n", testData);
    PRINTF("CRC-16 CCIT FALSE: 0x%x\r\n", checksum16);
    if (checksum16 != checkCcitFalseCrc16)
    {
        PRINTF("...Check fail. Expected: 0x%x\r\n", checkCcitFalseCrc16);
    }

    /* ***************
    * CRC-16/MAXIM *
    *************** */
    InitCrc16(base, 0x0U);
    CRC_WriteData(base, (uint8_t *)&testData[0], sizeof(testData) - 1);
    checksum16 = CRC_Get16bitResult(base);

    PRINTF("CRC-16 MAXIM: 0x%x\r\n", checksum16);
    if (checksum16 != checkMaximCrc16)
    {
        PRINTF("...Check fail. Expected: 0x%x\r\n", checkMaximCrc16);
    }

    /* ***************
    * CRC-16 KERMIT *
    *************** */
    InitCrc16_Kermit(base, 0x0U);
    CRC_WriteData(base, (uint8_t *)&testData[0], sizeof(testData) - 1);
    checksum16 = CRC_Get16bitResult(base);

    PRINTF("CRC-16 KERMIT: 0x%x\r\n", checksum16);
    if (checksum16 != checkKermitCrc16)
    {
        PRINTF("...Check fail. Expected: 0x%x\r\n", checkKermitCrc16);
    }

    /* ***************
    * CRC-32 *
    *************** */
    InitCrc32(base, 0xFFFFFFFFU);
    CRC_WriteData(base, (uint8_t *)&testData[0], sizeof(testData) - 1);
    checksum32 = CRC_Get32bitResult(base);

    PRINTF("CRC-32: 0x%x\r\n", checksum32);
    if (checksum32 != checkCrc32)
    {
        PRINTF("...Check fail. Expected: 0x%x\r\n", checkCrc32);
    }

    /* ***************
    * CRC-32/POSIX *
    *************** */
    InitCrc32_Posix(base, 0);
    CRC_WriteData(base, (uint8_t *)&testData[0], sizeof(testData) - 1);
    checksum32 = CRC_Get32bitResult(base);

    PRINTF("CRC-32 POSIX: 0x%x\r\n", checksum32);
    if (checksum32 != checkPosixCrc32)
    {
        PRINTF("...Check fail. Expected: 0x%x\r\n", checkPosixCrc32);
    }

    while (1)
    {
    }
}
