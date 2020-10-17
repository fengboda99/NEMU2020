#include "cpu/exec/template-start.h"

#define instr movs

make_helper(concat(movs_1_,SUFFIX)) {
	if(DATA_BYTE==2)
	{
		uint16_t ok= swaddr_read(reg_l(R_SI),2,R_DS);
		swaddr_write(reg_w(R_DI),2,ok,R_ES);
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
		uint32_t ok=swaddr_read(reg_l(R_ESI),4,R_DS);
		swaddr_write(reg_l(R_EDI),4,ok,R_ES);
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
