#include "cpu/exec/template-start.h"

#define instr lods

make_helper(concat(lods_1_,SUFFIX)) {
	if(DATA_BYTE==2)
	{
		swaddr_write(reg_w(R_AX),2,swaddr_read(reg_w(R_SI),4));
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
		if(DATA_BYTE==4)
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
		else
		{
			printf("%x %x",swaddr_read(reg_b(R_AL),1),swaddr_read(reg_b(R_DH),1));
			swaddr_write(reg_b(R_AL),1,swaddr_read(reg_b(R_DH),1));
			printf("%x %x",swaddr_read(reg_b(R_AL),1),swaddr_read(reg_b(R_DH),1));
			if(cpu.DF==0)
			{
				reg_l(R_DH)+=DATA_BYTE;
			}	
			else 
			{
				reg_l(R_DH)-=DATA_BYTE;	
			}
		}
	}
	print_asm_template2();	
	return 1;
}
#include "cpu/exec/template-end.h"
