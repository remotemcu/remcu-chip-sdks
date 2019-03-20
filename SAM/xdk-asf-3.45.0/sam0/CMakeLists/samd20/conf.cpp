
#include "TargetFun.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20000000 + 32*1024); 			//SRAM
	add_to_adin_interval(0x40000000,  0x40000000 + 64*1024); //Peripheral Bridge A
	add_to_adin_interval(0x41000000,  0x41000000 + 64*1024); //Peripheral Bridge B
	add_to_adin_interval(0x42000000,  0x42000000 + 64*1024); //Peripheral Bridge C
}

} //namespace