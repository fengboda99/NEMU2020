#include "cpu/exec/template-start.h"

#define instr jg

static void do_execute() {
	DATA_TYPE_S d = op_src->val;
	//printf("%x\n",cpu.eip);
	if(cpu.ZF==0&&cpu.OF==cpu.SF) cpu.eip += d;
	//printf("%x\n %x\n",d,cpu.eip);
	print_asm_template1();	
}

make_instr_helper(i);

#include "cpu/exec/template-end.h"
