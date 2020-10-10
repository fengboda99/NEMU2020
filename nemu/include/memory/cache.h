#ifndef __CACHE_H__
#define __CACHE_H__

#define CACHE_BLOCK_SIZE_B 6
#define CACHE_WAY_SIZE_B 3
#define CACHE_SET_SIZE_B 7
#define CACHE_BLOCK_SIZE (1<<CACHE_BLOCK_SIZE_B)
#define CACHE_WAY_SIZE (1<<CACHE_WAY_SIZE_B)
#define CACHE_SET_SIZE (1<<CACHE_SET_SIZE_B)

#define SECONDCACHE_BLOCK_SIZE_B 6
#define SECONDCACHE_WAY_SIZE_B 4
#define SECONDCACHE_SET_SIZE_B 12
#define SECONDCACHE_BLOCK_SIZE (1<<SECONDCACHE_BLOCK_SIZE_B)
#define SECONDCACHE_WAY_SIZE (1<<SECONDCACHE_WAY_SIZE_B)
#define SECONDCACHE_SET_SIZE (1<<SECONDCACHE_SET_SIZE_B)

uint64_t MTIME;

typedef struct {
	bool valid;
	uint32_t tag;
	uint8_t data[CACHE_BLOCK_SIZE];	
}Cache;

typedef struct {
	bool valid,dirty;
	uint32_t tag;
	uint8_t data[SECONDCACHE_BLOCK_SIZE];	
}SECONDCache;

Cache cache[CACHE_WAY_SIZE*CACHE_SET_SIZE];
SECONDCache secondcache[SECONDCACHE_WAY_SIZE*SECONDCACHE_SET_SIZE];

void cache_init();
uint32_t cache_read(hwaddr_t addr);
void cache_write(hwaddr_t addr,size_t len,uint32_t data);
uint32_t secondcache_read(hwaddr_t addr);
void secondcache_write(hwaddr_t addr,size_t len,uint32_t data);

#endif
