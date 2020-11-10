#include "cpu/exec/helper.h"
#include "device/port-io.h"


make_helper(outb) {
	print_asm("out    %%al,(%%dx)");
	pio_write(reg_w(R_DX), 1, (uint32_t) reg_b(R_EAX));
	return 1;
	
}

make_helper(outl) {
	assert(ops_decoded.is_operand_size_16 == 0);
	print_asm("out    %%eax,(%%dx)");
	pio_write(reg_w(R_DX), 4, cpu.eax);
	return 1;
	
}
