/**
 * \file
 *
 * \brief DMAC Application Note Example for the case 'ADC_NO_DMAC_MEM_MEM_USART'
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
 
 /*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <string.h>


#if defined(ADC_NO_DMAC_MEM_MEM_USART)

/* FUNCTION PROTOTYPES */

/*! \brief Initializes and enables ADC */
void configure_adc(void);

/*! \brief Initializes and enables SERCOM - USART */
void configure_usart(void);

/*! \brief Initializes and enables PORT */
void configure_port(void);

/*! \brief Initializes and enables System Timer (SysTick) */
void systick_init(void);

/*! This function calculates number of cycles taken from SysTick time stamp */
uint32_t calculate_cycles_taken(uint32_t start_cycle, uint32_t end_cycle);


/*! Writes data to SERCOM - USART */
void usart_write_data(struct usart_module *const module, uint8_t *usart_tx_data, uint32_t length);

/*! ADC interrupt Handler */
static void _adc_interrupt_handler(void);

/*! USART interrupt Handler */
static void _usart_interrupt_handler(void);


/* MACRO Definitions */

/*! Maximum reload value that can be loaded to SysTick */
#define SYSTICK_MAX_VALUE  (SysTick_LOAD_RELOAD_Msk - 1) 

/*! Number of ADC samples to be taken and transferred (for with and without case) */
#define BLOCK_COUNT 1024


/*! brief Flag to indicate adc conversion done when not using DMA */
volatile bool adc_conv_done = false;

/*! brief Number of ADC samples done when not using DMA */
uint32_t adc_sample_count = 0; 

/*! SysTick variables to take time stamp at different instance */
uint32_t time_stamp1 =0,time_stamp2=0;

/*! brief Contains the number of cycles taken from SysTick time stamp */ 
uint32_t cycles_taken=0, idle_loop_count=0;

/*! brief  buffer tp store ADC result */
uint8_t adc_result[BLOCK_COUNT],adc_result_copy[BLOCK_COUNT];

/*! brief Initialize SysTick reload and overflow counter variable */
static volatile uint32_t systick_reload = 0,systick_counter = 0;

/*! brief  USART module instance */
struct usart_module usart_instance;

/*! brief ADC module instance */
struct adc_module adc_instance;

/*! brief PORT base address */
volatile PortGroup *const port_base = (PortGroup *const)PORT;

/**
 * \brief Enable ADC interrupt 
 * \param module_inst           ADC module instance
 * \param interrupt_mask        Interrupts to be enabled in ADC
 */
static inline void adc_interrupt_enable(struct adc_module *const module_inst,
uint8_t interrupt_mask)
{
	/* ADC module base address */
	Adc *const adc_module = module_inst->hw;
	/* Enable interrupts */
	adc_module->INTENSET.reg = interrupt_mask;
}

/**
 * \brief ADC interrupt Handler 
 * \param adc_module_inst       ADC module instance
 * \param usart_module_inst     USART module instance
 */
static void _adc_interrupt_handler(void)
{
	/* ADC base address */
	Adc *const adc_hw = adc_instance.hw;
	
	/* get interrupt flags */
	uint32_t flags = adc_hw->INTFLAG.reg;

	/* Check if the all the samples has been done by ADC */
	if (adc_sample_count == BLOCK_COUNT){
		
		/* Clear ADC interrupt */
		adc_hw->INTFLAG.reg = ADC_INTFLAG_RESRDY;
		
		/* Disable ADC */
		adc_hw->CTRLA.reg &= ~ADC_CTRLA_ENABLE;

		/* Copy adc result to another buffer */
		memcpy_ram2ram(adc_result_copy,adc_result,BLOCK_COUNT);
		/* Write samples to USART */
		usart_write_data(&usart_instance,adc_result_copy,BLOCK_COUNT);

		/* Indicate conversion has been done */
 		adc_conv_done = true;
		/* Get the time stamp from SysTick */
		time_stamp2 = SysTick->VAL;

	}else if (flags & ADC_INTFLAG_RESRDY) {
		/* Clear ADC interrupt */
		adc_hw->INTFLAG.reg = ADC_INTFLAG_RESRDY;
		/* Store ADC result to RAM buffer */
		adc_result[adc_sample_count] = adc_hw->RESULT.reg;
		/* Count the number of samples taken so far */
		++adc_sample_count;
		/* Trigger next ADC conversion */
		adc_start_conversion(&adc_instance);
	}
} /* End of ADC Hander */

/**
 * \brief Actual ADC Handler
 * NOTE: This will point to the _adc_interrupt_handler function
 *       where the ADC interrupt is being processed.
 */
void ADC_Handler(void)
{
	#if defined (ENABLE_PORT_TOGGLE)
		/* 	 Use oscilloscope to probe the pin. */
		port_base->OUTTGL.reg = (1UL << PIN_PA14 % 32 );
	#endif
	_adc_interrupt_handler();

}

/**
 * \brief USART interrupt Handler 
 * \param usart_module_inst       USART module instance
 */
static void _usart_interrupt_handler(void)
{
	/* Pointer to the hardware module instance */
	SercomUsart *const usart_hw	= &(usart_instance.hw->USART);

	/* To store current interrupt status */
	uint8_t interrupt_status;

	/* Read interrupt flag register */
	interrupt_status = usart_hw->INTFLAG.reg;

	if (interrupt_status & SERCOM_USART_INTFLAG_TXC) {
		/* Clear Transfer Complete Interrupt */
		usart_hw->INTFLAG.reg = SERCOM_USART_INTENCLR_TXC;
	}

} /* End of USART Handler */

/**
 * \brief Actual SERCOM Handler
 * NOTE: This will point to the _usart_interrupt_handler function
 *       where the USART interrupt is being processed.
 */
#if (SAMD11) || (SAMD10) 
/* SERCOM2 is used in SAM D10/D11 devices */
void SERCOM2_Handler()
#else 
/* SERCOM4 is used in other devices */
void SERCOM4_Handler()
#endif
{
	_usart_interrupt_handler();
}

/**
 * \brief Write data to USART DATA register
 * \param usart_tx_data  Data to be written
 * \param length         Buffer length
 */
void usart_write_data(struct usart_module *const module, uint8_t *usart_tx_data, uint32_t length)
{
	/* Temporary count variable */
	uint32_t count ;

	/* SERCOM - USART base address */
	SercomUsart *const usart_hw	= &(module->hw->USART);

	for (count =0; count < length;count++){
		/* Wait until data register is empty */
		while(!(usart_hw->INTFLAG.reg & SERCOM_USART_INTFLAG_DRE));
		/* Write data to USART module */
		usart_hw->DATA.reg = usart_tx_data[count];
	}

}


/**
 * \brief SysTick interrupt handler
 */
void SysTick_Handler(void)
{
	/* Increment the software counter */
	systick_counter++;
}

/**
 * \brief Initialize the SysTick timer
 *
 */
void systick_init()
{
	/* Calculate the reload value */
	systick_reload = SYSTICK_MAX_VALUE;

	/* Initialize software counter */
	systick_counter = 0;

	/* Disable the SYSTICK Counter */
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);

	/* set reload register */
	SysTick->LOAD  =  systick_reload;

	/* set Priority for Cortex-M0 System Interrupts */
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

	/* Load the SysTick Counter Value */
	SysTick->VAL  = systick_reload;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
					SysTick_CTRL_TICKINT_Msk   |
					SysTick_CTRL_ENABLE_Msk;

	/* Enable SysTick interrupt */
	NVIC_EnableIRQ(SysTick_IRQn);
}

/**
 * \brief configure and enable SERCOM - USART
 */
void configure_usart(void)
{
	/* USART set up configuration */
	struct usart_config config_usart;
	
	/* USART base address */
	SercomUsart *const usart_hw	= (SercomUsart *const)EDBG_CDC_MODULE;
	
	/* Get USART default configuration */
	usart_get_config_defaults(&config_usart);

	/* Configure USART baud rate and pad */
	config_usart.baudrate    = 460800;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;

	/* Initialize USART */
	while (usart_init(&usart_instance,
	EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}

	/* Enable interrupt */
	system_interrupt_enable(EDBG_CDC_MODULE_IRQn);


	/* Enable USART */
	usart_enable(&usart_instance);
	
	/* Enable USART transfer complete interrupt */
	usart_hw->INTENSET.reg	= SERCOM_USART_INTFLAG_TXC;

}


/**
 * \brief Configure and enable ADC 
 */
void configure_adc(void)
{
	/* ADC configuration set up */
	struct adc_config config_adc;

	/* Get default ADC configuration */
	adc_get_config_defaults(&config_adc);

#if (SAMD11) || (SAMD10)
	config_adc.gain_factor     = ADC_GAIN_FACTOR_DIV2;
#endif
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV64;
	config_adc.reference       = ADC_REFERENCE_INTVCC1;
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN0;
	config_adc.resolution      = ADC_RESOLUTION_8BIT;

	/* Initialize ADC */
	adc_init(&adc_instance, ADC, &config_adc);

	/* Enable ADC Result ready interrupt */
	adc_interrupt_enable(&adc_instance,ADC_INTFLAG_RESRDY);
	/* Enable ADC module interrupt in NVIC */
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_ADC);

	/* Enable ADC module */
	adc_enable(&adc_instance);

}

/**
 * \brief Calculate number of cycles taken to execute certain number of 
 * instructions from the time stamp taken with system timer (SysTick)
 */
uint32_t calculate_cycles_taken(uint32_t start_cycle, uint32_t end_cycle)
{

	uint32_t total_cycles =0;

	/* Check if counter flow occurs */
	if (systick_counter == 0){
		/* Ensure Start cycle is greater than end cycle */
		if(start_cycle > end_cycle)
			total_cycles = start_cycle - end_cycle;
	}else if (systick_counter > 0){
		total_cycles = start_cycle + ((systick_counter-1) * SYSTICK_MAX_VALUE) 
							+ (SYSTICK_MAX_VALUE - end_cycle);
	}

	return total_cycles;
}

/**
 * \brief Configure port pins PA14 and PA16 as output with zero 
 * as initial out value.
 */
void configure_port(void)
{
	/* Set PA14 and PA15 as output */
	port_base->DIRSET.reg = (1UL << PIN_PA14 % 32 ) | (1UL << PIN_PA16 % 32 );
	/* Set OUT value to zero */
	port_base->OUT.reg = (0UL << PIN_PA14 % 32 ) | (0UL << PIN_PA16 % 32 );

}


/**
 * \brief Main Application Routine                              \n
 * - Initialize the system clocks                               \n
 * NOTE: The clock should be configured in conf_clock.h         \n
 * - Configure port pins (PA14 and PA16) are used here          \n
 * - Enable Global Interrupt                                    \n
 * - Configure and enable USART                                 \n
 * - Configure and enable ADC                                   \n
 * - Configure and enable DMAC and EVSYS if DMAC mode is chosen \n
 * - Start first ADC conversion                                 \n
 * - Count idle loop count in forever loop                      \n
 */
int main(void)
{

	/* Initialize system clocks */
	system_init();

#if defined(ENABLE_PORT_TOGGLE)
	/* Configure PORT pins PA14 and PA16 are configured here
	 * NOTE: Use oscilloscope to probe the pin.
	 */
	configure_port();
#endif

	/* ENable Global interrupt */
	system_interrupt_enable_global();

	/* Start SysTick Timer */
	systick_init();
 
	/* Configure SERCOM - USART */
	configure_usart();

	/* Configure and enable ADC */
	configure_adc();

	/* Get the time stamp 1 before starting ADC transfer */
	time_stamp1 = SysTick->VAL;
	

	/*
	 * Trigger first ADC conversion through software.
	 * NOTE: In case of using DMA, further conversions are triggered through
	 * event generated when previous ADC result is transferred to destination 
	 * (can be USART DATA register [or] RAM buffer).
	 * When DMA is not used, further conversions are triggered via software in 
	 * ADC handler after each result ready.
	 */
	adc_start_conversion(&adc_instance);

	while (1){
		
		#if defined (ENABLE_PORT_TOGGLE)
			/* 	 Use oscilloscope to probe the pin. */
			port_base->OUTTGL.reg = (1UL << PIN_PA16 % 32 );
		#endif
		
		/* Increment idle count whenever application reached while(1) loop */
		idle_loop_count++;

		/*
		 * Check if 1024 bytes transfer is done in either case (I.e. with or without
		 * using DMA.
		 * 'adc_conv_done' flag is set to true in the ADC handler once 
		 * 'adc_sample_count' reaches BLOCK_COUNT.
		 * 'adc_dma_transfer_is_done' is set to true once DMA transfer is done 
		 * in DMA call back for channel zero when 'ADC_DMAC_USART' is chosen.
		 * When choosing ADC_DMAC_MEM_MEM_USART mode, 'adc_dma_transfer_is_done' 
		 * is set to true in DMA channel call back for channel 2.
		 * DMA channel is disabled once reaching BLOCK_COUNT (with DMA cases).
		 * ADC is disabled once reaching BLOBK_COUNT samples (without DMA cases).
		 */
		if (adc_conv_done == true){

			/*
			 * Calculate number of cycles taken from the time stamp 
			 * taken before start of the conversion and after 1024 transfer
			 * is completed.
			 * NOTE: This value in relation to the idle_loop_count is 
			 * used in calculating CPU usage.
			 */
			cycles_taken = calculate_cycles_taken(time_stamp1,time_stamp2);

			/* Write the CPU cycles taken on USART */
			usart_write_data(&usart_instance,(uint8_t *)&cycles_taken, sizeof(cycles_taken));
			/* Print idle loop count on USART */
			usart_write_data(&usart_instance,(uint8_t *)&idle_loop_count, sizeof(idle_loop_count));

			/*
			 * Enter into forever loop as all transfers are completed and 
			 * DMAC/ADC is disabled 
			 */
			while(1);
		}
	}

}//end of main


// Application Documentation
/*! \main page
 * \section intro Introduction
 * This application demonstrates CPU usage when an application is 
 * implemented with and without DMA. Also it demonstrates different 
 * DMA transfer types such as Peripheral to peripheral, Peripheral 
 * to memory, memory to memory and memory to peripheral.
 *
 * ADC is sampled and the result data is sent to USART. This application is 
 * implemented with and without DMAC. These different cases are chosen by 
 * switching compiler options in the file conf_dma.h. 
 * 
 * The CPU cycles taken is calculated for all the cases using 
 * System Timer (SysTick). A variable is also incremented in the while(1) loop
 * which executes whenever CPU is available. The proportion of these two values
 * are used to calculate the CPU usage for the chosen case.
 *
 * \section referenceinfo References
 * - SAM D10/D11 SAM L22 device data sheet
 * - SAMD11 / SAML22 Xplained Pro board schematics
 * - IO1 Xplained board schematics
 *
 * \section compinfo Compiler Support
 * This example application supports
 * - GNU GCC for ARM
 *
 * \section deviceinfo Device support
 * - ATSAMD11/10 Series
 * - ATSAML22 Series
 *
 * \author
 * Microchip Technology Inc : http://www.microchip.com
 */
#endif
