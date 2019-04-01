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



#define HW_PLL_XTAL_MSEL_m1         (15)                    ///< FCCO = ((15+1) * 2 * 12MHz) / (0+1) = 384 MHz 
#define HW_PLLXTAL_CPU_CLK_DIV_m1   (3)                     ///< 384 MHz / (3+1) = 96 MHz
    #define HW_FLASHTIM_CPU_WC          (FLASHTIM_100MHZ_CPU)   ///< flash wait cycles, see enum 'FMC_FLASHTIM_T'

/** @brief PLL_clk = 360 MHz / div */
    #define HW_PLLIRC_CPU_CLK_DIV_m1        (3) 

    #define PINMUX_Port0                0
    #define PINMUX_Port1                1
    #define PINMUX_Port2                2
/**
 * @brief	Main program body
 * @return	Does not return
 */
int
HW_SetupIrcClocking(void)
{
	// Disconnect the Main PLL if it is connected already
	if (Chip_Clock_IsMainPLLConnected()) 
		Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT);

	// Disable the PLL if it is enabled
	if (Chip_Clock_IsMainPLLEnabled()) 
		Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);

	Chip_Clock_SetCPUClockDiv(0);
	Chip_Clock_SetMainPLLSource(SYSCTL_PLLCLKSRC_IRC);

	// FCCO = ((44+1) * 2 * 4MHz) / (0+1) = 360MHz
	Chip_Clock_SetupPLL(SYSCTL_MAIN_PLL, 44, 0);
	Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);

    // 360 MHz / (3+1) = 90MHz
	Chip_Clock_SetCPUClockDiv(HW_PLLIRC_CPU_CLK_DIV_m1);   
	while (!Chip_Clock_IsMainPLLLocked()) {} /* Wait for the PLL to Lock */

    // Setup FLASH access to 4 clocks (100MHz clock)
	Chip_SYSCTL_SetFLASHAccess(FLASHTIM_100MHZ_CPU);     
        
	Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT);        
        
    SystemCoreClockUpdate();
    return 0;
}
/***************************************************************************
 @brief  Config PLL using External Crystal
 @param  none, implicit: HW_PLLIRC_CPU_CLK_DIV
 @retval status of cofiguration, "0" - ok, "!0" - was error,
         error reason: timeout while PLL ready waiting
 @note   disable PLL before config, enable crystal, wait crystal is ready,
         set cpu clock divider to "0", select Xtal as PLL source,
         config PLL to 360 MHz, enable it, set cpu diviver, wait PLL is ready,
         also set flash access wait cycles
         based on "Chip_SetupXtalClocking" (see sysinit_17xx_40xx.c (LpcOpen 2.10))
*****************************************************************************/
int 
HW_SetupXtalClocking(void)
{
	// Disconnect the Main PLL if it is connected already
	if (Chip_Clock_IsMainPLLConnected())
		Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT);

	// Disable the PLL if it is enabled
	if (Chip_Clock_IsMainPLLEnabled())
		Chip_Clock_DisablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);

	// Enable the crystal
	if (!Chip_Clock_IsCrystalEnabled())
		Chip_Clock_EnableCrystal();
	while(!Chip_Clock_IsCrystalEnabled()) {}

	// Set PLL0 Source to Crystal Oscillator
	Chip_Clock_SetCPUClockDiv(0);
	Chip_Clock_SetMainPLLSource(SYSCTL_PLLCLKSRC_MAINOSC);

	// FCCO = ((HW_PLL_XTAL_MSEL_m1 + 1) * 2 * HW_XTAL_MHZ) / (0+1) = N MHz
	Chip_Clock_SetupPLL(SYSCTL_MAIN_PLL, HW_PLL_XTAL_MSEL_m1, 0);
	Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);

	// FCCO / (HW_PLLXTAL_CPU_CLK_DIV_m1+1) = CPU clock
	Chip_Clock_SetCPUClockDiv(HW_PLLXTAL_CPU_CLK_DIV_m1);
	while (!Chip_Clock_IsMainPLLLocked()) {} /* Wait for the PLL to Lock */

    // Setup FLASH access to N clocks
	Chip_SYSCTL_SetFLASHAccess(HW_FLASHTIM_CPU_WC);     
        
	Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_CONNECT);     
        
    SystemCoreClockUpdate();
    return 0;
}
/***************************************************************************
 @brief  Pins ReMapping
 @param  none, implicit: struct 'Hw_ProjPinsMuxing' (const setting for project)
 @retval none
 @note   use periph block 'IOCON', enable clock for them and mux pins,
         based on "Board_Init", "Board_SystemInit" (see board_sysinit.c, board.c (LpcOpen 2.10))
*****************************************************************************/
void
HW_PinsMuxing(void)
{
    // Periph GPIO clocking
	Chip_Clock_SetPCLKDiv( SYSCTL_PCLK_GPIOINT, SYSCTL_CLKDIV_2 );
	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);
    
    Chip_IOCON_Init(LPC_IOCON);
    //Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 26, (IOCON_FUNC2 | IOCON_DAC_EN ));
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 26, (  (0x1 << 16)	 | IOCON_FUNC2));
}

int main(void)
{

remcu_connect2OpenOCD("localhost", 6666);
remcu_resetRemoteUnit(ResetType::__HALT);
remcu_setVerboseLevel(LevelDebug::__INFO);

//HW_SetupIrcClocking();
    HW_SetupXtalClocking();

    sleep(2);

    HW_PinsMuxing();    // after it led_pin = 0V 


	Chip_GPIO_WriteDirBit(LPC_GPIO, 1, 18, true);


	/* Setup DAC pins for board and common CHIP code */
	Chip_DAC_Init(LPC_DAC);

	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_DAC, SYSCTL_CLKDIV_1);

	//Chip_DAC_SetDMATimeOut(LPC_DAC, 0x3FF);

	uint32_t dacClk = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_DAC);

	//Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_CNT_ENA | DAC_DMA_ENA);

	printf("dacClk %x \n", dacClk);

	//return 0;

	/* Enable count and DMA support */
	//Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_CNT_ENA );
		
		while(1){
		printf("!\n");
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 18, true);

		Chip_DAC_UpdateValue(LPC_DAC, 1000);
		/* Wait for DAC (DMA) interrupt request */
		//while (!(Chip_DAC_GetIntStatus(LPC_DAC))) {}

		sleep(1);

		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 18, false);

		Chip_DAC_UpdateValue(LPC_DAC, 0);
		/* Wait for DAC (DMA) interrupt request */
		//while (!(Chip_DAC_GetIntStatus(LPC_DAC))) {}

		sleep(1);
	}

		return 0;
}