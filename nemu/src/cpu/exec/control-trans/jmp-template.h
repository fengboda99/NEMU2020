#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	DATA_TYPE_S d = op_src->val;
	//printf("%x\n",cpu.eip);
	if(op_src->type ==OP_TYPE_MEM||op_src->type==OP_TYPE_REG)
	{
		cpu.eip = d-concat(decode_rm_,SUFFIX)(cpu.eip+1)-1;	
	}
	else 	
	cpu.eip += d;
	//printf("%x\n %x\n",d,cpu.eip);
	print_asm_template1();	
}

make_instr_helper(i);
make_instr_helper(rm);

#if DATA_BYTE == 4
make_helper(ljmp) {
	extern SEG_descriptor *seg_des;
	SEG_descriptor seg;
	seg_des = &seg;
	uint32_t op_first = instr_fetch(eip+1,4);
	uint16_t op_second = instr_fetch(eip+5,2);
	cpu.eip = op_first;
	cpu.cs.selector = op_second;
	//printf("1\n");
	Assert(((cpu.cs.selector>>3)<<3) <= cpu.gdtr.seg_limit, "OUT LIMIT %d, %d", ((cpu.cs.selector>>3)<<3), cpu.gdtr.seg_limit);
	//printf("2\n");
	seg_des->first = instr_fetch(cpu.gdtr.base_addr + ((cpu.cs.selector>>3)<<3), 4);
	//printf("3\n");
	seg_des->second = instr_fetch(cpu.gdtr.base_addr + ((cpu.cs.selector>>3)<<3)+4, 4);
	Assert(seg_des->p == 1, "segment ERROR");
	//printf("3\n");
	cpu.cs.base_addr1 = seg_des->base_addr1;
	cpu.cs.base_addr2 = seg_des->base_addr2;
	cpu.cs.base_addr3 = seg_des->base_addr3;
	cpu.cs.seg_limit1 = seg_des->seg_limit1;
	cpu.cs.seg_limit2 = seg_des->seg_limit2;
	cpu.cs.seg_limit3 = 0xfff;
	print_asm("ljmp %x,%x", op_second, op_first);
	return 0;
}
#endif
#include "cpu/exec/template-end.h"
