#include "macros.h"
#include "lib.h"
#include "mem.h"

#define __flush_tlb() \
do { \
unsigned int tmpreg; \
__asm__ __volatile__( \
"mov %%cr3, %0; # flush TLB \n" \
"mov %0, %%cr3; \n" \
: "=r" (tmpreg) \
:: "memory"); \
} while (0)


#define KERNEL_OFFSET	0xffff800000000000

#define PG_P	0x1
#define PG_RW	(1UL << 1)
#define PG_U	(1UL << 2)
#define PG_WT	(1UL >> 4)
#define PG_CD	(1UL >> 5)
#define PG_A	(1UL >> 6)
//#define PG_CD	(1UL >> 7)

#define PG_G	(1UL << 7)

extern char _end[];

extern uintptr_t *pml4e;
uint64_t mem_boot_alloc_end = (uint64_t)_end;

paddr_t *pml4;
paddr_t pdp[1];
paddr_t ptp[512];
paddr_t pte[2];

int mem_size = 1 * 1024 * 1024 * 1024;

void mem_init() {

	kprintf("mem_size: %lx\n", mem_size);

	int total_page = mem_size / (4 * 1024);

	kprintf("total_page: %ld, ptp: %ld, pdp: %ld, pml4: %ld\n", total_page, total_page / 512, total_page / 512 / 512, total_page / 512/ 512/ 512);

	pml4 = (paddr_t*)mem_boot_alloc(sizeof(uint64_t) * 512);
	

	unsigned long i;

	for (i = 0; i < 200000; i++) {

		uintptr_t vaddr = i * 4 * 1024 + KERNEL_OFFSET;

		uintptr_t pdp_idx = vaddr >> 39 & 0b111111111;
		uintptr_t ptp_idx = vaddr >> 30 & 0b111111111;
		uintptr_t pte_idx = vaddr >> 21 & 0b111111111;
		uintptr_t page_idx = vaddr >> 12 & 0b111111111;

		paddr_t *pdp, *ptp, *pte;

		if (!(pml4[pdp_idx] & PG_P)) {
			pdp = mem_boot_alloc(sizeof(uintptr_t) * 512);

			kprintf("%lx\n", virt2phy(pdp));
			pml4[pdp_idx] = virt2phy(pdp) | PG_P | PG_RW;
		} else {
			pdp = (paddr_t*)phy2virt(pml4[pdp_idx] & ~0xfff);
		}


		if (!(pdp[ptp_idx] & PG_P)) {
			ptp = mem_boot_alloc(sizeof(uintptr_t) * 512);
			pdp[ptp_idx] = virt2phy(ptp) | PG_P | PG_RW;
		} else {
			ptp = (paddr_t*)phy2virt(pdp[ptp_idx] & ~0xfff);
		}

		if (!(ptp[pte_idx] & PG_P)) {
			pte = mem_boot_alloc(sizeof(uintptr_t) * 512);
			ptp[pte_idx] = virt2phy(pte) | PG_P | PG_RW;
		} else {
			pte = (paddr_t*)phy2virt(ptp[pte_idx] & ~0xfff);
		}

		pte[page_idx] = (i << 12) | PG_P | PG_RW;
	}

	//set_cr3(virt2phy(pml4));
	//__flush_tlb();
}

void* mem_boot_alloc(size_t len) {
	uintptr_t ret = ALIGN(mem_boot_alloc_end, 8);
	mem_boot_alloc_end = (ret + ALIGN(len, 8));
	return (void*)ret;
}