/**
 * \file
 *
 * \brief  Pulse Density Modulation Interface Controller Example
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

/**
 * \mainpage  Pulse Density Modulation Interface Controller Example
 *
 * \section Purpose
 * This example demonstrates the use of the PDMIC module and reads data from a PDM microphone.
 *
 *
 * \section Requirements
 *
 * This example can be used on any SAMG board.
 * A PDM microphone must be connected on PA9 (PDMDAT) and PA10 (PDMCLK).
 *
 * \section Description
 * This example will continuously read 30 ms blocks of PDM data from the microphone via DMA and
 * place the filtered PCM data into the two buffers in the audio_buffer array. This means
 * the application can process 30 ms of data at a time, while the module continues to read
 * from the microphone.
 *
 * Configuration of the PDM module is as follows:
 * - 1MHz PDM clock
 * - Oversampling ratio 64
 * - Data size 16 bits
 * - All digital signal processing enabled
 * 
 *
 * \section Usage
 * When running the example, 30 ms of data from the connected PDM microphone will be read into the
 * audio_buffer array at a time.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

/*
 * Size of each PCM sample.
 * 1 MHz PDM clock, decimation of 64 -> Sampling rate 16kHz
 * 480 samples gives us 30 milliseconds of data.
 */
#define PCM_BUF_SIZE 480

/* Prescaler value for 1MHz PDM clock when running on 48MHz */
#define PRESCALER (48000000/(2*1000000))-1

/* Globally available PDMIC module struct */
static struct pdm_instance pdm;
/* Two buffers to store the PCM data */
static int16_t audio_buffer[2][PCM_BUF_SIZE];
/* Global variable to say which of the buffers should be used */
static uint8_t buffer_index = 0;
 
 
 /* Function to initalize the PDC transfer */
 static void init_pdc(void)
 {
	 struct pdc_packet packet;
	 Pdc *pdmic_pdc;
	 pdmic_pdc = pdmic_get_pdc_base(PDMIC0);
	 
	 /* Set buffer address and size */
	 packet.ul_addr = (uint32_t)&(audio_buffer[buffer_index][0]);
	 packet.ul_size = PCM_BUF_SIZE;

	 /* Initialize and enable PDC */
	 pdc_rx_init(pdmic_pdc, &packet, NULL);
	 pdc_enable_transfer(pdmic_pdc, PERIPH_PTCR_RXTEN);
 }
 
/* Callback for PDC transfer complete */
static void buffer_callback(const struct pdm_instance *const module)
{
	/* Toggle which buffer to fill */
	buffer_index ^= 1;
	/* Configure PDC to fill next buffer */
	init_pdc();
	/* Re-enable interrupt */
	pdm_enable_interrupt(&pdm, PDMIC_INTERRUPT_SRC_TRANSFER_END);
}

/* Function to initialize callback */
static void init_callback(void)
{
	/* Register callback for PDC transfer end */
	pdm_register_callback(&pdm, buffer_callback, PDM_CALLBACK_TRANSFER_END);
	/* Enable callback for PDC transfer end */
	pdm_enable_callback(&pdm, PDM_CALLBACK_TRANSFER_END);
	/* Enable interrupt for PDC transfer end */
	pdm_enable_interrupt(&pdm, PDMIC_INTERRUPT_SRC_TRANSFER_END);
	/* Enable IRQ */
	NVIC_EnableIRQ((IRQn_Type) PDMIC0_IRQn);
}

/* Function to setup the PDM module */
static void init_pdm(void)
{
	/* PDM configuration structure */
	struct pdm_config conf;
	/* Get default configuration */
	pdm_get_config_default(&conf);

	/* Prescaler for 1 MHz PDM clock */
	conf.prescal = PRESCALER;
	/* Set gain to 1 - if not, all conversions are 0 */
	conf.gain = 1;
	/* Oversampling ratio */
	conf.oversampling_ratio = PDMIC_OVERSAMPLING_RATIO_64;
	/* Data size */
	conf.conver_data_size = PDMIC_CONVERTED_DATA_SIZE_16;
	
	/* Initialize PDMIC0 with configuration */
	pdm_init(&pdm, PDMIC0, &conf);
}

int main (void)
{

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Configure PDM module*/
	init_pdm();
	/* Configure PDC */
	init_pdc();
	/* Configure callback */
	init_callback();

	Enable_global_interrupt();

	/* Enable PDM module */
	pdm_enable(&pdm);
	
	while(1) {
		/* PDM Data is continuously being read into audio_buffer */
	}
	
}
