#define SYMBOL_NAME(N) N
#define SYMBOL_NAME_LABEL(N) N##:
#define GLOBL(N)    \
.globl SYMBOL_NAME(N);   \
SYMBOL_NAME_LABEL(N)

    .section .text
    .globl _kernel_entry
    .extern kernel_main
    .code32
_kernel_entry:
    mov $stack_top, %eax
    mov %eax, %esp
    ltr %ax

    mov %esp, %eax
    pushw $0x23 //ss
    pushl %eax  //esp
    pushf      //eflags
    pushw $0x1b // cs
    pushl $ring3 // eip
    iret

    jmp .

ring3:
    mov $0x23, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    jmp .

    .globl cli
    .globl sti
cli:
    cli
    ret
sti:
    sti
    ret

    .globl divide_err
    .globl single_stepexception
    .globl nmi
    .globl breakpointexception
    .globl overflow
    .globl bounds_check
    .globl invalid_op
    .globl coprocessor_not_available
    .globl double_fault
    .globl coprocessor_seg_overrun
    .globl invalid_tss
    .globl seg_not_present
    .globl stackexception
    .globl general_protection
    .globl page_fault
    .globl coprocessor_err
/**
 * do errors
 */

/**
 * 除零错误 无错误号
 */
divide_err:
    push $0xffffffff
    push $0
    jmp exception
single_stepexception:
    push $0xffffffff
    push $1
    jmp exception
nmi:
    push $0xffffffff
    push $2
    jmp exception
breakpointexception:
    push $0xffffffff
    push $3
    jmp exception
overflow:
    push $0xffffffff
    push $4
    jmp exception
bounds_check:
    push $0xffffffff
    push $5
    jmp exception
invalid_op:
    push $0xffffffff
    push $6
    jmp exception
coprocessor_not_available:
    push $0xffffffff
    push $7
    jmp exception
double_fault:
    push $8
    jmp exception
coprocessor_seg_overrun:
    push $0xffffffff
    push $9
    jmp exception
invalid_tss:
    push $10
    jmp exception
seg_not_present:
    push $11
    jmp exception
stackexception:
    push $12
    jmp exception
general_protection:
    push $13
    jmp exception
page_fault:
    push $14
    jmp exception
coprocessor_err:
    push $0xffffffff
    push $16
    jmp exception

    .extern do_exception
exception:
    call do_exception
    add $0x8, %esp
    hlt


    .globl timer_interrupt
    .extern do_timer_interrupt
timer_interrupt:
//    hlt
//    push %ds
//    push %es
//    push %fs
//    push %gs
//    pushal
////    call do_timer_interrupt
//    movb $0x20, %al
//    outb %al, $0x20
//    popal
//    pop %gs
//    pop %fs
//    pop %es
//    pop %ds

    

    iretl

default_interrupt:
    hlt

    .section .data
    .globl gdt
    .globl gdtr
gdt:
    .rept 6
    .word 0, 0
    .byte 0, 0, 0, 0
    .endr
gdtr:
    .word gdtr - gdt - 1
    .long gdt

    .globl idt
idt:
    .rept 256
    .word 0x0
    .word 0x0008
    .word 0x8e00
    .word 0x0
    .endr
idtr:
    .word idtr - idt - 1
    .long idt

GLOBL(tss)
    .long    0    /* backlink */
    .long    stack_top    /* esp0 */
    .long    0x10    /* ss0 */
    .long    0    /* esp1 */
    .long    0    /* ss1 */
    .long    0    /* esp2 */
    .long    0    /* ss2 */
    .long    0    /* cr3 */
    .long    0    /* eip */
    .long    0    /* eflags */
    .long    0    /* eax */
    .long    0    /* ecx */
    .long    0    /* edx */
    .long    0    /* ebx */
    .long    0    /* esp */
    .long    0    /* ebp */
    .long    0    /* esi */
    .long    0    /* edi */
    .long    0    /* es */
    .long    0    /* cs */
    .long    0    /* ss */
    .long    0    /* ds */
    .long    0    /* fs */
    .long    0    /* gs */
    .long    0    /* ldt */
    .word    0    /* trap */
    .word    0    /* io_base */

    .globl _boot_param
_boot_param:
    .word 0x0

    .section .bss
    .space 1024 * 4
stack_top:
    .code64
