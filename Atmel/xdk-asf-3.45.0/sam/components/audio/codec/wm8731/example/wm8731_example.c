/**
 * \file
 *
 * \brief WM8731 example for SAM.
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
 * \mainpage WM8731 Example
 *
 * \section Purpose
 *
 * This example uses the Synchronous Serial Controller (SSC) of SAM devices
 * to output an audio stream through the on-board WM8731 CODEC.
 *
 * \section Requirements
 *
 * This example can be used with SAM evaluation kits with the on-board WM8731
 * CODEC.
 *
 * \section Description
 * This program plays a WAV file pre-loaded into the RAM. The audio stream is
 * sent through the SSC interface connected to the on-board WM8731, enabling
 * the sound to be audible using a pair of headphones.
 *
 * Since the WM8731 DAC requires that it be feeded a master clock multiple of
 * the sample rate, it is difficult to handle any WAV file. As such, this
 * example application is limited to playing files with the following format:
 * - Format: WAV
 * - Sample rate: 48 kHz
 *
 * The code can be roughly broken down as follows:
 * - Enable the clock.
 * - Configure and enable the Codec.
 * - Configure and enable the SSC interrupt.
 * - Load WAV file information.
 * - Play WAV file.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
	-- WM8731 example xxx --
	-- SAMxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	Menu :
	------
	W: Play the WAV file loaded
	I: Display the information of the WAV file
	R: Receive WAV file with XMODEM Protocol
	S: Stop playback
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "xmodem.h"

/* WAV letters "RIFF" */
#define WAV_CHUNKID       0x46464952
/* WAV letters "WAVE"*/
#define WAV_FORMAT        0x45564157
/* WAV letters "fmt "*/
#define WAV_SUBCHUNKID    0x20746D66

#if SAM3U
/** Address at which the WAV file is located*/
#define WAV_FILE_ADDRESS        BOARD_PSRAM_ADDR
#endif
#if SAM3XA
/** Address at which the WAV file is located*/
#define WAV_FILE_ADDRESS        BOARD_SDRAM_ADDR
#endif

/** Maximum size in bytes of the WAV file.*/
#define MAX_WAV_SIZE            0x800000

/** Address at which the recorded sample is stored */
#define RECORD_ADDRESS          (WAV_FILE_ADDRESS + MAX_WAV_SIZE)

/** Wav feature. */
#define SAMPLE_RATE             (48000)
/** Wav slot per frame */
#define SLOT_BY_FRAME           (2)
/** Bits per slot */
#define BITS_BY_SLOT            (16)

/* DMA channel used in this example. */
#define DMA_CH 0


/* Standard WAV file header information. */
struct wav_header {
	/* Contains the letters "RIFF" in ASCII form. */
	uint32_t chunk_id;
	/* Size of the rest of the chunk following this number. */
	uint32_t chunk_size;
	/* Contains the letters "WAVE". */
	uint32_t format;
	/* Contains the letters "fmt ". */
	uint32_t sub_chunk1_id;
	/* 16 for PCM.  This is the size of the rest of the Subchunk which follows this number. */
	uint32_t sub_chunk1_size;
	/* PCM = 1 (i.e. Linear quantization). Values other than 1 indicate some form of compression. */
	uint16_t audio_format;
	/* Mono = 1, Stereo = 2, etc. */
	uint16_t num_channels;
	/* 8000, 44100, etc. */
	uint32_t sample_rate;
	/* sample_rate * num_channels * bits_per_sample/8 */
	uint32_t byte_rate;
	/* num_channels * bits_per_sample/8 */
	uint16_t block_align;
	/* 8 bits = 8, 16 bits = 16, etc. */
	uint16_t bits_per_sample;
	/* Contains the letters "data". */
	uint32_t sub_chunk2_id;
	/* Number of bytes in the data. */
	uint32_t sub_chunk2_size;
};

/** Pointer to the playback WAV file header.*/
static const struct wav_header *p_wav_file =
		(struct wav_header *)WAV_FILE_ADDRESS;

/** Indicates if the WAV file is currently being played.*/
static uint8_t g_uc_is_wav_playing = 0;

/** Indicates if there is wav data */
static uint8_t g_uc_is_wav_available = 0;

/** Number of samples which have already been transmitted.*/
static uint32_t g_ul_transmitted_bytes;

/** Number of samples that have not yet been transmitted.*/
static uint32_t g_ul_remaining_bytes;

/**
 * \brief Configure the console UART.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Displays the user menu on the DBGU.
 */
static void display_menu(void)
{
	printf("Menu :\n\r");
	printf("------\n\r");

	/* Play a WAV file pre-loaded in Flash using SAM-BA */
	if (g_uc_is_wav_available && !g_uc_is_wav_playing) {
		printf("  W: Play the WAV file loaded\n\r");
	}
	/* Display the information of the WAV file (sample rate, stereo/mono and frame size) */
	if (g_uc_is_wav_available) {
		printf("  I: Display the information of the WAV file\n\r");
	} else {
		printf("  R: Receive WAV file with XMODEM Protocol\n\r");
	}
	/* Stop the current playback (if any) */
	if (g_uc_is_wav_playing) {
		printf("  S: Stop playback\n\r");
	}
}

/*
 * Init TWI interface for WM8731 .
 */
static void init_twi_wm8731(void)
{
	twi_options_t opt;

	/* Configure the options of TWI driver */
	opt.master_clk = sysclk_get_peripheral_hz();
	opt.speed	   = TWI_WM8731_CLK;
	opt.chip	   = WM8731_SLAVE_ADDRESS;
	twi_master_setup(TWI_WM8731, &opt);
}

/**
 * \brief  Initial the WM8731 to play back the sample WAV file.
 */
static void init_dac(void)
{
	uint32_t ul_value;
	/* First, disable programmable clock */
	pmc_disable_pck(PMC_PCK_0);
	/* Then, configure PMC Programmable Clock */
	pmc_switch_pck_to_mainck(PMC_PCK_0, PMC_MCKR_PRES_CLK_1);
	/* Finally, enable programmable clock */
	pmc_enable_pck(PMC_PCK_0);
	/* init control interface */
	init_twi_wm8731();
	/* reset the WM8731 */
	wm8731_reset();
	/* Select the WM8731 DAC */
	wm8731_dac_select(1);
	/* Set the WM8731 to usb mode and 48K DAC */
	wm8731_set_sampling_control(1,0,0);
	/* Set the WM8731 audio interface to I2S mode */
	ul_value = WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_I2S;
	wm8731_set_digital_audio_data_bit_length(ul_value);
	/* Set the WM8731 audio data bit length to 16bit */
	ul_value = WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_16_BIT;
	wm8731_set_digital_audio_data_bit_length(ul_value);
	/* Disable the WM8731 DAC soft mute */
	wm8731_set_dac_soft_mute(0);
	/* Power up the WM8731 DAC */
	wm8731_power_mode_dac();
	/* Active the WM8731 */
	wm8731_set_active(1);
}

/**
 * \brief  Initial the ssc interface.
 */
static void init_ssc(void)
{
	clock_opt_t tx_clk_option;
	data_frame_opt_t tx_data_frame_option;

	/* Initialize clock */
	pmc_enable_periph_clk(ID_SSC);

	/* Reset SSC */
	ssc_reset(SSC);
	/* Configure SSC */
	ssc_set_clock_divider(SSC, SAMPLE_RATE * (BITS_BY_SLOT + 1) * 2,
			sysclk_get_peripheral_hz());

	/* Transmitter clock mode configuration. */
	tx_clk_option.ul_cks = SSC_TCMR_CKS_MCK;
	tx_clk_option.ul_cko = SSC_TCMR_CKO_CONTINUOUS;
	tx_clk_option.ul_cki = 0;
	tx_clk_option.ul_ckg = SSC_TCMR_CKG_NONE;
	tx_clk_option.ul_start_sel = SSC_TCMR_START_RF_EDGE;
	tx_clk_option.ul_sttdly = 1;
	tx_clk_option.ul_period = BITS_BY_SLOT - 1;
	/* Transmitter frame mode configuration. */
	tx_data_frame_option.ul_datlen = BITS_BY_SLOT - 1;
	tx_data_frame_option.ul_msbf = SSC_TFMR_MSBF;
	tx_data_frame_option.ul_datnb = 0;
	tx_data_frame_option.ul_fslen = BITS_BY_SLOT - 1;
	tx_data_frame_option.ul_fslen_ext = 0;
	tx_data_frame_option.ul_fsos = SSC_TFMR_FSOS_NEGATIVE;
	tx_data_frame_option.ul_fsedge = SSC_TFMR_FSEDGE_POSITIVE;
	/* Configure the SSC transmitter to I2S mode. */
	ssc_set_transmitter(SSC, &tx_clk_option, &tx_data_frame_option);

	/* Disable transmitter first */
	ssc_disable_tx(SSC);

	/* Disable All Interrupt */
	ssc_disable_interrupt(SSC, 0xFFFFFFFF);
}

/**
 * \brief DMA driver configuration
 */
static void init_dma(void)
{
	uint32_t cfg;

	/* Enable DMA controller */
	dmac_enable(DMAC);

	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Disable the DMA channel for SSC */
	dmac_channel_disable(DMAC, DMA_CH);

	/* Set channel configuration register */
	cfg = DMAC_CFG_SOD_ENABLE |        /* Enable stop on done */
			DMAC_CFG_DST_H2SEL |       /* Hardware Selection for the Destination */
			DMAC_CFG_DST_PER(3) | /* Destination with Peripheral identifier */
			DMAC_CFG_AHB_PROT(1) |     /* Set AHB Protection */
			DMAC_CFG_FIFOCFG_ALAP_CFG; /* FIFO Configuration */

	dmac_channel_set_configuration(DMAC, DMA_CH, cfg);

	/* Set interrupt */
	NVIC_EnableIRQ(DMAC_IRQn);
	dmac_enable_interrupt(DMAC, (DMAC_EBCIER_CBTC0 << DMA_CH));
}

/**
 *  \brief Start DMA sending data.
 *
 * \param p_buffer Pointer to the data to be transmitted.
 * \param us_size Size of the data to be transmitted.
 */
static void ssc_dma(void *p_buffer, uint16_t us_size)
{
	dma_transfer_descriptor_t desc;

	desc.ul_source_addr = (uint32_t)p_buffer;
	desc.ul_destination_addr = (uint32_t)(&SSC->SSC_THR);
	desc.ul_ctrlA = DMAC_CTRLA_BTSIZE(us_size)
			| DMAC_CTRLA_SRC_WIDTH_HALF_WORD
			| DMAC_CTRLA_DST_WIDTH_HALF_WORD;
	desc.ul_ctrlB = DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE
			| DMAC_CTRLB_DST_DSCR_FETCH_DISABLE
			| DMAC_CTRLB_FC_MEM2PER_DMA_FC
			| DMAC_CTRLB_SRC_INCR_INCREMENTING
			| DMAC_CTRLB_DST_INCR_FIXED
			| DMAC_CTRLB_IEN;
	desc.ul_descriptor_addr = NULL;

	dmac_channel_single_buf_transfer_init(DMAC, DMA_CH, &desc);

	/* Start DMA transfer */
	dmac_channel_enable(DMAC, DMA_CH);

	/* Enable SSC transmitter */
	ssc_enable_tx(SSC);
}

/**
 * \brief Display the information of the WAV file (sample rate, stereo/mono
 * and frame size).
 */
static void display_wav_info(void)
{
	uint8_t uc_key;

	printf("%c[2J-- WAV file @ %x\n\r", 27, p_wav_file);
	printf("Wave file header information\n\r");
	printf("--------------------------------\n\r");
	printf("  - Chunk ID		 = 0x%08X\n\r", p_wav_file->chunk_id);
	printf("  - Chunk Size 	 = %u\n\r", p_wav_file->chunk_size);
	printf("  - Format 		 = 0x%08X\n\r", p_wav_file->format);
	printf("  - SubChunk ID	 = 0x%08X\n\r", p_wav_file->sub_chunk1_id);
	printf("  - Subchunk1 Size  = %u\n\r", p_wav_file->sub_chunk1_size);
	printf("  - Audio Format	 = 0x%04X\n\r", p_wav_file->audio_format);
	printf("  - Num. Channels	 = %d\n\r", p_wav_file->num_channels);
	printf("  - Sample Rate	 = %u\n\r", p_wav_file->sample_rate);
	printf("  - Byte Rate		 = %u\n\r", p_wav_file->byte_rate);
	printf("  - Block Align	 = %d\n\r", p_wav_file->block_align);
	printf("  - Bits Per Sample = %d\n\r", p_wav_file->bits_per_sample);
	printf("  - Subchunk2 ID	 = 0x%08X\n\r", p_wav_file->sub_chunk2_id);
	printf("  - Subchunk2 Size  = %u\n\r", p_wav_file->sub_chunk2_size);
	printf("\n\r-- Press any key to return to menu\n\r");
	while (uart_read(CONSOLE_UART, &uc_key));
}

/**
 * \brief Play a WAV file pre-loaded in PSRAM/SDRAM.
 *
 * \param ul_wav_data_address The address of the WAVE file.
 * \param ul_wav_size Wave file size. 
 */
static void start_play_wav(uint32_t ul_wav_data_address, uint32_t ul_wav_size)
{
	uint32_t ul_size;
	uint32_t ul_src_address;

	/* Start transmitting WAV file to SSC */
	g_ul_remaining_bytes = ul_wav_size;
	g_ul_transmitted_bytes = 0;

	/* Start DMA transfer */
	g_uc_is_wav_playing = 1;

	ul_size = Min(g_ul_remaining_bytes / (p_wav_file->bits_per_sample / 8),
			((DMA_MAX_LENGTH + 1) / (p_wav_file->bits_per_sample / 8) - 1));

	ul_src_address = ul_wav_data_address;
	g_ul_remaining_bytes -= ul_size * (p_wav_file->bits_per_sample / 8);
	g_ul_transmitted_bytes += ul_size * (p_wav_file->bits_per_sample / 8);

	ssc_dma((void *)ul_src_address, ul_size);
}

/**
 * \brief  Stop the current playback (if any).
 */
static void stop_play_wav(void)
{
	dmac_channel_stop_transfer(DMAC, DMA_CH);
	ssc_disable_tx(SSC);
	g_uc_is_wav_playing = 0;
}

/**
 * ISR for DMA interrupt
 */
void DMAC_Handler(void)
{
	uint32_t ul_size;
	uint32_t ul_src_address;
	uint32_t dma_status;

	dma_status = dmac_get_status(DMAC);

	if (dma_status & (DMAC_EBCISR_CBTC0 << DMA_CH)) {
		if (g_ul_remaining_bytes > 0) {
			/*Send remaining bytes */
			ul_size = Min(g_ul_remaining_bytes /
					(p_wav_file->bits_per_sample / 8),
					((DMA_MAX_LENGTH + 1) /
					(p_wav_file->bits_per_sample / 8) - 1));

			ul_src_address = WAV_FILE_ADDRESS + sizeof(struct wav_header) +
					g_ul_transmitted_bytes;
			g_ul_remaining_bytes -= ul_size *
					(p_wav_file->bits_per_sample / 8);
			g_ul_transmitted_bytes += ul_size *
					(p_wav_file->bits_per_sample / 8);
			ssc_dma((void *)ul_src_address, ul_size);
		} else {
			g_uc_is_wav_playing = 0;
			display_menu();
		}
	}
}


/**
 *  \brief ssc_dma_audio Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */

int main(void)
{
	uint8_t uc_key;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Configure console UART. */
	configure_console();

	/* Output example information */
	printf("\n\r\n\r\n\r");
	printf("-- WM8731 Example --\n\r");
	printf("-- %s --\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Enable PMC clock for SMC module */
	pmc_enable_periph_clk(ID_SMC);

#if SAM3U
	/* Initialize PSRAM */
	printf("-- Initialize PSRAM. --\n\r");

	/* Complete SMC configuration between PSRAM and SMC waveforms. */
	smc_set_setup_timing(SMC, 0, SMC_SETUP_NWE_SETUP(0)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, 0, SMC_PULSE_NWE_PULSE(6)
			| SMC_PULSE_NCS_WR_PULSE(6)
			| SMC_PULSE_NRD_PULSE(6)
			| SMC_PULSE_NCS_RD_PULSE(6));
	smc_set_cycle_timing(SMC, 0, SMC_CYCLE_NWE_CYCLE(8)
			| SMC_CYCLE_NRD_CYCLE(8));
	smc_set_mode(SMC, 0, SMC_MODE_READ_MODE | SMC_MODE_WRITE_MODE
			| SMC_MODE_DBW_BIT_16);
#endif

#if SAM3XA
	/* Initialize SDRAM */
	printf("-- Initialize SDRAM. --\n\r");

	sdramc_init((sdramc_memory_dev_t *) & SDRAM_MICRON_MT48LC16M16A2,
			sysclk_get_peripheral_hz());
#endif

	/* Initial the WM8731 to DAC */
	init_dac();

	/* Initial the ssc interface */
	init_ssc();

	/* Configure DMA */
	init_dma();

	/* Enter menu loop */
	while (1) {
		/* Display menu */
		display_menu();

		/* Process user input */
		while (uart_read(CONSOLE_UART, &uc_key));

		if ((uc_key == 'W') && !g_uc_is_wav_playing) {
			/* Play WAV file */
			start_play_wav(WAV_FILE_ADDRESS+sizeof(struct wav_header),
					p_wav_file->sub_chunk2_size);
		} else if ((uc_key == 'S') && g_uc_is_wav_playing) {
			/* Stop playback */
			stop_play_wav();
		} else if (uc_key == 'I') {
			/* Display WAV information */
			display_wav_info();
		} else if (uc_key == 'R') {
			/* Get a wav file from Hyper terminal using XMODEM protocol */
			xmodem_receive_file((usart_if)CONF_UART, (int8_t *)p_wav_file);
			g_uc_is_wav_available = 1;
			/* Load WAV file information */
			if ((p_wav_file->chunk_id != WAV_CHUNKID) ||
					(p_wav_file->format != WAV_FORMAT) ||
					(p_wav_file->sub_chunk1_size != 0x10)) {
				g_uc_is_wav_available = 0;
				printf("Please send the wav file!\n\r");
			}

			/* Sample rate must be 48kHz */
			if (p_wav_file->sample_rate != 48000) {
				g_uc_is_wav_available = 0;
				printf("The WAV file must have a sample rate of 48kHz!\n\r");
			}
		}
	}
}
