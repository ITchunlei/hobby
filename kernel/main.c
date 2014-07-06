#include "global.h"
#include "arch/x86/klib.h"
#include "arch/x86/int.h"
#include <cinix/proc.h>
#include <arch/x86/protect.h>



	

u32_t task_stack[1024];
void kernel_main(void) {
	display_str("arch_init is starting ....\n");
	arch_init();
	display_str("arch_init is ok ...\n");
	start_proc();	

//	for (int i = 0;i < 256;i ++) {
//		set_gate_desc(&_idt[i], (u32_t)int_handler, 8,
//		set_gate_desc_attr(1, RING0, 0, X86_IGATE, 0));
//	}
	
//	init_i8259();
//	sti();
//	display_str("kernel c file is starting .......\n");
//	display_str("kernel ......");

//	struct task_struct *p = proc_table;
//	p->stack_frame.ds = _SELECTOR_U_D;
//	p->stack_frame.es = _SELECTOR_U_D;
//	p->stack_frame.fs = _SELECTOR_U_D;
//	p->stack_frame.gs = _SELECTOR_U_D;
//	p->stack_frame.ss = _SELECTOR_U_D;
//	p->stack_frame.cs = _SELECTOR_U_C;
//	p->stack_frame.esp = (u32_t)task_stack;
//	p->stack_frame.eip = (u32_t)handle;
//	p->stack_frame.eflags = 0x1202;
//
//	
//	proc_ready = (u32_t)proc_table;
//	restart();
}

