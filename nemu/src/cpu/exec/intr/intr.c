#include <setjmp.h>
#include "nemu.h"
extern jmp_buf jbuf;
void push(int val) {
	reg_l(R_ESP)-=4;
	swaddr_write(reg_l(R_ESP),4,val,R_SS);
}
void raise_intr(uint8_t NO) {
	/*TODO: Trigger an interrupt
	 */
	Assert(NO*8<=cpu.idtr.seg_limit,"NUMBER EXCEEDED");
	GATE_descriptor gate;
	lnaddr_t addr = cpu.idtr.base_addr+NO*8;
	gate.first=lnaddr_read(addr,4);
	gate.second=lnaddr_read(addr+4,4);
	
	push(cpu.eflags);
	if(cpu.cr0.protect_enable==0) {
		cpu.IF=0;
		cpu.TF=0;	
	}
	push(cpu.cs.selector);
	push(cpu.eip);
	cpu.cs.selector = gate.selector;
	Assert(((cpu.cs.selector>>3)<<3) <= cpu.gdtr.seg_limit,"NUMBER EXCEEDED");
	seg_do(R_CS);
	//printf("1\n");
	cpu.eip=cpu.cs.base_addr+gate.offset1+(gate.offset2<<16);
	//printf("1\n");
	/* Jump back to cpu_exec() */
	longjmp(jbuf,1);
}

