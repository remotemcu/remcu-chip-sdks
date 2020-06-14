
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 8*1024); //SRAM

    add_to_adin_interval(0x40000000,  0x400263FF); //APB1 APB2 AHB
    add_to_adin_interval(0x50000000,  0x50001FFF); //APB3(D1)
}

uint32_t get_RAM_addr_for_test(){
    return 0x20000000;
}

} //namespace