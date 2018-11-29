#include "lib.h"
#include "mem.h"

paddr_t pml4[512];
paddr_t pdp[512];
paddr_t ptp[512];
//paddr_t p

void mem_init() {
	int i, total_page = 1 * 1024 * 1024 / 4;
	kprintf ("total pages: %d, total pte: %d\n, ptp: %d\n", total_page, total_page / 512 + 1, (total_page / 512 + 1) / 512 + 1);
	for (i = 0;i < total_page; ++i) {
		kprintf("%lx,", i * 4 * 1024);
	}
}