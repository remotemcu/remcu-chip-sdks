#include <Board_ADC.h>
#include <xmc_gpio.h>
#include <xmc_can.h>

#define TICKS_PER_SECOND 10

#define LED1 P3_9

// MCAN Node 2
#define CAN_TXD P1_9
#define CAN_RXD P1_8

#define CAN_FREQUENCY 120000000

/* CAN Bit time */
const XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t baud = 
{
  .can_frequency = CAN_FREQUENCY,
  .baudrate = 500000,
  .sample_point = 8000,
  .sjw = 1,
};

/* CAN message */
XMC_CAN_MO_t CAN_message =
{
  .can_mo_ptr = CAN_MO0,
  .can_priority = XMC_CAN_ARBITRATION_MODE_IDE_DIR_BASED_PRIO_2,
  .can_identifier = 0xff,
  .can_id_mask = 0xff,
  .can_id_mode = XMC_CAN_FRAME_TYPE_STANDARD_11BITS,
  .can_ide_mask = 1,
  .can_data_length = 2,
  .can_mo_type = XMC_CAN_MO_TYPE_TRANSMSGOBJ
};

void SysTick_Handler(void)
{
	XMC_GPIO_ToggleOutput(LED1);

	ADC_StartConversion();
	while (ADC_ConversionDone() != 0);
	
	CAN_message.can_data_word[0] = ADC_GetValue();
	XMC_CAN_MO_UpdateData(&CAN_message);
 
	/* Send data in CAN_message */
  XMC_CAN_MO_Transmit(&CAN_message);
}


int main(void)
{
	ADC_Initialize();
	
  /*Configure CAN Module*/
  XMC_CAN_Init(CAN, CAN_FREQUENCY);

  /*Configure CAN Node baudrate*/
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE2, &baud);
	
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE2);
  XMC_CAN_NODE_SetInitBit(CAN_NODE2);

	/* Configure CAN NODE input pin */
	XMC_GPIO_SetMode(CAN_RXD, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_CAN_NODE_SetReceiveInput(CAN_NODE2, XMC_CAN_NODE_RECEIVE_INPUT_RXDCA);

  /*Message Configuration*/
  XMC_CAN_MO_Config(&CAN_message);

  /*Allocate MO in Node List*/
  XMC_CAN_AllocateMOtoNodeList(CAN, 2, 0);
	
  XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE2);
  XMC_CAN_NODE_ResetInitBit(CAN_NODE2);
	
	/* Configure CAN NODE output pin */
	XMC_GPIO_SetMode(CAN_TXD, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2);

	/* Configure LED pin */
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  /* Configure SysTick */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

	while(1);
}

