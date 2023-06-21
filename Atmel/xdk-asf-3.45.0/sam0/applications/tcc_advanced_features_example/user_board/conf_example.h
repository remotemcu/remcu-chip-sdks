/**
 * \file
 *
 * \brief SAM D21 TCC Advanced Features example configuration
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


#ifndef CONFIG_EXAMPLE_H_
#define CONFIG_EXAMPLE_H_

/* enable the feature */
#define ENABLE_RAMP2C_MODE				true
#define ENABLE_RAMP2_DMA				false

/* Enable fault blanking feature in RAMP2C mode */
/* Enable when RAMP2C mode is Enabled
	ENABLE_RAMP2C_MODE				true
*/
#define ENABLE_FAULT_BALNKING			true
#define AC_SCALING_FACTOR				32

#if ENABLE_RAMP2C_MODE == true
#define CC0_Value						2500
#define CCB0_Value						0

#define CC1_Value						1250
#define CCB1_Value						0

#define CC2_Value						1250
#define CCB2_Value						0

#define PER_Value						5000
#define PERB_Value						0

#else

#define CC0_Value						250
#define CCB0_Value						250

#define CC1_Value						250
#define CCB1_Value						250

#define CC2_Value						250
#define CCB2_Value						250

#define PER_Value						500
#define PERB_Value						500
#endif

#define GLCK_SOURCE						GCLK_GENERATOR_1
#define TCC_CLOCK_DIVIDER				TCC_CLOCK_PRESCALER_DIV1

/* if enabled RAMP2C mode */ 
#if (ENABLE_RAMP2C_MODE == true)

#define TRIGGER_PIN						PIN_PA02
#define FAULT_INPUT_PIN					PIN_PA14
#define BLANKPRESC						15

#elif (ENABLE_RAMP2_DMA == true)

#define TRIGGER_PIN						PIN_PA10

#endif

/* function prototypes*/
void config_ramp2c(void);
void config_ramp2_dma(void);
void trigger_generation(void);
void trigger_fault(void);

#endif /* CONFIG_EXAMPLE_H_ */