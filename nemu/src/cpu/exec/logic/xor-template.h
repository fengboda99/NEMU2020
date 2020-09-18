#include "cpu/exec/template-start.h"

#define instr xor

static void do_execute () {
	DATA_TYPE result = op_dest->val ^ op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	cpu.CF=0;
	cpu.OF=0;
	cpu.ZF=!result;
	int ccc = result;
	cpu.SF= ccc<0?1:0;
	int cnt=0;
	while(ccc)
	{
		ccc = ccc&(ccc-1);
		cnt++;
	}
	cpu.PF = cnt%2==0? 1:0;
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
