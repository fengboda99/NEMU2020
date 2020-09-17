#include "cpu/exec/template-start.h"

#define instr leave

make_helper(concat(leave_1_,SUFFIX)) {
	REG(R_ESP) = REG(R_EBP);
	REG(R_EBP) = MEM_R(REG(R_ESP));
	REG(R_ESP)+=4;
	return 1;
}


#include "cpu/exec/template-end.h"
