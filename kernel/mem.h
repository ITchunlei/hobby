#ifndef __MEM_H__
#define __MEM_H__

#include "reg.h"

typedef uint64_t paddr_t;


inline paddr_t vir2phy(paddr_t vir) {
	return 0;
}

inline paddr_t phy2vir(paddr_t phy) {
	return 0;
}

void mem_init();

#endif /* __MEM_H__ */