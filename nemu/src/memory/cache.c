#include "common.h"
#include "burst.h"
#include "memory/cache.h"
#include <stdlib.h>

void ddr3read(hwaddr_t addr, void *data);
void ddr3write(hwaddr_t addr, void *data, uint8_t *mask);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

void cache_init() {
	int i;
	for(i=0;i<CACHE_WAY_SIZE*CACHE_SET_SIZE;i++) {
		cache[i].valid = false;	
	}
	for(i=0;i<SECONDCACHE_WAY_SIZE*SECONDCACHE_SET_SIZE;i++) {
		secondcache[i].valid = false;	
	}
}

//return the cache id
uint32_t cache_read(hwaddr_t addr) {
	uint32_t tag = addr>>(CACHE_SET_SIZE_B+CACHE_BLOCK_SIZE_B);
	uint32_t set = addr>>(CACHE_BLOCK_SIZE_B);
	set &=(CACHE_SET_SIZE-1);
	//uint32_t block = (addr>>CACHE_BLOCK_SIZE_B)<<CACHE_BLOCK_SIZE_B;

	int i;
	for(i=set*CACHE_WAY_SIZE;i<(set+1)*CACHE_WAY_SIZE;i++) {
		if(cache[i].valid&&cache[i].tag==tag) {
			return i;
		}
	}
	// hit miss
	int j = secondcache_read(addr);
	srand(i);
	i = CACHE_WAY_SIZE *set + rand()%CACHE_WAY_SIZE;
	memcpy(cache[i].data,secondcache[j].data,CACHE_BLOCK_SIZE);
	
	/*	
	srand(i);
	i = CACHE_WAY_SIZE *set + rand()%CACHE_WAY_SIZE;
	int j;
	for(j=0;j<CACHE_BLOCK_SIZE/BURST_LEN;j++) {
		ddr3read(block+j*BURST_LEN,cache[i].data+j*BURST_LEN);	
	}
	*/
	cache[i].valid = true;
	cache[i].tag = tag;
	return i;
}

uint32_t secondcache_read(hwaddr_t addr) {
	uint32_t tag = addr>>(SECONDCACHE_SET_SIZE_B+SECONDCACHE_BLOCK_SIZE_B);
	uint32_t set = addr>>(SECONDCACHE_BLOCK_SIZE_B);
	set &=(SECONDCACHE_SET_SIZE-1);
	uint32_t block = (addr>>SECONDCACHE_BLOCK_SIZE_B)<<SECONDCACHE_BLOCK_SIZE_B;

	int i;
	for(i=set*SECONDCACHE_WAY_SIZE;i<(set+1)*SECONDCACHE_WAY_SIZE;i++) {
		if(secondcache[i].valid&&secondcache[i].tag==tag) {
			return i;
		}
	}
	// hit miss	
	srand(i);
	i = SECONDCACHE_WAY_SIZE *set + rand()%SECONDCACHE_WAY_SIZE;
	if(secondcache[i].dirty&&secondcache[i].valid) {
		uint32_t addr2 = (secondcache[i].tag<<(SECONDCACHE_SET_SIZE_B+SECONDCACHE_BLOCK_SIZE_B)) | (set<<(SECONDCACHE_BLOCK_SIZE_B));
		uint8_t mask[2*BURST_LEN];
		memset(mask,1,2*BURST_LEN);
		int j;
		for(j=0;j<SECONDCACHE_BLOCK_SIZE/BURST_LEN;j++) {
			ddr3write(addr2+j*BURST_LEN,secondcache[i].data+j*BURST_LEN,mask);		
		}
	}
	int j;
	for(j=0;j<SECONDCACHE_BLOCK_SIZE/BURST_LEN;j++) {
		ddr3read(block+j*BURST_LEN,secondcache[i].data+j*BURST_LEN);	
	}
	
	secondcache[i].valid = true;
	secondcache[i].tag = tag;
	secondcache[i].dirty = false;
	
	return i;
}

void cache_write(hwaddr_t addr,size_t len,uint32_t data) {
	uint32_t tag = addr>>(CACHE_SET_SIZE_B+CACHE_BLOCK_SIZE_B);
	uint32_t set = addr>>(CACHE_BLOCK_SIZE_B);
	set &=(CACHE_SET_SIZE-1);
	uint32_t offset = addr&(CACHE_BLOCK_SIZE-1);
	
	int i;
	for(i=set*CACHE_WAY_SIZE;i<(set+1)*CACHE_WAY_SIZE;i++) {
		if(cache[i].valid&&cache[i].tag==tag) {
			if(offset+len>CACHE_BLOCK_SIZE) {
				//dram_write(addr,CACHE_BLOCK_SIZE-offset,data); //write through
				memcpy(cache[i].data+offset,&data,CACHE_BLOCK_SIZE-offset);
				secondcache_write(addr,CACHE_BLOCK_SIZE-offset,data);
				cache_write(addr+CACHE_BLOCK_SIZE-offset,len-(CACHE_BLOCK_SIZE-offset),data>>(CACHE_BLOCK_SIZE-offset));
			}	
			else {	
				//dram_write(addr,len,data); //write through 
				memcpy(cache[i].data+offset,&data,len);	
				secondcache_write(addr,len,data);		
			}
			return ;
		}
	}
	
	secondcache_write(addr,len,data);	
}

void secondcache_write(hwaddr_t addr,size_t len,uint32_t data) {
	uint32_t tag = addr>>(SECONDCACHE_SET_SIZE_B+SECONDCACHE_BLOCK_SIZE_B);
	uint32_t set = addr>>(SECONDCACHE_BLOCK_SIZE_B);
	set &=(SECONDCACHE_SET_SIZE-1);
	uint32_t offset = addr&(SECONDCACHE_BLOCK_SIZE-1);
	
	int i;
	for(i=set*SECONDCACHE_WAY_SIZE;i<(set+1)*SECONDCACHE_WAY_SIZE;i++) {
		if(secondcache[i].valid&&secondcache[i].tag==tag) {
			secondcache[i].dirty = true;
			if(offset+len>SECONDCACHE_BLOCK_SIZE) {
				//dram_write(addr,SECONDCACHE_BLOCK_SIZE-offset,data);
				memcpy(secondcache[i].data+offset,&data,SECONDCACHE_BLOCK_SIZE-offset);
				secondcache_write(addr+SECONDCACHE_BLOCK_SIZE-offset,len-(SECONDCACHE_BLOCK_SIZE-offset),data>>(SECONDCACHE_BLOCK_SIZE-offset));
			}	
			else {	
				//dram_write(addr,len,data);
				memcpy(secondcache[i].data+offset,&data,len);			
			}
			return ;
		}
	}
	
	int j = secondcache_read(addr);
	secondcache[j].dirty = true;
	memcpy(secondcache[j].data+offset,&data,len);
	//dram_write(addr,len,data);	
}
