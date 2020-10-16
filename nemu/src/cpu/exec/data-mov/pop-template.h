#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute() {
	current_sreg = R_SS;
	OPERAND_W(op_src,MEM_R(reg_l(R_ESP)));
	MEM_W(reg_l(R_ESP),0);
	reg_l(R_ESP)+=DATA_BYTE;
}

make_instr_helper(r);

#include "cpu/exec/template-end.h"
