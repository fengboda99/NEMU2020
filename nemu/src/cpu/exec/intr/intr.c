#include <setjmp.h>
#include "nemu.h"
extern jmp_buf jbuf;

void raise_intr(uint8_t NO) {

	/*TODO: Trigger an interrupt
	 */
	printf("\n%d\n",NO);
	/* Jump back to cpu_exec() */
	longjmp(jbuf,1);
}

