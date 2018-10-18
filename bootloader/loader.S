
.text
.code16
.global start
start:
	cli
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

	mov $start, %sp

#	loader kernel
#	start 3 sector, temp read 255 sectors, ^^
	mov		$0x30, %cl
	mov		$0x0, %ax
	mov		%ax, %es
	mov		$0x1100, %bx
    mov     $0x3, %ax
	calll read_sector

#	load gdt
	lgdtl	gdtr

    calll l_main

#	jmp code32
	ljmpl $0x8, $tmp_protect_mode

r_mode:
	jmp .

read_sector:
    push	%bp
	mov		%sp, %bp
	sub		$0x2, %esp

	movb	%cl, -2(%bp)
	push	%bx
# 	18 secotr each trunk
	movb	$0x18, %bl
	div		%bl
	incb	%ah
	movb	%ah, %cl
	movb	%al, %dh
	shr		$0x1, %al
	mov		%al, %ch
	andb	$0x1, %dh
	pop		%bx

#	driver number 0
	movb	$0x0, %dl
1:
	movb	$0x2, %ah
	movb	-2(%bp), %al
	int		$0x13
	jc		1b
	add		$0x2, %esp
	pop		%bp
	ret

.code32

tmp_protect_mode:
#	ljmp	$0,


protect_mode:
	mov	$0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov %ax, %fs
	mov %ax, %gs

	call	main32

	xor %eax, %eax
	mov $0x1100, %eax
	jmp *%eax

.balign 4
gdt:
	.quad	0x0 /* null desc */
	.quad	0x00cf9a000000ffff /* code desc */
	.quad	0x00cf92000000ffff /* data desc */
	.quad    0x00cf9a000000ffff /* code desc */
	.quad    0x00cf92000000ffff /* data desc */
gdtr:
    .word    gdtr - gdt - 1
    .long    gdt

