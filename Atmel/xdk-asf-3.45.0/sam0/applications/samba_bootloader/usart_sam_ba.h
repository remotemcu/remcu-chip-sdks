/**
 * \file
 *
 * \brief USART functions for SAM-BA on SAM0
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

#ifndef _USART_SAM_BA_H_
#define _USART_SAM_BA_H_

/* USART buffer size (must be a power of two) */
#define USART_BUFFER_SIZE        128

/* Define the default time-out value for USART. */
#define USART_DEFAULT_TIMEOUT    1000

/* Xmodem related defines */
/* CRC16  polynomial */
#define CRC16POLY                0x1021

#define SHARP_CHARACTER          '#'

/* X/Ymodem protocol: */
#define SOH                      0x01
//#define STX                    0x02
#define EOT                      0x04
#define ACK                      0x06
#define NAK                      0x15
#define CAN                      0x18
#define ESC                      0x1b

#define PKTLEN_128               128
//#define PKTLEN_1K   1024


/**
 * \brief Open the given USART
 */
void usart_open(void);

/**
 * \brief Stops the USART
 */
void usart_close(void);

/**
 * \brief Puts a byte on usart line
 *
 * \param value      Value to put
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
int usart_putc(int value);

/**
 * \brief Waits and gets a value on usart line
 *
 * \return value read on usart line
 */
int usart_getc(void);

/**
 * \brief Returns true if the SAM-BA Uart received the sharp char
 *
 * \return Returns true if the SAM-BA Uart received the sharp char
 */
int usart_sharp_received(void);

/**
 * \brief This function checks if a character has been received on the usart line
 *
 * \return \c 1 if a byte is ready to be read.
 */
bool usart_is_rx_ready(void);

/**
 * \brief Gets a value on usart line
 *
 * \return value read on usart line
 */
int usart_readc(void);

/**
 * \brief Send buffer on usart line
 *
 * \param data pointer
 * \param number of data to send
 * \return number of data sent
 */
uint32_t usart_putdata(void const* data, uint32_t length); //Send given data (polling)

/**
 * \brief Gets data from usart line
 *
 * \param data pointer
 * \param number of data to get
 * \return value read on usart line
 */
uint32_t usart_getdata(void* data, uint32_t length); //Get data from comm. device

/**
 * \brief Send buffer on usart line using Xmodem protocol
 *
 * \param data pointer
 * \param number of data to send
 * \return number of data sent
 */
uint32_t usart_putdata_xmd(void const* data, uint32_t length); //Send given data (polling) using xmodem (if necessary)

/**
 * \brief Gets data from usart line using Xmodem protocol
 *
 * \param data pointer
 * \param number of data to get
 * \return value read on usart line
 */
uint32_t usart_getdata_xmd(void* data, uint32_t length); //Get data from comm. device using xmodem (if necessary)

/**
 * \brief Gets data from usart line using Xmodem protocol
 *
 * \param data pointer
 * \param number of data to get
 * \return value read on usart line
 */
unsigned short add_crc(char ptr, unsigned short crc);

uint8_t getPacket(uint8_t *pData, uint8_t sno);

#endif // _USART_SAM_BA_H_
