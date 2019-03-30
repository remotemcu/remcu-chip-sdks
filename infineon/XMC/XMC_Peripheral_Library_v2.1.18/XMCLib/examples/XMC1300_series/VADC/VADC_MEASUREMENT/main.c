/* =========================================================================== *
 * Copyright (c) 2014, Infineon Technologies AG                                *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 * Redistributions of source code must retain the above copyright notice, this *
 * list of conditions and the following disclaimer. Redistributions in binary  *
 * form must reproduce the above copyright notice, this list of conditions and *
 * the following disclaimer in the documentation and/or other materials        *
 * provided with the distribution. Neither the name of the copyright holders   *
 * nor the names of its contributors may be used to endorse or promote         *
 * products derived from this software without specific prior written          *
 * permission.                                                                 *
 *                                                                                                                                                                                                                                                                                                                   *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       *
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      *
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR           *
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       *
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         *
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; *
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    *
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     *
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF      *
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                  *
 * To improve the quality of the software, users are encouraged to share       *
 * modifications, enhancements or bug fixes with                               *
 * Infineon Technologies AG (dave@infineon.com).                               *
 *                                                                             *
 * ========================================================================== */

/*******************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC1000 Series                                         **
**                                                                            **
** AUTHOR : Application Engineering Team                                      **
**                                                                            **
** Project version update to  v 1.0.0  Initial Version                        **
**                                                                            **
** MODIFICATION DATE : Aug 01, 2014                                           **
**                                                                            **
*******************************************************************************/
/*
 *  file : Main.c
 *  brief : This is an example depicting usage of the low level SCU and ADC driver.
 *          The SCU driver is used to set up the clocks and take ADC out of reset.
 *          The ADC driver is used to configure various functional blocks of the
 *          peripheral, setting up of a single entry queue and converting the lone
 *          entry by means of a software generated queue conversion request.
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <xmc_vadc.h>
#include <xmc_scu.h>
#include <xmc_gpio.h>

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
#define RES_REG_NUMBER    (0)
#define CHANNEL_NUMBER    (7U)
#define VADC_GROUP_PTR    (VADC_G1) /* P2.5 */
#define VADC_GROUP_ID     (1)
#define IRQ_PRIORITY      (10U)
#define DELAY_COUNT       (500U)

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/
volatile uint32_t g_num_interrupts;
volatile bool     g_int_flag;

/* Initialization data of the SCU driver */
XMC_SCU_CLOCK_CONFIG_t g_clock_object =
{
  XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK,
  XMC_SCU_CLOCK_RTCCLKSRC_DCO2,
  0U, /* fdiv = 0 */
  1U, /* idiv = 1 */
};

/* Initialization data of VADC Global resources */
XMC_VADC_GLOBAL_CONFIG_t g_global_handle =
{
  .disable_sleep_mode_control = 0,
  .class0 = 
  {
    .conversion_mode_standard       =  XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv           = 3U,
    .conversion_mode_emux           =  XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel    = 0,
   },
  .class1 = 
  {
    .conversion_mode_standard    =  XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv        = 3U,
    .conversion_mode_emux        =  XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel = 3U
  },
  .data_reduction_control = 0,
  .wait_for_read_mode = true,
  .event_gen_enable = false,
  .boundary0 = 0,
  .boundary1 = 0
 };

/* Initialization data of a VADC group */
XMC_VADC_GROUP_CONFIG_t g_group_handle =
{
  .class0 = 
  {
    .conversion_mode_standard       =  XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv           = 3U,
    .conversion_mode_emux           =  XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel    = 3U,
  },
  .class1 = 
  {
    .conversion_mode_standard       =  XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv           = 3U,
    .conversion_mode_emux           =  XMC_VADC_CONVMODE_12BIT,
    .sampling_phase_emux_channel    = 3U,
  },
  .arbitration_round_length = 0x0,
  .arbiter_mode =  XMC_VADC_GROUP_ARBMODE_ALWAYS,
  .boundary0 = 0, /* Boundary-0 */
  .boundary1 = 0,  /* Boundary-1 */
  .emux_config = 
  {
    .emux_mode = XMC_VADC_GROUP_EMUXMODE_SWCTRL,
    .stce_usage = 0,
    .emux_coding = XMC_VADC_GROUP_EMUXCODE_BINARY,
    .starting_external_channel = 0,
    .connected_channel = 0
  }
};

/* Identifier of the hardware group */
XMC_VADC_GROUP_t *g_group_identifier =VADC_GROUP_PTR;

/* Channel configuration data */
XMC_VADC_CHANNEL_CONFIG_t  g_channel_handle =
{
  .channel_priority              = 1U,
  .input_class                   = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
  .alias_channel                 = XMC_VADC_CHANNEL_ALIAS_DISABLED,
  .bfl                           = 0,
  .event_gen_criteria            = XMC_VADC_CHANNEL_EVGEN_ALWAYS,
  .alternate_reference           = XMC_VADC_CHANNEL_REF_INTREF,
  .result_reg_number             = (uint8_t) RES_REG_NUMBER,
  .sync_conversion               = false,                          /* Sync Feature disabled*/
  .result_alignment              = XMC_VADC_RESULT_ALIGN_RIGHT,
  .use_global_result             = false,
  .broken_wire_detect_channel    = false,
  .broken_wire_detect            = false
};

/* Result configuration data */
XMC_VADC_RESULT_CONFIG_t g_result_handle = 
{
  .post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
  .data_reduction_control = 0,
  .part_of_fifo           = false, /* No FIFO */
  .wait_for_read_mode     = true, /* WFS */
  .event_gen_enable       = false  /* No result event */
};

/* Queue hardware configuration data */
XMC_VADC_QUEUE_CONFIG_t g_queue_handle =
{
  .req_src_priority = (uint8_t)3, /* Highest Priority = 3, Lowest = 0 */
  .conv_start_mode  = XMC_VADC_STARTMODE_WFS,
  .external_trigger = (bool) false, /* No external trigger */
  .trigger_signal   = XMC_VADC_REQ_TR_A, /* Irrelevant */
  .trigger_edge     = XMC_VADC_TRIGGER_EDGE_NONE,
  .gate_signal      = XMC_VADC_REQ_GT_A, /* Irrelevant */
  .timer_mode       = (bool) false, /* No timer mode */
};

/* Queue Entry */
XMC_VADC_QUEUE_ENTRY_t g_queue_entry =
{
 .channel_num        = CHANNEL_NUMBER,
 .refill_needed      = true, /* Refill is needed */
 .generate_interrupt = true, /* Interrupt generation is needed */
 .external_trigger   = true  /* External trigger is required */
};

XMC_GPIO_CONFIG_t gpio_input =
{
  .mode = XMC_GPIO_MODE_INPUT_TRISTATE
};

/*********************************************************************************************************************
 * MAIN APPLICATION
 ********************************************************************************************************************/

/* Interrupt handler */
void VADC0_G1_0_IRQHandler(void)
{
  XMC_VADC_RESULT_SIZE_t result;

  /* Read the result register */
  result = XMC_VADC_GROUP_GetResult(g_group_identifier,RES_REG_NUMBER);

  /* Clear result event */
  XMC_VADC_GROUP_ClearResultEvent(g_group_identifier,RES_REG_NUMBER);

  /* Acknowledge the interrupt */
  XMC_VADC_GROUP_QueueClearReqSrcEvent(g_group_identifier);

  /* Bump up the interrupt count */
  g_num_interrupts++;

  /* Signal to the main application that the interrupt has occured */
  g_int_flag = true;
  result = result;
}

/* Application entry point */
int main(void)
{

  /* Initialize clock */
  XMC_SCU_CLOCK_Init(&g_clock_object);

  /* Initialize the VADC global registers */
  XMC_VADC_GLOBAL_Init(VADC, &g_global_handle);

  /* Configure a conversion kernel */
  XMC_VADC_GROUP_Init(g_group_identifier, &g_group_handle);

  /* Configure the queue request source of the aforesaid conversion kernel */
  XMC_VADC_GROUP_QueueInit(g_group_identifier, &g_queue_handle);

  /* Configure a channel belonging to the aforesaid conversion kernel */
  XMC_VADC_GROUP_ChannelInit(g_group_identifier,CHANNEL_NUMBER, &g_channel_handle);

  /* Configure a result resource belonging to the aforesaid conversion kernel */
  XMC_VADC_GROUP_ResultInit(g_group_identifier, RES_REG_NUMBER, &g_result_handle);

  /* Add the channel to the queue */
  XMC_VADC_GROUP_QueueInsertChannel(g_group_identifier, g_queue_entry);

  /* Set priority of NVIC node meant to e connected to Kernel Request source event */
  NVIC_SetPriority(VADC0_G1_0_IRQn, IRQ_PRIORITY);

  /* Connect RS Event to the NVIC nodes */
  XMC_VADC_GROUP_QueueSetReqSrcEventInterruptNode(g_group_identifier, XMC_VADC_SR_GROUP_SR0);

  /* Enable IRQ */
  NVIC_EnableIRQ(VADC0_G1_0_IRQn);

  /* Enable the analog converters */
  XMC_VADC_GROUP_SetPowerMode(g_group_identifier, XMC_VADC_GROUP_POWERMODE_NORMAL);

  /* Perform calibration of the converter */
  XMC_VADC_GLOBAL_StartupCalibration(VADC);

  /* Start conversion by generating a conversion request (Simulating external trigger) */
  XMC_VADC_GROUP_QueueTriggerConversion(g_group_identifier);

  XMC_GPIO_Init(XMC_GPIO_PORT2,5,&gpio_input);


  while(1)
  {
    /* Spin until ISR is executed */
    while(g_int_flag == false)
    {

    }

    /* Clear the ISR flag */
    g_int_flag = false;

    /* Create an artificial delay */
    for(volatile uint32_t delay = 0; delay < DELAY_COUNT; delay++)
    {

    }

    /* Restart the conversion by regenerating a conversion request */
    XMC_VADC_GROUP_QueueTriggerConversion(g_group_identifier);
  }
}
