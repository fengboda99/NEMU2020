#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	cpu.CF = 0;
	cpu.OF = 0;
	int ans = op_dest->val & op_src->val;
	if(ans<0) cpu.SF = 1;
	else cpu.SF = 0;
	if(ans==0) cpu.ZF = 1;
	else cpu.ZF = 0;
	//printf("%d\n",cpu.ZF);
	int cnt = 0;
	ans&=0xff;
	while(ans) {
		ans = ans&(ans-1);
		cnt++;
	}
	if(cnt%2) {
		cpu.PF = 0;
	}
	else cpu.PF = 1;
	print_asm_template2();
}

make_instr_helper(r2rm);
make_instr_helper(i2rm);
make_instr_helper(i2a);
#include "cpu/exec/template-end.h"
