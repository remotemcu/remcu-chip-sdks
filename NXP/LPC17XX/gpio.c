///////////////////////////////////////////////////////////////////////////////
//  Includes
#include <unistd.h>
#include <stdio.h>

#define CHIP_LPC175X_6X
#define CORE_M3

#include "chip.h"

#include "remcu.h"

const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

/**
 * @brief	Main program body
 * @return	Does not return
 */
int main(void)
{

remcu_connect2OpenOCD("localhost", 6666);
remcu_resetRemoteUnit(ResetType::__HALT);
remcu_setVerboseLevel(LevelDebug::__INFO);

	/* Generic Initialization */
	SystemCoreClockUpdate();

	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	Chip_GPIO_WriteDirBit(LPC_GPIO, 1, 18, true);
		
		while(1){
		printf("!\n");
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 18, true);
		sleep(1);
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 18, false);
		sleep(1);
	}

		return 0;
}