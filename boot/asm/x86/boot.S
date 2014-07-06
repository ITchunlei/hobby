#ifndef __BOOT_H__
#define __BOOT_H__
#include "boot.h"
#endif
.code16
.extern boot_main
.globl _start
.section .text
_start:
	movw %cs, %ax
	movw %ax, %es
	movw %ax, %ds
	movw %ax, %ss
	movw $STACK_TOP, %sp
	movzwl %sp, %esp
	movl $0x0, %ebp
	calll	boot_main
loop:
	jmp loop
.section .data
.section .bss
.space 4096
STACK_TOP:

	
