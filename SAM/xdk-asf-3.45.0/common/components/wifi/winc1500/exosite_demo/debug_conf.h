/*
 * \file
 *
 * \brief WINC1500 Exosite Example.
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
#ifndef DEBUG_CONF_H_INCLUDE
#define DEBUG_CONF_H_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif
	
/* Debug */
#define DEBUG(...)		printf(__VA_ARGS__)

#define DEBUG_EOL    "\r\n"
#define DEBUG_STRING_HEADER "-- WINC1500 chip & Exosite IoT Demo --"DEBUG_EOL \
"-- "BOARD_NAME " --"DEBUG_EOL	\
"-- Compiled: "__DATE__ " "__TIME__ " --"DEBUG_EOL

#define DEBUG_CONF_WIFI			"WINC1500: "
#define DEBUG_CONF_SOCKET		"SOCKET: "
#define DEBUG_CONF_IO1_BOARD	"IO1_BOARD: "
#define DEBUG_CONF_EXOSITE		"EXOSITE: "

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_CONF_H_INCLUDE */