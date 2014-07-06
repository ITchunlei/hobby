#include <arch/x86/protect.h>

void set_gate_desc(struct gate_desc_struct *gate_desc, unsigned long offset,
	unsigned short selector, unsigned short attr) {
	gate_desc->addr_off_low = offset & 0xffff;
	gate_desc->selector	 = selector;
	gate_desc->attr	 = attr;
	gate_desc->addr_off_high = (offset>>16) & 0xffff;
}

void set_seg_desc(struct seg_desc_struct *seg_desc, unsigned long base, 
		unsigned long limit, unsigned short attr ){
	seg_desc->limit_low 	    = limit & 0xffff;
	seg_desc->base_low         = base & 0xffff;
	seg_desc->base_mid         = (base >> 16) & 0xff;
	seg_desc->attr_low         = attr & 0xff;
	seg_desc->limit_high_attr_high = ((attr >> 8) & 0xf0 )|((limit>>16) & 0xff);
	seg_desc->base_high	    = (base >> 24) & 0xff; 
}

void set_tss_desc(struct seg_desc_struct *seg_desc, unsigned long base
		,unsigned char dpl) {
	set_seg_desc(seg_desc, base, 0x67,
		set_seg_desc_attr(1, 1, 1, dpl, 0, X86_TSS));
}
