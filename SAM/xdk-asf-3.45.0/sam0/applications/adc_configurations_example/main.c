/**
 * \file
 *
 * \brief SAMD21 ADC Configuration example
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

/*
* \mainpage
 * \section intro Introduction
 * This example demonstrates how to use enable and configure different features of ADC module.
 *
 * \section files Main Files
 * - conf_board.h: Board Configuration
 * - conf_example.h: ADC Features Configuration
 * - conf_clocks.h: SAM D21 Clock configuration
 * - adc_configure.h: ADC configuration prototype declarations
 * - adc_configure.c: ADC configuration definitions
 * - adc_temp.h: ADC temperature sensor prototype declarations
 * - adc_temp.c: ADC temperature calculation and definitions
 * 

 
 * This example has been tested with the following setup:
 *   - SAMD21 Xplained Pro 
 *   - UART configuration is 115200 baudrate, no parity, data 8 bit.
 *
 * \section example description Description of the example
 * The example helps to configure the ADC module 
 * based on macro definition available in conf_example.h.
 * The Serial Console used to get input from user where necessary
 * display the ADC input voltage after the ADC configuration done.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/design-centers/8-bit">Atmel AVR</A>.\n
 */
 /**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
#include <asf.h>
#include "conf_example.h"
#include "adc_configure.h"
#include "adc_temp.h"

/* Structure for ADC module instance */
struct adc_module adc_instance;

/* Structure for USART module instance */
struct usart_module console_instance;

/*  To Store ADC output in voltage format */
float result;

/* To store raw_result of ADC output */
uint16_t raw_result;

/* To read the STATUS register of ADC */
uint8_t status;


int main(void)
{
	/* Configuration of clock and board */
	system_init();
	
	/* Serial Console configuration */
	configure_console();
	
	/* Delay Module Initialization */
	delay_init();
	
	while (1){
	
	/* Differential Mode configuration */
	#if (ADC_MODE_DIFFERENTIAL == ENABLE)
	adc_differential();
	#endif
	
	/* Hardware Averaging configuration */
	#if (ADC_MODE_HW_AVERAGING == ENABLE)
	adc_hardware_averaging();
	#endif
	
	/* Oversampling configuration */
	#if (ADC_MODE_OVERSAMPLING == ENABLE)
	adc_oversampling();
	#endif
	
	/* Window Monitoring configuration */
	#if (ADC_MODE_WINDOW == ENABLE)
	adc_window_monitor();
	#endif
	
	/* ADC calibration configuration */
	#if (ADC_MODE_CALIBRATION == ENABLE)
	adc_calibration();
	#endif	
	
	/* Temperature Sensor configuration */
	#if (ADC_MODE_TEMP_SENSOR == ENABLE)
	adc_temp_sensor(); 
	#endif	
	
	delay_s(1);
	
	}
	
}

/**
* \brief ADC START and Read Result.
*
* This function starts the ADC and wait for the ADC
* conversation to be complete	and read the ADC result
* register and return the same to calling function.
*/

uint16_t adc_start_read_result(void)
{
	uint16_t adc_result = 0;
	
	adc_start_conversion(&adc_instance);
	while((adc_get_status(&adc_instance) & ADC_STATUS_RESULT_READY) != 1);
		
	adc_read(&adc_instance, &adc_result);
	
	return adc_result;
}


/**
* \brief Configure serial Console.
*
* This function configures and enable the SERCOM
* module with below Settings.

* GLCK for SERCOM	-> GCLK_GENERATOR_0 (8MHz)
* SERCOM instance	-> 3
* TXD				-> PA22
* RXD				-> PA23
* BAUDRATE			-> 115200
* STOP BIT			-> 1
* CHARACTER			-> 8
* PARITY			-> NONE
*
*/

void configure_console(void)
{
	
	struct usart_config conf_usart;
	
	usart_get_config_defaults(&conf_usart);
	
	conf_usart.baudrate = 115200;
	conf_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	
	conf_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	conf_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	conf_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	conf_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	
	stdio_serial_init(&console_instance, EDBG_CDC_MODULE, &conf_usart);
	
	usart_enable(&console_instance);
}

/**
* \brief ADC Differential mode.
*
* This function configures the ADC as differential mode 
* and converts the differential voltage applied on positive
* input and negative input. Prints the differential voltage
* on serial console and disable the ADC.
*/

void adc_differential(void)
{
	int16_t raw_result_signed;
	
	configure_adc_differential();
	
	raw_result = adc_start_read_result();
	
	raw_result_signed = (int16_t)raw_result;	
	result = ((float)raw_result_signed * (float)ADC_REFERENCE_INTVCC1_VALUE)/(float)ADC_11BIT_FULL_SCALE_VALUE;
	
	printf("\nDifferential Voltage on ADC Input = %fV", result);
	
	adc_disable(&adc_instance);
}


/**
* \brief ADC Hardware Averaging mode.
*
* This function configures the ADC as hardware averaging mode 
* and converts the ADC input applied on positive input then 
* prints the ADC input voltage on serial console after hardware 
* averaging done and disable the ADC
*/

void adc_hardware_averaging(void)
{
	configure_adc_averaging();
	
	raw_result = adc_start_read_result();
	
	result = ((float)raw_result * (float)ADC_REFERENCE_INTVCC1_VALUE)/(float)ADC_12BIT_FULL_SCALE_VALUE;
	
	printf("\nADC Input Voltage with Averaging = %fV", result);
	
	adc_disable(&adc_instance);
}


/**
* \brief ADC Oversampling mode.
*
* This function configures the ADC with normal mode and oversampling feature
* and converts the ADC input applied on positive input. Prints the ADC input 
* voltage for both mode on serial console to recognize the improvement.
*/

void adc_oversampling(void)
{
	configure_adc();
	
	raw_result = adc_start_read_result();
	
	result = ((float)raw_result * (float)ADC_REFERENCE_INTVCC1_VALUE)/(float)ADC_12BIT_FULL_SCALE_VALUE;
	
	printf("\nADC Input Voltage before Oversampling = %fV", result);
	
	adc_disable(&adc_instance);
	
	configure_adc_sampling();
	
	raw_result = adc_start_read_result();
	
	result = ((float)raw_result * (float)ADC_REFERENCE_INTVCC1_VALUE)/(float)ADC_16BIT_FULL_SCALE_VALUE;
	
	printf("\nADC Input Voltage after Oversampling = %fV", result);
	
	adc_disable(&adc_instance);
}

/**
* \brief ADC Window Monitor mode.
*
* This function configures the ADC as window monitor mode and predefine the
* voltage level for monitoring. If the ADC input exceeds the voltage level the
* LED0 will be in ON state in SAMD21 Xplained Pro.
*/

void adc_window_monitor(void)
{
	configure_adc_window_monitor();
	
	adc_start_conversion(&adc_instance);
	while((adc_get_status(&adc_instance) & ADC_STATUS_RESULT_READY) != 1);
	
	status = adc_get_status(&adc_instance);
	
	adc_read(&adc_instance, &raw_result);
	
	if (status & ADC_STATUS_WINDOW){
		port_pin_set_output_level(LED0_PIN, LOW);
		printf("\nLED0 is ON");
	}
	else{
		port_pin_set_output_level(LED0_PIN, HIGH);
		printf("\nLED0 is OFF");
	}
}

/**
* \brief ADC Calibration mode.
*
* This function enable/disable the ADC calibration based
* on the user input from serial console.

* For offset calibration user has to connect GND(0V) on ADC input.

* For Gain Calibration user has to connect 1.55V on ADC input.

* Serial console prints the ADC input voltage after calibration done.
*/

void adc_calibration(void)	
{
	uint8_t key;
	
	printf("\x0C\n-- Start of ADC Calibration Example --\n");

	configure_adc();
	
	printf("Commands:\n");
	printf("- key 'c' to enable correction\n");
	printf("- key 'd' to disable correction\n");
		
	key = getchar();
	
	delay_ms(500);
	
	if (key == 'c') {
		adc_correction_start();				
	}
	if (key == 'd') {
		adc_correction_stop();	
	}
	
	raw_result = adc_start_read_result();
	
	result = ((float)raw_result * (float)ADC_REFERENCE_INTVCC1_VALUE)/(float)ADC_12BIT_FULL_SCALE_VALUE;
	
	printf("\nADC Input voltage is %fV", result);	
	
	printf("\n-- End of ADC Calibration Example --\n");

}

/**
* \brief ADC internal TemperatureSensor mode.
*
* This function enables the internal temperature sensor for ADC input and displays 
* the current room temperature in serial console after the calculation done using ADC result.
*/

void adc_temp_sensor(void)
{
	float temp;
	
	system_voltage_reference_enable(SYSTEM_VOLTAGE_REFERENCE_TEMPSENSE);
	
	configure_adc_temp();
	
	load_calibration_data();
	
	raw_result = adc_start_read_result();
	
	temp = calculate_temperature(raw_result);
	
	printf("\nThe current temperature is = %f degree Celsius", temp);
	
}
