/*
 * the entry file of kernel!
 * author: wangchunlei
 * date: 2014-1-31
 */


#ifndef	KERNEL_STACK_SIZE
#define KERNEL_STACK_SIZE	4 * 1024
#endif


	.align	32
	.section .text
begin_text:
	.section .data
begin_data:
	.section .bss
begin_bss:
	.section .text
	.globl	_start
	.globl 	_tss
	.globl	_gdt
	.globl	_idt
	.globl	_gdt_ptr
	.globl	_idt_ptr
	.globl	test
_start:
	/*
	 * set kernel stack!
	 */
	movw	$0x10, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss
	movl	$_kernel_stack_top, %esp
	
	call	kernel_main	// go to c file
	jmp .

/***************************** trap and fault **********************/
	.globl	_div_err
	.globl	_single_step_exception
	.globl	_nmi
	.globl	_breakpoint_exception
	.globl	_overflow
	.globl	_bounds_check
	.globl	_invalid_op
	.globl	_coprocessor_not_available
	.globl	_double_fault
	.globl	_coprocessor_seg_overrun
	.globl	_invalid_tss
	.globl	_seg_not_present
	.globl	_stack_exception
	.globl	_general_protection
	.globl	_page_fault
	.globl	_coprocessor_err
_div_err:
	push	$0xffffffff
	push	$0
	jmp	_exception
_single_step_exception:
	push	$0xffffffff
	push	$1
	jmp	_exception
_nmi:
	push	$0xffffffff
	push	$2
	jmp	_exception
_breakpoint_exception:
	push	$0xffffffff
	push	$3
	jmp	_exception
_overflow:
	push	$0xffffffff
	push	$4
	jmp	_exception
_bounds_check:
	push	$0xffffffff
	push	$5
	jmp	_exception
_invalid_op:
	push	$0xffffffff
	push	$6
	jmp	_exception
_coprocessor_not_available:
	push	$0xffffffff
	push	$7
	jmp	_exception
_double_fault:
	push	$8
	jmp	_exception
_coprocessor_seg_overrun:
	push	$0xffffffff
	push	$9
	jmp	_exception
_invalid_tss:
	push	$10
	jmp	_exception
_seg_not_present:
	push	$11
	jmp	_exception
_stack_exception:
	push	$12
	jmp	_exception
_general_protection:
	push	$13
	jmp	_exception
_page_fault:
	push	$14
	jmp	_exception
_coprocessor_err:
	push	$0xffffffff
	push	$16
	jmp	_exception

_exception:
	call	exception_handler
	add	$8, %esp
	hlt

/******************************interupt handler*********************/
	.align	16
	.globl	_clock_int
	.globl	_keyboard_int
	.globl	_start_root_proc
_clock_int:	/* clock interupt */
	sub	$4, %esp
	pushal
	push	%ds
	push	%es
	push	%fs
	push	%gs
	movl	$_kernel_stack_top, %esp
	incb	%gs:0x0b8000
	mov	$0x20, %al
	out	%al, $0x20
	jmp	_ret_from_int	

_keyboard_int:	/* keyboard interupt */
	jmp	_ret_from_int
_save_context:
	//pushal
	//push	%ds
	//push	%es
	//push	%fs
	//push	%gs
_ret_from_int:
	movl	proc_ready, %esp
	lea	72(%esp), %eax
	mov	%eax, _tss + 4
	pop	%gs
	pop	%fs
	pop	%es
	pop	%ds
	popal	
	addl	$4, %esp
	iretl
_start_root_proc:
	iretl
	
	.globl	hwint00
hwint00:
	iretl

/* restart */
	
	.globl	restart
restart:
	jmp	_ret_from_int
_idt:
	.rept	256
	.word	0x0100
	.word	0x8
	.word	0x8e00
	.word	0x3
	.endr
_idt_ptr:
	.word 	_idt_ptr - _idt - 1
	.long	0
_gdt:
	.quad	0x0 /* null descriptor */
	.quad	0x00cf9a000000ffff /* kernel code descriptor */
	.quad	0x00cf92000000ffff /* kernel data descriptor */
	.quad	0x00cffa000000ffff /* user code descriptor */
	.quad	0x00cff2000000ffff /* user data descriptor */
	.quad	0x0 /* tss descriptor */
_gdt_ptr:
	.word	_gdt_ptr - _gdt - 1
	.long	0
_tss:
	.long	0	/* backlink */
	.long	0	/* esp0 */
	.long	0	/* ss0 */
	.long	0	/* esp1 */
	.long	0	/* ss1 */
	.long	0	/* esp2 */
	.long	0	/* ss2 */
	.long	0	/* cr3 */
	.long	0	/* eip */
	.long	0	/* eflags */
	.long	0	/* eax */
	.long	0	/* ecx */
	.long	0	/* edx */
	.long	0	/* ebx */
	.long	0	/* esp */
	.long	0	/* ebp */
	.long	0	/* esi */
	.long	0	/* edi */
	.long	0	/* es */
	.long	0	/* cs */
	.long	0	/* ss */
	.long	0	/* ds */
	.long	0	/* fs */
	.long	0	/* gs */
	.long	0	/* ldt */
	.word	0	/* trap */
	.word	0	/* io_base */




	.section .data
	.globl	_boot_param
_boot_param:
	.word	0x0
	.word	0x0
	.section .bss
	.globl	_kernel_stack_top
	.space KERNEL_STACK_SIZE, 0
_kernel_stack_top:
	
	
	
		
	
