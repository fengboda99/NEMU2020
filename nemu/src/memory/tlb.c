#include "memory/tlb.h"

void tlb_init() {
	int i;
	for(i=0;i<TLB_SIZE;i++) {
		tlb[i].valid = false;	
	}
}
uint32_t tlb_read(uint32_t tag) {
	int i;
	for(i=0;i<TLB_SIZE;i++) {
		if(tlb[i].valid&&tlb[i].tag==tag) return tlb[i].page;	
	}
	return -1;
}

void tlb_write(uint32_t tag,uint32_t page) {
	int i;
	bool v = false;
	for(i=0;i<TLB_SIZE;i++) {
		if(!tlb[i].valid) {
			v = true;
			break;		
		}	
	}
	if(!v) i = rand()%TLB_SIZE;
	tlb[i].valid = true;
	tlb[i].tag = tag;
	tlb[i].page = page;
}
