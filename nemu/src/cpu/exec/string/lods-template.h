#include "cpu/exec/template-start.h"

#define instr lods

make_helper(concat(lods_1_,SUFFIX)) {
	if(DATA_BYTE==2)
	{
		reg_w(R_AX)=swaddr_read(reg_w(R_SI),2,R_DS);
		if(cpu.DF==0)
		{
			reg_w(R_SI)+=DATA_BYTE;
		}	
		else 
		{
			reg_w(R_SI)-=DATA_BYTE;	
		}
	}
	else 
	{
		REG(R_EAX) = swaddr_read(reg_l(R_ESI),DATA_BYTE,R_DS);
		if(cpu.DF==0)
		{
			reg_l(R_ESI)+=DATA_BYTE;
		}	
		else 
		{
			reg_l(R_ESI)-=DATA_BYTE;	
		}
	}	
	print_asm_template2();	
	return 1;
}
#include "cpu/exec/template-end.h"
