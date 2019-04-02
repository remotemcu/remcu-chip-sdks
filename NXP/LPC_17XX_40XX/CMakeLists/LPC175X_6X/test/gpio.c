///////////////////////////////////////////////////////////////////////////////
//  Includes
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

#include "device_defines.h"
#include "chip.h"

#include "remcu.h"

const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

/**
 * @brief	Main program body
 * @return	Does not return
 */
int main(int argc, char** argv)
{
  printf("argc : %d\n", argc);

  if(argc < 3){
        printf("test requare 2 arguments: host and port\n");
        return -1;
    }
    const char * host = argv[1];
    printf("argv[1] : %s\n", argv[1]);
    printf("argv[2] : %s\n", argv[2]);
    const uint16_t port = (atoi(argv[2]) & 0xFFFF);
    printf("port : %d\n", port);

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

remcu_resetRemoteUnit(__HALT);
//remcu_setVerboseLevel(LevelDebug::__INFO);
remcu_setVerboseLevel(__ERROR);

  assert(remcu_is_connected());

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