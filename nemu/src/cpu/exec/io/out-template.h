#include "cpu/exec/template-start.h"

#define instr out
uint32_t pio_write(ioaddr_t, size_t,  uint32_t);

make_helper(concat(out_1_,SUFFIX)) {
	print_asm("out    %%al,(%%dx)");
	pio_write(reg_w(R_DX), DATA_BYTE, REG(R_EAX));
	return 1;
}



#include "cpu/exec/template-end.h"
