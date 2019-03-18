/**
 * \file
 *
 * \brief Instance description for AES
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAML22_AES_INSTANCE_
#define _SAML22_AES_INSTANCE_

/* ========== Register definition for AES peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_AES_CTRLA              (0x42004000U) /**< \brief (AES) Control A */
#define REG_AES_CTRLB              (0x42004004U) /**< \brief (AES) Control B */
#define REG_AES_INTENCLR           (0x42004005U) /**< \brief (AES) Interrupt Enable Clear */
#define REG_AES_INTENSET           (0x42004006U) /**< \brief (AES) Interrupt Enable Set */
#define REG_AES_INTFLAG            (0x42004007U) /**< \brief (AES) Interrupt Flag Status */
#define REG_AES_DATABUFPTR         (0x42004008U) /**< \brief (AES) Data buffer pointer */
#define REG_AES_DBGCTRL            (0x42004009U) /**< \brief (AES) Debug control */
#define REG_AES_KEYWORD0           (0x4200400CU) /**< \brief (AES) Keyword 0 */
#define REG_AES_KEYWORD1           (0x42004010U) /**< \brief (AES) Keyword 1 */
#define REG_AES_KEYWORD2           (0x42004014U) /**< \brief (AES) Keyword 2 */
#define REG_AES_KEYWORD3           (0x42004018U) /**< \brief (AES) Keyword 3 */
#define REG_AES_KEYWORD4           (0x4200401CU) /**< \brief (AES) Keyword 4 */
#define REG_AES_KEYWORD5           (0x42004020U) /**< \brief (AES) Keyword 5 */
#define REG_AES_KEYWORD6           (0x42004024U) /**< \brief (AES) Keyword 6 */
#define REG_AES_KEYWORD7           (0x42004028U) /**< \brief (AES) Keyword 7 */
#define REG_AES_INDATA             (0x42004038U) /**< \brief (AES) Indata */
#define REG_AES_INTVECTV0          (0x4200403CU) /**< \brief (AES) Initialisation Vector 0 */
#define REG_AES_INTVECTV1          (0x42004040U) /**< \brief (AES) Initialisation Vector 1 */
#define REG_AES_INTVECTV2          (0x42004044U) /**< \brief (AES) Initialisation Vector 2 */
#define REG_AES_INTVECTV3          (0x42004048U) /**< \brief (AES) Initialisation Vector 3 */
#define REG_AES_HASHKEY0           (0x4200405CU) /**< \brief (AES) Hash key 0 */
#define REG_AES_HASHKEY1           (0x42004060U) /**< \brief (AES) Hash key 1 */
#define REG_AES_HASHKEY2           (0x42004064U) /**< \brief (AES) Hash key 2 */
#define REG_AES_HASHKEY3           (0x42004068U) /**< \brief (AES) Hash key 3 */
#define REG_AES_GHASH0             (0x4200406CU) /**< \brief (AES) Galois Hash 0 */
#define REG_AES_GHASH1             (0x42004070U) /**< \brief (AES) Galois Hash 1 */
#define REG_AES_GHASH2             (0x42004074U) /**< \brief (AES) Galois Hash 2 */
#define REG_AES_GHASH3             (0x42004078U) /**< \brief (AES) Galois Hash 3 */
#define REG_AES_CIPLEN             (0x42004080U) /**< \brief (AES) Cipher Length */
#define REG_AES_RANDSEED           (0x42004084U) /**< \brief (AES) Random Seed */
#else
#define REG_AES_CTRLA              (*(RwReg  *)0x42004000U) /**< \brief (AES) Control A */
#define REG_AES_CTRLB              (*(RwReg8 *)0x42004004U) /**< \brief (AES) Control B */
#define REG_AES_INTENCLR           (*(RwReg8 *)0x42004005U) /**< \brief (AES) Interrupt Enable Clear */
#define REG_AES_INTENSET           (*(RwReg8 *)0x42004006U) /**< \brief (AES) Interrupt Enable Set */
#define REG_AES_INTFLAG            (*(RwReg8 *)0x42004007U) /**< \brief (AES) Interrupt Flag Status */
#define REG_AES_DATABUFPTR         (*(RwReg8 *)0x42004008U) /**< \brief (AES) Data buffer pointer */
#define REG_AES_DBGCTRL            (*(WoReg8 *)0x42004009U) /**< \brief (AES) Debug control */
#define REG_AES_KEYWORD0           (*(WoReg  *)0x4200400CU) /**< \brief (AES) Keyword 0 */
#define REG_AES_KEYWORD1           (*(WoReg  *)0x42004010U) /**< \brief (AES) Keyword 1 */
#define REG_AES_KEYWORD2           (*(WoReg  *)0x42004014U) /**< \brief (AES) Keyword 2 */
#define REG_AES_KEYWORD3           (*(WoReg  *)0x42004018U) /**< \brief (AES) Keyword 3 */
#define REG_AES_KEYWORD4           (*(WoReg  *)0x4200401CU) /**< \brief (AES) Keyword 4 */
#define REG_AES_KEYWORD5           (*(WoReg  *)0x42004020U) /**< \brief (AES) Keyword 5 */
#define REG_AES_KEYWORD6           (*(WoReg  *)0x42004024U) /**< \brief (AES) Keyword 6 */
#define REG_AES_KEYWORD7           (*(WoReg  *)0x42004028U) /**< \brief (AES) Keyword 7 */
#define REG_AES_INDATA             (*(RwReg  *)0x42004038U) /**< \brief (AES) Indata */
#define REG_AES_INTVECTV0          (*(WoReg  *)0x4200403CU) /**< \brief (AES) Initialisation Vector 0 */
#define REG_AES_INTVECTV1          (*(WoReg  *)0x42004040U) /**< \brief (AES) Initialisation Vector 1 */
#define REG_AES_INTVECTV2          (*(WoReg  *)0x42004044U) /**< \brief (AES) Initialisation Vector 2 */
#define REG_AES_INTVECTV3          (*(WoReg  *)0x42004048U) /**< \brief (AES) Initialisation Vector 3 */
#define REG_AES_HASHKEY0           (*(RwReg  *)0x4200405CU) /**< \brief (AES) Hash key 0 */
#define REG_AES_HASHKEY1           (*(RwReg  *)0x42004060U) /**< \brief (AES) Hash key 1 */
#define REG_AES_HASHKEY2           (*(RwReg  *)0x42004064U) /**< \brief (AES) Hash key 2 */
#define REG_AES_HASHKEY3           (*(RwReg  *)0x42004068U) /**< \brief (AES) Hash key 3 */
#define REG_AES_GHASH0             (*(RwReg  *)0x4200406CU) /**< \brief (AES) Galois Hash 0 */
#define REG_AES_GHASH1             (*(RwReg  *)0x42004070U) /**< \brief (AES) Galois Hash 1 */
#define REG_AES_GHASH2             (*(RwReg  *)0x42004074U) /**< \brief (AES) Galois Hash 2 */
#define REG_AES_GHASH3             (*(RwReg  *)0x42004078U) /**< \brief (AES) Galois Hash 3 */
#define REG_AES_CIPLEN             (*(RwReg  *)0x42004080U) /**< \brief (AES) Cipher Length */
#define REG_AES_RANDSEED           (*(RwReg  *)0x42004084U) /**< \brief (AES) Random Seed */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for AES peripheral ========== */
#define AES_DMAC_ID_RD              36       // DMA DATA Read trigger
#define AES_DMAC_ID_WR              35       // DMA DATA Write trigger

#endif /* _SAML22_AES_INSTANCE_ */
