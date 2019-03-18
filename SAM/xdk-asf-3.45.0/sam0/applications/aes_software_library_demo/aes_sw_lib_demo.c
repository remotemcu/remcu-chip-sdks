/**
 * \file AES-128 five confidentiality modes demo example using 
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


/* Include ASF  file */
#include <asf.h>
#include "conf_example.h"
#include "crypt.h"

/** Global Variable declaration **/

/* Pointer to the EDBG UART module instance */
struct usart_module usart_instance;

/* Key Initialization vector */
uint8_t key_vectors[] = {0x2b, 0x7e, 0x15, 0x16,
                         0x28, 0xae, 0xd2, 0xa6,
                         0xab, 0xf7, 0x15, 0x88,
                         0x09, 0xcf, 0x4f, 0x3c};

/*  Initialization vector 
 * Note: AES Standard FIPS SP800-38A provides detailed explanation 
 * on generation of init_vector for different CFB modes
 */
#if (AES_CBC == true) | (AES_CFB == true) | (AES_OFB == true)

	uint8_t init_vector[] = {0x00, 0x01, 0x02, 0x03,
							 0x04, 0x05, 0x06, 0x07,
							 0x08, 0x09, 0x0a, 0x0b,
							 0x0c, 0x0d, 0x0e, 0x0f};

#endif

/* Input plain text data that are to be encrypted */
uint8_t pText[64] = {"Input_Text_blck1Input_Text_blck2Input_Text_blck3Input_Text_blck4"};
/* array to store the encrypted message */
uint8_t cText[64];
/* array to store the decrypted message */
uint8_t pText1[64];

/**  Function Prototypes **/

/*! \brief Configure EDBG USART for stdio function.
 */
static void configure_usart(void);

/*! \brief Hard fault handler to handle if any hard fault occurs.
 */
void HardFault_Handler(void)
{
  while(1);
}

/*!
 * \brief Initialize USART to communicate with on board EDBG - SERCOM 
 * with the following settings.
 * - 8-bit asynchronous USART
 * - No parity
 * - One stop bit
 * - 115200 baud
 */ 
static void configure_usart(void)
{
	struct usart_config config_usart;
	// Get the default USART configuration
	usart_get_config_defaults(&config_usart);
	// Configure the baudrate
	config_usart.baudrate = 115200;
	// Configure the pin multiplexing for USART
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	// route the printf output to the USART
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	// enable USART
	usart_enable(&usart_instance);
}

/*!
 * \brief Main application function.                              \n
 * -> Initialize clock                                            \n
 * -> Initialize USART for print functions                        \n
 * -> Initialize AES to generate Key schedule for AES-128         \n
 * -> Based on the AES mode enabled in conf_example.h file,       \n
 *    execute encryption and decryption of a message and          \n
 *    compare them against input data to check its functionality. \n
 * -> The decrypted message can be viewed on the COM port terminal \n
 */
int main(void)
{

	/*
	 * Initialize the System clock 
	 * Note: Clock should be configured in conf_clock.h
	 */
	system_init();

	/* Configure EDBG SERCOM UART to print messages */
	configure_usart();

	/* Generate key schedule for AES-128 from the Cipher Key */
	aes_init(key_vectors); 

	/* Print status messages */
	printf("AES key generated successfully!..\r\n");
	/* Print Input message for user */
	printf("\n The message to be encrypted is:\r\n");
	printf("\n %s \r\n",pText);

	/*
	 * Perform ECB, CFB, OFB, CTR and CBC Encryption and Decryption
	 * based on the mode enabled in conf_example.h. User can choose
	 * the mode that he wants to evaluate. By default, all modes are
	 * enabled.
	 * The decrypted message is printed to EDBG virtual COM port.
	 * If the decrypted message is same as the input plain text,
	 * it ensures the working of each mode.
	 */
#if (AES_ECB == true)
        
     	//Perform ECB Encryption
	ecb_encrypt( pText, cText, sizeof(pText) );
	for (volatile int i = 0; i < 1000; i++);
	//Perform ECB Decryption
	ecb_decrypt( cText, pText1, sizeof(cText));
	//Print decrypted message
	printf("\n Decrypted message using AES-ECB mode : \r\n");
	printf("\n %s \r\n",pText1);

#endif

#if (AES_CFB == true)

	//Perform CFB Encryption
	cfb_encrypt(pText, cText, init_vector, CFB_MODE_128, sizeof(pText));
	for (volatile int i = 0; i < 1000; i++);
	//Perform CFB Decryption
	cfb_decrypt(cText, pText1, init_vector, CFB_MODE_128, sizeof(cText));
	//Print decrypted message
	printf("\n Decrypted message using AES-CFB mode : \r\n");
	printf("\n %s \r\n",pText1);
 
#endif

#if (AES_OFB == true)

	//Perform OFB Encryption
	ofb_encrypt(pText, cText, init_vector, sizeof(pText));
	for (volatile int i = 0; i < 1000; i++);
	//Perform OFB Decryption
	ofb_encrypt(cText, pText1, init_vector, sizeof(cText));
	//Print decrytped message
	printf("\n Decrypted message using AES-OFB mode : \r\n");
	printf("\n %s \r\n",pText1);

#endif

#if (AES_CTR == true)

	/* Initialize Counter block with initialization vector, 
	 * nonce and counter value
	 */
	ctr_blk_t counter_vector = {
		.i_vector = AES_CTR_IVECTOR,
		.nonce = AES_CTR_NONCE,
		.counter = AES_CTR_COUNTER
	};
	//Perform CTR Encryption
	ctr_encrypt_decrypt(pText, cText, &counter_vector, sizeof(pText));
	//Send Counter block value to decryptor
	for (volatile int i = 0; i < 1000; i++);
	counter_vector.i_vector = AES_CTR_IVECTOR;
	counter_vector.nonce = AES_CTR_NONCE;
	counter_vector.counter = AES_CTR_COUNTER;
	//Perform CTR Decryption
	ctr_encrypt_decrypt(cText, pText1, &counter_vector, sizeof(pText1));
	//Print decrypted message
	printf("\n Decrypted message using AES-CTR mode : \r\n");
	printf("\n %s \r\n",pText1);

#endif

/*! \warning CBC mode is done at the last as it process input plain text 
 * during encryption and so the plain text value is not retained.
 * For testing purpose, to preserve the input plan text for testing with
 * other modes, this mode is added at the last.
 */
#if (AES_CBC == true)

	//Perform CBC Encryption
	cbc_encrypt(pText, cText, init_vector, sizeof(pText));
	for (volatile int i = 0; i < 1000; i++);
	//Perform CBC Decryption
	cbc_decrypt(cText, pText1, init_vector, sizeof(cText));
	//Print decrypted message
	printf("\n Decrypted message using AES-CBC mode : \r\n");
	printf("\n %s \r\n",pText1);

#endif

	/* Forever loop */
	while(1);

}

/* Application Documentation */
/*! \mainpage
 * \section intro Introduction
 * This is the documentation of software library implementation of 
 * AES-128 (FIPS -197)and its five confidentiality modes (FIPS SP800-38A) 
 * as per FIPS standard. This also give demonstration example implementing 
 * the five modes.
 * 
 * In this example, for a given 64 block of input plain text, AES encryption 
 * is performed. The Decryption is performed on the resulting cipher text.
 * The resulting plain text should be same as that of the input plain text.
 * This confirms the working of each mode.
 *
 * The corresponding application note mentioned below should be referred for 
 * the detailed documentation about software library implementation and 
 * AES mode description. 
 * Application Note: Software library for AES-128 Encryption and Decryption 
 *
 * \section files Main files related to this application
 * - aes.c          : AES-128 source file
 * - aes.h          : AES-128 header file
 * - crypt.c        : 5 modes of AES-128 source file
 * - crypt.h        : 5 modes of AES-128 header file
 * - conf_clock.h   : Clock configuration file
 * - conf_example.h : Example configuration file
 * - main.c         : Main Application file
 *
 * \section referenceinfo References
 * - Application Note : Software library for AES-128 Encryption and Decryption
 * - Respective Device datasheet
 * - FIPS-197 standard for description about AES-128 algorithm
 * - FIPS SP800-38A standard for 5 modes description
 *
 * 
 * \section compinfo Compiler Support
 * This application supports 
 * - ARM GCC
 *
 * \section testinfo Test Information
 * This example has been tested on SAM D21 Xplained Pro board.
 * As the AES software library is platform independent, the
 * implementation can be adopted for any device.
 * 
 * \section setupinfo Setup Information of this example
 * The SAM D21 Xplained Pro board is connected to PC via EBDG port.
 * Terminal window with EDBG Virtual COM port should be opened with 
 * setting 115200 baud rate, No parity and 1 stop bit with hardware
 * flow control None.
 * Once the firmware is programmed, the input plain text message and 
 * message after decrypting is printed. Both the message should
 * be same if the encryption and decryption of all modes are executed
 * properly. 
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 * Support and FAQ: visit
 * <a href="https://www.microchip.com/support/">Microchip Support</a>
 *
 * \author
 * Microchip Technology Inc : http://www.microchip.com \n
 */
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 


