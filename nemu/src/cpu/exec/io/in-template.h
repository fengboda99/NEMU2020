#include "cpu/exec/template-start.h"

#define instr in
uint32_t pio_read(ioaddr_t, size_t);

make_helper(concat(in_1_,SUFFIX)) {
	print_asm("in    %%al,(%%dx)");
	REG(R_EAX) = pio_read(reg_w(R_DX), DATA_BYTE);
	return 1;
}




#include "cpu/exec/template-end.h"
