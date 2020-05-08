
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 8*1024); 	//SRAM max 48- 64к
	add_to_adin_interval(0x40000000,  0x40000000 + 0x267FF); //Peripheral  0x4002 33FF CRC
	//add_to_adin_interval(0xE0042000,  0xE0042000 + 0xB); //DBGMCU_BASE RM0008 26.17 - 672 page
}

uint32_t get_RAM_addr_for_test(){
    return 0x20000000;
}

} //namespace