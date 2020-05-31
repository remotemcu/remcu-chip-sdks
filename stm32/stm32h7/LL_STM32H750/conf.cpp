
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x30000000, 0x30000000 + 8*1024); //SRAM  192(112+16+64)
    add_to_adin_interval(0x40000000,  0x4000D3FF); //APB1(D2)
    add_to_adin_interval(0x40010000,  0x400177FF); //APB2(D2)
    add_to_adin_interval(0x40020000,  0x400223FF); //AHB1(D2) no USB , eth
    add_to_adin_interval(0x48020000,  0x480233FF); //AHB2(D2)
    add_to_adin_interval(0x50001000,  0x50003FFF); //APB3(D1)
    add_to_adin_interval(0x51000000,  0x52008FFF); //AHB3(D1)
    add_to_adin_interval(0x58000000,  0x580267FF); //AHB4(D3)
    //add_to_adin_interval(0x60000000,  0xE0000000); //AHB3 FSMC & FMC
}

uint32_t get_RAM_addr_for_test(){
    return 0x30000000;
}

} //namespace