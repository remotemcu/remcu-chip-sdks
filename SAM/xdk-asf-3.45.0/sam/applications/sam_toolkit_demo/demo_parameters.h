/**
 * \file
 *
 * \brief SAM toolkit demo parameter header file.
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef DEMO_PARAMETERS_H_INCLUDED
#define DEMO_PARAMETERS_H_INCLUDED

#include "rtouch.h"

/** Parameters magic number, LMTA */
#define DEMO_PARAMETERS_MAGIC 0x4c4d5441

/** Demo calibration number */
#define DEMO_CALIB_NUM 5

/** This structure is used to save application parameters in Internal Flash */
typedef struct
{
	uint32_t magic ;
	uint32_t ppt_delay ;
	uint32_t hour ;
	uint32_t minute ;
	uint32_t second ;
	uint32_t day ;
	uint32_t month ;
	uint32_t year ;
	uint32_t backlight ;
	rtouch_calibration_point_t calib_points[DEMO_CALIB_NUM] ;
} demo_param_t ;

/** Parameters used for demo */
extern demo_param_t g_demo_parameters ;

uint32_t demo_parameters_initialize( void ) ;
uint32_t demo_parameters_commit_changes( void ) ;

#endif /* DEMO_PARAMETERS_H_INCLUDED */
