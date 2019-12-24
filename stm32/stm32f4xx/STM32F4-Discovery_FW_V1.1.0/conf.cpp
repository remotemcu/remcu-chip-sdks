
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + (112)*1024); 			//SRAM
    add_to_adin_interval(0x40000000,  0x40008000); //APB1
    add_to_adin_interval(0x40010000,  0x40016C00); //APB2
    add_to_adin_interval(0x40020000,  0x40080000); //AHB1
    add_to_adin_interval(0x50000000,  0x50060C00); //AHB2
    add_to_adin_interval(0xA0000000,  0xA0001000); //AHB3
}

uint32_t get_RAM_addr_for_test(){
    return 0x20000000;
}

} //namespace