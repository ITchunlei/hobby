#define SIZE 256

.macro setup_interrupt
l_\@:
.if \@ == 8 || (\@ >= 10 && \@ <= 14) || \@ == 17
    pushq $\@
    jmp _interrupt
.else
    pushq $0
    pushq $\@
    jmp _interrupt
.endif   
# .if \@ < 8 || (\@ > 8 && \@ < 10) || (\@ > 14 && \@ < 17) || \@ > 17
#     pushq $0
# .endif
#     pushq $\@
#     jmp _interrupt
.pushsection .rodata.interrupt
.quad l_\@
.popsection
.endm


.text
.global _interrupt_table
.balign 8
.pushsection .rodata.interrupt
_interrupt_table:
.popsection
.rept SIZE
setup_interrupt
.endr

.global _interrupt
_interrupt:
    cld

    # save context
    pushq   %rax
    pushq   %rcx
    pushq   %rdx
    pushq   %rbx
    pushq   %rsi
    pushq   %rdi
    pushq   %r8
    pushq   %r9
    pushq   %r10
    pushq   %r11
    pushq   %r12
    pushq   %r13
    pushq   %r14
    pushq   %r15
    movq    %ds, %rax
    pushq   %rax
    movq    %es, %rax
    pushq   %rax
    pushq   %fs
    pushq   %gs

    movq %rsp, %rdi

    #lea stack_top(%rip), %rsp

    call do_interrupt



.Lrestore_context:
    # restore context
    popq    %gs
    popq    %fs
    popq    %rax
    movq    %rax, %es
    popq    %rax
    movq    %rax, %ds
    popq    %r15
    popq    %r14
    popq    %r13
    popq    %r12
    popq    %r11
    popq    %r10
    popq    %r9
    popq    %r8
    popq    %rdi
    popq    %rsi
    popq    %rbx
    popq    %rdx
    popq    %rcx
    popq    %rax

#   popq    %cs
#   popq    %rip
#   popq    %rsp
#   popq    %ss

    addq $0x10, %rsp
    #hlt
    iretq

 .global restore_context
 restore_context:
    movq %rdi, %rsp
    jmp .Lrestore_context

 .global context_stack
context_stack:
    .quad 0x0