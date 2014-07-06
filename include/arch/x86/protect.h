/*
 * file : protect.h
 * author : wangchunlei
 * date : 2014
 */

#ifndef	__SEG_H__
#define	__SEG_H__
#include <cinix/types.h>

#define	RING0	0
#define RING1	1
#define	RING3	3
#define X86_XR	0xa
#define	X86_RW	0x2
#define	X86_RWH	0x3
#define X86_TSS 0x9
#define X86_LDT 0x2
#define	X86_IGATE	0xe
#define	X86_TGATE	0xf
#define	X86_CGATE	0xc


#define	_SELECTOR_K_C	0x8
#define	_SELECTOR_K_D	0x10
#define	_SELECTOR_U_C	0x18 + 0x3
#define	_SELECTOR_U_D	0x20 + 0x3
#define	_SELECTOR_TSS 	0x28

#define	sti()	asm volatile("sti\n\t");
#define	cli()	asm volatile("cli\n\t");



#define	ltr(tr)	asm volatile("ltr %%ax\n\t": :"a"(tr));
#define	lgdt(gdt_ptr)	asm volatile("lgdt %0\n\t"::"m"(gdt_ptr));
#define	lldt(ldt_ptr)	asm volatile("lldt %%ax\n\t"::"a"(ldt_ptr));
#define lidt(idt_ptr)   asm volatile("lidt %0"::"m"(idt_ptr));
#define	set_seg_desc_attr(G,DB,P,DPL,S,TYPE)	\
	TYPE|(S<<4)|(DPL<<5)|(P<<7)|(DB<<14)|(G<<15)
#define set_gate_desc_attr(P, DPL, S, TYPE, PCOUNT)  \
	(P<<15)|(DPL<<13)|(S<<12)|(TYPE<<8)|(PCOUNT)

struct seg_desc_struct {
	u16_t	limit_low;
	u16_t	base_low;
	u8_t	base_mid;
	u8_t	attr_low;
	u8_t	limit_high_attr_high;
	u8_t	base_high;
}__attribute__((packed));

struct gate_desc_struct {
	u16_t	addr_off_low;
	u16_t	selector;
	u16_t	attr;
	u16_t	addr_off_high;
}__attribute__((packed));

struct ptr_struct {
	u16_t	limit;
	u32_t	base_addr;
}__attribute__((packed));

/*
 * tss struct
 */

struct tss_struct {
	u32_t	back_link;
	u32_t	esp0;
	u32_t	ss0;
	u32_t	esp1;
	u32_t	ss1;
	u32_t	esp2;
	u32_t	ss2;
	u32_t	cr3;
	u32_t	eip;
	u32_t	eflags;
	u32_t	eax;
	u32_t	ecx;
	u32_t	edx;
	u32_t	ebx;
	u32_t	esp;
	u32_t	ebp;
	u32_t	esi;
	u32_t	edi;
	u32_t	es;
	u32_t	cs;
	u32_t	ss;
	u32_t	ds;
	u32_t	fs;
	u32_t	gs;
	u32_t	ldt;
	u16_t	trap;
	u16_t	io_base;
};


/*
 * stack frame
 */
struct stack_frame_struct {
	u32_t	gs;
	u32_t	fs;
	u32_t	es;
	u32_t	ds;
	u32_t	edi;
	u32_t	esi;
	u32_t	ebp;
	u32_t	kesp;
	u32_t	ebx;
	u32_t	edx;
	u32_t	ecx;
	u32_t	eax;
	u32_t	return_addr;
	u32_t	eip;
	u32_t	cs;
	u32_t	eflags;
	u32_t	esp;
	u32_t	ss;
};


void set_gate_desc(struct gate_desc_struct*, u32_t, u16_t, u16_t);
void set_seg_desc(struct seg_desc_struct*, u32_t, u32_t, u16_t);
void set_tss_desc(struct seg_desc_struct*, u32_t, u8_t);
void set_ldt_desc(struct seg_desc_struct*, u32_t, u32_t, u8_t);
#endif	/* __SEG_H__ */
