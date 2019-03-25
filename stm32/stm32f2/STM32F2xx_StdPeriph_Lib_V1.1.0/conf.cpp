
#include "TargetFun.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 0x1BFFF); 			//SRAM
	add_to_adin_interval(0x40000000,  0x40000000 + 0x267FF); //Peripheral 
	add_to_adin_interval(0xE0042000,  0xE0042000 + 0x267FF); //DBGMCU_BASE
}

} //namespace