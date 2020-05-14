
#include "target.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 8*1024); 		//SRAM
	add_to_adin_interval(0x40000000,  0x4000A000); //APB1
    add_to_adin_interval(0x40010000,  0x40018000); //APB2
    add_to_adin_interval(0x40020000,  0x400243FF); //AHB1
    add_to_adin_interval(0x48000000,  0x48001800); //AHB2
    add_to_adin_interval(0x50000000,  0x500007FF); //AHB3

}

uint32_t get_RAM_addr_for_test(){
    return 0x20000000;
}

} //namespace