#include <arch/x86/protect.h>
#include <cinix/proc.h>
#include "arch/x86/klib.h"


struct task_struct proc_table[NR_TASKS]; /* process table */
extern struct task_struct *proc_ready = proc_table;
extern void restart();
char stack[4096];
void test() {
	for (;;) {
		for (int i = 0;i < 6000;i ++) {
			for (int j = 0 ; j < i; j ++) {

			}
		}
		display_str("a,");
	}
}
void start_proc(void) {
	display_str("hello world!!!\n");
	proc_ready->stack_frame.ds = _SELECTOR_U_D;
	proc_ready->stack_frame.es = _SELECTOR_U_D;
	proc_ready->stack_frame.fs = _SELECTOR_U_D;
	proc_ready->stack_frame.gs = _SELECTOR_U_D;
	proc_ready->stack_frame.ss = _SELECTOR_U_D;
	proc_ready->stack_frame.cs = _SELECTOR_U_C;
	proc_ready->stack_frame.esp = (unsigned long)stack;
	proc_ready->stack_frame.eip = (unsigned long)test;
	proc_ready->stack_frame.eflags = 0x1202;
	restart();
}


