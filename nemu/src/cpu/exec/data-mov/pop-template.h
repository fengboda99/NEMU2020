#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute() {
	OPRERAND(op_src,MEM_R(REG(R_ESP)));
	MEM_W(REG(R_ESP),0);
	reg_l(R_ESP)+=4;
}

make_instr_helper(r);

#include "cpu/exec/template-end.h"
