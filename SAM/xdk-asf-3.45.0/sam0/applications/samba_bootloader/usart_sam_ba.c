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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "usart_sam_ba.h"
#include "conf_board.h"
#include "conf_clocks.h"
#include "conf_bootloader.h"

/* Local reference to current Usart instance in use with this driver */
struct usart_module usart_sam_ba;

/* Variable to let the main task select the appropriate communication interface */
volatile uint8_t b_sharp_received;

/* RX and TX Buffers + rw pointers for each buffer */
volatile uint8_t buffer_rx_usart[USART_BUFFER_SIZE];

volatile uint8_t idx_rx_read;
volatile uint8_t idx_rx_write;

volatile uint8_t buffer_tx_usart[USART_BUFFER_SIZE];

volatile uint8_t idx_tx_read;
volatile uint8_t idx_tx_write;

/* Test for timeout in AT91F_GetChar */
uint8_t error_timeout;
uint16_t size_of_data;
uint8_t mode_of_transfer;


/**
 * \brief Open the given USART
 */
void usart_open()
{
	struct usart_config config;

	usart_get_config_defaults(&config);

	config.baudrate     = BOOT_USART_BAUDRATE;
	config.mux_setting  = BOOT_USART_MUX_SETTINGS;
#ifdef BOOT_USART_PAD0
	config.pinmux_pad0  = BOOT_USART_PAD0;
#endif
#ifdef BOOT_USART_PAD1
	config.pinmux_pad1  = BOOT_USART_PAD1;
#endif
#ifdef BOOT_USART_PAD2
	config.pinmux_pad2  = BOOT_USART_PAD2;
#endif
#ifdef BOOT_USART_PAD3
	config.pinmux_pad3  = BOOT_USART_PAD3;
#endif
	config.generator_source = BOOT_USART_GCLK_SOURCE;

	while (usart_init(&usart_sam_ba, BOOT_USART_MODULE, &config)
			!= STATUS_OK) {
	}

	usart_enable(&usart_sam_ba);
	usart_enable_transceiver(&usart_sam_ba, USART_TRANSCEIVER_TX);
	usart_enable_transceiver(&usart_sam_ba, USART_TRANSCEIVER_RX);
	//Initialize flag
	b_sharp_received = false;
	idx_rx_read = 0;
	idx_rx_write = 0;
	idx_tx_read = 0;
	idx_tx_write = 0;

	error_timeout = 0;
}

/**
 * \brief Close the given USART
 */
void usart_close(void)
{
	usart_disable(&usart_sam_ba);
	usart_disable_transceiver(&usart_sam_ba, USART_TRANSCEIVER_TX);
	usart_disable_transceiver(&usart_sam_ba, USART_TRANSCEIVER_RX);
}

/**
 * \brief Puts a byte on usart line
 * The type int is used to support printf redirection from compiler LIB.
 *
 * \param value Value to put
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
int usart_putc(int value)
{
	usart_write_wait(&usart_sam_ba, (uint16_t)value);
	return 1;
}



int usart_getc(void) {
	uint16_t retval;
	//Wait until input buffer is filled
	while(!(usart_is_rx_ready()));
	usart_read_wait(&usart_sam_ba, &retval);
	return (int)retval;

}

int usart_sharp_received(void) {
	if (usart_is_rx_ready()) {
		if (usart_getc() == SHARP_CHARACTER)
			return (true);
	}
	return (false);
}

bool usart_is_rx_ready(void) {
	return (BOOT_USART_MODULE->USART.INTFLAG.reg & SERCOM_USART_INTFLAG_RXC);
}

int usart_readc(void) {
	int retval;
	retval = buffer_rx_usart[idx_rx_read];
	idx_rx_read = (idx_rx_read + 1) & (USART_BUFFER_SIZE - 1);
	return (retval);
}

/**
 * \brief Send given data (polling)
 */
uint32_t usart_putdata(void const* data, uint32_t length) {
	uint32_t i;
	uint8_t* ptrdata;
	ptrdata = (uint8_t*) data;
	for (i = 0; i < length; i++) {
		usart_putc(*ptrdata);
		ptrdata++;
	}
	return (i);
}

/**
 * \brief Get data from com device
 */
uint32_t usart_getdata(void* data, uint32_t length) {
	uint8_t* ptrdata;
	ptrdata = (uint8_t*) data;
	*ptrdata = usart_getc();
	return (1);
}

/**
 * \brief Compute the CRC
 */
unsigned short add_crc(char ptr, unsigned short crc) {

	unsigned short cmpt;

	crc = crc ^ (int) ptr << 8;

	for (cmpt = 0; cmpt < 8; cmpt++) {
		if (crc & 0x8000)
			crc = crc << 1 ^ CRC16POLY;
		else
			crc = crc << 1;
	}

	return (crc & 0xFFFF);
}

static uint16_t getbytes(uint8_t *ptr_data, uint16_t length) {
	uint16_t crc = 0;
	uint16_t cpt;
	uint8_t c;

	for (cpt = 0; cpt < length; ++cpt) {
		c = usart_getc();
		if (error_timeout)
			return 1;
		crc = add_crc(c, crc);
		//crc = (crc << 8) ^ xcrc16tab[(crc>>8) ^ c];
		if (size_of_data || mode_of_transfer) {
			*ptr_data++ = c;
			if (length == PKTLEN_128)
				size_of_data--;
		}
	}

	return crc;
}

/**
 * \brief Used by Xup to send packets.
 */
static int putPacket(uint8_t *tmppkt, uint8_t sno) {
	uint32_t i;
	uint16_t chksm;
	uint8_t data;

	chksm = 0;

	usart_putc(SOH);

	usart_putc(sno);
	usart_putc((uint8_t) ~(sno));

	for (i = 0; i < PKTLEN_128; i++) {
		if (size_of_data || mode_of_transfer) {
			data = *tmppkt++;
			size_of_data--;
		} else
			data = 0x00;

		usart_putc(data);

		chksm = add_crc(data, chksm);
	}

	/* An "endian independent way to extract the CRC bytes. */
	usart_putc((uint8_t) (chksm >> 8));
	usart_putc((uint8_t) chksm);

	return (usart_getc()); /* Wait for ack */
}

/**
 * \brief Used by Xdown to retrieve packets.
 */
uint8_t getPacket(uint8_t *ptr_data, uint8_t sno) {
	uint8_t seq[2];
	uint16_t crc, xcrc;

	getbytes(seq, 2);
	xcrc = getbytes(ptr_data, PKTLEN_128);
	if (error_timeout)
		return (false);

	/* An "endian independent way to combine the CRC bytes. */
	crc = (uint16_t) usart_getc() << 8;
	crc += (uint16_t) usart_getc();

	if (error_timeout == 1)
		return (false);

	if ((crc != xcrc) || (seq[0] != sno) || (seq[1] != (uint8_t) (~sno))) {
		usart_putc(CAN);
		return (false);
	}

	usart_putc(ACK);
	return (true);
}

/**
 * \brief Called when a transfer from target to host is being made(considered an upload).
 */
uint32_t usart_putdata_xmd(void const* data, uint32_t length) {
	uint8_t c, sno = 1;
	uint8_t done;
	uint8_t * ptr_data = (uint8_t *) data;
	error_timeout = 0;
	if (!length)
		mode_of_transfer = 1;
	else {
		size_of_data = length;
		mode_of_transfer = 0;
	}

	if (length & (PKTLEN_128 - 1)) {
		length += PKTLEN_128;
		length &= ~(PKTLEN_128 - 1);
	}

	/* Startup synchronization... */
	/* Wait to receive a NAK or 'C' from receiver. */
	done = 0;
	while (!done) {
		c = (uint8_t) usart_getc();
		if (error_timeout) { // Test for timeout in usart_getc
			error_timeout = 0;
			c = (uint8_t) usart_getc();
			if (error_timeout) {
				error_timeout = 0;
				return (0);
			}
		}
		switch (c) {
		case NAK:
			done = 1;
			break;
		case 'C':
			done = 1;
			break;
		case 'q': /* ELS addition, not part of XMODEM spec. */
			return (0);
		default:
			break;
		}
	}

	done = 0;
	sno = 1;
	while (!done) {
		c = (uint8_t) putPacket((uint8_t *) ptr_data, sno);
		if (error_timeout) { // Test for timeout in usart_getc
			error_timeout = 0;
			return (0);
		}
		switch (c) {
		case ACK:
			++sno;
			length -= PKTLEN_128;
			ptr_data += PKTLEN_128;
			break;
		case NAK:
			break;
		case CAN:
		case EOT:
		default:
			done = 0;
			break;
		}
		if (!length) {
			usart_putc(EOT);
			usart_getc(); /* Flush the ACK */
			break;
		}
	}

	mode_of_transfer = 0;
	return (1);
}

/**
 * \brief Called when a transfer from host to target is being made (considered an download).
 */
uint32_t usart_getdata_xmd(void* data, uint32_t length) {
	uint32_t timeout;
	char c;
	uint8_t * ptr_data = (uint8_t *) data;
	uint32_t b_run, nbr_of_timeout = 100;
	uint8_t sno = 0x01;

	//Copied from legacy source code ... might need some tweaking
	uint32_t loops_per_second = system_clock_source_get_hz(CONF_CLOCK_GCLK_0_CLOCK_SOURCE) / 10;

	error_timeout = 0;

	if (length == 0)
		mode_of_transfer = 1;
	else {
		size_of_data = length;
		mode_of_transfer = 0;
	}

	/* Startup synchronization... */
	/* Continuously send NAK or 'C' until sender responds. */
	while (1) {
		usart_putc('C');
		timeout = loops_per_second;
		while (!(usart_is_rx_ready()) && timeout)
			timeout--;
		if (timeout)
			break;

		if (!(--nbr_of_timeout))
			return (0);
	}

	b_run = true;
	while (b_run != false) {
		c = (char) usart_getc();
		if (error_timeout) { // Test for timeout in usart_getc
			error_timeout = 0;
			return (0);
		}
		switch (c) {
		case SOH: /* 128-byte incoming packet */
			b_run = getPacket(ptr_data, sno);
			if (error_timeout) { // Test for timeout in usart_getc
				error_timeout = 0;
				return (0);
			}
			if (b_run == true) {
				++sno;
				ptr_data += PKTLEN_128;
			}
			break;
		case EOT:
			usart_putc(ACK);
			b_run = false;
			break;
		case CAN:
		/* "X" User-invoked abort */
		case ESC:
		default:
			b_run = false;
			break;
		}
	}
	mode_of_transfer = 0;
	return (true);
}

