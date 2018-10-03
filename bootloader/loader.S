#include "lib.h"
.text
.code16
GLOBAL(_start)
	cli
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

	mov $_start, %sp

#	loader kernel
	calll read_bs

#	load gdt
	lgdtl	gdtr

#	open a20
	inb    $0x92, %al
	orb    $0x2, %al
	outb    %al, $0x92

#	enable cr0 PE
	mov	%cr0, %eax
	orl $0x1, %eax
	mov %eax, %cr0

#	jmp code32
	ljmpl $0x8, $protect_mode

read_bs:
    push %es
    movw $0x0201, %ax
    /** 读一个扇区 **/
    movb $0x6, %al
    movb $0x0, %ch
    /** 0-5 起始扇区 6-7 磁道**/
    movb $0x04, %cl
    /** dl 驱动器号 dh 磁头号 **/
    movw $0x0, %dx
    /** es:bx 数据缓冲区地址 **/
    movw $0x0, %bx
    movw %bx, %es
    movw $0x1100, %bx
    int $0x13
    pop %es
    ret

.code32
protect_mode:
	mov	$0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov %ax, %fs
	mov %ax, %gs

	xor %eax, %eax
	cpuid
	mov $0x1100, %eax
	jmp *%eax

.balign 4
gdt:
	.quad	0x0 /* null desc */
	.quad	0x00cf9a000000ffff /* code desc */
	.quad	0x00cf92000000ffff /* data desc */
gdtr:
    .word    gdtr - gdt - 1
    .long    gdt

