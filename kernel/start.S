//
//  start.s
//  Boot
//
//  Created by chunlei on 2018/10/3.
//  Copyright © 2018 los. All rights reserved.
//

.section .text
.global _start
_start:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov %ax, %fs
	mov %ax, %gs
	mov $stack_top, %esp

.extern kernel_main
	call kernel_main
	jmp	.

.section .data
.globl _boot_param
_boot_param:
	.quad 0x0

.section .bss
	.space 1024 * 4
stack_top:
