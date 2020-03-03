
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0, 0x400); 			//SRAM max 0x800 Bytes
	add_to_adin_interval(0x5000,  0x5800); //Perephipheral registers
	add_to_adin_interval(0x8000,  0x10000); //Flash
}

uint32_t get_RAM_addr_for_test(){
    return 0;
}

} //namespace