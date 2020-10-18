#include "cpu/exec/template-start.h"

#define instr std

make_helper(std) {
	cpu.DF=1; 
	print_asm_template1();
	return 1;
}

#include "cpu/exec/template-end.h"
