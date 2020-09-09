#include "cpu/exec/template-start.h"

#define instr je

static void do_execute() {
	int d = op_src->val;
	cpu.eip += d;
	print_asm_template1();	
}

make_instr_helper(r);

#include "cpu/exec/template-end.h"
