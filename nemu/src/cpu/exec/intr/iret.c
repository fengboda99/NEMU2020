#include "cpu/exec/helper.h"
#include "nemu.h"
int pop() {
	uint32_t tmp = swaddr_read(reg_l(R_ESP),4,R_SS);
	reg_l(R_ESP)+=4;
	//printf("%x\n",tmp);
	return tmp;
}
make_helper(iret) {
	if(cpu.cr0.protect_enable==0) {
		cpu.eip=pop();
		cpu.cs.selector = pop();
		cpu.eflags = pop();	
	}
	else {
		//printf("1\n");
		cpu.eip=pop();
		cpu.cs.selector = pop();
		cpu.eflags = pop();
		//printf("13\n");
		seg_do(R_CS);
	}	
	
	return 0;
	
}
