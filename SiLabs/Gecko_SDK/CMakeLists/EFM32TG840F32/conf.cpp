
#include "TargetFun.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0x20000000, 0x20001000); 			//SRAM
	add_to_adin_interval(0x40000000,  0x41000000); //Perephi
	//add_to_adin_interval(0x42000000,  0x44000000); //Perephi Bit
}

} //namespace