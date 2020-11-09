#include "cpu/exec/helper.h"
#include "nemu.h"
int pop1() {
	uint32_t tmp = swaddr_read(reg_l(R_ESP),4,R_SS);
	reg_l(R_ESP)+=4;
	return tmp;
}
make_helper(iret) {
	if(cpu.cr0.protect_enable==0) {
		cpu.eip=pop1();
		cpu.cs.selector = pop1();
		cpu.eflags = pop1();	
	}
	else {
		//printf("1\n");
		cpu.eip=pop1();
		cpu.cs.selector = pop1();
		cpu.eflags = pop1();
		//printf("13\n");
		seg_do(R_CS);
	}	
	
	return 0;
	
}
