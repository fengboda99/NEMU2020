#ifndef __TLB_H__
#define __TLB_H__


#include "common.h"
#include <stdlib.h>

#define TLB_SIZE 64

typedef struct {
	bool valid;
	uint32_t tag;
	uint32_t page;
}TLB;


TLB tlb[TLB_SIZE];

void tlb_init();
void tlb_write(uint32_t tag,uint32_t page);
uint32_t tlb_read(uint32_t tag);

#endif
