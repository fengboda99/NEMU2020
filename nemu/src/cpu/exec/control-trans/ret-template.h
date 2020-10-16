#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_1_,SUFFIX)) {
	current_sreg = R_SS;
	cpu.eip = MEM_R(reg_l(R_ESP));
	reg_l(R_ESP) +=4;
	return 0;
}
make_helper(concat(ret_i_,SUFFIX)) {
	DATA_TYPE_S d = instr_fetch(cpu.eip+1,2);
	//printf("%x\n",cpu.eip);
	current_sreg = R_SS;
	cpu.eip = MEM_R(reg_l(R_ESP));
	if(DATA_BYTE==2) cpu.eip = cpu.eip&0xffff;
	reg_l(R_ESP) +=DATA_BYTE;
	reg_l(R_ESP) +=d;
	print_asm_template1();	
	return 0;
}

#include "cpu/exec/template-end.h"
