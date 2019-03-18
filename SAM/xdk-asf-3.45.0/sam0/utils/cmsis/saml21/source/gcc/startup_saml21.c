/**
 * \file
 *
 * \brief gcc starttup file for SAML21
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

#include "saml21.h"

/* Initialize segments */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

void __libc_init_array(void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M0+ core handlers */
void NMI_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HardFault_Handler       ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Peripherals handlers */
void SYSTEM_Handler          ( void ) __attribute__ ((weak, alias("Dummy_Handler"))); /* MCLK, OSCCTRL, OSC32KCTRL, PAC, PM, SUPC, TAL */
void WDT_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void NVMCTRL_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_Handler            ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef ID_USB
void USB_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
void EVSYS_Handler           ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM0_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM1_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM2_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM3_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef ID_SERCOM4
void SERCOM4_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
#ifdef ID_SERCOM5
void SERCOM5_Handler         ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
void TCC0_Handler            ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC1_Handler            ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC2_Handler            ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef ID_TC2
void TC2_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
#ifdef ID_TC3
void TC3_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
void TC4_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef ID_ADC
void ADC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
#ifdef ID_AC
void AC_Handler              ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
#ifdef ID_DAC
void DAC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
#ifdef ID_PTC
void PTC_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
#ifdef ID_AES
void AES_Handler             ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif
#ifdef ID_TRNG
void TRNG_Handler            ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif

/* Exception Table */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {

        /* Configure Initial Stack Pointer, using linker-generated symbols */
        (void*) (&_estack),

        (void*) Reset_Handler,
        (void*) NMI_Handler,
        (void*) HardFault_Handler,
        (void*) (0UL), /* Reserved */
        (void*) (0UL), /* Reserved */
        (void*) (0UL), /* Reserved */
        (void*) (0UL), /* Reserved */
        (void*) (0UL), /* Reserved */
        (void*) (0UL), /* Reserved */
        (void*) (0UL), /* Reserved */
        (void*) SVC_Handler,
        (void*) (0UL), /* Reserved */
        (void*) (0UL), /* Reserved */
        (void*) PendSV_Handler,
        (void*) SysTick_Handler,

        /* Configurable interrupts */
        (void*) SYSTEM_Handler,         /*  0 Main Clock, Oscillators Control, 32k Oscillators Control, Peripheral Access Controller, Power Manager, Supply Controller, Trigger Allocator */
        (void*) WDT_Handler,            /*  1 Watchdog Timer */
        (void*) RTC_Handler,            /*  2 Real-Time Counter */
        (void*) EIC_Handler,            /*  3 External Interrupt Controller */
        (void*) NVMCTRL_Handler,        /*  4 Non-Volatile Memory Controller */
        (void*) DMAC_Handler,           /*  5 Direct Memory Access Controller */
#ifdef ID_USB
        (void*) USB_Handler,            /*  6 Universal Serial Bus */
#else
        (void*) (0UL), /* Reserved */
#endif
        (void*) EVSYS_Handler,          /*  7 Event System Interface */
        (void*) SERCOM0_Handler,        /*  8 Serial Communication Interface 0 */
        (void*) SERCOM1_Handler,        /*  9 Serial Communication Interface 1 */
        (void*) SERCOM2_Handler,        /* 10 Serial Communication Interface 2 */
        (void*) SERCOM3_Handler,        /* 11 Serial Communication Interface 3 */
#ifdef ID_SERCOM4
        (void*) SERCOM4_Handler,        /* 12 Serial Communication Interface 4 */
#else
        (void*) (0UL), /* Reserved */
#endif
#ifdef ID_SERCOM5
        (void*) SERCOM5_Handler,        /* 13 Serial Communication Interface 5 */
#else
        (void*) (0UL), /* Reserved */
#endif
        (void*) TCC0_Handler,           /* 14 Timer Counter Control 0 */
        (void*) TCC1_Handler,           /* 15 Timer Counter Control 1 */
        (void*) TCC2_Handler,           /* 16 Timer Counter Control 2 */
        (void*) TC0_Handler,            /* 17 Basic Timer Counter 0 */
        (void*) TC1_Handler,            /* 18 Basic Timer Counter 1 */
#ifdef ID_TC2
        (void*) TC2_Handler,            /* 19 Basic Timer Counter 2 */
#else
        (void*) (0UL), /* Reserved */
#endif
#ifdef ID_TC3
        (void*) TC3_Handler,            /* 20 Basic Timer Counter 3 */
#else
        (void*) (0UL), /* Reserved */
#endif
        (void*) TC4_Handler,            /* 21 Basic Timer Counter 4 */
#ifdef ID_ADC
        (void*) ADC_Handler,            /* 22 Analog Digital Converter */
#else
        (void*) (0UL), /* Reserved */
#endif
#ifdef ID_AC
        (void*) AC_Handler,             /* 23 Analog Comparators */
#else
        (void*) (0UL), /* Reserved */
#endif
#ifdef ID_DAC
        (void*) DAC_Handler,            /* 24 Digital-to-Analog Converter */
#else
        (void*) (0UL), /* Reserved */
#endif
#ifdef ID_PTC
        (void*) PTC_Handler,            /* 25 Peripheral Touch Controller */
#else
        (void*) (0UL), /* Reserved */
#endif
#ifdef ID_AES
        (void*) AES_Handler,            /* 26 Advanced Encryption Standard */
#else
        (void*) (0UL), /* Reserved */
#endif
#ifdef ID_TRNG
        (void*) TRNG_Handler,           /* 27 True Random Generator */
#else
        (void*) (0UL), /* Reserved */
#endif
        (void*) (0UL)  /* Reserved */
};

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)
{
        uint32_t *pSrc, *pDest;

        /* Initialize the relocate segment */
        pSrc = &_etext;
        pDest = &_srelocate;

        if (pSrc != pDest) {
                for (; pDest < &_erelocate;) {
                        *pDest++ = *pSrc++;
                }
        }

        /* Clear the zero segment */
        for (pDest = &_szero; pDest < &_ezero;) {
                *pDest++ = 0;
        }

        /* Set the vector table base address */
        pSrc = (uint32_t *) & _sfixed;
        SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

        /* Overwriting the default value of the NVMCTRL.CTRLB.MANW bit (errata reference 13134) */
        NVMCTRL->CTRLB.bit.MANW = 1;

        /* Initialize the C library */
        __libc_init_array();

        /* Branch to main function */
        main();

        /* Infinite loop */
        while (1);
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
        while (1) {
        }
}
