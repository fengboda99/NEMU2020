#include "cpu/exec/template-start.h"


#define instr call

static void do_execute() {
	int d = op_src -> val;
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+5);
	cpu.eip+=d;
	print_asm_template1();
}

make_helper(concat(call_rm_,SUFFIX)) {
	int d = op_src -> val;
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+5);
	cpu.eip=d-5;
	printf("%x\n",d);
	print_asm_template1();
	return 5;
}

make_instr_helper(i);


#include "cpu/exec/template-end.h"
