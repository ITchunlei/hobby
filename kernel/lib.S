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
