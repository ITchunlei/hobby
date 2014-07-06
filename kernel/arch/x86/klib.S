	.section .text
	.globl	display_str
display_str:
	push	%ebp
	movl	%esp, %ebp
	push	%ebx
	push	%esi
	push	%edi
	
	movl	8(%ebp), %esi
	movl	_boot_param, %edi
	movb	$0x0f, %ah
1:	
	lodsb
	test	%al, %al	
	jz	2f
	cmp	$0x0a, %al
	jnz	3f
	push	%eax
	movl	%edi, %eax
	movb	$160, %bl
	div	%bl
	and	$0x0ff, %eax
	inc	%eax
	movb	$160, %bl
	mul	%bl
	movl	%eax, %edi
	popl	%eax
	jmp	1b
3:
	mov	%ax, %gs:0x0b8000(%edi)
	add	$2, %edi
	jmp	1b
2:
	movl	%edi,  _boot_param
	
	popl	%edi
	popl	%esi
	popl	%ebx
	popl	%ebp
	ret

