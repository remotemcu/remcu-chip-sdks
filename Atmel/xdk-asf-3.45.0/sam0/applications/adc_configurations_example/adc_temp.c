/**
 * \file
 *
 * \brief ADC Temperature Sensor configuration file
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
#include <asf.h>
#include "adc_temp.h"

/* Structure for ADC module instance */
extern struct adc_module adc_instance;


/*  The following variables have referred with respect to device data sheet 
	Equation1 and Equation1b on section "Temperature Sensor Characteristics" 
	of Electrical Characteristics */

float coarse_temp; /* Coarse value of the temperature - tempC */ 
float fine_temp;   /* Finer value of the temperature - tempF */

float tempR;       /* Production Room Temperature value read from NVM memory - tempR */
float tempH;	   /* Production Hot Temperature value read from NVM memory - tempH */
float INT1VR;      /* Room temp 2’s complement of the internal 1V reference value - INT1VR */
float INT1VH;	   /* Hot temp 2’s complement of the internal 1V reference value - INT1VR */
uint16_t ADCR;     /* Production Room Temperature ADC Value read from NVM memory - ADCR */
uint16_t ADCH;     /* Production Hot Temperature ADC Value read from NVM memory - ADCH */

float VADCR;	   /* Room Temperature ADC voltage - VADCR */
float VADCH;	   /* Hot Temperature ADC voltage - VADCH */

/**
* \brief ADC Temperature Sensor mode configuration.
* This function enables internal temperature sensor feature of ADC with below Settings

* GLCK for ADC		-> GCLK_GENERATOR_1 (8MHz)
* CLK_ADC			-> 512 KHz
* REFERENCE			-> internal 1 V
* POSITIVE INPUT	-> INTRENAL Temperature reference
* NEGATIVE INPUT	-> 
* SAMPLES			-> 4
* SAMPLE_LENGTH		-> 4
*/

void configure_adc_temp(void)
{
	struct adc_config conf_adc;
	
	adc_get_config_defaults(&conf_adc);
	
	conf_adc.clock_source = GCLK_GENERATOR_1;
	conf_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV16;
	conf_adc.reference = ADC_REFERENCE_INT1V;
	conf_adc.positive_input = ADC_POSITIVE_INPUT_TEMP;
	conf_adc.negative_input = ADC_NEGATIVE_INPUT_GND;
	conf_adc.sample_length = ADC_TEMP_SAMPLE_LENGTH;
	
	adc_init(&adc_instance, ADC, &conf_adc);
	
	ADC->AVGCTRL.reg = ADC_AVGCTRL_ADJRES(2) | ADC_AVGCTRL_SAMPLENUM_4;
	
	adc_enable(&adc_instance);
}

/**
* \brief Decimal to Fraction Conversation.
* This function converts the decimal value into fractional 
* and return the fractional value for temperature calculation
*/
float convert_dec_to_frac(uint8_t val)
{
	if (val < 10)
	{
		return ((float)val/10.0);
	}
	
	else if (val <100)
	{
		return ((float)val/100.0);
	}
	
	else
	{
		return ((float)val/1000.0);
	}
}

/**
* \brief Calibration Data.
* This function extract the production calibration data information from
* Temperature log row content and store it variables for temperature calculation
*
*/
void load_calibration_data(void)
{
	volatile uint32_t val1;				/* Temperature Log Row Content first 32 bits */
	volatile uint32_t val2;				/* Temperature Log Row Content another 32 bits */
	uint8_t room_temp_val_int;			/* Integer part of room temperature in °C */
	uint8_t room_temp_val_dec;			/* Decimal part of room temperature in °C */
	uint8_t hot_temp_val_int;			/* Integer part of hot temperature in °C */
	uint8_t hot_temp_val_dec;			/* Decimal part of hot temperature in °C */
	int8_t room_int1v_val;				/* internal 1V reference drift at room temperature */
	int8_t hot_int1v_val;				/* internal 1V reference drift at hot temperature*/
	
	uint32_t *temp_log_row_ptr = (uint32_t *)NVMCTRL_TEMP_LOG;
	
	val1 = *temp_log_row_ptr;
	temp_log_row_ptr++;
	val2 = *temp_log_row_ptr;
	
	room_temp_val_int = (uint8_t)((val1 & NVMCTRL_FUSES_ROOM_TEMP_VAL_INT_Msk) >> NVMCTRL_FUSES_ROOM_TEMP_VAL_INT_Pos);
	
	room_temp_val_dec = (uint8_t)((val1 & NVMCTRL_FUSES_ROOM_TEMP_VAL_DEC_Msk) >> NVMCTRL_FUSES_ROOM_TEMP_VAL_DEC_Pos);
	
	hot_temp_val_int = (uint8_t)((val1 & NVMCTRL_FUSES_HOT_TEMP_VAL_INT_Msk) >> NVMCTRL_FUSES_HOT_TEMP_VAL_INT_Pos);
	
	hot_temp_val_dec = (uint8_t)((val1 & NVMCTRL_FUSES_HOT_TEMP_VAL_DEC_Msk) >> NVMCTRL_FUSES_HOT_TEMP_VAL_DEC_Pos);
	
	room_int1v_val = (int8_t)((val1 & NVMCTRL_FUSES_ROOM_INT1V_VAL_Msk) >> NVMCTRL_FUSES_ROOM_INT1V_VAL_Pos);
	
	hot_int1v_val = (int8_t)((val2 & NVMCTRL_FUSES_HOT_INT1V_VAL_Msk) >> NVMCTRL_FUSES_HOT_INT1V_VAL_Pos);
	
	ADCR = (uint16_t)((val2 & NVMCTRL_FUSES_ROOM_ADC_VAL_Msk) >> NVMCTRL_FUSES_ROOM_ADC_VAL_Pos);
	
	ADCH = (uint16_t)((val2 & NVMCTRL_FUSES_HOT_ADC_VAL_Msk) >> NVMCTRL_FUSES_HOT_ADC_VAL_Pos);
	
	tempR = room_temp_val_int + convert_dec_to_frac(room_temp_val_dec);
	
	tempH = hot_temp_val_int + convert_dec_to_frac(hot_temp_val_dec);
	
	INT1VR = 1 - ((float)room_int1v_val/INT1V_DIVIDER_1000);
	
	INT1VH = 1 - ((float)hot_int1v_val/INT1V_DIVIDER_1000);
	
	VADCR = ((float)ADCR * INT1VR)/ADC_12BIT_FULL_SCALE_VALUE_FLOAT;
	
	VADCH = ((float)ADCH * INT1VH)/ADC_12BIT_FULL_SCALE_VALUE_FLOAT;
}

/**
* \brief Temperature Calculation.
* This function calculate fine temperature using Equation1 and Equation
* 1b as mentioned in data sheet section "Temperature Sensor Characteristics"
* of Electrical Characteristics.
*
*/
float calculate_temperature(uint16_t raw_code)
{
	float VADC;      /* Voltage calculation using ADC result for Coarse Temp calculation */
	float VADCM;     /* Voltage calculation using ADC result for Fine Temp calculation. */
	float INT1VM;    /* Voltage calculation for reality INT1V value during the ADC conversion */
	
	VADC = ((float)raw_code * INT1V_VALUE_FLOAT)/ADC_12BIT_FULL_SCALE_VALUE_FLOAT;
	
	/* Coarse Temp Calculation by assume INT1V=1V for this ADC conversion */
	coarse_temp = tempR + (((tempH - tempR)/(VADCH - VADCR)) * (VADC - VADCR));
	
	/* Calculation to find the real INT1V value during the ADC conversion */
	INT1VM = INT1VR + (((INT1VH - INT1VR) * (coarse_temp - tempR))/(tempH - tempR));
	
	VADCM = ((float)raw_code * INT1VM)/ADC_12BIT_FULL_SCALE_VALUE_FLOAT;
	
	/* Fine Temp Calculation by replace INT1V=1V by INT1V = INT1Vm for ADC conversion */
	fine_temp = tempR + (((tempH - tempR)/(VADCH - VADCR)) * (VADCM - VADCR));
	
	return fine_temp;
}

