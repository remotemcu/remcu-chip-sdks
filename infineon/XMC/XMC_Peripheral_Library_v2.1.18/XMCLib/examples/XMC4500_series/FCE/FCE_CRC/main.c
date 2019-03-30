/* =========================================================================== *
 * Copyright (c) 2014, Infineon Technologies AG                                *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 * Redistributions of source code must retain the above copyright notice, this *
 * list of conditions and the following disclaimer. Redistributions in binary  *
 * form must reproduce the above copyright notice, this list of conditions and *
 * the following disclaimer in the documentation and/or other materials        *
 * provided with the distribution. Neither the name of the copyright holders   *
 * nor the names of its contributors may be used to endorse or promote         *
 * products derived from this software without specific prior written          *
 * permission.                                                                 *
 *                                                                                                                                                                                                                                                                                                                   *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       *
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      *
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR           *
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       *
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         *
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; *
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    *
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     *
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF      *
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                  *
 * To improve the quality of the software, users are encouraged to share       *
 * modifications, enhancements or bug fixes with                               *
 * Infineon Technologies AG (dave@infineon.com).                               *
 *                                                                             *
 * ========================================================================== */

/*******************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000 Series      		                              **
**                                                                            **
** AUTHOR : Application Engineering Team                                      **
**                                            	                              **
** Project version update to  v 1.0.0  Initial Version  	                  **
** 							  v 1.0.1  Updated with error status check		  **																			  **
**																			  **
** MODIFICATION DATE : Sep 05, 2014                                           **
**                                                                            **
*******************************************************************************/
/*
 *  file : XMC4_FCE_Example1
 *  brief : This example uses the XMC_FCE Low Level Driver to perform
 *  		CRC8, CRC16 and CRC32 operation
 */

#include <xmc_fce.h>

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/
/*Data Packet 1 */
int8_t usecase1_Data1[] = "Lorem ipsum dolor sit amet, ";
/*Data Packet 2 */
int8_t usecase1_Data2[] = "consectetur adipiscing elit. Donec metus eros, a";
/*Data Packet 3 */
int8_t usecase1_Data3[] = "ccumsan ut vestibulum id, suscipit nec augue. Aenean et lectus ut libero lacinia faucibus ut vel lectus. Pellentesque iaculis libero ac lectus blandit accumsan. Pellentesque at nulla eget metus aliquam tincidunt. Aenean cursus purus vitae lacus cursus pharetra. In hac habitasse platea dictumst. Curabitur nulla odio, porttitor eu pharetra at, pulvinar gravida velit. Aenean eu dapibus purus. Proin blandit feugiat urna, at iaculis elit accumsan ut. Pellentesque molestie pharetra erat, eget semper urna vehicula nec. Nam tristique sollicitudin diam, faucibus aliquet velit pharetra a. Duis a placerat risus. Phasellus vel diam nibh, quis elementum nisl. Phasellus lectus quam, mollis eu consequat ut, bibendum eget arcu. Nullam at felis a elit auctor suscipit eu quis ipsum. Mauris luctus, diam sit amet iaculis malesuada, urna orci convallis tellus, vitae molestie diam justo sed metus. Etiam volutpat volutpat justo, vel facilisis mi eleifend ut. Aenean egestas, sem eu vulputate lacinia, odio ligula mollis risus, a semper eros risus sed arcu. Sed feugiat augue eget erat bibendum vitae consequat purus tempus. Morbi lobortis nunc eget ligula vehicula non pharetra dolor commodo. Pellentesque ligula nibh, eleifend blandit aliquam vel, euismod non tellus. Quisque dictum laoreet feugiat. Maecenas a varius sapien. Ut semper nulla id turpis cursus ornare. Nullam quis erat et augue imperdiet pharetra nec a sem. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aenean feugiat, orci ultricies pellentesque viverra, nisl elit molestie augue, et scelerisque risus felis nec nulla. Maecenas congue arcu ac lectus bibendum at lacinia elit tristique. Cras fringilla vestibulum lectus. Praesent quis nisi turpis, sed tristique sem. Nam adipiscing posuere faucibus. In iaculis placerat semper. Curabitur in nunc quis enim vehicula aliquam quis at sapien. In hac habitasse platea orci aliquam...";

/* FCE configuration for CRC32 operation using Kernal 0
 * Algorithm: IR Byte Wise Reflection disabled
 * 			: CRC 32-Bit Wise Reflection disabled
 *          : XOR with final CRC enabled
 * Initial seedvalue: 0U
 */
XMC_FCE_t FCE_config0 =
{
  .kernel_ptr 	 = XMC_FCE_CRC32_0,    /**< FCE Kernel Pointer */
  .fce_cfg_update.config_refin = XMC_FCE_REFIN_RESET,
  .fce_cfg_update.config_refout = XMC_FCE_REFOUT_RESET,
  .fce_cfg_update.config_xsel = XMC_FCE_INVSEL_SET,
  .seedvalue	 	= 0U
};

/* FCE configuration for CRC32 operation using Kernal 1
 * Algorithm: IR Byte Wise Reflection disabled
 * 			: CRC 32-Bit Wise Reflection disabled
 *          : XOR with final CRC disabled
 * Initial seedvalue: 0U
 */
XMC_FCE_t FCE_config1 =
{
  .kernel_ptr 	 = XMC_FCE_CRC32_1,    /**< FCE Kernel Pointer */
  .fce_cfg_update.config_refin = XMC_FCE_REFIN_RESET,
  .fce_cfg_update.config_refout = XMC_FCE_REFOUT_RESET,
  .fce_cfg_update.config_xsel = XMC_FCE_INVSEL_RESET,
  .seedvalue	 = 0U
};

/* FCE configuration for CRC16 operation using Kernal 2
 * Algorithm: IR Byte Wise Reflection enabled
 * 			: CRC 32-Bit Wise Reflection disabled
 *          : XOR with final CRC disabled
 * Initial seedvalue: 0U
 */
XMC_FCE_t FCE_config2 =
{
  .kernel_ptr 	 = XMC_FCE_CRC16,    /**< FCE Kernel Pointer */
  .fce_cfg_update.config_refin = XMC_FCE_REFIN_SET,
  .fce_cfg_update.config_refout = XMC_FCE_REFOUT_RESET,
  .fce_cfg_update.config_xsel = XMC_FCE_INVSEL_RESET,
  .seedvalue	 = 0U
};

/* FCE configuration for CRC8 operation using Kernal 3
 * Algorithm: IR Byte Wise Reflection disabled
 * 			: CRC 32-Bit Wise Reflection disabled
 *          : XOR with final CRC disabled
 * Initial seedvalue: 0U
 */
XMC_FCE_t FCE_config3 =
{
  .kernel_ptr 	 = XMC_FCE_CRC8,    /**< FCE Kernel Pointer */
  .fce_cfg_update.config_refin = XMC_FCE_REFIN_RESET,
  .fce_cfg_update.config_refout = XMC_FCE_REFOUT_RESET,
  .fce_cfg_update.config_xsel = XMC_FCE_INVSEL_RESET,
  .seedvalue	 = 0U
};

/*********************************************************************************************************************
 * MAIN APPLICATION
 ********************************************************************************************************************/

int main(void)
{
	uint32_t Read_CRCResult32;
	uint16_t Read_CRCResult16;
	uint8_t  Read_CRCResult8;
	uint32_t temp_length;
	uint32_t temp_mismatch;
	uint32_t CRC_result;
	bool flagstatus;
	XMC_FCE_STATUS_t fce_status;

	/* Enable FCE module */
	XMC_FCE_Enable();

	/* Initialize the FCE Configuration */
	XMC_FCE_Init(&FCE_config0);
	XMC_FCE_Init(&FCE_config1);
	XMC_FCE_Init(&FCE_config2);
	XMC_FCE_Init(&FCE_config3);

	/* Initialize error counter*/
	temp_mismatch = 0;

	/* Step 1: Performs a CRC32 check using Kernel 0 on Usecase1_Data1
	 * Seed value is set to 0.
	 * => CRC = 0xbb8d49a6, RES = 0x4472b659
	 */
	XMC_FCE_InitializeSeedValue(&FCE_config0, 0);
	fce_status = XMC_FCE_CalculateCRC32(&FCE_config0, (uint32_t *) usecase1_Data1, strlen((const char *)(usecase1_Data1)), &Read_CRCResult32);
	while(fce_status== XMC_FCE_STATUS_ERROR)
	{
		/* endless loop if error */
	}
	XMC_FCE_GetCRCResult(&FCE_config0, &CRC_result);

	/* Step 2: Performs a CRC32 check using Kernel 1 on Usecase1_Data1
	 * Seed value is set to 0. CRC check comparison is enabled
	 * CRC checksum is using result from earlier CRC check
	 * No CRC mismatch found.
	 * CRC = 0xbb8d49a6, RES = 0xbb8d49a6
	 */
	XMC_FCE_EnableOperation(&FCE_config1,XMC_FCE_CFG_CONFIG_CCE);

	/* Used in 32bit FCE, therefore temp_length is divided by 4*/
	temp_length = (strlen((char *)(usecase1_Data1)))>>2;
	XMC_FCE_UpdateCRCCheck(&FCE_config1, Read_CRCResult32);
	XMC_FCE_UpdateLength(&FCE_config1, temp_length);

	XMC_FCE_InitializeSeedValue(&FCE_config1, 0);
	fce_status = XMC_FCE_CalculateCRC32(&FCE_config1, (uint32_t *) usecase1_Data1, strlen((const char *)(usecase1_Data1)), &Read_CRCResult32);
	while(fce_status== XMC_FCE_STATUS_ERROR)
	{
		/* endless loop if error */
	}

	XMC_FCE_GetCRCResult(&FCE_config1, &CRC_result);
	if(XMC_FCE_GetEventStatus(&FCE_config1,XMC_FCE_STS_MISMATCH_CRC))
	{
		temp_mismatch += 1U;
	}

	/* Step 3: Performs a CRC32 check using Kernel 1 on Usecase1_Data2
	 * Seed value is set to 0. CRC check comparison is enabled
	 * CRC checksum is using result from earlier CRC check
	 * CRC mismatch found and Length Error found.
	 * CRC = 0x8f2d7440, RES = 0x8f2d7440
	 */
	XMC_FCE_InitializeSeedValue(&FCE_config1, 0);
	XMC_FCE_UpdateLength(&FCE_config1, temp_length);

	fce_status = XMC_FCE_CalculateCRC32(&FCE_config1, (uint32_t *) usecase1_Data2, strlen((const char *)(usecase1_Data2)), &Read_CRCResult32);
	while(fce_status== XMC_FCE_STATUS_ERROR)
	{
		/* endless loop if error */
	}

	XMC_FCE_GetCRCResult(&FCE_config1, &CRC_result);
	if (XMC_FCE_GetEventStatus(&FCE_config1,XMC_FCE_STS_MISMATCH_CRC))
	{
		temp_mismatch += 2U;
	}

	/* Step 4: Performs a CRC16 check using Kernel 2 on Usecase1_Data3
	 * Seed value is set to 0.
	 * CRC = 0x191e, RES = 0x191e
	 */
	XMC_FCE_InitializeSeedValue(&FCE_config2, 0);
	fce_status = XMC_FCE_CalculateCRC16(&FCE_config2, (uint16_t *) usecase1_Data3, strlen((const char *)(usecase1_Data3)), &Read_CRCResult16);
	while(fce_status== XMC_FCE_STATUS_ERROR)
	{
		/* endless loop if error */
	}

	XMC_FCE_GetCRCResult(&FCE_config2, &CRC_result);

	/* Step 5: Performs a CRC8 check using Kernel 3 on Usecase1_Data4
	 * Seed value is set to 0. CRC = 0xbe, RES = 0xbe
	 */
	XMC_FCE_InitializeSeedValue(&FCE_config3, 0);
	fce_status = XMC_FCE_CalculateCRC8(&FCE_config3, (uint8_t *)usecase1_Data3, strlen((const char *)(usecase1_Data3)), &Read_CRCResult8);
	while(fce_status== XMC_FCE_STATUS_ERROR)
	{
		/* endless loop if error */
	}
	XMC_FCE_GetCRCResult(&FCE_config3, &CRC_result);

	/* Step 6: Trigger a mismatch flag
	 */
	flagstatus = XMC_FCE_GetEventStatus(&FCE_config3, XMC_FCE_STS_MISMATCH_CRC);
	while(flagstatus)
	{
		/* endless loop if mismatch flag is triggered */
	}
	XMC_FCE_TriggerMismatch(&FCE_config3, XMC_FCE_CTR_MISMATCH_CRC);
	flagstatus = XMC_FCE_GetEventStatus(&FCE_config3, XMC_FCE_STS_MISMATCH_CRC);
	while(flagstatus)
	{
		/* endless loop if mismatch flag is triggered */
	}

	while(1)
	{

	}
}
