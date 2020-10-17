#include "cpu/exec/template-start.h"


#define instr call

static void do_execute() {
	int d = op_src -> val;
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+5,R_SS);
	cpu.eip+=d;
	print_asm_template1();
}

make_helper(concat(call_rm_,SUFFIX)) {
	int len = concat(decode_rm_,SUFFIX)(eip+1);	
	int d = op_src -> val;
	//printf("%x\n",d);
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+len+1,R_SS);
	cpu.eip=d-len-1;
	print_asm_template1();
	return len+1;
}

make_instr_helper(i);


#include "cpu/exec/template-end.h"
