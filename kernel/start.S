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


#define KERNEL_LOADED 0x1100
#define KERNEL_BASE 0xffff800000000000
#define K_CODE_SELECTOR 0x8
#define K_DATA_SELECTOR 0x10

#define K_CODE32_SELECTOR 0x38
#define K_DATA32_SELECTOR 0x40

#define PHY_ADDR(x) ((x) - KERNEL_BASE + KERNEL_LOADED)

#define KERNEL_OFFSET 0x0
#define PA(x) ((x) - KERNEL_BASE + KERNEL_OFFSET)

#define LOAD_GDT(l,b)   \
    

.section .text
.global _start
_start:
    movq $PA(stack_top), %rsp
    
page_init:
    #	top-level pde
    movl $0x61007, 0x60000
    movl $0x61007, 0x60800

    #two-level pde
    movl $0x62007, 0x61000

    #pde
    movl $0x000087, 0x62000
    movl $0x200087, 0x62008
    movl $0x400087, 0x62010
    movl $0x600087, 0x62018
    movl $0x800087, 0x62020
    movl $0xa00087, 0x62028

    #open PAE
    movq %cr4, %rax
    bts $5, %rax
    movq %rax, %cr4

    #load cr3
    movq $0x60000, %rax
    movq %rax, %cr3

    movw $(gdt_end - gdt - 1), %ax
    movw %ax, -6(%rsp)
    movq $PA(gdt), %rcx
    movq %rcx, -4(%rsp)
    
    lgdt -6(%rsp)

    pushq $K_CODE_SELECTOR
    leaq .Lstart(%rip), %rax
    movq $KERNEL_BASE, %rbx
    addq %rbx, %rax
    pushq %rax
    lretq

.Lstart:
    lgdt gdtr(%rip)
    xorq %rax, %rax
    movq %rax, %ds
    movq %rax, %es
    movq %rax, %gs
    movq %rax, %ss
    movq %rax, %fs

    lea stack_top(%rip), %rsp

    # mov	$0x48, %ax
    # ltr	%ax

    call start_kernel
    
.Lhalt:
    hlt
    jmp .Lhalt

.section .data
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
.global tss_desc_table
tss_desc_table:
    /* TSS_SELECTORs */
    .short 0x0              /* limit 15:00 */
    .short 0x0                /* base 15:00 */
    .byte  0                /* base 23:16 */
    .byte  0b10001001       /* P(1) DPL(00) 0 10 B(0) 1 */
    .byte  0b10000000       /* G(1) 0 0 AVL(0) limit 19:16 */
    .byte  0                /* base 31:24 */
    /* second half of 64bit desciptor */
    .int   0x00000000       /* base 63:32 */
    .int   0x00000000       /* reserved/sbz */
gdt_end:
gdtr:
    .word	gdtr - gdt - 1
    .quad	gdt
/*
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

*/
.globl _boot_param
_boot_param:
    .quad 0x0
.bss
    .space 1024 * 4
.global stack_top
stack_top:
