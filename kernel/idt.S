#define IDT_SIZE 256

#include "asm.h"

.macro di idx, error_code=0
.global _int\idx
._int\idx:
.if \error_code == 0
    push $\error_code
.endif
    push $1
.endm


.macro sum i=0, size=8
.global label_\i
label_\i:
.if \i == 8 || (\i >= 10 && \i <= 14) || \i == 17
.else    
.endif
.if \size-\i
//sum "(\i+1)", \size
.endif
    jmp do_interrupt
.endm

.text
.global _int_table
_int_table:
.rept 5
di 0
.endr

.global do_interrupt
do_interrupt:
    iretq

