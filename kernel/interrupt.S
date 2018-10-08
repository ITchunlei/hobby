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
	iretq

