#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_1_,SUFFIX)) {
	cpu.eip = MEM_R(reg_l(R_ESP));
	reg_l(R_ESP) +=4;
	return 1;
}


#include "cpu/exec/template-end.h"
