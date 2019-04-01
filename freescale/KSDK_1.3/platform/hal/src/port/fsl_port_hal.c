/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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

#include "fsl_port_hal.h"

#if FSL_FEATURE_SOC_PORT_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PORT_HAL_SetLowGlobalPinCtrl
 * Description   : Configure low half of pin control register for the same settings,
 *                 this function operates pin 0 -15 of one specific port.
 *
 *END**************************************************************************/
void PORT_HAL_SetLowGlobalPinCtrl(PORT_Type * base, uint16_t lowPinSelect, uint16_t config)
{
    uint32_t combine = lowPinSelect;
    combine = (combine << 16) + config;
    PORT_WR_GPCLR(base, combine);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PORT_HAL_SetHighGlobalPinCtrl
 * Description   : Configure high half of pin control register for the same
 *                 settings, this function operates pin 16 -31 of one specific port.
 *
 *END**************************************************************************/
void PORT_HAL_SetHighGlobalPinCtrl(PORT_Type * base, uint16_t highPinSelect, uint16_t config)
{
    uint32_t combine = highPinSelect;
    combine = (combine << 16) + config;
    PORT_WR_GPCHR(base, combine);
}

#endif /* FSL_FEATURE_SOC_PORT_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

#ifdef REMCU_LIB

void PORT_HAL_SetMuxMode(PORT_Type * base,
                                       uint32_t pin,
                                       port_mux_t mux)
{
    assert(pin < 32U);
    PORT_BWR_PCR_MUX(base, pin, mux);
}

#if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
/*!
 * @brief Enables or disables the open drain.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 * @param isOpenDrainEnabled  enable open drain or not
 *        - false: Open Drain output is disabled on the corresponding pin.
 *        - true : Open Drain output is disabled on the corresponding pin.
 */
void PORT_HAL_SetOpenDrainCmd(PORT_Type * base,
                                                 uint32_t pin,
                                                 bool isOpenDrainEnabled)
{
    assert(pin < 32U);
    PORT_BWR_PCR_ODE(base, pin, isOpenDrainEnabled);
}
#endif

#if FSL_FEATURE_PORT_HAS_PULL_ENABLE
/*!
 * @brief Enables or disables the internal pull resistor.
 *
 * @param base  port base pointer
 * @param pin       port pin number
 * @param isPullEnabled  internal pull resistor enable or disable
 *        - true : internal pull resistor is enabled.
 *        - false: internal pull resistor is disabled.
 */
void PORT_HAL_SetPullCmd(PORT_Type * base,
                                       uint32_t pin,
                                       bool isPullEnabled)
{
    assert(pin < 32U);
    PORT_BWR_PCR_PE(base, pin, isPullEnabled);
}
#endif

#if FSL_FEATURE_PORT_HAS_PULL_SELECTION
/*!
 * @brief Selects the internal resistor as pull-down or pull-up.
 *
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * @param base  port base pointer.
 * @param pin       port pin number
 * @param pullSelect  internal resistor pull feature selection
 *        - kPortPullDown: internal pull-down resistor is enabled.
 *        - kPortPullUp  : internal pull-up resistor is enabled.
 */
void PORT_HAL_SetPullMode(PORT_Type * base,
                                        uint32_t pin,
                                        port_pull_t pullSelect)
{
    assert(pin < 32U);
    PORT_BWR_PCR_PS(base, pin, pullSelect);
}
#endif

#if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
/*!
 * @brief Configures the passive filter if the pin is used as a digital input.
 *
 * If enabled, a low pass filter (10 MHz to 30 MHz bandwidth)  is enabled
 * on the digital input path. Disable the Passive Input Filter when supporting
 * high speed interfaces (> 2 MHz) on the pin.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 * @param isPassiveFilterEnabled  passive filter configuration
 *        - false: passive filter is disabled.
 *        - true : passive filter is enabled.
 */
void PORT_HAL_SetPassiveFilterCmd(PORT_Type * base,
                                                uint32_t pin,
                                                bool isPassiveFilterEnabled)
{
    assert(pin < 32U);
    PORT_BWR_PCR_PFE(base, pin, isPassiveFilterEnabled);
}
#endif

#if FSL_FEATURE_PORT_HAS_SLEW_RATE
/*!
 * @brief Configures the fast/slow slew rate if the pin is used as a digital output.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 * @param rateSelect  slew rate selection
 *        - kPortFastSlewRate: fast slew rate is configured.
 *        - kPortSlowSlewRate: slow slew rate is configured.
 */
void PORT_HAL_SetSlewRateMode(PORT_Type * base,
                                            uint32_t pin,
                                            port_slew_rate_t rateSelect)
{
    assert(pin < 32U);
    PORT_BWR_PCR_SRE(base, pin, rateSelect);
}
#endif

#if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
/*!
 * @brief Configures the drive strength if the pin is used as a digital output.
 *
 * @param base  port base pointer
 * @param pin  port pin number
 * @param driveSelect  drive strength selection
 *        - kLowDriveStrength : low drive strength is configured.
 *        - kHighDriveStrength: high drive strength is configured.
 */
void PORT_HAL_SetDriveStrengthMode(PORT_Type * base,
                                                 uint32_t pin,
                                                 port_drive_strength_t driveSelect)
{
    assert(pin < 32U);
    PORT_BWR_PCR_DSE(base, pin, driveSelect);
}
#endif

#endif //REMCU_LIB