/** \defgroup nm_bsp BSP
 *
 * \file
 *
 * \brief This module contains WILC BSP APIs declarations.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
/**@defgroup  BSPDefine Defines
 * @ingroup nm_bsp
 * @{
 */
#ifndef _NM_BSP_H_
#define _NM_BSP_H_

#define NMI_API
/*!< 
*        Attribute used to define memory section to map Functions in host memory.
*/

#ifdef __MCF964548__
#define CONST code
#else
#define CONST const
#endif
/*!< 
*     Used for code portability.
*/

/*!
 * @typedef      void (*tpfNmBspIsr) (void);
 * @brief           Pointer to function.\n
 *                     Used as a data type of ISR function registered by \ref nm_bsp_register_isr
 * @return         None
 */
typedef void (*tpfNmBspIsr)(void);



#ifndef NULL
#define NULL ((void*)0)
#endif
/*!< 
*    Void Pointer to '0' in case of NULL is not defined. 
*/


#define BSP_MIN(x,y) ((x)>(y)?(y):(x))
/*!< 
*     Computes the minimum of \b x and \b y.
*/

 //@}

/**@defgroup  DataT  DataTypes
 * @ingroup nm_bsp
 * @{
 */
 
  /*!
 * @ingroup DataTypes
 * @typedef      unsigned char	uint8;
 * @brief        Range of values between 0 to 255
 */
typedef unsigned char	uint8;

 /*!
 * @ingroup DataTypes
 * @typedef      unsigned short	uint16;
 * @brief        Range of values between 0 to 65535
 */
typedef unsigned short	uint16;

 /*!
 * @ingroup Data Types
 * @typedef      unsigned long	uint32;
 * @brief        Range of values between 0 to 4294967295
 */ 
typedef unsigned long	uint32;


  /*!
 * @ingroup Data Types
 * @typedef      signed char		sint8;
 * @brief        Range of values between -128 to 127
 */
typedef signed char		sint8;

 /*!
 * @ingroup DataTypes
 * @typedef      signed short	sint16;
 * @brief        Range of values between -32768 to 32767
 */
typedef signed short	sint16;

  /*!
 * @ingroup DataTypes
 * @typedef      signed long		sint32;
 * @brief        Range of values between -2147483648 to 2147483647
 */

typedef signed long		sint32;
 //@}

#ifndef CORTUS_APP


#ifdef __cplusplus
extern "C"{
#endif

/** \defgroup BSPAPI Function
 *   @ingroup nm_bsp
 */


/** @defgroup NmBspInitFn nm_bsp_init
 *  @ingroup BSPAPI
 *   Initialize BSP
 */
 /**@{*/
/*!
 * @fn           sint8 nm_bsp_init(void);
 * @brief        Initialization for bsp (\e Board \e Support \e Package) such as Reset and Chip Enable Pins for WILC, delays, register ISR, enable/disable IRQ for WILC, ...etc.\n
 *                   You must use this function in the head of your application to enable WILC and Host Driver communicate each other.
 * @warning      Missing use will lead to unavailability of host communication.\n
 *  @note        Implementation of this function is host dependent.
 * @return       The function returns @ref M2M_SUCCESS for successful operations and a negative value otherwise.

 */
sint8 nm_bsp_init(void);
 /**@}*/

 
 /** @defgroup NmBspDeinitFn nm_bsp_deinit
 *    @ingroup BSPAPI
 *   	 De-initialization for bsp (\e Board \e Support \e Package)
 */
 /**@{*/
/*!
 * @fn           sint8 nm_bsp_deinit(void);
 * @pre          Initialize \ref nm_bsp_init first
 * @warning      Missing use may lead to unknown behavior in case of soft reset.\n
 * @note         Implementation of this function is host dependent.
 * @see          nm_bsp_init               
 * @return      The function returns @ref M2M_SUCCESS for successful operations and a negative value otherwise.

 */
sint8 nm_bsp_deinit(void);
 /**@}*/

 
/** @defgroup NmBspResetFn  nm_bsp_reset
*     @ingroup BSPAPI
*      Reinitialization for bsp (\e Board \e Support \e Package) by resetting NMC1500 SoC by setting \ref CHIP_EN and \ref RESET_N signals low, 
 *     \ref CHIP_EN high then \ref RESET_N high
*/
/**@{*/
 /*!
 * @fn           void nm_bsp_reset(void);
 * @brief     
 * @param [in]   None
 * @pre          Initialize \ref nm_bsp_init first
 * @note         Implementation of this function is host dependent and called by HIF layer.
 * @see          nm_bsp_init    
 * @return       None

 */
void nm_bsp_reset(void);
 /**@}*/

 
/** @defgroup NmBspSleepFn nm_bsp_sleep
*     @ingroup BSPAPI
*     Sleep in units of milliseconds.\n
*    This function used by HIF Layer according to different situations. 
*/
/**@{*/
/*!
 * @fn           void nm_bsp_sleep(uint32);
 * @brief   
 * @param [in]   u32TimeMsec
 *               Time unit in milliseconds
 * @pre          Initialize \ref nm_bsp_init first
 * @warning      Maximum value must nor exceed 4294967295 milliseconds which is equal to 4294967.295 seconds.\n
 * @note         Implementation of this function is host dependent.
 * @see           nm_bsp_init               
 * @return       None
 */
void nm_bsp_sleep(uint32 u32TimeMsec);
/**@}*/

  
/** @defgroup NmBspRegisterFn nm_bsp_register_isr
*     @ingroup BSPAPI
*   Register ISR (\e Interrupt \e Service \e Routine) in the initialization of HIF (\e Host \e Interface) Layer.
*/
/**@{*/
/*!
 * @fn           void nm_bsp_register_isr(tpfNmBspIsr);
 * @param [in]   pfIsr
 *               Pointer to ISR handler in HIF
 * @warning      Make sure that ISR for IRQ pin for WILC is disabled by default in your implementation.
 * @note         Implementation of this function is host dependent and called by HIF layer.
  * @see        tpfNmBspIsr
 * @return       None

 */
void nm_bsp_register_isr(tpfNmBspIsr pfIsr);
/**@}*/

  
/** @defgroup NmBspInterruptCtrl nm_bsp_interrupt_ctrl
*     @ingroup BSPAPI
*    Synchrnonous enable/disable interrupts fucntion
*/
/**@{*/
/*!
 * @fn           void nm_bsp_interrupt_ctrl(uint8);
 * @brief        Enable/Disable interrupts
 * @param [in]   u8Enable
 *               '0' disable interrupts. '1' enable interrupts 
 * @see          tpfNmBspIsr           
 * @note         Implementation of this function is host dependent and called by HIF layer.
 * @return       None

 */
void nm_bsp_interrupt_ctrl(uint8 u8Enable);
  /**@}*/

 /** @defgroup NmBspMalloc nm_bsp_malloc
*     @ingroup BSPAPI
*    Synchrnonous memory allocate API
*/
/**@{*/
/*!
 * @fn           void* nm_bsp_malloc(uint32);
 * @brief        Allocate memory
 * @param [in]   u32Size
 *               Size of the requested memory 
 * @note         Implementation of this function is host dependent and called by HIF layer.
 * @return       Pointer to the allocated buffer, or NULL otherwise

 */
void* nm_bsp_malloc(uint32 u32Size);
  /**@}*/

 /** @defgroup NmBspFree nm_bsp_free
*     @ingroup BSPAPI
*    Synchrnonous memory free API
*/
/**@{*/
/*!
 * @fn           void nm_bsp_free(void*);
 * @brief        Free memory
 * @param [in]   pvMemBuffer
 *               Pointer to the buffer to be freed 
 * @note         Implementation of this function is host dependent and called by HIF layer.
 * @return       None

 */
void nm_bsp_free(void* pvMemBuffer);
  /**@}*/

#ifdef __cplusplus
}
#endif

#endif

#ifdef WIN32
#include "nm_bsp_win32.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef __K20D50M__
#include "nm_bsp_k20d50m.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef __MSP430FR5739__
#include "bsp_msp430fr5739.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef _FREESCALE_MCF51CN128_
#include "bsp/include/nm_bsp_mcf51cn128.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef __MCF964548__
#include "bsp/include/nm_bsp_mc96f4548.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef __APP_APS3_CORTUS__
#include "nm_bsp_aps3_cortus.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef __KERNEL__
#include "bsp\include\nm_bsp_linux.h"
#define __M2M_DMA_BUF_ATT__
#endif

#if (defined __SAMD21J18A__) || (defined __SAMD21G18A__)
#include "bsp/include/nm_bsp_samd21.h"
#define __M2M_DMA_BUF_ATT__
#endif

#if (defined __SAM4S16C__) || (defined __SAM4SD32C__)
#include "bsp/include/nm_bsp_sam4s.h"
#define __M2M_DMA_BUF_ATT__		__attribute__((aligned(32)))
#endif
#if (defined __SAMV71Q21__) || (defined __SAMS70N21__) || (defined __SAMV71Q21B__)
#include "bsp/include/nm_bsp_samv71.h"
#define __M2M_DMA_BUF_ATT__		__attribute__((aligned(32)))
#endif

#ifdef __SAMG53N19__
#include "bsp/include/nm_bsp_samg53.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef __SAMG55J19__
#include "bsp/include/nm_bsp_samg55.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef CORTUS_APP
#include "crt_iface.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef NRF51 
#include "nm_bsp_nrf51822.h"
#define __M2M_DMA_BUF_ATT__
#endif

#ifdef _ARDUINO_UNO_
#include <bsp/include/nm_bsp_arduino_uno.h>
#define __M2M_DMA_BUF_ATT__
#endif


#ifdef _NM_BSP_BIG_END
#define NM_BSP_B_L_32(x) \
((((x) & 0x000000FF) << 24) + \
(((x) & 0x0000FF00) << 8)  + \
(((x) & 0x00FF0000) >> 8)   + \
(((x) & 0xFF000000) >> 24))
#define NM_BSP_B_L_16(x) \
((((x) & 0x00FF) << 8) + \
(((x)  & 0xFF00) >> 8))
#else
#define NM_BSP_B_L_32(x)  (x)
#define NM_BSP_B_L_16(x)  (x)
#endif


#endif	/*_NM_BSP_H_*/
