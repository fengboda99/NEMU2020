#include "cpu/exec/template-start.h"

#define instr cld

make_helper(cld) {
	cpu.DF=0; 
	print_asm_template1();
	return 1;
}

#include "cpu/exec/template-end.h"
