
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20020000, 0x20020000 + 8*1024); //SRAM  192(112+16+64)
    add_to_adin_interval(0x40000000,  0x40007FFF); //APB1
    add_to_adin_interval(0x40010000,  0x40016BFF); //APB2
    add_to_adin_interval(0x40020000,  0x40080000); //AHB1
    add_to_adin_interval(0x50000000,  0x50060C00); //AHB2
    //add_to_adin_interval(0x60000000,  0xE0000000); //AHB3 FSMC & FMC
}

uint32_t get_RAM_addr_for_test(){
    return 0x20020000;
}

} //namespace