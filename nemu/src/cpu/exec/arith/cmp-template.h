#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute() {
	//printf("1bsbsbasasdoasjoidjia\n");
	int d1 = op_src->val;
	int d2 = op_dest->val;
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
	cpu.CF = op_dest->val<op_src->val;	
}
#if DATA_BYTE ==2 || DATA_BYTE == 4
make_instr_helper(si2rm);
#endif
make_instr_helper(i2rm);
make_instr_helper(rm2r);
make_instr_helper(r2rm);
make_instr_helper(i2a);
#include "cpu/exec/template-end.h"
