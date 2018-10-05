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

	movq	$0x91007,	0x90000
#movq	$0x91007,	0x90800

	movq	$0x92007,	0x91000

	movq	$0x000083,	0x92000
	movq	$0x200083,	0x92008
	movq	$0x400083,	0x92010
	movq	$0x600083,	0x92018
	movq	$0x800083,	0x92020
	movq	$0xa00083,	0x92028

    lgdt    gdtr

#	open PAE
	mov	%cr4,	%eax
	bts	$5,	%eax
	mov	%eax,	%cr4

#	load cr3
	mov	$0x90000,	%eax
	mov	%eax,	%cr3

#	enable 64bit mode
	mov	$0x0c0000080, %ecx
	rdmsr
	bts	$8, %eax
	wrmsr

#	open PE and pading(cr0)
	mov	%cr0, %eax
	bts	$0, %eax
	bts	$31, %eax
	mov %eax, %cr0

	.code32
	ljmp	$0x8, $entry

	.code64
entry:
//    movq    $0x90000,    %rax
//    movq    %rax,        %cr3
//    movq    switch_seg(%rip),    %rax
//    pushq    $0x08
//    pushq    %rax
//    lretq
//
//#    jmp 64bit
//switch_seg:
//    .quad    entry64
//
//entry64:
//    movq    $0x10, %rax
//    movq    %rax,    %ds
//    movq    %rax,    %es
//    movq    %rax,    %gs
//    movq    %rax,    %ss
.extern kernel_main
	call kernel_main
	jmp	.

	.section .data
	.balign 8
pml4e:	/* 一级页目录 */
	.quad	3100 + 7
pdpte:	/* 二级页目录 */
	.quad	4100 + 3
pde:
	.quad	0x000083
	.quad	0x200083
	.quad	0x400083
	.quad	0x600083
    .quad    0xe0000083        /*0x a00000*/
    .quad    0xe0200083
    .quad    0xe0400083
    .quad    0xe0600083
    .quad    0xe0800083        /*0x1000000*/
    .quad    0xe0a00083
    .quad    0xe0c00083
    .quad    0xe0e00083

gdt:
    .quad    0x0000000000000000            /*0    NULL descriptor                   00*/
    .quad    0x0020980000000000            /*1    KERNEL    Code    64-bit    Segment    08*/
    .quad    0x0000920000000000            /*2    KERNEL    Data    64-bit    Segment    10*/
    .quad    0x0000000000000000            /*3    USER    Code    32-bit    Segment 18*/
    .quad    0x0000000000000000            /*4    USER    Data    32-bit    Segment 20*/
    .quad    0x0020f80000000000            /*5    USER    Code    64-bit    Segment    28*/
    .quad    0x0000f20000000000            /*6    USER    Data    64-bit    Segment    30*/
    .quad    0x00cf9a000000ffff            /*7    KERNEL    Code    32-bit    Segment    38*/
    .quad    0x00cf92000000ffff            /*8    KERNEL    Data    32-bit    Segment    40*/
    .fill    100,8,0                    /*10 ~ 11 TSS (jmp one segment <9>) in long-mode 128-bit 50*/
gdtr:
	.word	gdtr - gdt - 1
	.quad	gdt

.globl _boot_param
_boot_param:
	.quad 0x0

.section .bss
	.space 1024 * 4
stack_top:
