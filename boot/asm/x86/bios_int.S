.text
.type bios_int, @function
.code16
.globl bios_int
bios_int:
	pushl	%ebp
	movl 	%esp, %ebp
	subl	$12, %esp
	movl	%edx, -8(%ebp)
	movl	%ecx, -12(%ebp)
	movw	%ax, -4(%ebp)
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
1:	
.byte	0
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
	rep;	movsd
2:
	and	$44, %sp
	popal
	pop	%gs
	pop	%fs
	popfl
	pop 	%ebp
	ret
