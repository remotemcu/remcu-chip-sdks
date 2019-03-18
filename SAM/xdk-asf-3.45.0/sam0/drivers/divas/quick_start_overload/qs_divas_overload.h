/**
 * \file
 *
 * \brief SAM Divide and Square Root Accelerator (DIVAS) Driver Quick Start
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \page asfdoc_sam0_divas_overload_use_case Quick Start Guide for DIVAS - Overload
 *
 * In this use case, the Divide and Square Root Accelerator (DIVAS) module is 
 * used.
 *
 * This use case will calculate the data in overload mode. If all the calculation 
 * results are the same as the desired results, the board LED will be lighted.
 * Otherwise, the board LED will be flashing. The variable "result" can indicate 
 * which calculation is wrong.
 *
 * \section asfdoc_sam0_divas_overload_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_divas_overload_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_divas_overload_use_case_setup_code Code
 * The following must be added to the user application source file, outside
 * any function:
 
 * The signed and unsigned dividend: 
 * \snippet qs_divas_overload.c buffer

 * Copy-paste the following function code to your user application:
 * \snippet qs_divas_overload.c calculate
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_divas_overload.c setup_init
 *
 * \section asfdoc_sam0_divas_overload_use_case_imp Implementation
 *
 * \subsection asfdoc_sam0_trng_overload_use_case_imp_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_divas_overload.c main
 *
 * \subsection asfdoc_sam0_divas_overload_use_case_imp_flow Workflow
 * -# Signed division calculation.
 *    \snippet qs_divas_overload.c main_1
 * -# Unsigned division calculation.
 *    \snippet qs_divas_overload.c main_2
 * -# Signed reminder calculation.
 *    \snippet qs_divas_overload.c main_3
 * -# Unsigned reminder calculation.
 *    \snippet qs_divas_overload.c main_4
 * -# Square root calculation.
 *    \snippet qs_divas_overload.c main_5
 * -# Infinite loop.
 *    \snippet qs_divas_overload.c main_6
 */

