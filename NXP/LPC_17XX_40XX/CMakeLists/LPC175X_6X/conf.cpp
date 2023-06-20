
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x2007C000, 0x20080000); 			//16 kB AHB SRAM0
	add_to_adin_interval(0x2009C000,  0x200A0000); //GPIO
	add_to_adin_interval(0x40000000,  0x40100000); //APB0 APB1 peripherals
	//add_to_adin_interval(0x42000000,  0x44000000); //Perephi bitband
}

uint32_t get_RAM_addr_for_test(){
    return 0x2007C000;
}


} //namespace