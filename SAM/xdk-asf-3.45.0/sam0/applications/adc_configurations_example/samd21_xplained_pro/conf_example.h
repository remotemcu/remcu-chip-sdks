/**
 * \file
 *
 * \brief SAM D21 Xplained Pro board ADC configurations Example.
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

#ifndef CONF_EXAMPLE_H_INCLUDED
#define CONF_EXAMPLE_H_INCLUDED


#define ENABLE	1
#define	DISABLE	0

/* Macro Definitions for ADC Configuration */

/* Please define any one of the below ADC mode */
#define ADC_MODE_DIFFERENTIAL	DISABLE
#define ADC_MODE_HW_AVERAGING	DISABLE	
#define ADC_MODE_OVERSAMPLING	DISABLE
#define ADC_MODE_WINDOW			DISABLE
#define ADC_MODE_CALIBRATION	DISABLE
#define ADC_MODE_TEMP_SENSOR	ENABLE

#if (ADC_MODE_DIFFERENTIAL + ADC_MODE_HW_AVERAGING + ADC_MODE_OVERSAMPLING \
	+ ADC_MODE_WINDOW + ADC_MODE_CALIBRATION + ADC_MODE_TEMP_SENSOR) > 1 
#error "Please enable only one feature at a time"
#endif


/* Macro Definitions for ADC SCALE definitions */

#define ADC_REFERENCE_INTVCC1_VALUE		1.65
#define ADC_12BIT_FULL_SCALE_VALUE		4095
#define ADC_11BIT_FULL_SCALE_VALUE		2047
#define ADC_16BIT_FULL_SCALE_VALUE		65535
/* 12 bit ADC value for corresponding 0.75V with respect 1.65V reference */
#define ADC_WINDOW_LOWER_THERSOLD_VALUE 0x0745 


/* Function Prototypes for the ADC mode operation */

uint16_t adc_start_read_result(void);
void adc_differential(void);
void adc_hardware_averaging(void);
void adc_oversampling(void);
void adc_window_monitor(void);
void adc_calibration(void);
void adc_temp_sensor(void);

/* Function prototype for Serial console */
void configure_console(void);

#endif /* CONF_EXAMPLE_H_INCLUDED */
