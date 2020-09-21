#include "cpu/exec/template-start.h"

#define instr lods

make_helper(concat(lods_1_,SUFFIX)) {
	if(DATA_BYTE==2)
	{
		swaddr_write(reg_l(R_EAX),2,swaddr_read(reg_l(R_ESI),2));
		if(cpu.DF==0)
		{
			reg_l(R_ESI)+=DATA_BYTE;
		}	
		else 
		{
			reg_l(R_ESI)-=DATA_BYTE;	
		}
	}
	else 
	{
		swaddr_write(reg_l(R_EAX),4,swaddr_read(reg_l(R_ESI),4));
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
