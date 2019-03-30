#include "xmc_gpio.h"
#include "xmc_dma.h"
#include "xmc_ccu4.h"

/* Generate a PWM using the DMA
 * Using double buffering, while one buffer is used to update the PWM duty cycle the other buffer one can be updated
 * using new values.
 */

uint32_t shadow_transfer_enable;
uint32_t duty_cycles[2][48];

/* DMA linked list */
__attribute__((aligned(32))) XMC_DMA_LLI_t dma_ll[2] =
{
  {
    .block_size = 48,
    .src_addr = (uint32_t)&duty_cycles[0][0],
    .dst_addr = (uint32_t)&CCU40_CC40->CRS,
    .llp = &dma_ll[1],
    .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
    .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
    .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
    .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
    .src_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
    .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
    .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA,
    .enable_src_linked_list = true,
    .enable_dst_linked_list = true,
  },
  {
    .block_size = 48,
    .src_addr = (uint32_t)&duty_cycles[1][0],
    .dst_addr = (uint32_t)&CCU40_CC40->CRS,
    .llp = &dma_ll[0],
    .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
    .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
    .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
    .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
    .src_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
    .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
    .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA,
    .enable_src_linked_list = true,
    .enable_dst_linked_list = true,
  }
};

/* DMA channel used to transfer duty cycles using a linked list to achieve a double buffer */
XMC_DMA_CH_CONFIG_t dma_ch0_config =
{
  .block_size = 48,
  .linked_list_pointer = (XMC_DMA_LLI_t *)&dma_ll[0],
  .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA,
  .transfer_type = XMC_DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_LINKED,
  .src_handshaking = XMC_DMA_CH_SRC_HANDSHAKING_SOFTWARE,
  .dst_handshaking = XMC_DMA_CH_DST_HANDSHAKING_HARDWARE,
  .dst_peripheral_request = DMA0_PERIPHERAL_REQUEST_CCU40_SR0_0,
  .priority = XMC_DMA_CH_PRIORITY_0,
};

/* DMA channel used to transfer the shadow transfer request */
XMC_DMA_CH_CONFIG_t dma_ch1_config =
{
  .block_size = 48,
  .src_addr = (uint32_t)&shadow_transfer_enable,
  .dst_addr = (uint32_t)&CCU40->GCSS,
  .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
  .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
  .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
  .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
  .src_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
  .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
  .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA,
  .transfer_type = XMC_DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_RELOAD,
  .src_handshaking = XMC_DMA_CH_SRC_HANDSHAKING_SOFTWARE,
  .dst_handshaking = XMC_DMA_CH_DST_HANDSHAKING_HARDWARE,
  .dst_peripheral_request = DMA0_PERIPHERAL_REQUEST_CCU40_SR0_0,
  .priority = XMC_DMA_CH_PRIORITY_0
};

XMC_CCU4_SLICE_COMPARE_CONFIG_t ccu4_slice_compare =
{
 .prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
 .timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
};


int main(void)
{
  for (int i = 0; i < 48; ++i)
  {
    duty_cycles[0][i] = 1365 * i ;
    duty_cycles[1][i] = (1365 * 47) - (1365 * i);
  }

  shadow_transfer_enable = CCU4_GCSS_S0SE_Msk;

  XMC_DMA_Init(XMC_DMA0);
  XMC_DMA_CH_Init(XMC_DMA0, 0, &dma_ch0_config);
  XMC_DMA_CH_Init(XMC_DMA0, 1, &dma_ch1_config);

  XMC_CCU4_Init(CCU40, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);

  XMC_CCU4_EnableClock(CCU40, 0);
  XMC_CCU4_StartPrescaler(CCU40);

  XMC_CCU4_SLICE_CompareInit(CCU40_CC40, &ccu4_slice_compare);

  XMC_CCU4_SLICE_EnableEvent(CCU40_CC40, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);
  XMC_CCU4_SLICE_SetInterruptNode(CCU40_CC40, XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP, XMC_CCU4_SLICE_SR_ID_0);

  XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU40_CC40, 65535);
  XMC_CCU4_SLICE_SetTimerCompareMatch(CCU40_CC40, 65535);

  XMC_CCU4_EnableShadowTransfer(CCU40, XMC_CCU4_SHADOW_TRANSFER_SLICE_0);

  XMC_GPIO_SetMode(P0_15, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_15_AF_CCU40_OUT0);

  XMC_DMA_CH_Enable(XMC_DMA0, 0);
  XMC_DMA_CH_Enable(XMC_DMA0, 1);

  XMC_CCU4_SLICE_StartTimer(CCU40_CC40);

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {

  }
}
