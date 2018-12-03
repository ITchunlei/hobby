	.text
	.code16
	.globl start
start:
#	cli
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	mov $start, %sp

#	calll l_main

#	lgdtl gdtr



#	ljmpl $0x8, $tmp_protect_mode



1:
#    jmp 1b

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

    calll enable_A20

    calll enable_PE

#    calll l_main

#	jmp code32
	ljmpl $0x8, $protect_mode

r_mode_tmp:
	calll disable_PE
	ljmpl	$0, $r_mode

r_mode:

#	calll main32
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


e820_entry:
	mov $0x0000e820, %eax
	mov $0x534d4150, %edx
	mov $0x0, %ebx
	mov $20, %ecx
	

	.code32
tmp_protect_mode:
    mov    $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov %ax, %fs
    mov %ax, %gs

	ljmp	$0x18, $r_mode_tmp

	jmp .


protect_mode:
	mov	$0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov %ax, %fs
	mov %ax, %gs

	call	main32


page_table_init:
    movl $0x91003, 0x90000
	
    movl $0x92003, 0x91000

    movl $0x000083, 0x92000
    movl $0x200083, 0x92008
    movl $0x400083, 0x92010
    movl $0x600083, 0x92018
    movl $0x800083, 0x92020
    movl $0xa00083, 0x92028

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

#    jump to kernel
    pushl $0x18
    pushl $0x1100
    lretl

	.balign 8
gdt:
	.quad	 0x0 /* null desc */

    /* CODE_SELECTOR */
    .short 0xffff           /* limit 15:00 */
    .short 0x0000           /* base 15:00 */
    .byte  0x00             /* base 23:16 */
    .byte  0b10011010       /* P(1) DPL(00) S(1) 1 C(0) R(1) A(0) */
    .byte  0b11001111       /* G(1) D(1) 0 0 limit 19:16 */
    .byte  0x0              /* base 31:24 */

     /* DATA_SELECTOR */
    .short 0xffff           /* limit 15:00 */
    .short 0x0000           /* base 15:00 */
    .byte  0x00             /* base 23:16 */
    .byte  0b10010010       /* P(1) DPL(00) S(1) 0 E(0) W(1) A(0) */
    .byte  0b11001111       /* G(1) B(1) 0 0 limit 19:16 */
    .byte  0x0              /* base 31:24 */

    .quad    0x0020980000000000            /*1    KERNEL    Code    64-bit    Segment    08*/
    .quad    0x0000920000000000            /*2    KERNEL    Data    64-bit    Segment    10*/

    /* -- 16 bit real mode CS --
     * base = 0x00000000, limit 0x0FFFF (1 B Granularity), present
     * type = 16 bit code execute/read only/conforming, DPL = 0
     */
    .word    0xFFFF, 0
    .byte    0, 0x9E, 0, 0

    /* -- 16 bit real mode DS --
     * base = 0x00000000, limit 0x0FFFF (1 B Granularity), present
     * type = 16 bit data read/write, DPL = 0
     */
    .word    0xFFFF, 0
    .byte    0, 0x92, 0, 0

//     /* 16bit CODE_SELECTOR */
//    .short 0xffff           /* limit 15:00 */
//    .short 0x0000           /* base 15:00 */
//    .byte  0x00             /* base 23:16 */
//    .byte  0b10011010       /* P(1) DPL(00) S(1) 1 C(0) R(1) A(0) */
//    .byte  0b11001111       /* G(1) D(1) 0 0 limit 19:16 */
//    .byte  0x0              /* base 31:24 */
//
//    .quad     0x00cf9a000000ffff /* code desc */
//    .quad     0x00cf92000000ffff /* data desc */
//    .quad    0x00cf9a000000ffff /* code desc */
//    .quad    0x00cf92000000ffff /* data desc */
gdtr:
    .word    gdtr - gdt - 1
    .long    gdt

