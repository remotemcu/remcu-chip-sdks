/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/** @file
 * @defgroup nrf_adc_example main.c
 * @{
 * @ingroup nrf_adc_example
 * @brief ADC Example Application main file.
 *
 * This file contains the source code for a sample application using the ADC driver.
 */

 
#include <stdlib.h>
//#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
/* Includes ------------------------------------------------------------------*/

#include "remcu.h"

#include "nrf_drv_adc.h"
// #include "nordic_common.h"
#include "boards.h"



#if (defined(_WIN32) || defined(WIN32) || defined(WIN64) || defined(_WIN64))
  #define sleep _sleep
#else
#include <unistd.h>
#endif



#define ADC_BUFFER_SIZE 10                                /**< Size of buffer for ADC samples.  */
static nrf_adc_value_t       adc_buffer[ADC_BUFFER_SIZE]; /**< ADC buffer. */
static nrf_drv_adc_channel_t m_channel_config = NRF_DRV_ADC_DEFAULT_CHANNEL(NRF_ADC_CONFIG_INPUT_2); /**< Channel instance. Default configuration used. */

/**
 * @brief ADC initialization.
 */
static void adc_config(void)
{
    ret_code_t ret_code;
    nrf_drv_adc_config_t config = NRF_DRV_ADC_DEFAULT_CONFIG;

    ret_code = nrf_drv_adc_init(&config, NULL);
    printf("ret_code %d\n", ret_code);

    nrf_drv_adc_channel_enable(&m_channel_config);
}

/**
  * @brief main entry point.
  * @par Parameters None
  * @retval void None
  * @par Required preconditions: None
  */
int main(int argc, char** argv)
{
  printf("argc : %d\n", argc);

  if(argc < 3){
        printf("test requare 2 arguments: host and port\n");
        return -1;
    }
    const char * host = argv[1];
    printf("host : %s\n", argv[1]);
    printf("port string : %s\n", argv[2]);
    const uint16_t port = (atoi(argv[2]) & 0xFFFF);
    printf("port : %d\n", port);

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

  remcu_resetRemoteUnit(__HALT);
  remcu_setVerboseLevel(__ERROR);

  assert(remcu_isConnected());

  SystemInit(); // init function from asm code

  bsp_board_leds_init();

  adc_config();


  while (true)
  {
      ret_code_t code = nrf_drv_adc_buffer_convert(adc_buffer,ADC_BUFFER_SIZE);
      printf("nrf_drv_adc_buffer_convert return %d\n", code);
      uint32_t i;
      for (i = 0; i < ADC_BUFFER_SIZE; i++)
      {
          // manually trigger ADC conversion
          nrf_drv_adc_sample();
          // no enter into sleep mode
          // __SEV();
          // __WFE();
          // __WFE();
          printf("adc value: %x\n", adc_buffer[i]);

          sleep(1);
          bsp_board_led_invert(BSP_BOARD_LED_0);
      }
  }


}		
