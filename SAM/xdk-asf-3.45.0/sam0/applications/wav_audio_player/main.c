/**
 * \file
 *
 * \brief SAM D20 DAC WAV AUDIO PLAYER
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
 * \mainpage SAM D20 DAC WAV Audio Player Application
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This application plays the .wav audio files that is stored in a
 * microSD card using the DAC module in SAM D20 devices.
 */

/**
 * \page appdoc_main SAM D20 WAV Audio Player Application
 *
 * Overview:
 * - \ref appdoc_sam0_dac_wav_player_intro
 * - \ref appdoc_sam0_dac_wav_player_setup
 * - \ref appdoc_sam0_dac_wav_player_usage
 * - \ref appdoc_sam0_dac_wav_player_compinfo
 * - \ref appdoc_sam0_dac_wav_player_contactinfo
 *
 * \section appdoc_sam0_dac_wav_player_intro Introduction
 * This application plays the .wav audio files that is stored in a
 * microSD card using the DAC module in SAM D20 devices.
 *
 * A timer is used to guarantee the DAC conversions are performed at the
 * correct sample rate, using the Event System module of the device to link
 * the periodic timer output events to the DAC module to trigger new sample 
 * conversions.
 * FAT file system is used to read the .wav files stored in microSD card.
 * Audio samples read from the opened file are stored in a buffer and then
 * played back using the DAC module.
 *
 * This application has been tested on following board:
 * - SAM D20 Xplained Pro
 *
 * \section appdoc_sam0_dac_wav_player_setup Hardware Setup
 * The device's DAC channel output (PA02) should be connected to an
 * audio amplifier / 3.5mm audio jack or an oscilloscope so that the 
 * generated audio can be listened / monitored.
 *
 * \section appdoc_sam0_dac_wav_player_usage Usage
 * The project directory will have two test .wav audio files. Copy
 * the audio files to a microSD card and plug it into the slot of the I/O1 
 * Xplained Pro wing board. Now plug the I/O1 wing board into the EXT1 header
 * of SAM D20 Xplained Pro board.
 *
 * When application starts, it will initialize the peripherals (Timer, Event
 * system, DAC and mounts the file system). After mounting, it will search for
 * the audio file specified in variable 'test_file_name[]'. Note that this
 * variable has to be initialized with the filename of one of the audio files 
 * copied into the microSD card.
 *
 * The file system will then open the file, read the audio header, estimate
 * the timer compare value based on sample rate, read the audio samples and
 * then plays back using DAC. 
 *
 * The timer will generate both interrupt and event. The event will move the
 * value in DAC DATABUF register to DAC DATA register. The interrupt handler
 * will load next data into DAC DATABUF register.
 *
 * The status of all the operation is sent to the terminal via the SERCOM
 * USART module connected to EDBG. The settings is 38400 baud 8-n-1.
 *
 * Refer application note 'Waveform Generator and WAV Audio Player using DAC'
 * for more details.
 *
 * \section appdoc_sam0_dac_wav_player_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_dac_wave_generator_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>

/* Audio buffer size of this example */
#define AUDIO_BUF_SIZE  1024

/* Global Variables */

/* Standard WAV audio header */
COMPILER_PACK_SET(1)
struct wav_header {
	char ChunkID[4];
	uint32_t ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	uint32_t Subchunk1Size;
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPerSample;
	char Subchunk2ID[4];
	uint32_t Subchunk2Size;
};
struct wav_header audio_header;
COMPILER_PACK_RESET()

/* Buffer and status variables */
int16_t temp_audio_buf[AUDIO_BUF_SIZE];
uint16_t audio_data_0[AUDIO_BUF_SIZE/2], audio_data_1[AUDIO_BUF_SIZE/2];
volatile uint16_t *audio_data_ptr;
volatile bool current_data_buf = 0, audio_playback_done = false;
uint32_t nb_audio_blocks, block_cnt, buf_cnt, i, j;
unsigned int temp;

/* Variable that selects the required audio file to play */
char test_file_name[] = "test_16khz.wav";
/* FAT FS variables */
Ctrl_status status;
FRESULT res;
FATFS fs;
FIL file_object;

/* ASF Driver module structure variables */
struct usart_module cdc_uart_module;
struct tc_module tc_inst;
struct dac_module dac_inst;

/* Function prototypes */
void timer_match_callback(struct tc_module *const module_inst);
static void cdc_uart_init(void);
static void timer_init(void);
static void dac_initialize(void);
static void evsys_init(void);
static void mount_file_system(void);

/* Timer 0 interrupt handler to process match channel 0 interrupt */
void timer_match_callback(struct tc_module *const module_inst)
{
	dac_chan_write(&dac_inst, 0, *audio_data_ptr++);
	buf_cnt++;
	if (buf_cnt == (AUDIO_BUF_SIZE/2))
	{
		buf_cnt = 0;
		audio_playback_done = true;
	}
}

/* STDIO serial driver initialization function */
static void cdc_uart_init(void)
{
	struct usart_config usart_conf;

	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	usart_conf.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	usart_conf.baudrate    = 38400;

	stdio_serial_init(&cdc_uart_module, EDBG_CDC_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/* Timer TC0 initialization function */
static void timer_init(void)
{
	struct tc_config conf_tc;
	struct tc_events conf_tc_events = \
		{.generate_event_on_compare_channel[0] = 1};
	tc_get_config_defaults(&conf_tc);
	conf_tc.clock_source = GCLK_GENERATOR_3;
	conf_tc.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	conf_tc.counter_16_bit.compare_capture_channel[0] = 0xFFFF;
	tc_init(&tc_inst, TC0, &conf_tc);
	tc_enable_events(&tc_inst, &conf_tc_events);
	tc_enable(&tc_inst);
	tc_stop_counter(&tc_inst);
	tc_register_callback(&tc_inst, \
							timer_match_callback, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_inst, TC_CALLBACK_CC_CHANNEL0);
}

/* DAC initialization */
static void dac_initialize(void)
{
	struct dac_config conf_dac;
	struct dac_events conf_dac_events = {.on_event_start_conversion = 1};
	dac_get_config_defaults(&conf_dac);
	conf_dac.clock_source = GCLK_GENERATOR_3;
	conf_dac.reference = DAC_REFERENCE_INT1V;
	dac_init(&dac_inst, DAC, &conf_dac);
	dac_enable_events(&dac_inst, &conf_dac_events);
	dac_enable(&dac_inst);
}

/* Event System initialization */
static void evsys_init(void)
{
	struct events_resource conf_event_resource;
	struct events_config conf_event;
	events_get_config_defaults(&conf_event);
	conf_event.edge_detect = EVENTS_EDGE_DETECT_NONE;
	conf_event.path = EVENTS_PATH_ASYNCHRONOUS;
	conf_event.generator = EVSYS_ID_GEN_TC0_MCX_0;
	events_allocate(&conf_event_resource, &conf_event);
	events_attach_user(&conf_event_resource, EVSYS_ID_USER_DAC_START);
}

/* Function to mount file system, open audio file and read
   audio header */
static void mount_file_system(void)
{	
	/* Wait card present and ready */
	do {
		status = sd_mmc_test_unit_ready(0);
		if (CTRL_FAIL == status) {
			printf("Card install FAIL\n\r");
			printf("Please unplug and re-plug the card.\n\r");
			while (CTRL_NO_PRESENT != sd_mmc_check(0)) {
			}
		}
	} while (CTRL_GOOD != status);
	
	/* Mount the file sytem */
	printf("Mount disk (f_mount)...\r\n");
	memset(&fs, 0, sizeof(FATFS));
	res = f_mount(LUN_ID_SD_MMC_0_MEM, &fs);
	if (FR_INVALID_DRIVE == res) {
		printf("[FAIL] res %d\r\n", res);
		while(1);
	}
	printf("[OK]\r\n");
	
	/* Open the WAV file */
	printf("Open a file (f_open)...\r\n");
	res = f_open(&file_object, (char const *)test_file_name, FA_READ);
	if (res != FR_OK) {
		printf("[FAIL] res %d\r\n", res);
		while(1);
	}
	printf("[OK]\r\n");
	
	/* Read audio header */
	printf("Read from file (f_read)...\r\n");
	res = f_read(&file_object, (uint8_t *)&audio_header, \
					sizeof(audio_header), &temp);
	if (res != FR_OK) {
		printf("[FAIL] res %d\r\n", res);
		while(1);
	}
	printf("[OK]\r\n");
}

/* Main function */
int main(void)
{
	/* Initialize system clocks.
	 * Note : Configuration to be in conf_clocks.h file.
	 */
	system_init();
	/* Initialize UART for CDC communication */
	cdc_uart_init();
	/* Initialize Timer Counter 0*/
	timer_init();
	/* Initialize DAC */
	dac_initialize();
	/* Initialize Event System */
	evsys_init();
	/* Initialize and enable global interrupt */
	irq_initialize_vectors();
	cpu_irq_enable();

	/* Initialize SD MMC stack */
	sd_mmc_init();
	/* Mount file system to read the audio header from test
	 * .WAV file in the SD card
	 */
	mount_file_system();
	/* Set timer 0 compare value corresponding to wav sample rate */
	tc_set_compare_value(&tc_inst, 0, \
		(system_gclk_gen_get_hz(GCLK_GENERATOR_3)/audio_header.SampleRate));
	
	/* The input data is processed for block of AUDIO_BUF_SIZE.
	 * Find number of AUDIO_BUF_SIZE data blocks in the input .WAV file. 
	 * Subchunk2Size of the audio header tells the number of audio data in 
	 * the input wave file. 
	 * Note : As it is stereo data both left and right channel data is read. 
	 * But only left channel data is processed. So when reading the audio 
	 * samples the read size is set to twice the AUDIO_BUF_SIZE.
	 */
	nb_audio_blocks = audio_header.Subchunk2Size - \
						(audio_header.Subchunk2Size % (AUDIO_BUF_SIZE*2));
	nb_audio_blocks = nb_audio_blocks/(AUDIO_BUF_SIZE*2);
	
	/* Read audio data from the input wav file in temp_audio_buf */
	res = f_read(&file_object, (uint8_t *)temp_audio_buf, \
					AUDIO_BUF_SIZE*2, &temp);
	if (res != FR_OK) {
		printf("[FAIL] Reading first block!\r\n");
		while(1);
	}
	/* The input file is in 16 bit signed PCM format. But the DAC
	 * does not support signed values, So shift the input data
	 * by 32767 bits to form signed value. Store the resulting value 
	 * to buffer 1 (i.e. audio_data_0).
	 */
	j = 0;
	for (i = 0; i < AUDIO_BUF_SIZE; i = i+2) {
		int32_t temp2 = (int32_t)temp_audio_buf[i] + 32767;
		temp = (uint16_t)(temp2 & 0xFFFF);
		audio_data_0[j++] = (temp >> 6);
	}	
	/* Move the current data pointer to buffer1 */
	audio_data_ptr = audio_data_0;
	current_data_buf = 0;
	/* Start timer to sample first block */
	tc_start_counter(&tc_inst);
	
	/* Read data for nb_audio_blocks-1 times as it is once read before */
	for (block_cnt = 0; block_cnt < nb_audio_blocks-1; block_cnt++)	{
		/* Check if the pointer is in buffer1 or 2 via current_data_buf value 
		 * and switch the buffer accordingly. 
		 */
		if (current_data_buf == 0) {
			/* Read audio data */
			res = f_read(&file_object, (uint8_t *)temp_audio_buf, AUDIO_BUF_SIZE*2, &temp);
			if (res != FR_OK) {
				printf("[FAIL] Reading block %d\r\n", (int)i);
				while(1);
			}
			/* Shift to form unsigned value */
			j = 0;
			for (i = 0; i < AUDIO_BUF_SIZE; i = i+2) {
				temp = (uint16_t)((int32_t)temp_audio_buf[i] + 32768);
				audio_data_1[j++] = (temp >> 6);
			}
			/* Wait until it is sampled by DAC. It is set at timer call back
			 * to indicate next set of data can be processed.
			 */
			while(!audio_playback_done);
			audio_playback_done = false;
			audio_data_ptr = audio_data_1;
			current_data_buf = 1;
		}
		else {
			/* Read audio data */
			res = f_read(&file_object, (uint8_t *)temp_audio_buf, AUDIO_BUF_SIZE*2, &temp);
			if (res != FR_OK) {
				printf("[FAIL] Reading block %d\r\n", (int)i);
				while(1);
			}
			/* Shift to form unsigned value */
			j = 0;
			for (i = 0; i < AUDIO_BUF_SIZE; i = i+2) {
				temp = (uint16_t)((int32_t)temp_audio_buf[i] + 32768);
				audio_data_0[j++] = (temp >> 6);
			}
			/* Wait until it is sampled by DAC. It is set at timer call back
			 * to indicate next set of data can be processed.
			 */
			while(!audio_playback_done);
			audio_playback_done = false;
			/* Switch the pointer to next buffer */
			audio_data_ptr = audio_data_0;
			current_data_buf = 0;
		}
	}
	/* Stop the timer once processing all input audio data */
	tc_stop_counter(&tc_inst);
	/* Close the file */
	f_close(&file_object);
	printf("Audio playback done! Closing File.\r\n");
	/* Loop until next reset */
	while (1) {
		
	}
}
