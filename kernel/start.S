//
//  start.S
//  Boot
//
//  Created by chunlei on 2018/10/3.
//  Copyright © 2018 los. All rights reserved.
//

# 0x100000 ~ ... 空
# 0x09FC00 ~ 0xFFFFF SystemROM/E-systemROM/Reversed/DisplayArea/E-BIOS 不可用
# 0x000500 ~ 0x9FBFF 空
# 0x000400 ~ 0x004FF BIOS 参数区域 不可用
# 0x000000 ~ 0x003FF 实模式中断向量表	可用

//(1)    首先，要进入保护模式，即CR0.PE=1
//(2)    其次，先初始化页表！但注意，千万不能打开先分页机制！
//(3)    打开CR4.PAE
//(4)    打开EFER.LME=1
//(5)    打开CR0.PG=1，分页使能。
//(6)    这时候处理器自动将EFER.LMA设置，进入长模式
//(7)    一个跳转

.text
.code32
.global _start
_start:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov %ax, %fs
	mov %ax, %gs
	mov $stack_top, %esp

#	top-level pde
	movl	$0x91003,	0x90000
#	movq	$0x91007,	0x90800

#	two-level pde
	movl	$0x92003,	0x91000

#	pde
	movl	$0x000083,	0x92000
	movl	$0x200083,	0x92008
	movl	$0x400083,	0x92010
	movl	$0x600083,	0x92018
	movl	$0x800083,	0x92020
	movl	$0xa00083,	0x92028

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

	//ljmp	$0x8, $start64
	pushfl
	push	$0x8
	push	$start64
	lretl
.code64
start64:
    movq    $0x10, %rax
    movq    %rax,    %ds
    movq    %rax,    %es
    movq    %rax,    %gs
    movq    %rax,    %ss
	movq	$stack_top, %rsp

	mov	$0x48, %ax
	ltr	%ax

    movq    go_to_kernel(%rip),    %rax
#	pushfq
    pushq    $0x08
    pushq    %rax
    lretq

0:
	hlt
	jmp    0b

go_to_kernel:
	.quad start_kernel

.data
.balign 8
gdt:
    .quad    0x0000000000000000            /*0    NULL descriptor                   00*/
    .quad    0x0020980000000000            /*1    KERNEL    Code    64-bit    Segment    08*/
    .quad    0x0000920000000000            /*2    KERNEL    Data    64-bit    Segment    10*/
    .quad    0x0000000000000000            /*3    USER    Code    32-bit    Segment 18*/
    .quad    0x0000000000000000            /*4    USER    Data    32-bit    Segment 20*/
    .quad    0x0020f80000000000            /*5    USER    Code    64-bit    Segment    28*/
    /* USER_CODE_64_SELECTOR */
//    .short 0xffff           /* limit 15:00 */
//    .short 0x0000           /* base 15:00 */
//    .byte  0x00             /* base 23:16 */
//    .byte  0b11111010       /* P(1) DPL(11) S(1) 1 C(0) R(1) A(0) */
//    .byte  0b10101111       /* G(1) D(0) L(1) AVL(0) limit 19:16 */
//    .byte  0x0              /* base 31:24 */



	.quad    0x0000f20000000000            /*6    USER    Data    64-bit    Segment    30*/
    .quad    0x00cf9a000000ffff            /*7    KERNEL    Code    32-bit    Segment    38*/
    .quad    0x00cf92000000ffff            /*8    KERNEL    Data    32-bit    Segment    40*/
//    /* null entry */
//    .int 0
//    .int 0

//    /* CODE_SELECTOR */
//    .short 0xffff           /* limit 15:00 */
//    .short 0x0000           /* base 15:00 */
//    .byte  0x00             /* base 23:16 */
//    .byte  0b10011010       /* P(1) DPL(00) S(1) 1 C(0) R(1) A(0) */
//    .byte  0b11001111       /* G(1) D(1) 0 0 limit 19:16 */
//    .byte  0x0              /* base 31:24 */

//    /* CODE_64_SELECTOR */
//    .short 0x0000           /* limit 15:00 */
//    .short 0x0000           /* base 15:00 */
//    .byte  0x00             /* base 23:16 */
//    .byte  0b10011010       /* P(1) DPL(00) S(1) 1 C(0) R(1) A(0) */
//    .byte  0b10101111       /* G(1) D(0) L(1) AVL(0) limit 19:16 */
//    .byte  0x0              /* base 31:24 */
//
//    /* DATA_SELECTOR */
//    .short 0x0000           /* limit 15:00 */
//    .short 0x0000           /* base 15:00 */
//    .byte  0x00             /* base 23:16 */
//    .byte  0b10010010       /* P(1) DPL(00) S(1) 0 E(0) W(1) A(0) */
//    .byte  0b11001111       /* G(1) B(1) 0 0 limit 19:16 */
//    .byte  0x0              /* base 31:24 */

//    /* disable 32bit ring3 code descriptor on 64bit kernel */
//    .int  0x0
//    .int  0x0
//
//    /* USER_DATA_SELECTOR */
//    .short 0xffff           /* limit 15:00 */
//    .short 0x0000           /* base 15:00 */
//    .byte  0x00             /* base 23:16 */
//    .byte  0b11110010       /* P(1) DPL(11) S(1) 0 E(0) W(1) A(0) */
//    .byte  0b11001111       /* G(1) B(1) 0 0 limit 19:16 */
//    .byte  0x0              /* base 31:24 */
//


    /* TSS_SELECTORs */
    .short 0x68              /* limit 15:00 */
    .short tss                /* base 15:00 */
    .byte  0                /* base 23:16 */
    .byte  0b10001001       /* P(1) DPL(00) 0 10 B(0) 1 */
    .byte  0b10000000       /* G(1) 0 0 AVL(0) limit 19:16 */
    .byte  0                /* base 31:24 */
    /* second half of 64bit desciptor */
    .int   0x00000000       /* base 63:32 */
    .int   0x00000000       /* reserved/sbz */
gdtr:
	.word	gdtr - gdt - 1
	.quad	gdt

tss:
	.long	 0x0  // reserved
	.quad	 0x300000  //rsp0
	.quad	 0x0  //rsp1
	.quad	 0x0  //rsp2
	.quad	 0x0  //reserved
	.quad	 0x7c00  //ist1
    .quad    0x7c00  //ist2
    .quad    0x7c00  //ist3
    .quad    0x7c00  //ist4
    .quad    0x7c00  //ist5
    .quad    0x7c00  //ist6
    .quad    0x7c00  //ist7
    .quad    0x0  //reserved
	.long	 0x0  // i/o map base address


.globl _boot_param
_boot_param:
	.quad 0x0

.bss
	.space 1024 * 4
stack_top:
