/**
 * \file
 *
 * \brief Header file for SAMC21J16A
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMC21J16A_
#define _SAMC21J16A_

/**
 * \ingroup SAMC21_definitions
 * \addtogroup SAMC21J16A_definitions SAMC21J16A definitions
 * This file defines all structures and symbols for SAMC21J16A:
 *   - registers and bitfields
 *   - peripheral base address
 *   - peripheral ID
 *   - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>
#ifndef __cplusplus
typedef volatile const uint32_t RoReg;   /**< Read only 32-bit register (volatile const unsigned int) */
typedef volatile const uint16_t RoReg16; /**< Read only 16-bit register (volatile const unsigned int) */
typedef volatile const uint8_t  RoReg8;  /**< Read only  8-bit register (volatile const unsigned int) */
#else
typedef volatile       uint32_t RoReg;   /**< Read only 32-bit register (volatile const unsigned int) */
typedef volatile       uint16_t RoReg16; /**< Read only 16-bit register (volatile const unsigned int) */
typedef volatile       uint8_t  RoReg8;  /**< Read only  8-bit register (volatile const unsigned int) */
#endif
typedef volatile       uint32_t WoReg;   /**< Write only 32-bit register (volatile unsigned int) */
typedef volatile       uint16_t WoReg16; /**< Write only 16-bit register (volatile unsigned int) */
typedef volatile       uint8_t  WoReg8;  /**< Write only  8-bit register (volatile unsigned int) */
typedef volatile       uint32_t RwReg;   /**< Read-Write 32-bit register (volatile unsigned int) */
typedef volatile       uint16_t RwReg16; /**< Read-Write 16-bit register (volatile unsigned int) */
typedef volatile       uint8_t  RwReg8;  /**< Read-Write  8-bit register (volatile unsigned int) */
#define CAST(type, value) ((type *)(value))
#define REG_ACCESS(type, address) (*(type*)(address)) /**< C code: Register value */
#else
#define CAST(type, value) (value)
#define REG_ACCESS(type, address) (address) /**< Assembly code: Register address */
#endif

/* ************************************************************************** */
/**  CMSIS DEFINITIONS FOR SAMC21J16A */
/* ************************************************************************** */
/** \defgroup SAMC21J16A_cmsis CMSIS Definitions */
/*@{*/

/** Interrupt Number Definition */
typedef enum IRQn
{
  /******  Cortex-M0+ Processor Exceptions Numbers ******************************/
  NonMaskableInt_IRQn      = -14,/**<  2 Non Maskable Interrupt                 */
  HardFault_IRQn           = -13,/**<  3 Cortex-M0+ Hard Fault Interrupt        */
  SVCall_IRQn              = -5, /**< 11 Cortex-M0+ SV Call Interrupt           */
  PendSV_IRQn              = -2, /**< 14 Cortex-M0+ Pend SV Interrupt           */
  SysTick_IRQn             = -1, /**< 15 Cortex-M0+ System Tick Interrupt       */
  /******  SAMC21J16A-specific Interrupt Numbers ***********************/
  SYSTEM_IRQn              =  0, /**<  0 SAMC21J16A System Interrupts */
  MCLK_IRQn                =  0, /**<  0 SAMC21J16A Main Clock (MCLK) */
  OSCCTRL_IRQn             =  0, /**<  0 SAMC21J16A Oscillators Control (OSCCTRL) */
  OSC32KCTRL_IRQn          =  0, /**<  0 SAMC21J16A 32k Oscillators Control (OSC32KCTRL) */
  PAC_IRQn                 =  0, /**<  0 SAMC21J16A Peripheral Access Controller (PAC) */
  PM_IRQn                  =  0, /**<  0 SAMC21J16A Power Manager (PM) */
  SUPC_IRQn                =  0, /**<  0 SAMC21J16A Supply Controller (SUPC) */
  TAL_IRQn                 =  0, /**<  0 SAMC21J16A Trigger Allocator (TAL) */
  WDT_IRQn                 =  1, /**<  1 SAMC21J16A Watchdog Timer (WDT) */
  RTC_IRQn                 =  2, /**<  2 SAMC21J16A Real-Time Counter (RTC) */
  EIC_IRQn                 =  3, /**<  3 SAMC21J16A External Interrupt Controller (EIC) */
  FREQM_IRQn               =  4, /**<  4 SAMC21J16A Frequency Meter (FREQM) */
  TSENS_IRQn               =  5, /**<  5 SAMC21J16A Temperature Sensor (TSENS) */
  NVMCTRL_IRQn             =  6, /**<  6 SAMC21J16A Non-Volatile Memory Controller (NVMCTRL) */
  DMAC_IRQn                =  7, /**<  7 SAMC21J16A Direct Memory Access Controller (DMAC) */
  EVSYS_IRQn               =  8, /**<  8 SAMC21J16A Event System Interface (EVSYS) */
  SERCOM0_IRQn             =  9, /**<  9 SAMC21J16A Serial Communication Interface 0 (SERCOM0) */
  SERCOM1_IRQn             = 10, /**< 10 SAMC21J16A Serial Communication Interface 1 (SERCOM1) */
  SERCOM2_IRQn             = 11, /**< 11 SAMC21J16A Serial Communication Interface 2 (SERCOM2) */
  SERCOM3_IRQn             = 12, /**< 12 SAMC21J16A Serial Communication Interface 3 (SERCOM3) */
  SERCOM4_IRQn             = 13, /**< 13 SAMC21J16A Serial Communication Interface 4 (SERCOM4) */
  SERCOM5_IRQn             = 14, /**< 14 SAMC21J16A Serial Communication Interface 5 (SERCOM5) */
  CAN0_IRQn                = 15, /**< 15 SAMC21J16A Control Area Network 0 (CAN0) */
  CAN1_IRQn                = 16, /**< 16 SAMC21J16A Control Area Network 1 (CAN1) */
  TCC0_IRQn                = 17, /**< 17 SAMC21J16A Timer Counter Control 0 (TCC0) */
  TCC1_IRQn                = 18, /**< 18 SAMC21J16A Timer Counter Control 1 (TCC1) */
  TCC2_IRQn                = 19, /**< 19 SAMC21J16A Timer Counter Control 2 (TCC2) */
  TC0_IRQn                 = 20, /**< 20 SAMC21J16A Basic Timer Counter 0 (TC0) */
  TC1_IRQn                 = 21, /**< 21 SAMC21J16A Basic Timer Counter 1 (TC1) */
  TC2_IRQn                 = 22, /**< 22 SAMC21J16A Basic Timer Counter 2 (TC2) */
  TC3_IRQn                 = 23, /**< 23 SAMC21J16A Basic Timer Counter 3 (TC3) */
  TC4_IRQn                 = 24, /**< 24 SAMC21J16A Basic Timer Counter 4 (TC4) */
  ADC0_IRQn                = 25, /**< 25 SAMC21J16A Analog Digital Converter 0 (ADC0) */
  ADC1_IRQn                = 26, /**< 26 SAMC21J16A Analog Digital Converter 1 (ADC1) */
  AC_IRQn                  = 27, /**< 27 SAMC21J16A Analog Comparators (AC) */
  DAC_IRQn                 = 28, /**< 28 SAMC21J16A Digital Analog Converter (DAC) */
  SDADC_IRQn               = 29, /**< 29 SAMC21J16A Sigma-Delta Analog Digital Converter (SDADC) */
  PTC_IRQn                 = 30, /**< 30 SAMC21J16A Peripheral Touch Controller (PTC) */

  PERIPH_COUNT_IRQn        = 31  /**< Number of peripheral IDs */
} IRQn_Type;

typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;

  /* Cortex-M handlers */
  void* pfnReset_Handler;
  void* pfnNMI_Handler;
  void* pfnHardFault_Handler;
  void* pfnReservedM12;
  void* pfnReservedM11;
  void* pfnReservedM10;
  void* pfnReservedM9;
  void* pfnReservedM8;
  void* pfnReservedM7;
  void* pfnReservedM6;
  void* pfnSVC_Handler;
  void* pfnReservedM4;
  void* pfnReservedM3;
  void* pfnPendSV_Handler;
  void* pfnSysTick_Handler;

  /* Peripheral handlers */
  void* pfnSYSTEM_Handler;                /*  0 Main Clock, Oscillators Control, 32k Oscillators Control, Peripheral Access Controller, Power Manager, Supply Controller, Trigger Allocator */
  void* pfnWDT_Handler;                   /*  1 Watchdog Timer */
  void* pfnRTC_Handler;                   /*  2 Real-Time Counter */
  void* pfnEIC_Handler;                   /*  3 External Interrupt Controller */
  void* pfnFREQM_Handler;                 /*  4 Frequency Meter */
  void* pfnTSENS_Handler;                 /*  5 Temperature Sensor */
  void* pfnNVMCTRL_Handler;               /*  6 Non-Volatile Memory Controller */
  void* pfnDMAC_Handler;                  /*  7 Direct Memory Access Controller */
  void* pfnEVSYS_Handler;                 /*  8 Event System Interface */
  void* pfnSERCOM0_Handler;               /*  9 Serial Communication Interface 0 */
  void* pfnSERCOM1_Handler;               /* 10 Serial Communication Interface 1 */
  void* pfnSERCOM2_Handler;               /* 11 Serial Communication Interface 2 */
  void* pfnSERCOM3_Handler;               /* 12 Serial Communication Interface 3 */
  void* pfnSERCOM4_Handler;               /* 13 Serial Communication Interface 4 */
  void* pfnSERCOM5_Handler;               /* 14 Serial Communication Interface 5 */
  void* pfnCAN0_Handler;                  /* 15 Control Area Network 0 */
  void* pfnCAN1_Handler;                  /* 16 Control Area Network 1 */
  void* pfnTCC0_Handler;                  /* 17 Timer Counter Control 0 */
  void* pfnTCC1_Handler;                  /* 18 Timer Counter Control 1 */
  void* pfnTCC2_Handler;                  /* 19 Timer Counter Control 2 */
  void* pfnTC0_Handler;                   /* 20 Basic Timer Counter 0 */
  void* pfnTC1_Handler;                   /* 21 Basic Timer Counter 1 */
  void* pfnTC2_Handler;                   /* 22 Basic Timer Counter 2 */
  void* pfnTC3_Handler;                   /* 23 Basic Timer Counter 3 */
  void* pfnTC4_Handler;                   /* 24 Basic Timer Counter 4 */
  void* pfnADC0_Handler;                  /* 25 Analog Digital Converter 0 */
  void* pfnADC1_Handler;                  /* 26 Analog Digital Converter 1 */
  void* pfnAC_Handler;                    /* 27 Analog Comparators */
  void* pfnDAC_Handler;                   /* 28 Digital Analog Converter */
  void* pfnSDADC_Handler;                 /* 29 Sigma-Delta Analog Digital Converter */
  void* pfnPTC_Handler;                   /* 30 Peripheral Touch Controller */
} DeviceVectors;

/* Cortex-M0+ processor handlers */
void Reset_Handler               ( void );
void NMI_Handler                 ( void );
void HardFault_Handler           ( void );
void SVC_Handler                 ( void );
void PendSV_Handler              ( void );
void SysTick_Handler             ( void );

/* Peripherals handlers */
void SYSTEM_Handler              ( void );
void WDT_Handler                 ( void );
void RTC_Handler                 ( void );
void EIC_Handler                 ( void );
void FREQM_Handler               ( void );
void TSENS_Handler               ( void );
void NVMCTRL_Handler             ( void );
void DMAC_Handler                ( void );
void EVSYS_Handler               ( void );
void SERCOM0_Handler             ( void );
void SERCOM1_Handler             ( void );
void SERCOM2_Handler             ( void );
void SERCOM3_Handler             ( void );
void SERCOM4_Handler             ( void );
void SERCOM5_Handler             ( void );
void CAN0_Handler                ( void );
void CAN1_Handler                ( void );
void TCC0_Handler                ( void );
void TCC1_Handler                ( void );
void TCC2_Handler                ( void );
void TC0_Handler                 ( void );
void TC1_Handler                 ( void );
void TC2_Handler                 ( void );
void TC3_Handler                 ( void );
void TC4_Handler                 ( void );
void ADC0_Handler                ( void );
void ADC1_Handler                ( void );
void AC_Handler                  ( void );
void DAC_Handler                 ( void );
void SDADC_Handler               ( void );
void PTC_Handler                 ( void );

/*
 * \brief Configuration of the Cortex-M0+ Processor and Core Peripherals
 */

#define LITTLE_ENDIAN          1
#define __CM0PLUS_REV          1         /*!< Core revision r0p1 */
#define __MPU_PRESENT          1         /*!< MPU present or not */
#define __NVIC_PRIO_BITS       2         /*!< Number of bits used for Priority Levels */
#define __VTOR_PRESENT         1         /*!< VTOR present or not */
#define __Vendor_SysTickConfig 0         /*!< Set to 1 if different SysTick Config is used */

/**
 * \brief CMSIS includes
 */

#include <core_cm0plus.h>
#if !defined DONT_USE_CMSIS_INIT
#include "system_samc21.h"
#endif /* DONT_USE_CMSIS_INIT */

/*@}*/

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMC21J16A */
/* ************************************************************************** */
/** \defgroup SAMC21J16A_api Peripheral Software API */
/*@{*/

#include "component/ac.h"
#include "component/adc.h"
#include "component/can.h"
#include "component/ccl.h"
#include "component/dac.h"
#include "component/divas.h"
#include "component/dmac.h"
#include "component/dsu.h"
#include "component/eic.h"
#include "component/evsys.h"
#include "component/freqm.h"
#include "component/gclk.h"
#include "component/hmatrixb.h"
#include "component/mclk.h"
#include "component/mtb.h"
#include "component/nvmctrl.h"
#include "component/oscctrl.h"
#include "component/osc32kctrl.h"
#include "component/pac.h"
#include "component/pm.h"
#include "component/port.h"
#include "component/rstc.h"
#include "component/rtc.h"
#include "component/sdadc.h"
#include "component/sercom.h"
#include "component/supc.h"
#include "component/tal.h"
#include "component/tc.h"
#include "component/tcc.h"
#include "component/tsens.h"
#include "component/wdt.h"
/*@}*/

/* ************************************************************************** */
/**  REGISTERS ACCESS DEFINITIONS FOR SAMC21J16A */
/* ************************************************************************** */
/** \defgroup SAMC21J16A_reg Registers Access Definitions */
/*@{*/

#include "instance/ac.h"
#include "instance/adc0.h"
#include "instance/adc1.h"
#include "instance/can0.h"
#include "instance/can1.h"
#include "instance/ccl.h"
#include "instance/dac.h"
#include "instance/divas.h"
#include "instance/dmac.h"
#include "instance/dsu.h"
#include "instance/eic.h"
#include "instance/evsys.h"
#include "instance/freqm.h"
#include "instance/gclk.h"
#include "instance/hmatrixhs.h"
#include "instance/mclk.h"
#include "instance/mtb.h"
#include "instance/nvmctrl.h"
#include "instance/oscctrl.h"
#include "instance/osc32kctrl.h"
#include "instance/pac.h"
#include "instance/pm.h"
#include "instance/port.h"
#include "instance/rstc.h"
#include "instance/rtc.h"
#include "instance/sdadc.h"
#include "instance/sercom0.h"
#include "instance/sercom1.h"
#include "instance/sercom2.h"
#include "instance/sercom3.h"
#include "instance/sercom4.h"
#include "instance/sercom5.h"
#include "instance/supc.h"
#include "instance/tal.h"
#include "instance/tc0.h"
#include "instance/tc1.h"
#include "instance/tc2.h"
#include "instance/tc3.h"
#include "instance/tc4.h"
#include "instance/tcc0.h"
#include "instance/tcc1.h"
#include "instance/tcc2.h"
#include "instance/tsens.h"
#include "instance/wdt.h"
/*@}*/

/* ************************************************************************** */
/**  PERIPHERAL ID DEFINITIONS FOR SAMC21J16A */
/* ************************************************************************** */
/** \defgroup SAMC21J16A_id Peripheral Ids Definitions */
/*@{*/

// Peripheral instances on HPB0 bridge
#define ID_PAC            0 /**< \brief Peripheral Access Controller (PAC) */
#define ID_PM             1 /**< \brief Power Manager (PM) */
#define ID_MCLK           2 /**< \brief Main Clock (MCLK) */
#define ID_RSTC           3 /**< \brief Reset Controller (RSTC) */
#define ID_OSCCTRL        4 /**< \brief Oscillators Control (OSCCTRL) */
#define ID_OSC32KCTRL     5 /**< \brief 32k Oscillators Control (OSC32KCTRL) */
#define ID_SUPC           6 /**< \brief Supply Controller (SUPC) */
#define ID_GCLK           7 /**< \brief Generic Clock Generator (GCLK) */
#define ID_WDT            8 /**< \brief Watchdog Timer (WDT) */
#define ID_RTC            9 /**< \brief Real-Time Counter (RTC) */
#define ID_EIC           10 /**< \brief External Interrupt Controller (EIC) */
#define ID_FREQM         11 /**< \brief Frequency Meter (FREQM) */
#define ID_TSENS         12 /**< \brief Temperature Sensor (TSENS) */

// Peripheral instances on HPB1 bridge
#define ID_PORT          32 /**< \brief Port Module (PORT) */
#define ID_DSU           33 /**< \brief Device Service Unit (DSU) */
#define ID_NVMCTRL       34 /**< \brief Non-Volatile Memory Controller (NVMCTRL) */
#define ID_DMAC          35 /**< \brief Direct Memory Access Controller (DMAC) */
#define ID_MTB           36 /**< \brief Cortex-M0+ Micro-Trace Buffer (MTB) */
#define ID_HMATRIXHS     37 /**< \brief HSB Matrix (HMATRIXHS) */

// Peripheral instances on HPB2 bridge
#define ID_EVSYS         64 /**< \brief Event System Interface (EVSYS) */
#define ID_SERCOM0       65 /**< \brief Serial Communication Interface 0 (SERCOM0) */
#define ID_SERCOM1       66 /**< \brief Serial Communication Interface 1 (SERCOM1) */
#define ID_SERCOM2       67 /**< \brief Serial Communication Interface 2 (SERCOM2) */
#define ID_SERCOM3       68 /**< \brief Serial Communication Interface 3 (SERCOM3) */
#define ID_SERCOM4       69 /**< \brief Serial Communication Interface 4 (SERCOM4) */
#define ID_SERCOM5       70 /**< \brief Serial Communication Interface 5 (SERCOM5) */
#define ID_CAN0          71 /**< \brief Control Area Network 0 (CAN0) */
#define ID_CAN1          72 /**< \brief Control Area Network 1 (CAN1) */
#define ID_TCC0          73 /**< \brief Timer Counter Control 0 (TCC0) */
#define ID_TCC1          74 /**< \brief Timer Counter Control 1 (TCC1) */
#define ID_TCC2          75 /**< \brief Timer Counter Control 2 (TCC2) */
#define ID_TC0           76 /**< \brief Basic Timer Counter 0 (TC0) */
#define ID_TC1           77 /**< \brief Basic Timer Counter 1 (TC1) */
#define ID_TC2           78 /**< \brief Basic Timer Counter 2 (TC2) */
#define ID_TC3           79 /**< \brief Basic Timer Counter 3 (TC3) */
#define ID_TC4           80 /**< \brief Basic Timer Counter 4 (TC4) */
#define ID_ADC0          81 /**< \brief Analog Digital Converter 0 (ADC0) */
#define ID_ADC1          82 /**< \brief Analog Digital Converter 1 (ADC1) */
#define ID_SDADC         83 /**< \brief Sigma-Delta Analog Digital Converter (SDADC) */
#define ID_AC            84 /**< \brief Analog Comparators (AC) */
#define ID_DAC           85 /**< \brief Digital Analog Converter (DAC) */
#define ID_PTC           86 /**< \brief Peripheral Touch Controller (PTC) */
#define ID_CCL           87 /**< \brief Configurable Custom Logic (CCL) */
#define ID_TAL           88 /**< \brief Trigger Allocator (TAL) */

#define ID_PERIPH_COUNT  89 /**< \brief Number of peripheral IDs */
/*@}*/

/* ************************************************************************** */
/**  BASE ADDRESS DEFINITIONS FOR SAMC21J16A */
/* ************************************************************************** */
/** \defgroup SAMC21J16A_base Peripheral Base Address Definitions */
/*@{*/

#if defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)
#define AC                            (0x42005000UL) /**< \brief (AC) APB Base Address */
#define ADC0                          (0x42004400UL) /**< \brief (ADC0) APB Base Address */
#define ADC1                          (0x42004800UL) /**< \brief (ADC1) APB Base Address */
#define CAN0                          (0x42001C00UL) /**< \brief (CAN0) APB Base Address */
#define CAN1                          (0x42002000UL) /**< \brief (CAN1) APB Base Address */
#define CCL                           (0x42005C00UL) /**< \brief (CCL) APB Base Address */
#define DAC                           (0x42005400UL) /**< \brief (DAC) APB Base Address */
#define DIVAS                         (0x48000000UL) /**< \brief (DIVAS) AHB Base Address */
#define DIVAS_IOBUS                   (0x60000200UL) /**< \brief (DIVAS) IOBUS Base Address */
#define DMAC                          (0x41006000UL) /**< \brief (DMAC) APB Base Address */
#define DSU                           (0x41002000UL) /**< \brief (DSU) APB Base Address */
#define EIC                           (0x40002800UL) /**< \brief (EIC) APB Base Address */
#define EVSYS                         (0x42000000UL) /**< \brief (EVSYS) APB Base Address */
#define FREQM                         (0x40002C00UL) /**< \brief (FREQM) APB Base Address */
#define GCLK                          (0x40001C00UL) /**< \brief (GCLK) APB Base Address */
#define HMATRIXHS                     (0x4100A000UL) /**< \brief (HMATRIXHS) APB Base Address */
#define MCLK                          (0x40000800UL) /**< \brief (MCLK) APB Base Address */
#define MTB                           (0x41008000UL) /**< \brief (MTB) APB Base Address */
#define NVMCTRL                       (0x41004000UL) /**< \brief (NVMCTRL) APB Base Address */
#define NVMCTRL_CAL                   (0x00800000UL) /**< \brief (NVMCTRL) CAL Base Address */
#define NVMCTRL_LOCKBIT               (0x00802000UL) /**< \brief (NVMCTRL) LOCKBIT Base Address */
#define NVMCTRL_OTP1                  (0x00806000UL) /**< \brief (NVMCTRL) OTP1 Base Address */
#define NVMCTRL_OTP2                  (0x00806008UL) /**< \brief (NVMCTRL) OTP2 Base Address */
#define NVMCTRL_OTP3                  (0x00806010UL) /**< \brief (NVMCTRL) OTP3 Base Address */
#define NVMCTRL_OTP4                  (0x00806018UL) /**< \brief (NVMCTRL) OTP4 Base Address */
#define NVMCTRL_OTP5                  (0x00806020UL) /**< \brief (NVMCTRL) OTP5 Base Address */
#define NVMCTRL_TEMP_LOG              (0x00806030UL) /**< \brief (NVMCTRL) TEMP_LOG Base Address */
#define NVMCTRL_USER                  (0x00804000UL) /**< \brief (NVMCTRL) USER Base Address */
#define OSCCTRL                       (0x40001000UL) /**< \brief (OSCCTRL) APB Base Address */
#define OSC32KCTRL                    (0x40001400UL) /**< \brief (OSC32KCTRL) APB Base Address */
#define PAC                           (0x40000000UL) /**< \brief (PAC) APB Base Address */
#define PM                            (0x40000400UL) /**< \brief (PM) APB Base Address */
#define PORT                          (0x41000000UL) /**< \brief (PORT) APB Base Address */
#define PORT_IOBUS                    (0x60000000UL) /**< \brief (PORT) IOBUS Base Address */
#define RSTC                          (0x40000C00UL) /**< \brief (RSTC) APB Base Address */
#define RTC                           (0x40002400UL) /**< \brief (RTC) APB Base Address */
#define SDADC                         (0x42004C00UL) /**< \brief (SDADC) APB Base Address */
#define SERCOM0                       (0x42000400UL) /**< \brief (SERCOM0) APB Base Address */
#define SERCOM1                       (0x42000800UL) /**< \brief (SERCOM1) APB Base Address */
#define SERCOM2                       (0x42000C00UL) /**< \brief (SERCOM2) APB Base Address */
#define SERCOM3                       (0x42001000UL) /**< \brief (SERCOM3) APB Base Address */
#define SERCOM4                       (0x42001400UL) /**< \brief (SERCOM4) APB Base Address */
#define SERCOM5                       (0x42001800UL) /**< \brief (SERCOM5) APB Base Address */
#define SUPC                          (0x40001800UL) /**< \brief (SUPC) APB Base Address */
#define TAL                           (0x42006000UL) /**< \brief (TAL) APB Base Address */
#define TC0                           (0x42003000UL) /**< \brief (TC0) APB Base Address */
#define TC1                           (0x42003400UL) /**< \brief (TC1) APB Base Address */
#define TC2                           (0x42003800UL) /**< \brief (TC2) APB Base Address */
#define TC3                           (0x42003C00UL) /**< \brief (TC3) APB Base Address */
#define TC4                           (0x42004000UL) /**< \brief (TC4) APB Base Address */
#define TCC0                          (0x42002400UL) /**< \brief (TCC0) APB Base Address */
#define TCC1                          (0x42002800UL) /**< \brief (TCC1) APB Base Address */
#define TCC2                          (0x42002C00UL) /**< \brief (TCC2) APB Base Address */
#define TSENS                         (0x40003000UL) /**< \brief (TSENS) APB Base Address */
#define WDT                           (0x40002000UL) /**< \brief (WDT) APB Base Address */
#else
#define AC                ((Ac       *)0x42005000UL) /**< \brief (AC) APB Base Address */
#define AC_INST_NUM       1                          /**< \brief (AC) Number of instances */
#define AC_INSTS          { AC }                     /**< \brief (AC) Instances List */

#define ADC0              ((Adc      *)0x42004400UL) /**< \brief (ADC0) APB Base Address */
#define ADC1              ((Adc      *)0x42004800UL) /**< \brief (ADC1) APB Base Address */
#define ADC_INST_NUM      2                          /**< \brief (ADC) Number of instances */
#define ADC_INSTS         { ADC0, ADC1 }             /**< \brief (ADC) Instances List */

#define CAN0              ((Can      *)0x42001C00UL) /**< \brief (CAN0) APB Base Address */
#define CAN1              ((Can      *)0x42002000UL) /**< \brief (CAN1) APB Base Address */
#define CAN_INST_NUM      2                          /**< \brief (CAN) Number of instances */
#define CAN_INSTS         { CAN0, CAN1 }             /**< \brief (CAN) Instances List */

#define CCL               ((Ccl      *)0x42005C00UL) /**< \brief (CCL) APB Base Address */
#define CCL_INST_NUM      1                          /**< \brief (CCL) Number of instances */
#define CCL_INSTS         { CCL }                    /**< \brief (CCL) Instances List */

#define DAC               ((Dac      *)0x42005400UL) /**< \brief (DAC) APB Base Address */
#define DAC_INST_NUM      1                          /**< \brief (DAC) Number of instances */
#define DAC_INSTS         { DAC }                    /**< \brief (DAC) Instances List */

#define DIVAS             ((Divas    *)0x48000000UL) /**< \brief (DIVAS) AHB Base Address */
#define DIVAS_IOBUS       ((Divas    *)0x60000200UL) /**< \brief (DIVAS) IOBUS Base Address */
#define DIVAS_INST_NUM    1                          /**< \brief (DIVAS) Number of instances */
#define DIVAS_INSTS       { DIVAS }                  /**< \brief (DIVAS) Instances List */

#define DMAC              ((Dmac     *)0x41006000UL) /**< \brief (DMAC) APB Base Address */
#define DMAC_INST_NUM     1                          /**< \brief (DMAC) Number of instances */
#define DMAC_INSTS        { DMAC }                   /**< \brief (DMAC) Instances List */

#define DSU               ((Dsu      *)0x41002000UL) /**< \brief (DSU) APB Base Address */
#define DSU_INST_NUM      1                          /**< \brief (DSU) Number of instances */
#define DSU_INSTS         { DSU }                    /**< \brief (DSU) Instances List */

#define EIC               ((Eic      *)0x40002800UL) /**< \brief (EIC) APB Base Address */
#define EIC_INST_NUM      1                          /**< \brief (EIC) Number of instances */
#define EIC_INSTS         { EIC }                    /**< \brief (EIC) Instances List */

#define EVSYS             ((Evsys    *)0x42000000UL) /**< \brief (EVSYS) APB Base Address */
#define EVSYS_INST_NUM    1                          /**< \brief (EVSYS) Number of instances */
#define EVSYS_INSTS       { EVSYS }                  /**< \brief (EVSYS) Instances List */

#define FREQM             ((Freqm    *)0x40002C00UL) /**< \brief (FREQM) APB Base Address */
#define FREQM_INST_NUM    1                          /**< \brief (FREQM) Number of instances */
#define FREQM_INSTS       { FREQM }                  /**< \brief (FREQM) Instances List */

#define GCLK              ((Gclk     *)0x40001C00UL) /**< \brief (GCLK) APB Base Address */
#define GCLK_INST_NUM     1                          /**< \brief (GCLK) Number of instances */
#define GCLK_INSTS        { GCLK }                   /**< \brief (GCLK) Instances List */

#define HMATRIXHS         ((Hmatrixb *)0x4100A000UL) /**< \brief (HMATRIXHS) APB Base Address */
#define HMATRIXB_INST_NUM 1                          /**< \brief (HMATRIXB) Number of instances */
#define HMATRIXB_INSTS    { HMATRIXHS }              /**< \brief (HMATRIXB) Instances List */

#define MCLK              ((Mclk     *)0x40000800UL) /**< \brief (MCLK) APB Base Address */
#define MCLK_INST_NUM     1                          /**< \brief (MCLK) Number of instances */
#define MCLK_INSTS        { MCLK }                   /**< \brief (MCLK) Instances List */

#define MTB               ((Mtb      *)0x41008000UL) /**< \brief (MTB) APB Base Address */
#define MTB_INST_NUM      1                          /**< \brief (MTB) Number of instances */
#define MTB_INSTS         { MTB }                    /**< \brief (MTB) Instances List */

#define NVMCTRL           ((Nvmctrl  *)0x41004000UL) /**< \brief (NVMCTRL) APB Base Address */
#define NVMCTRL_CAL                   (0x00800000UL) /**< \brief (NVMCTRL) CAL Base Address */
#define NVMCTRL_LOCKBIT               (0x00802000UL) /**< \brief (NVMCTRL) LOCKBIT Base Address */
#define NVMCTRL_OTP1                  (0x00806000UL) /**< \brief (NVMCTRL) OTP1 Base Address */
#define NVMCTRL_OTP2                  (0x00806008UL) /**< \brief (NVMCTRL) OTP2 Base Address */
#define NVMCTRL_OTP3                  (0x00806010UL) /**< \brief (NVMCTRL) OTP3 Base Address */
#define NVMCTRL_OTP4                  (0x00806018UL) /**< \brief (NVMCTRL) OTP4 Base Address */
#define NVMCTRL_OTP5                  (0x00806020UL) /**< \brief (NVMCTRL) OTP5 Base Address */
#define NVMCTRL_TEMP_LOG              (0x00806030UL) /**< \brief (NVMCTRL) TEMP_LOG Base Address */
#define NVMCTRL_USER                  (0x00804000UL) /**< \brief (NVMCTRL) USER Base Address */
#define NVMCTRL_INST_NUM  1                          /**< \brief (NVMCTRL) Number of instances */
#define NVMCTRL_INSTS     { NVMCTRL }                /**< \brief (NVMCTRL) Instances List */

#define OSCCTRL           ((Oscctrl  *)0x40001000UL) /**< \brief (OSCCTRL) APB Base Address */
#define OSCCTRL_INST_NUM  1                          /**< \brief (OSCCTRL) Number of instances */
#define OSCCTRL_INSTS     { OSCCTRL }                /**< \brief (OSCCTRL) Instances List */

#define OSC32KCTRL        ((Osc32kctrl *)0x40001400UL) /**< \brief (OSC32KCTRL) APB Base Address */
#define OSC32KCTRL_INST_NUM 1                          /**< \brief (OSC32KCTRL) Number of instances */
#define OSC32KCTRL_INSTS  { OSC32KCTRL }             /**< \brief (OSC32KCTRL) Instances List */

#define PAC               ((Pac      *)0x40000000UL) /**< \brief (PAC) APB Base Address */
#define PAC_INST_NUM      1                          /**< \brief (PAC) Number of instances */
#define PAC_INSTS         { PAC }                    /**< \brief (PAC) Instances List */

#define PM                ((Pm       *)0x40000400UL) /**< \brief (PM) APB Base Address */
#define PM_INST_NUM       1                          /**< \brief (PM) Number of instances */
#define PM_INSTS          { PM }                     /**< \brief (PM) Instances List */

#define PORT              ((Port     *)0x41000000UL) /**< \brief (PORT) APB Base Address */
#define PORT_IOBUS        ((Port     *)0x60000000UL) /**< \brief (PORT) IOBUS Base Address */
#define PORT_INST_NUM     1                          /**< \brief (PORT) Number of instances */
#define PORT_INSTS        { PORT }                   /**< \brief (PORT) Instances List */

#define PTC_GCLK_ID       37
#define PTC_INST_NUM      1                          /**< \brief (PTC) Number of instances */
#define PTC_INSTS         { PTC }                    /**< \brief (PTC) Instances List */

#define RSTC              ((Rstc     *)0x40000C00UL) /**< \brief (RSTC) APB Base Address */
#define RSTC_INST_NUM     1                          /**< \brief (RSTC) Number of instances */
#define RSTC_INSTS        { RSTC }                   /**< \brief (RSTC) Instances List */

#define RTC               ((Rtc      *)0x40002400UL) /**< \brief (RTC) APB Base Address */
#define RTC_INST_NUM      1                          /**< \brief (RTC) Number of instances */
#define RTC_INSTS         { RTC }                    /**< \brief (RTC) Instances List */

#define SDADC             ((Sdadc    *)0x42004C00UL) /**< \brief (SDADC) APB Base Address */
#define SDADC_INST_NUM    1                          /**< \brief (SDADC) Number of instances */
#define SDADC_INSTS       { SDADC }                  /**< \brief (SDADC) Instances List */

#define SERCOM0           ((Sercom   *)0x42000400UL) /**< \brief (SERCOM0) APB Base Address */
#define SERCOM1           ((Sercom   *)0x42000800UL) /**< \brief (SERCOM1) APB Base Address */
#define SERCOM2           ((Sercom   *)0x42000C00UL) /**< \brief (SERCOM2) APB Base Address */
#define SERCOM3           ((Sercom   *)0x42001000UL) /**< \brief (SERCOM3) APB Base Address */
#define SERCOM4           ((Sercom   *)0x42001400UL) /**< \brief (SERCOM4) APB Base Address */
#define SERCOM5           ((Sercom   *)0x42001800UL) /**< \brief (SERCOM5) APB Base Address */
#define SERCOM_INST_NUM   6                          /**< \brief (SERCOM) Number of instances */
#define SERCOM_INSTS      { SERCOM0, SERCOM1, SERCOM2, SERCOM3, SERCOM4, SERCOM5 } /**< \brief (SERCOM) Instances List */

#define SUPC              ((Supc     *)0x40001800UL) /**< \brief (SUPC) APB Base Address */
#define SUPC_INST_NUM     1                          /**< \brief (SUPC) Number of instances */
#define SUPC_INSTS        { SUPC }                   /**< \brief (SUPC) Instances List */

#define TAL               ((Tal      *)0x42006000UL) /**< \brief (TAL) APB Base Address */
#define TAL_INST_NUM      1                          /**< \brief (TAL) Number of instances */
#define TAL_INSTS         { TAL }                    /**< \brief (TAL) Instances List */

#define TC0               ((Tc       *)0x42003000UL) /**< \brief (TC0) APB Base Address */
#define TC1               ((Tc       *)0x42003400UL) /**< \brief (TC1) APB Base Address */
#define TC2               ((Tc       *)0x42003800UL) /**< \brief (TC2) APB Base Address */
#define TC3               ((Tc       *)0x42003C00UL) /**< \brief (TC3) APB Base Address */
#define TC4               ((Tc       *)0x42004000UL) /**< \brief (TC4) APB Base Address */
#define TC_INST_NUM       5                          /**< \brief (TC) Number of instances */
#define TC_INSTS          { TC0, TC1, TC2, TC3, TC4 } /**< \brief (TC) Instances List */

#define TCC0              ((Tcc      *)0x42002400UL) /**< \brief (TCC0) APB Base Address */
#define TCC1              ((Tcc      *)0x42002800UL) /**< \brief (TCC1) APB Base Address */
#define TCC2              ((Tcc      *)0x42002C00UL) /**< \brief (TCC2) APB Base Address */
#define TCC_INST_NUM      3                          /**< \brief (TCC) Number of instances */
#define TCC_INSTS         { TCC0, TCC1, TCC2 }       /**< \brief (TCC) Instances List */

#define TSENS             ((Tsens    *)0x40003000UL) /**< \brief (TSENS) APB Base Address */
#define TSENS_INST_NUM    1                          /**< \brief (TSENS) Number of instances */
#define TSENS_INSTS       { TSENS }                  /**< \brief (TSENS) Instances List */

#define WDT               ((Wdt      *)0x40002000UL) /**< \brief (WDT) APB Base Address */
#define WDT_INST_NUM      1                          /**< \brief (WDT) Number of instances */
#define WDT_INSTS         { WDT }                    /**< \brief (WDT) Instances List */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/*@}*/

/* ************************************************************************** */
/**  PORT DEFINITIONS FOR SAMC21J16A */
/* ************************************************************************** */
/** \defgroup SAMC21J16A_port PORT Definitions */
/*@{*/

#include "pio/samc21j16a.h"
/*@}*/

/* ************************************************************************** */
/**  MEMORY MAPPING DEFINITIONS FOR SAMC21J16A */
/* ************************************************************************** */

#define FLASH_SIZE            0x10000UL /* 64 kB */
#define FLASH_PAGE_SIZE       64
#define FLASH_NB_OF_PAGES     1024
#define FLASH_USER_PAGE_SIZE  64
#define HSRAM_SIZE            0x2000UL /* 8 kB */

#define FLASH_ADDR            (0x00000000u) /**< FLASH base address */
#define FLASH_USER_PAGE_ADDR  (0x00800000u) /**< FLASH_USER_PAGE base address */
#define HSRAM_ADDR            (0x20000000u) /**< HSRAM base address */
#define HPB0_ADDR             (0x40000000u) /**< HPB0 base address */
#define HPB1_ADDR             (0x41000000u) /**< HPB1 base address */
#define HPB2_ADDR             (0x42000000u) /**< HPB2 base address */
#define PPB_ADDR              (0xE0000000u) /**< PPB base address */

#define DSU_DID_RESETVALUE    0x11010202UL
#define AC_PAIRS              2
#define DMAC_CH_NUM           12
#define EVSYS_CHANNELS        12
#define PORT_GROUPS           2
#define RWW_SIZE              0x800UL /* 2 kB */

/* ************************************************************************** */
/**  ELECTRICAL DEFINITIONS FOR SAMC21J16A */
/* ************************************************************************** */


#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* SAMC21J16A_H */
