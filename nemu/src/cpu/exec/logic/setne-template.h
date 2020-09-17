#include "cpu/exec/template-start.h"

#define instr setne

static void do_execute() {
	int f;
	if(cpu.ZF==0) f=1;
	else f=0;
	OPERAND_W(op_src,f); 
	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
