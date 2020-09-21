#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat(stos_1_,SUFFIX)) {
	if(ops_decoded.is_operand_size_16)
	{
		swaddr_write(reg_w(R_DI),2,reg_w(R_AX));
		if(cpu.DF==0)
		{
			reg_w(R_DI)+=DATA_BYTE;
		}	
		else 
		{
			reg_w(R_DI)-=DATA_BYTE;	
		}
	}
	else 
	{
		swaddr_write(reg_l(R_EDI),4,reg_l(R_EAX));
		if(cpu.DF==0)
		{
			reg_l(R_EDI)+=DATA_BYTE;
		}	
		else 
		{
			reg_l(R_EDI)-=DATA_BYTE;	
		}
	}	
	print_asm_template2();	
	return 1;
}
#include "cpu/exec/template-end.h"
