#include "cpu/exec/template-start.h"


#define instr call

static void do_execute() {
	int d = op_src -> val;
	reg_l(R_ESP) -= 4;
	swaddr_write(reg_l(R_ESP),4,cpu.eip+5);
	cpu.eip+=d;
	print_asm_template1();
}

make_instr_helper(i);
make_instr_helper(rm);
#include "cpu/exec/template-end.h"
