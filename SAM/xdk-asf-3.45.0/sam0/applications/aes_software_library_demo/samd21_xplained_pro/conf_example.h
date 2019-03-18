/**
 * \file Example configuration file AES-128 mode demo example using 
 *        Software Library
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
 /**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef CONF_EXAMPLE_H_
#define CONF_EXAMPLE_H_


/* Set to true to enable respective mode 
 * set to false to disable the respective mode
 */
//Enable/Disable ECB mode
#define AES_ECB    true

//Enable/Disable CBC mode
#define AES_CBC    true

//Enable/Disable CFB mode
#define AES_CFB    true

//Enable/Disable OFB mode
#define AES_OFB    true

//Enable/Disable CTR mode
#define AES_CTR    true


/* If CTR mode is enabled, load the counter, nonce and IV value */
#if (AES_CTR == true)
	#define AES_CTR_IVECTOR  0xC0543B59DA48D90BULL
	#define  AES_CTR_NONCE   0x006CB6DB
	#define  AES_CTR_COUNTER 0x00000001
#endif

// Available CFB modes
#define CFB_MODE_8    8
#define CFB_MODE_64   64
#define CFB_MODE_128  128

#endif /* CONF_EXAMPLE_H_ */