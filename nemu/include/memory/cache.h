#ifndef __CACHE_H__
#define __CACHE_H__

#define CACHE_BLOCK_SIZE_B 6
#define CACHE_WAY_SIZE_B 3
#define CACHE_SET_SIZE_B 7
#define CACHE_BLOCK_SIZE (1<<CACHE_BLOCK_SIZE_B)
#define CACHE_WAY_SIZE (1<<CACHE_WAY_SIZE_B)
#define CACHE_SET_SIZE (1<<CACHE_SET_SIZE_B)

uint64_t MTIME;

typedef struct {
	bool valid;
	uint32_t tag;
	uint8_t data[CACHE_BLOCK_SIZE];	
}Cache;

Cache cache[CACHE_WAY_SIZE*CACHE_SET_SIZE];

void cache_init();
uint32_t cache_read(hwaddr_t addr);
void cache_write(hwaddr_t addr,size_t len,uint32_t data);


#endif
