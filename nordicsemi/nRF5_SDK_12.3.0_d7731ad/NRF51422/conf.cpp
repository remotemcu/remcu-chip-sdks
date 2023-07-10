
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 8*1024); //SRAM  8k
    add_to_adin_interval(0x40000000,  0x40008000); //APB peripherals
    add_to_adin_interval(0x50000000,  0x50060000); //AHB peripherals
    add_to_adin_interval(0xF0000FE0,  0xF0000FE0 + 4); //AHB peripherals
}

uint32_t get_RAM_addr_for_test(){
    return 0x20000000;
}

} //namespace