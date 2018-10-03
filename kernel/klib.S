//    .section .text
//    .extern _boot_param
//    .code32
//    .globl lgdt
//lgdt:
//    push %edx
//    mov 4(%esp), %edx
//    lgdt (%edx)
//    pop %edx
//    ret
//
//
///**
// * void out_byte(u16_t port, u8_t value);
// */
//    .globl out_byte
//out_byte:
//    mov 4(%esp), %edx
//    mov 8(%esp), %al
//    out %al, %dx
//    nop
//    nop
//    ret
//
///**
// * u8_t in_byte(u16_t port);
// */
//    .globl in_byte
//in_byte:
//    mov 4(%esp), %edx
//    xor %eax, %eax
//    in %dx, %al
//    nop
//    nop
//    ret

	.section .text
    .globl kprint
kprint:
	pushq    %rbp
    movq    %rsp, %rbp
    push    %rbx
    push    %rsi
    push    %rdi

    movq    8(%rbp), %rsi
    movl    _boot_param, %edi
    movb    $0x0f, %ah
1:
    lodsb
    test    %al, %al
    jz    2f
    cmp    $0x0a, %al
    jnz    3f
    push    %rax
    movl    %edi, %eax
    movb    $160, %bl
    div    %bl
    and    $0x0ff, %eax
    inc    %eax
    movb    $160, %bl
    mul    %bl
    movl    %eax, %edi
    popq    %rax
    jmp    1b
3:
    mov    %ax, %gs:0x0b8000(%edi)
    add    $2, %edi
    jmp    1b
2:
    movl    %edi,  _boot_param

    popq    %rdi
    popq    %rsi
    popq    %rbx
    popq    %rbp
    ret
