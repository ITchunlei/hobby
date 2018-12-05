#ifndef __MEM_H__
#define __MEM_H__

#include "reg.h"
#include "types.h"

typedef uint64_t paddr_t;


static inline paddr_t virt2phy(void* virt) {
	return ((uint64_t)virt - 0xffff800000000000);
}

static inline void* phy2virt(paddr_t addr) {
	return (void*)(addr + 0xffff800000000000);
}

void* mem_boot_alloc(size_t len);

void mem_init();

#endif /* __MEM_H__ */