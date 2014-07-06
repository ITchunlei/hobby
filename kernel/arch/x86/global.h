#ifndef	__GLOBAL_H__
#define __GLOBAL_H__
extern struct gate_desc_struct *_idt;
extern struct seg_desc_struct *_gdt;
extern struct tss_struct _tss;
extern struct ptr_struct _gdt_ptr;
extern struct ptr_struct _idt_ptr;
extern unsigned long *_kernel_stack_top;
extern void init_i8259(void);
extern void hwint00(void);
#endif
