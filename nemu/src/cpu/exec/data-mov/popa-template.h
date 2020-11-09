#include "cpu/exec/template-start.h"

#define instr popa

make_helper(concat(popa_1_,SUFFIX)) {
	int i;
	for(i=R_DI;i>=R_AX;i--) {
		if(i!=4) {
			REG(i) = MEM_R(REG(R_SP),R_SS);	
		}	
		REG(R_SP)+=DATA_BYTE;	
	}
	return 1;
}


#include "cpu/exec/template-end.h"
