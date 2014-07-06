	.file	"boot_main.c"
#APP
	.code16gcc
	
#NO_APP
	.text
	.globl	bios_int
	.type	bios_int, @function
bios_int:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$12, %esp
	movl	%edx, -8(%ebp)
	movl	%ecx, -12(%ebp)
	movw	%ax, -4(%ebp)
#APP
# 11 "boot_main.c" 1
	mov	%al, 1f
	pushfl
	push	%fs
	push	%gs
	pushal
	subw	$44, %sp
	mov	%dx, %si
	mov	%sp, %di
	movw	$11, %cx
	rep;	movsd
	popal
	pop	%ds
	pop	%es
	pop	%fs
	pop	%gs
	popfl
	.byte	0xcd
	1:	.byte	0
	pushfl
	push	%gs
	push	%fs
	push	%es
	push	%ds
	pushal
	cld
	movzwl	%sp, %esp
	mov	%cs, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	68(%esp), %di
	and	%di, %di
	jz	2f
	mov	%sp, %si
	mov	$11, %cx
	rep; movsd
	2:
	add	$44, %sp
	popal
	pop	%gs
	pop	%fs
	popfl
	
# 0 "" 2
#NO_APP
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	bios_int, .-bios_int
	.globl	boot_main
	.type	boot_main, @function
boot_main:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$96, %esp
	movl	$3681, -20(%ebp)
	movl	$0, -4(%ebp)
	jmp	.L3
.L4:
	leal	-92(%ebp), %edx
	leal	-48(%ebp), %eax
	movl	%edx, %ecx
	movl	%eax, %edx
	movl	$16, %eax
	call	bios_int
	addl	$1, -4(%ebp)
.L3:
	cmpl	$99, -4(%ebp)
	jle	.L4
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	boot_main, .-boot_main
	.ident	"GCC: (GNU) 4.8.2 20131212 (Red Hat 4.8.2-7)"
	.section	.note.GNU-stack,"",@progbits
