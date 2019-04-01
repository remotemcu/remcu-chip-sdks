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

    #define HW_XTAL_MHZ                     (12)
    #define HW_XTAL_HZ                      (12*1000*1000)  ///< used for 'OscRateIn', which used for LpcOpen lib
    
    #define HW_WDT_PERIOD_MS                (5000)
    
/*--- Pins -------------------------------------*/
    #define PINMUX_Port0                0
    #define PINMUX_Port1                1
    #define PINMUX_Port2                2
// LED0  (P1.18)
    #define LED0_PINn        18                                 ///< Led0, Pins Muxing::Pin Number, for 'PINMUX_GRP_T'
    #define LED0_PORTn       1                                  ///< Led0, Pins Muxing::Port Number, for 'PINMUX_GRP_T'
    #define LED0_CFG        (IOCON_MODE_INACT | IOCON_FUNC0)    ///< Led0, Pins Muxing::Pull-Up or not, Pin Func number, for 'PINMUX_GRP_T'
    
// UART0 RX(P0.3)  TX(P0.2)   
    #define UART0_PORTn     0                                   ///< Uart0, Pins Muxing::Port Number, for 'PINMUX_GRP_T'
    #define UART0_RX_PINn   3                                   ///< Uart0, Pins Muxing::Pin Number, for 'PINMUX_GRP_T'
    #define UART0_RX_CFG    (IOCON_MODE_INACT | IOCON_FUNC1)    ///< Uart0, Pins Muxing::Pull-Up or not + Pin Func number, for 'PINMUX_GRP_T'
    #define UART0_TX_PINn   2                                   ///< Uart0, Pins Muxing::Pin Number, for 'PINMUX_GRP_T'
    #define UART0_TX_CFG    (IOCON_MODE_INACT | IOCON_FUNC1)    ///< Uart0, Pins Muxing::Pull-Up or not + Pin Func number, for 'PINMUX_GRP_T'  
    

/* Pin muxing configuration */
    STATIC const PINMUX_GRP_T       
    Hw_ProjPinsMuxing[] = 
    {
        { LED0_PORTn,  LED0_PINn,   LED0_CFG }
    };
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
    
    Chip_IOCON_Init(LPC_IOCON);
    Chip_IOCON_SetPinMuxing(LPC_IOCON, Hw_ProjPinsMuxing, sizeof(Hw_ProjPinsMuxing) / sizeof(PINMUX_GRP_T));
}

    /** @brief Uart Errors, shown in Line Status Reg (LSR) */
    #define UART_LS_ERRORs      (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI) ///< OE - is set when UARTn RSR has a new character assembled and the UARTn RBR FIFO is full.
                                                                                        ///< FE - when the stop bit of a received character is a logic 0.
                                                                                        ///< BI - When RXDn is held in the spacing state (all zeroes) for one full character transmission (start, data, parity, stop).
    #define UART_ADP_RX_SIZE    128     ///< byte size of receive buffer, must be row of 2
    #define UART_ADP_TX_SIZE    128     ///< byte size of tx buffer, must be row of 2
    
    #define UART_ADP_TX_FIFO_MAXLOAD    14  ///< load some bytes less, than fifo_size = 16 bytes
    /*--- Defines ----------------------------------*/

    #define UART_CFG_8B_1SP          (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT)   ///< uart configuration set: word len + number of stop_bits

    #define UART_ADP                  LPC_UART0 
    #define UART_ADP_PCLK_DIV        (SYSCTL_CLKDIV_1) ///< PCLK divider for UART clock, see enum 'CHIP_SYSCTL_CLKDIV_T'       
    #define UART_ADP_IRQn             UART0_IRQn
    #define UART_ADP_IRQ_PRIOR        1
    
    #define UartADP_IRQHandler        UART0_IRQHandler  ///< user pseudonym for irq_handler
    
/*--- HW Fast Macroses --------------------------*/

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

	uint32_t              baudrate = 115200;
	uint32_t settings =  UART_CFG_8B_1SP;

Chip_UART_DeInit(UART_ADP); // On reset, UART0 is enabled, and UART2/3 are disabled,
                                // so disbale tx, disable clock
    
	Chip_Clock_SetPCLKDiv( SYSCTL_PCLK_UART0, UART_ADP_PCLK_DIV );  // Periph UART clocking, divider for PCLK
    
    Chip_UART_Init(UART_ADP);   // enable clock, enable-reset fifos, disable tx, irqs, some ctrl regs to default state
    
  //Chip_UART_SetBaudFDR(pUART, baudrate);
	Chip_UART_SetBaud(UART_ADP, baudrate);
    
	Chip_UART_ConfigData(UART_ADP, settings); // reg 'LCR'
    //Chip_UART_SetupFIFOS(UART_ADP, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0)); //?
    Chip_UART_TXEnable(UART_ADP);
    
    //Chip_UART_SetupFIFOS(UART_ADP, (UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV3));
    


		
		while(1){
		printf("!\n");
		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 18, true);

		Chip_UART_SendByte (UART_ADP, 0xAA);



		sleep(1);

		uint8_t ret = Chip_UART_ReadByte (UART_ADP);

		printf("ret %x\n", ret);

		Chip_GPIO_WritePortBit(LPC_GPIO, 1, 18, false);

		sleep(1);
	}

		return 0;
}