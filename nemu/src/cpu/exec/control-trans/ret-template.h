#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_1_,SUFFIX)) {
	cpu.eip = MEM_R(reg_l(R_ESP));
	reg_l(R_ESP) +=4;
	return 0;
}

static void do_execute() {
	DATA_TYPE_S d = op_src->val;
	//printf("%x\n",cpu.eip);
	cpu.eip = MEM_R(reg_l(R_ESP));
	if(DATA_BYTE==2) cpu.eip = cpu.eip&0xffff;
	reg_l(R_ESP) +=DATA_BYTE;
	reg_l(R_ESP) +=d;
	print_asm_template1();	
}

make_instr_helper(i);

#include "cpu/exec/template-end.h"
