#define SIZE 256

.macro setup_interrupt
l_\@:
.if \@ < 8 || (\@ > 8 && \@ < 10) || (\@ > 14 && \@ < 17) || \@ > 17
    pushq $0
.endif
    pushq $\@
    jmp _interrupt
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
    movq 0(%rsp), %rdi
    movq 8(%rsp), %rsi
    movq 16(%rsp), %rdx
    movq 24(%rsp), %rcx
    movq 32(%rsp), %r8
    movq 40(%rsp), %r9
    call do_interrupt
    addq $0x10,	%rsp
    iretq

