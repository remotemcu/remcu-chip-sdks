
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 8*1024); 	//SRAM max 10Кб
	add_to_adin_interval(0x40000000,  0x40000000 + 0x233FF); //Peripheral 
	//add_to_adin_interval(0xE0042000,  0xE0042000 + 0xB); //DBGMCU_BASE
}

uint32_t get_RAM_addr_for_test(){
    return 0x20000000;
}

} //namespace