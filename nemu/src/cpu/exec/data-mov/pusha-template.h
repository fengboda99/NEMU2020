#include "cpu/exec/template-start.h"

#define instr pusha

make_helper(concat(pusha_1_,SUFFIX)) {
	if(DATA_BYTE==2) {	
		DATA_TYPE tmp = REG(R_SP);
		int i;
		for(i=R_AX;i<=R_DI;i++) {
			if(i==R_SP) {
				REG(R_SP)-=2;
				MEM_W(REG(R_SP),tmp,R_SS);			
			}		
			else {
				REG(R_SP)-=2;
				MEM_W(REG(R_SP),REG(i),R_SS);		
			}
		}
	}
	else {
		DATA_TYPE tmp = REG(R_ESP);
		int i;
		for(i=R_EAX;i<=R_EDI;i++) {
			if(i==R_ESP) {
				REG(R_ESP)-=4;
				MEM_W(REG(R_SP),tmp,R_SS);			
			}		
			else {
				REG(R_ESP)-=4;
				MEM_W(REG(R_ESP),REG(i),R_SS);		
			}
		}
	}
	return 1;
}




#include "cpu/exec/template-end.h"
