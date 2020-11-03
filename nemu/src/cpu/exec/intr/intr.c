#include <setjmp.h>
extern jmp_buf jbuf;

void raise_intr(uint8_t) {

	/*TODO: Trigger an interrupt
	 */
	
	/* Jump back to cpu_exec() */
	longjmp(jbuf,1);
}
