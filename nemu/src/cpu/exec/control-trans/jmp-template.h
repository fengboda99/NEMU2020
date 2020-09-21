#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	DATA_TYPE_S d = op_src->val;
	//printf("%x\n",cpu.eip);
	if(op_src->type ==OP_TYPE_MEM||op_src->type==OP_TYPE_REG)
	{
		cpu.eip = d-concat(decode_rm_,SUFFIX)(cpu.eip+1)-1;	
	}
	else 	
	cpu.eip += d;
	//printf("%x\n %x\n",d,cpu.eip);
	print_asm_template1();	
}

make_instr_helper(i);
make_instr_helper(rm);
#include "cpu/exec/template-end.h"
