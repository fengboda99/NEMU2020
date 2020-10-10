#include "common.h"
#include "burst.h"
#include "memory/cache.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	/*int id = cache_read(addr);
	uint32_t offset = addr&(CACHE_BLOCK_SIZE-1);
	uint8_t tmp[2*BURST_LEN];
	if(offset+len>CACHE_BLOCK_SIZE) {
		int id2 = cache_read(addr+CACHE_BLOCK_SIZE-offset);	
		memcpy(tmp,cache[id].data+offset,CACHE_BLOCK_SIZE-offset);
		memcpy(tmp+CACHE_BLOCK_SIZE-offset,cache[id2].data,len-(CACHE_BLOCK_SIZE-offset));
	}
	else {
		memcpy(tmp,cache[id].data+offset,len);
	}
	int zero=0;
	uint32_t ans = unalign_rw(tmp+zero,4)&(~0u >> ((4 - len) << 3));
	return ans;*/
	return dram_read(addr,len)&(~0u >> ((4 - len) << 3));
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	//cache_write(addr, len, data);
	dram_write(addr,len,data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}

