
#include "TargetFun.h"
#include "AddressInterval.h"

namespace remcu {

void setConfig(){
    clearConfig();
    add_to_mem_interval(0, 0x800); 			//SRAM
	add_to_adin_interval(0x800,  0x10000); //Perephi
}

} //namespace