/**
 *
 * \file
 *
 * \brief UTF-8 utils.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#include "asf.h"
#include "FreeRTOS.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int u8_convert(char *dest, int sz, unsigned int *src, int srcsz)
{
	unsigned int ch;
	int i = 0;
	char *dest_end = dest + sz;

	while (srcsz<0 ? src[i]!=0 : i < srcsz) {
		ch = src[i];
		if (ch < 0x80) {
			if (dest >= dest_end)
			return i;
			*dest++ = (char)ch;
		}
		else if (ch < 0x800) {
			if (dest >= dest_end-1)
			return i;
			*dest++ = (ch>>6) | 0xC0;
			*dest++ = (ch & 0x3F) | 0x80;
		}
		else if (ch < 0x10000) {
			if (dest >= dest_end-2)
			return i;
			*dest++ = (ch>>12) | 0xE0;
			*dest++ = ((ch>>6) & 0x3F) | 0x80;
			*dest++ = (ch & 0x3F) | 0x80;
		}
		else if (ch < 0x110000) {
			if (dest >= dest_end-3)
			return i;
			*dest++ = (ch>>18) | 0xF0;
			*dest++ = ((ch>>12) & 0x3F) | 0x80;
			*dest++ = ((ch>>6) & 0x3F) | 0x80;
			*dest++ = (ch & 0x3F) | 0x80;
		}
		i++;
	}
	if (dest < dest_end)
	*dest = '\0';
	return i;
}

int u8_get_req_len(unsigned int *src, int sz)
{
	unsigned int ch;
	int i = 0;
	int len = 0;

	while (sz<0 ? src[i]!=0 : i < sz) {
		ch = src[i];
		if (ch < 0x80) {
			len = len+1;
		}
		else if (ch < 0x800) {
			len = len+2;
		}
		else if (ch < 0x10000) {
			len = len+3;
		}
		else if (ch < 0x110000) {
			len = len+4;
		}
		i++;
	}
	return len;
}

unsigned int* u8_encode(const wchar_t line[])
{
	unsigned int *wcs = NULL;
	int len = 0, i;
	
	len = wcslen(line) + 1; // include space for the end of string '\0' character
	if (len == 1) {
		return NULL;
	}
	unsigned int *utf8_input = (unsigned int *)pvPortMalloc(len * sizeof(int));
	if(utf8_input == NULL) {
			return NULL;
	}
	for (i = 0; i < len; i++)
		utf8_input[i] = line[i];
		
	int utf8len = u8_get_req_len(utf8_input, len);
	wcs = (unsigned int *)pvPortMalloc(utf8len * sizeof(char));
	if(wcs == NULL) {
		vPortFree(utf8_input);
		return NULL;
	}
	
	u8_convert(wcs, utf8len, utf8_input, len);
	vPortFree(utf8_input);
	return wcs;
}


#if 0 // Some more utility functions

static const unsigned int offsetsFromUTF8[6] = {
    0x00000000UL, 0x00003080UL, 0x000E2080UL,
    0x03C82080UL, 0xFA082080UL, 0x82082080UL
};

static const char trailingBytesForUTF8[256] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/* This returns length of next utf-8 sequence */
int utf8_seqlen(char *s)
{
    return trailingBytesForUTF8[(unsigned int)(unsigned char)s[0]] + 1;
}

/* conversions without error checking
   only works for valid UTF-8, i.e. no 5- or 6-byte sequences
   srcsz = source size in bytes, or -1 if 0-terminated
   sz = dest size in # of wide characters

   returns # characters converted
   dest will always be L'\0'-terminated, even if there isn't enough room
   for all the characters.
   if sz = srcsz+1 (i.e. 4*srcsz+4 bytes), there will always be enough space.
*/
int u8_toucs(unsigned int *dest, int sz, char *src, int srcsz)
{
    unsigned int ch;
    char *src_end = src + srcsz;
    int nb;
    int i=0;

    while (i < sz-1) {
        nb = trailingBytesForUTF8[(unsigned char)*src];
        if (srcsz == -1) {
            if (*src == 0)
                goto done_toucs;
        }
        else {
            if (src + nb >= src_end)
                goto done_toucs;
        }
        ch = 0;
        switch (nb) {
            /* these fall through deliberately */
        case 3: ch += (unsigned char)*src++; ch <<= 6;
        case 2: ch += (unsigned char)*src++; ch <<= 6;
        case 1: ch += (unsigned char)*src++; ch <<= 6;
        case 0: ch += (unsigned char)*src++;
        }
        ch -= offsetsFromUTF8[nb];
        dest[i++] = ch;
    }
 done_toucs:
    dest[i] = 0;
    return i;
}
int u8_wc_toutf8(char *dest, unsigned int ch)
{
	if (ch < 0x80) {
		dest[0] = (char)ch;
		return 1;
	}
	if (ch < 0x800) {
		dest[0] = (ch>>6) | 0xC0;
		dest[1] = (ch & 0x3F) | 0x80;
		return 2;
	}
	if (ch < 0x10000) {
		dest[0] = (ch>>12) | 0xE0;
		dest[1] = ((ch>>6) & 0x3F) | 0x80;
		dest[2] = (ch & 0x3F) | 0x80;
		return 3;
	}
	if (ch < 0x110000) {
		dest[0] = (ch>>18) | 0xF0;
		dest[1] = ((ch>>12) & 0x3F) | 0x80;
		dest[2] = ((ch>>6) & 0x3F) | 0x80;
		dest[3] = (ch & 0x3F) | 0x80;
		return 4;
	}
	return 0;
}

int u8_is_locale_utf8(char *locale)
{
	/* this code based on libutf8 */
	const char* cp = locale;

	for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++) {
		if (*cp == '.') {
			const char* encoding = ++cp;
			for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++)
			;
			if ((cp-encoding == 5 && !strncmp(encoding, "UTF-8", 5))
			|| (cp-encoding == 4 && !strncmp(encoding, "utf8", 4)))
			return 1; /* it's UTF-8 */
			break;
		}
	}
	return 0;
}


int u8_vprintf(char *fmt, va_list ap)
{
	int cnt, sz=0;
	char *buf;
	unsigned int *wcs;

	sz = 512;
	buf = (char*)alloca(sz);
	try_print:
	cnt = vsnprintf(buf, sz, fmt, ap);
	if (cnt >= sz) {
		buf = (char*)alloca(cnt - sz + 1);
		sz = cnt + 1;
		goto try_print;
	}
	wcs = (unsigned int*)alloca((cnt+1) * sizeof(unsigned int));
	cnt = u8_toucs(wcs, cnt+1, buf, cnt);
	printf("%ls", (wchar_t*)wcs);
	return cnt;
}

int u8_printf(char *fmt, ...)
{
	int cnt;
	va_list args;

	va_start(args, fmt);

	cnt = u8_vprintf(fmt, args);

	va_end(args);
	return cnt;
}

#endif