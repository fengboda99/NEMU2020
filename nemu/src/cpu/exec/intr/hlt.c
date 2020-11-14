#include "cpu/exec/helper.h"
#include "nemu.h"

make_helper(hlt) {
	extern void device_update();
	while(cpu.INTR==0) {
		device_update();	
	}
	//print_asm("hlt");
	return 1;
}
