/*
 * file : arch_init.c
 * author : wangchunlei
 * date : 2014
 */
#include <arch/x86/protect.h>
#include "global.h"

void _div_err(void);
void _single_step_exception(void);
void _nmi(void);
void _breakpoint_exception(void);
void _overflow(void);
void _bounds_check(void);
void _invalid_op(void);
void _coprocessor_not_available(void);
void _double_fault(void);
void _coprocessor_seg_overrun(void);
void _invalid_tss(void);
void _seg_not_present(void);
void _stack_exception(void);
void _general_protection(void);
void _page_fault(void);
void _coprocessor_err(void);


void _clock_int(void);

static void init_tss(void);
static void init_gdt(void);
static void init_idt(void);


static void test() {
	for(;;);
}






void init_pde(unsigned long p){
	int i;
	for(i = 0;i < 1024; i ++)
		*(long*)(p+4*i) = 4096*i+7+0x101000;
}

void init_pdt(unsigned long p){
	int i;
	for(i = 0;i < 1024*1024; i ++)
		*(long*)(p+4*i) = 4096*i+7;
}

void start_page(unsigned long pde){
	asm volatile("mov	%%eax, %%cr3\n\t"
				"mov	%%cr0, %%ebx\n\t"
				"or		$0x80000000, %%ebx\n\t"
				"mov	%%ebx, %%cr0\n\t"
				"nop\n\t"
				"nop\n\t"
				"nop\n\t": :"a"(pde));
}



void arch_init(void) {
	cli();	      /* close interupt */
	init_gdt();   /* initialize global descriptor tables */
	init_tss();
	init_pde(0x100000);
	init_pdt(0x101000);
	start_page(0x100000);
	init_idt();   /* initialize interupt descriptor tables */
	init_i8259(); /* initialize i8259 chip */
	sti();	      /* open interupt */	
} 

static void init_tss(void) {
	_tss.ss0     = _SELECTOR_K_D;
	_tss.esp0    = (unsigned long)&_kernel_stack_top;
	_tss.io_base = 0x68;
	ltr(0x28);
}
static void init_gdt(void) {
	set_seg_desc(&_gdt[0], 0, 0 , 0);
	set_seg_desc(&_gdt[1], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, RING0, 1, X86_XR));	
	set_seg_desc(&_gdt[2], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, RING0, 1, X86_RW));
	set_seg_desc(&_gdt[3], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, RING3, 1, X86_XR));
	set_seg_desc(&_gdt[4], 0, 0xfffff
		, set_seg_desc_attr(1, 1, 1, RING3, 1, X86_RW));
	set_tss_desc(&_gdt[5], (unsigned long)&_tss, RING0);
	_gdt_ptr.limit = (sizeof(struct seg_desc_struct) * 6 - 1);
	_gdt_ptr.base_addr  = (unsigned long)_gdt;
	lgdt(_gdt_ptr);
}

static void init_idt(void) {
	set_gate_desc(&_idt[0], (unsigned long)_div_err
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[1], (unsigned long)_single_step_exception
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[2], (unsigned long)_nmi
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[3], (unsigned long)_breakpoint_exception
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[4], (unsigned long)_overflow
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[5], (unsigned long)_bounds_check
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[6], (unsigned long)_invalid_op
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[7], (unsigned long)_coprocessor_not_available
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[8], (unsigned long)_double_fault
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[9], (unsigned long)_coprocessor_seg_overrun
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[10], (unsigned long)_invalid_tss
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[11], (unsigned long)_seg_not_present
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[12], (unsigned long)_stack_exception
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[13], (unsigned long)_general_protection
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[14], (unsigned long)_page_fault
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[15], (unsigned long)_page_fault
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	set_gate_desc(&_idt[16], (unsigned long)_coprocessor_err
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));

	for (int i = 17;i < 256;i ++) {
		set_gate_desc(&_idt[i], (unsigned long)0
			, _SELECTOR_K_C
			,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	}
	set_gate_desc(&_idt[32], (unsigned long)_clock_int
		, _SELECTOR_K_C
		,set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
	_idt_ptr.limit = (sizeof(struct gate_desc_struct)) * 256 -1;
	_idt_ptr.base_addr = (unsigned long)_idt;
	lidt(_idt_ptr);
}


