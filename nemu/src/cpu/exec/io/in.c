#include "cpu/exec/helper.h"
#include "device/port-io.h"


make_helper(inb) {
	print_asm("in    %%al,(%%dx)");
	reg_b(R_EAX) = (uint8_t)pio_read(reg_w(R_DX), 1);
	return 1;
	
}

make_helper(inl) {
	assert(ops_decoded.is_operand_size_16 == 0);
	print_asm("in    %%eax,(%%dx)");
	cpu.eax = pio_read(reg_w(R_DX), 4);
	return 1;
	
}

