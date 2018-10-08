//
//  interrupt.S
//  Boot
//
//  Created by chunlei on 2018/10/5.
//  Copyright © 2018 los. All rights reserved.
//

#include "asm.h"

GLOBAL(divide_error)
    pushq    $0xffffffffffffffff
	push	$0x0
	jmp	exception
GLOBAL(debug_exception)
    pushq    $0xffffffffffffffff
    pushq    $0x1
    jmp    exception
GLOBAL(nmi_interrupt)
    pushq    $0xffffffffffffffff
    pushq    $0x2
    jmp    exception
GLOBAL(breakpoint)
    pushq    $0xffffffffffffffff
    pushq    $0x3
    jmp    exception
GLOBAL(overflow)
    pushq    $0xffffffffffffffff
    pushq    $0x4
    jmp    exception
GLOBAL(bound_range_exceeded)
    pushq    $0xffffffffffffffff
    pushq    $0x5
    jmp    exception
GLOBAL(invalid_opcode)
    pushq    $0xffffffffffffffff
    pushq    $0x6
    jmp    exception
GLOBAL(device_not_available)
    pushq    $0xffffffffffffffff
    pushq    $0x7
    jmp    exception
GLOBAL(double_fault)
    pushq    $0x8
    jmp    exception
GLOBAL(coprocessor_segment_overrun)
    pushq    $0xffffffffffffffff
    pushq    $0x9
    jmp    exception
GLOBAL(invalid_tss)
    pushq    $10
    jmp    exception
GLOBAL(segment_not_present)
    pushq    $11
    jmp    exception
GLOBAL(stack_segment_fault)
    pushq    $12
    jmp    exception
GLOBAL(general_protection)
    pushq    $13
    jmp    exception
GLOBAL(page_fault)
    pushq    $14
    jmp    exception
GLOBAL(x87_fpu_floating_poing_error)
    pushq    $0xffffffffffffffff
    pushq    $15
    jmp    exception
GLOBAL(alignment_check)
    pushq    $16
    jmp    exception
GLOBAL(machine_check)
    pushq    $0xffffffffffffffff
    pushq    $17
    jmp    exception
GLOBAL(simd_floating_point_exception)
    pushq    $0xffffffffffffffff
    pushq    $18
    jmp    exception
GLOBAL(virtualization_exception)
    pushq    $0xffffffffffffffff
    pushq    $20
    jmp    exception
exception:
	movq	0(%rsp), %rdi
	movq	8(%rsp), %rsi
	movq	16(%rsp), %rdx
	movq	24(%rsp), %rcx
	movq	32(%rsp), %r8
	movq	40(%rsp), %r9
	callq	do_exception
	addq	$0x10,	%rsp
	hlt

GLOBAL(timer_interrupt)
	callq	do_timer_interrup
	hlt
	//iretq



GLOBAL(user_mode)
    #    top-level pde
    movl    $0x81007,    0x80000
    #    movq    $0x91007,    0x90800

    #    two-level pde
    movl    $0x82007,    0x81000

    #    pde
    movl    $0x000087,    0x82000
    movl    $0x200087,    0x82008
    movl    $0x400087,    0x82010
    movl    $0x600087,    0x82018
    movl    $0x800087,    0x82020
    movl    $0xa00087,    0x82028


	pushq	$0x33
	pushq	$0x1000
	pushq	$0x0002
	pushq	$0x2b
	movq    go_to_l3_mode(%rip),    %rax
	pushq	%rax


    mov    $0x80000,    %eax
    mov    %eax,    %cr3

	//jmp .
	iretq

go_to_l3_mode:
	.quad	l3_mode

