#include "cpu/exec/template-start.h"

#define instr movs

make_helper(concat(movs_1_,SUFFIX)) {
	if(DATA_BYTE==2)
	{
		current_sreg = R_DS;
		uint16_t ok= swaddr_read(reg_l(R_SI),2);
		current_sreg = R_ES;
		swaddr_write(reg_w(R_DI),2,ok);
		if(cpu.DF==0)
		{
			reg_w(R_DI)+=DATA_BYTE;
			reg_w(R_SI)+=DATA_BYTE;
		}	
		else 
		{
			reg_w(R_DI)-=DATA_BYTE;
			reg_w(R_SI)-=DATA_BYTE;	
		}
	}
	else 
	{
		current_sreg = R_DS;
		uint32_t ok=swaddr_read(reg_l(R_ESI),4);
		current_sreg = R_ES;
		swaddr_write(reg_l(R_EDI),4,ok);
		if(cpu.DF==0)
		{
			reg_l(R_EDI)+=DATA_BYTE;
			reg_l(R_ESI)+=DATA_BYTE;
		}	
		else 
		{
			reg_l(R_EDI)-=DATA_BYTE;
			reg_l(R_ESI)-=DATA_BYTE;	
		}	
	}
	print_asm_template2();	
	return 1;
}
#include "cpu/exec/template-end.h"
