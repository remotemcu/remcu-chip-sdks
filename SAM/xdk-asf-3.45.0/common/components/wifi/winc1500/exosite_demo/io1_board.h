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


#ifndef IO1_BOARD_H_INCLUDE
#define IO1_BOARD_H_INCLUDE

#include <ctype.h>
#include "driver/include/m2m_types.h"

#ifdef __cplusplus
extern "C" {
#endif
	
#define IO1_BOARD_VENDOR_LENGTH_MAX 50
#define IO1_BOARD_ID_LENGTH_MAX 100
#define IO1_BOARD_SERIAL_NUMBER_LENGTH_MAX 100
#define IO1_BOARD_PASSWORD_LENGTH_MAX 100
#define IO1_BOARD_SSID_LENGTH_MAX 100

/** 
*	\brief structure of io1_board information.
*/
typedef struct _io1_board_info
{
	char board_vendor[IO1_BOARD_VENDOR_LENGTH_MAX];
	char board_id[IO1_BOARD_ID_LENGTH_MAX];
	char board_sn[IO1_BOARD_SERIAL_NUMBER_LENGTH_MAX];
	char cik[50];
	uint8_t is_activate;
}io1_board_info;

/*
*	\brief	Initialize each sensor of io1 board.
*
*	\return	true initialized sensor of io1 board.
*/
bool	io1_board_init(void);

/*
*	\brief Returns pointer to the io1-board information.
*	
*	\return	io1_board information ex> name, vendor, s/n.
*/
io1_board_info * io1_board_get_info(void);

/*
*	\brief	Prepares io1_sensor_module for using sensor information.
*			call it, before call io1_board_prepare_to_get_info function.
*/
void	io1_board_prepare_to_get_info(void);

/*
*	\brief	Returns the value of temperature sensor.
*
*	\return	the value of temperature sensor.	
*/
int		io1_board_get_temperature(void);


/*
*	\brief Returns the value of light sensor.
*
*	\return	the value of light sensor.
*/
int		io1_board_get_lightvalue(void);

/*
*	\brief  Sets the Io1 board LED (on,off).
*
*	\param	on	true, LED Light on.
*/
void	io1_board_set_led(bool on);

/*
*	\brief  Write cik value to SD card.
*
*	\param	cik value.
*	\return	true on success, false otherwise.
*/
bool	io1_board_save_cik_value_to_sd(char *pbuf);

/*
*	\brief  reset cik value
*
*/
void	io1_board_reset_cik_value(void);

#ifdef __cplusplus
}
#endif

#endif /* IO1_BOARD_H_ */