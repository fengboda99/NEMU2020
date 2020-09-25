#include "cpu/exec/template-start.h"

#define instr jno

static void do_execute() {
	DATA_TYPE_S d = op_src->val;
	//printf("%x\n",cpu.eip);
	if(cpu.OF==0) cpu.eip += d;
	//printf("%x\n %x\n",d,cpu.eip);
	print_asm_template1();	
}

make_instr_helper(i);

#include "cpu/exec/template-end.h"
