#include "cpu/exec/template-start.h"

#define instr scas

make_helper(concat(scas_1_,SUFFIX)) {
	int d1,d2;
	if(DATA_BYTE==2)
	{
		d1 = swaddr_read(reg_w(R_DI),2,R_ES);
		d2 = reg_w(R_AX);
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
		d1 = swaddr_read(reg_l(R_EDI),4,R_ES);
		d2 = reg_l(R_EAX);
		if(DATA_BYTE==1)
		{
			d1 &= 0xff;
			d2 &= 0xff;		
		}
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
	int ans = d2-d1;
	cpu.ZF = !ans;
	cpu.SF = ans<0?1:0;
 	int n =ans;
	n&=0xff;
	int cnt =0;
	while(n) {
		n = n&(n-1);
		cnt++;
	}	
	cpu.PF = cnt%2==0? 1:0;
	if((ans>0&&d1>0&&d2<=0)||(ans<0&&d1<0&&d2>=0)) cpu.OF = 1;
	else cpu.OF = 0;
	cpu.CF = (unsigned int)d2<(unsigned int)d1;
	return 1;
}
#include "cpu/exec/template-end.h"
