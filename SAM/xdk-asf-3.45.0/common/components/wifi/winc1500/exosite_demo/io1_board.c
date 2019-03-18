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

#include "asf.h"
#include "io1_board.h"
#include "sd_mmc_spi.h"
#include "debug_conf.h"

/* Token sequence, For Extension board information */
#define MANUFACTURE_TOKEN_COUNT				0
#define BOARD_NAME_TOKEN_COUNT				1
#define BOARD_REVISION_NUMBER_TOKEN_COUNT	2
#define BOARD_SERIAL_NUMBER_TOKEN_COUNT		3

/* stored data key */
#define SD_FILE_KEY_CIK_CODE		"cik_key"

/** EDBG TWI interface address */
#define EDBG_ADDRESS 0x28;
/** Request token of EDBG TWI information interface */
#define EDBG_EXTEN_BOARDS_TOKEN 0xE1;

/* Storage file */
#define SETTING_FILE_PATH "/settings.ini"

/* IO1 board - adc instance */
extern  struct i2c_master_module dev_inst_at30tse75x;
struct adc_module adc_instance;
FATFS fs;

static io1_board_info g_info;

const char *sec_type_values[] = {
	"invalid",
	"none",
	"wpa_psk",
	"wep",
	"802.1x"
};

/************************************************************************/
/* declare inner function                                               */
/************************************************************************/
static void _lightsensor_init(void);
static void _sd_init(void);
static bool _load_setting_from_sd(void);
static bool _save_setting_to_sd(void);
static bool _decode_board_info(uint8_t *buffer);

char* LTRIM(char *s);
char* RTRIM(char* s);
char* TRIM(char *p);
/************************************************************************/
/* implement function                                                   */
/************************************************************************/
bool io1_board_init()
{
	/* Initialize temperature sensor */
	at30tse_init();

	/* initialize light sensor */
	_lightsensor_init();

	/* Initialize SD card */
	_sd_init();
	
	/* Configure LEDs as outputs, turn them off */
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(44/*pin number*/, &pin_conf);
	
	return true;
}

io1_board_info * io1_board_get_info()
{
	uint8_t request_token = EDBG_EXTEN_BOARDS_TOKEN;
	struct i2c_master_packet master_packet;
	uint8_t read_buffer[1024];
	uint8_t board_num = 0;
	uint8_t i,j;
	uint32_t timeout= 0;	
	
	_load_setting_from_sd();
	 
	/** Send the request token */
	master_packet.address         = EDBG_ADDRESS;
	master_packet.data_length     = 1;
	master_packet.data            = &request_token;
	master_packet.ten_bit_address = false;
	master_packet.high_speed      = false;
	master_packet.hs_master_code  = 0x0;

	timeout = 0;
	while (i2c_master_write_packet_wait_no_stop(&dev_inst_at30tse75x, &master_packet) != STATUS_OK)
	{
		if (timeout++ == 1000) 
		{
			DEBUG("ERROR i2c write timeout"DEBUG_EOL); 
			DEBUG(DEBUG_CONF_IO1_BOARD"Error :io1_board_get_info"DEBUG_EOL);
			return NULL;
		}
	}

	/** Get the extension boards info */
	master_packet.data_length     = 1024;
	master_packet.data            = read_buffer;
	timeout = 0;
	 
	while (i2c_master_read_packet_wait(&dev_inst_at30tse75x, &master_packet) != STATUS_OK) 
	{
		if (timeout++ == 1000) 
		{
			DEBUG("ERROR i2c read timeout"DEBUG_EOL); 
			DEBUG(DEBUG_CONF_IO1_BOARD"Error :io1_board_get_info"DEBUG_EOL);
			return NULL;
		}
	}

	/** Check and show info */
	uint8_t extension_map[2];
	extension_map[0] = read_buffer[0];
	extension_map[1] = read_buffer[1];
	
	for (i = 0; i < 2; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			if (extension_map[1 - i] & 0x01)
			{
				/** show extension board info */
				DEBUG(DEBUG_EOL);
				DEBUG(DEBUG_CONF_IO1_BOARD"Extension board %d detected \r\n", (i * 8) + j);
				if( _decode_board_info(&read_buffer[2 + 64 * board_num]) )
					return &g_info;
					
				board_num++;
			}
			extension_map[1 - i] = extension_map[1 - i] >> 1;
		}
	}
	DEBUG(DEBUG_CONF_IO1_BOARD"Error :io1_board_get_info"DEBUG_EOL);
	return NULL;
}

void io1_board_prepare_to_get_info()
{
	adc_start_conversion(&adc_instance);
}

int io1_board_get_temperature()
{
	double value = at30tse_read_temperature();
	return (int)value;
}

int io1_board_get_lightvalue()
{
	uint16_t valtage_light;
	// Read the voltage
	if (adc_read(&adc_instance, &valtage_light) != STATUS_OK)
	{
		DEBUG( DEBUG_CONF_IO1_BOARD" Failed to read light value" DEBUG_EOL);
		valtage_light = -1;
	}
	return (int)valtage_light;
}

void io1_board_set_led(bool on)
{
	if( on )
	{
		port_pin_set_output_level(44/*pin number*/,0);
	}
	else
	{
		port_pin_set_output_level(44/*pin number*/,1);
	}
}	

bool io1_board_save_cik_value_to_sd(char *pbuf)
{
	memcpy(g_info.cik, pbuf,strlen(pbuf));
	g_info.is_activate = true;
	
	_save_setting_to_sd();
	
	return false;	
}

void io1_board_reset_cik_value()
{
	memset(g_info.cik, 0x00,sizeof(char)*50);
	g_info.is_activate = false;
}
/**
* \brief intialize light sensor
*/
static void _lightsensor_init()
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	config_adc.positive_input = 18;/*EXT2_ADC_0_CHANNEL;*/
	adc_init(&adc_instance, ADC/*EXT2_ADC_MODULE*/, &config_adc);
	adc_enable(&adc_instance);
}

static void _sd_init(void)
{	
	const uint8_t slot = 0;
	sd_mmc_spi_init();
	sd_mmc_init();
	
	sd_mmc_spi_select_device(slot, SD_MMC_SPI_MAX_CLOCK, 1, false);
	while(sd_mmc_check(slot) == SD_MMC_ERR_NO_CARD) ;
	
	FRESULT ret = f_mount(0, &fs);
	if( ret != FR_OK)
	{
		DEBUG(DEBUG_CONF_IO1_BOARD"ERROR : Mounting SD card failed : code %d" DEBUG_EOL, ret);
		while(1);
	}	
}

static bool _load_setting_from_sd()// io1_board_info * g_info)
{
	FIL file ;

	FRESULT r = f_open(&file,SETTING_FILE_PATH, FA_READ);
	if( r != FR_OK )
	{
		DEBUG(DEBUG_CONF_IO1_BOARD"ERROR : failed to read setting file"  DEBUG_EOL);
		return false;
	}
	
	char line[255];
	char *key, *value;
	char *ptr, *endptr;
	
	while( f_gets(line, sizeof(line), &file) != NULL)
	{
		ptr = strchr(line, '#');
		if( ptr != NULL )
		*ptr = '\0';
		
		endptr = strchr(line, '=');
		if( endptr == NULL)
		continue;
		
		// fetch key and value
		key   = TRIM(line);
		value = TRIM(endptr + 1);
		// find proper key and set the value
		if (strncmp(key, SD_FILE_KEY_CIK_CODE,strlen(SD_FILE_KEY_CIK_CODE)) == 0)
		{
			strncpy(g_info.cik, value, strlen(value));
			if( strlen(g_info.cik) == 40 )
				g_info.is_activate = true;
			else
				g_info.is_activate = false;
		}
	}

	return true;
}

static bool _save_setting_to_sd()
{
	bool write_failed = false;

	FIL fil;
	FRESULT res = f_open(&fil, SETTING_FILE_PATH, FA_WRITE | FA_CREATE_ALWAYS);
	if (res != FR_OK)
	{
		DEBUG(DEBUG_CONF_IO1_BOARD"ERROR: can not open file: %s ret %u" DEBUG_EOL, SETTING_FILE_PATH, (unsigned)res);
		return -1;
	}
	write_failed |= !f_printf(&fil, "%s=%s\n", SD_FILE_KEY_CIK_CODE, g_info.cik);
	f_close(&fil);
	if (write_failed)
		DEBUG(DEBUG_CONF_IO1_BOARD"ERROR: Failed to save airsync.conf" DEBUG_EOL);
	return (!write_failed);
}

static bool _decode_board_info(uint8_t *buffer)
{
	char extension_info[64];
	uint8_t token_cnt = 0;
	char *p_token = NULL;

	memcpy(extension_info, buffer, 64);
	p_token = extension_info;

	while(1)
	{
		if( token_cnt == MANUFACTURE_TOKEN_COUNT)
		{
			char tmp[20] = {0,};
			char *ptmp = NULL;
			strcpy(tmp,p_token );
			ptmp = strlwr(tmp);
			strcpy(g_info.board_vendor,ptmp);
			DEBUG(DEBUG_CONF_IO1_BOARD"Manufacturer name: %s"DEBUG_EOL,g_info.board_vendor );
		}
		else if( token_cnt == BOARD_NAME_TOKEN_COUNT)
		{
			strcpy(g_info.board_id,p_token );
			DEBUG(DEBUG_CONF_IO1_BOARD"Board id: %s"DEBUG_EOL,g_info.board_id );}
		else if( token_cnt == BOARD_REVISION_NUMBER_TOKEN_COUNT)
		{
			DEBUG(DEBUG_CONF_IO1_BOARD"Manufacturer revision: %s"DEBUG_EOL,p_token );
		}
		else if( token_cnt == BOARD_SERIAL_NUMBER_TOKEN_COUNT)
		{
			strcpy(g_info.board_sn,p_token+6 );
			DEBUG(DEBUG_CONF_IO1_BOARD"board sn: %s"DEBUG_EOL,g_info.board_sn );
			return true;
		}
		else
			break;
		
		p_token = strchr(p_token, (int)'\0' );
		p_token++;
		
		if(p_token[0] == 0x00 || p_token[0] == 0xFF)
			break;
		
		token_cnt++;
	}
	return false;
}

/**
 * @brief Remove leading white-space characters from the string
 *
 * @param[in] p   the string to be trimmed
 *
 * @return pointer to the first byte of the trimmed string
 */
char *LTRIM(char *p)
{
	if (NULL != p)
		while (isspace((int)*p))
			++p;
	return p;
}

/**
 * @brief Remove trailing white-space characters from the string
 *
 * @param[in] p   the string to be trimmed
 *
 * @return pointer to the first byte of the trimmed string
 */
char *RTRIM(char *p)
{
	if ((NULL != p) && ('\0' != *p))
	{
		char *rp = p + strlen(p) - 1;
		while (isspace((int)*rp) && (rp >= p))
			--rp;
		rp[1] = '\0';
	}
	return p;
}

/**
 * @brief Remove both leading and trailing white-space characters from the string
 *
 * @param[in] p   the string to be trimmed
 *
 * @return pointer to the first byte of the trimmed string
 */
char *TRIM(char *p)
{
	return RTRIM(LTRIM(p));
}