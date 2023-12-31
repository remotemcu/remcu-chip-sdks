
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 32*1024); 			//SRAM
	add_to_adin_interval(0x40000000,  0x60000000); //Peripheral 
}

uint32_t get_RAM_addr_for_test(){
    return 0x20000000;
}

} //namespace