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

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_sysmpu.h"

#include "clock_config.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define CPU_REG_NVIC_SHCSR (*((uint32_t *)(0xE000ED24U)))
#define CPU_REG_NVIC_SHCSR_BUSFAULTENA (0x00020000U)
#define CPU_REG_SCnSCB_ACTLR (*((uint32_t *)(0xE000E008U)))
#define CPU_REG_SCnSCB_ACTLR_DISDEFWBUF (0x00000002U)

/* Region actual end/start address is computed by the following equation. */
#define ACTUAL_REGION_END_ADDR(x) ((uint32_t)(x) | (0x1FU))
#define ACTUAL_REGION_START_ADDR(x) ((uint32_t)(x) & (~0x1FU))
#define SYSMPU_EXAMPLE_TEST_SIZE      (20U)
#define SYSMPU_FAULTHAND_TIMEOUT       (0x100U)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile bool g_busFaultFlag = false;
#if defined(SYSMPU_EXAMPLE_TEST_ADDRESS)
volatile uint32_t *regionArray = (uint32_t *)SYSMPU_EXAMPLE_TEST_ADDRESS;
#else
volatile uint32_t regionArray[SYSMPU_EXAMPLE_TEST_SIZE];
#endif
uint32_t g_count = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief The function is used to enable bus fault
 */
void EnableBusFaultIrq(void)
{
    CPU_REG_NVIC_SHCSR |= CPU_REG_NVIC_SHCSR_BUSFAULTENA;
}

/*!
 * @brief The function is used to disable write buffer
 */
void DisableWritebuffer(void)
{
    CPU_REG_SCnSCB_ACTLR |= CPU_REG_SCnSCB_ACTLR_DISDEFWBUF;
}

/*!
 * @brief BusFault IRQ Handler
 */
#if defined(KM34Z7_SERIES) || defined(KL81Z7_SERIES) || defined(KL82Z7_SERIES)
void HardFault_Handler(void)
#else
void BusFault_Handler(void)
#endif
{
    sysmpu_rwxrights_master_access_control_t accessRights =
    {
        kSYSMPU_SupervisorEqualToUsermode,
        kSYSMPU_UserReadWriteExecute,
#if FSL_FEATURE_SYSMPU_HAS_PROCESS_IDENTIFIER
        false,
#endif
    };

    /* RegionArray is not updated. */
    PRINTF("\r\nCore access violation and generate busfault.\r\n");
    PRINTF("\r\nRegionArray[%d] = %d, not updated.\r\n", g_count, regionArray[g_count]);


    /* Reset master access rights to r/w/x. */
    SYSMPU_SetRegionRwxMasterAccessRights(SYSMPU, 0, 0, &accessRights);

    PRINTF("\r\nCore is granted write access permission.\r\n");
    g_busFaultFlag = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    sysmpu_hardware_info_t hardwareInform;
    sysmpu_config_t userConfig0;
    sysmpu_config_t userConfig1;
    sysmpu_config_t userConfig2;

    /* Initialize the configure structure. */
    memset((void *)&userConfig0, 0, sizeof(sysmpu_config_t));
    memset((void *)&userConfig1, 0, sizeof(sysmpu_config_t));
    memset((void *)&userConfig2, 0, sizeof(sysmpu_config_t));

    /* Initialize the region 1, region 3, master 0 -  core access rights supervisior r/w/x , user r/w/x. */
    sysmpu_rwxrights_master_access_control_t right1 =
    {
        kSYSMPU_SupervisorEqualToUsermode,
        kSYSMPU_UserReadWriteExecute,
#if FSL_FEATURE_SYSMPU_HAS_PROCESS_IDENTIFIER
        false,
#endif /* FSL_FEATURE_SYSMPU_HAS_PROCESS_IDENTIFIER */
    };
    /* Initialize the region 2, master 0 -  core access rights supervisior r/x , user no access. */
    sysmpu_rwxrights_master_access_control_t right2 =
    {
        kSYSMPU_SupervisorReadExecute,
        kSYSMPU_UserNoAccessRights,
#if FSL_FEATURE_SYSMPU_HAS_PROCESS_IDENTIFIER
        false,
#endif /* FSL_FEATURE_SYSMPU_HAS_PROCESS_IDENTIFIER */
    };

    userConfig0.regionConfig.regionNum = 1;                /*!< SYSMPU region number 1. */
    userConfig0.regionConfig.startAddress = 0;             /*!< Memory region start address. */
    userConfig0.regionConfig.endAddress =
        ACTUAL_REGION_START_ADDR((uint32_t)&regionArray[0]) - 0x1; /*!< Memory region end address. */
    userConfig0.regionConfig.accessRights1[0] = right1;            /*!< Low masters access permission. master 0. */
    userConfig0.next = &userConfig1;

    userConfig1.regionConfig.regionNum = 2;                  /*!< SYSMPU region number 2. */
    userConfig1.regionConfig.startAddress =
        ACTUAL_REGION_START_ADDR((uint32_t)&regionArray[0]); /*!< Memory region start address. */
    userConfig1.regionConfig.endAddress =
        ACTUAL_REGION_END_ADDR((uint32_t)&regionArray[SYSMPU_EXAMPLE_TEST_SIZE - 1]); /*!< Memory region end address. */
    userConfig1.regionConfig.accessRights1[0] = right2; /*!< Low masters access permission. master 0. */
    userConfig1.next = &userConfig2;

    userConfig2.regionConfig.regionNum = 3;             /*!< SYSMPU region number 3. */
    userConfig2.regionConfig.startAddress =
        ACTUAL_REGION_START_ADDR(userConfig1.regionConfig.endAddress + 1); /*!< Memory region start address. */
    userConfig2.regionConfig.endAddress = 0xFFFFFFFFU; /*!< Memory region end address. */
    userConfig2.regionConfig.accessRights1[0] = right1; /*!< Low masters access permission. master 0. */
    userConfig2.next = NULL;

    /* Hardware Initialization. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

#if defined(KV58F24_SERIES) || defined(KV56F24_SERIES)
    SCB_DisableDCache();
#else
    /* Disable write buffer. */
    DisableWritebuffer();
#endif

    /* Enable bus fault. */
    EnableBusFaultIrq();

    /* SYSMPU Initialization. */
    SYSMPU_Init(SYSMPU, &userConfig0);
    PRINTF("\r\nSYSMPU Example Start.\r\n");

    /* Get Hardware information. */
    SYSMPU_GetHardwareInfo(SYSMPU, &hardwareInform);
    PRINTF("\r\nSYSMPU revision level %d, %d slave ports and %d region numbers are supported.\r\n",
           hardwareInform.hardwareRevisionLevel, hardwareInform.slavePortsNumbers,
           (hardwareInform.regionsNumbers * 4 + 8));

    /* The accesses are all opened after initialize. */
    for (uint32_t i = 0; i < SYSMPU_EXAMPLE_TEST_SIZE; i++)
    {
        regionArray[i] = 0;
    }

    while (1)
    {
        PRINTF("\r\nSet regionArray0 to un-writeable.\r\n");

        /* Remove Core write permission in region 0. */
        SYSMPU_SetRegionRwxMasterAccessRights(SYSMPU, 0, 0, &right2);
        
        PRINTF("\r\nWrite %d to regionArray at No.%d.\r\n", g_count, g_count);
        /* Cannot write here, bus fault occur. */
        regionArray[g_count] = g_count;

        /* ISB to make sure the instruction execute sequence. */
        __ISB();
 
        /* Add delay to avoid the check instruction to be done during the bus fault handler response period. */
        for (volatile uint32_t i = 0; i < SYSMPU_FAULTHAND_TIMEOUT; i++)
        {
            __NOP();
        }

        if (false == g_busFaultFlag)
        {
            /* Error occur. */
            PRINTF("\r\nERROR: Cannot protect regionArray.\r\n");
        }
        else
        {
            sysmpu_access_err_info_t inform;
            /* Get the error information. */
            for (uint32_t count = kSYSMPU_Slave0; count < FSL_FEATURE_SYSMPU_SLAVE_COUNT; count++)
            {
                if (SYSMPU_GetSlavePortErrorStatus(SYSMPU, (sysmpu_slave_t)count))
                {
                    SYSMPU_GetDetailErrorAccessInfo(SYSMPU, (sysmpu_slave_t)count, &inform);
                    PRINTF("\r\nError access happen on slave port: %d, access master port %d.\r\n", count,
                           inform.master);
                    PRINTF("\r\nError access attributes: %s.\r\n",
                           inform.attributes ?
                               ((inform.accessControl - 1) ? "accessSupervisorMode" : "accessUserMode") :
                               "accessUserMode");
                    PRINTF("\r\nError access type: %s.\r\n", inform.accessType ? "write" : "read");
                    PRINTF("\r\nError access control: %s.\r\n",
                           inform.accessControl ?
                               ((inform.accessControl - 1) ? "overlappRegion" : "noneOverLappRegion") :
                               "noRegionHit");
                    PRINTF("\r\nError access address: 0x%x.\r\n", inform.address);
                }
            }
            
            /* Update again. */
            regionArray[g_count] = g_count;

            /* Bus fault occurs, regionArray is updated. */
            PRINTF("\r\nRegionArray[%d] = %d, updated now.\r\n", g_count, regionArray[g_count]);
            PRINTF("\r\nProtected regionArray successfully.\r\n");
            
            g_busFaultFlag = false;
        }


        /* Clear regionArray. */
        /*regionArray[g_count] = 0;*/

        PRINTF("\r\nPress any key to continue.\r\n");
        GETCHAR();
        if (++g_count == SYSMPU_EXAMPLE_TEST_SIZE)
        {
            g_count = 0;
        }
    }
}
