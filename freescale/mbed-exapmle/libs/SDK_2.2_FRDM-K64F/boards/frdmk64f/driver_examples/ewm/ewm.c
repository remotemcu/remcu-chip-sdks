/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_gpio.h"
#include "fsl_ewm.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SW_GPIO BOARD_SW2_GPIO
#define SW_GPIO_PIN BOARD_SW2_GPIO_PIN
#define SW_NAME BOARD_SW2_NAME

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/
volatile bool ewmIsrFlag = false;
static EWM_Type *base = EWM;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Configure gpio as input for button
 *
 */
void gpio_configure(void)
{
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput, 0,
    };
    GPIO_PinInit(SW_GPIO, SW_GPIO_PIN, &sw_config);
}

/*!
 * @brief Check if button is pressed.
 *
 * This function gets the state of button.
 *
 * @return 0 if button is not pressed.
 *         1 if button is pressed
 */
static uint32_t is_key_pressed(void)
{
    return !(GPIO_ReadPinInput(SW_GPIO, SW_GPIO_PIN));
}

/*!
 * @brief EWM interrupt handler
 *
 */
void WDOG_EWM_IRQHandler(void)
{
    EWM_DisableInterrupts(base, kEWM_InterruptEnable); /*!< de-assert interrupt request */
    ewmIsrFlag = true;
}

void delay(void)
{
    for (uint32_t i = 0; i < 0x7fffffU; i++)
    {
        __NOP();
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    ewm_config_t config;

    /* Init hardware*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    gpio_configure();

    /* EWM peripheral driver test */
    /*
     * config.enableEwm = true;
     * config.enableEwmInput = false;
     * config.setInputAssertLogic = false;
     * config.enableInterrupt = false;
     * config.clockSource = kEWM_LpoClockSource0;
     * config.prescaler = 0U;
     * config.compareLowValue = 0U;
     * config.compareHighValue = 0xFEU;
     */
    EWM_GetDefaultConfig(&config);
    config.enableInterrupt = true;
    NVIC_EnableIRQ(WDOG_EWM_IRQn);
    EWM_Init(base, &config);

    PRINTF("\r\n EWM example ");
    PRINTF("\r\n Press %s to expire EWM ", SW_NAME);
    while (1)
    {
        /* Restart counter*/
        EWM_Refresh(base);
        /* Check for SW button push*/
        if (is_key_pressed())
        {
            /*Check ewm interrupt occur*/
            while (!ewmIsrFlag)
            {
            }
            PRINTF("\r\n EWM interrupt is occurred");

            /* Clear interrupt flag*/
            ewmIsrFlag = false;
            PRINTF("\r\n Press %s to expire EWM again", SW_NAME);
            /*Restart counter and enable interrupt for next run*/
            EWM_Refresh(base);
            /* Delay for a while in order to press button, interrrupt occurred only once*/
            delay();
            /*Enable EWM interrupt*/
            EWM_EnableInterrupts(base, kEWM_InterruptEnable);
        }
    }
}
