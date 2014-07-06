#####################################################
# common function for boot
# author: wangchunlei
# date: 2013-12-25
#####################################################
.type put_char, @function
.globl put_char
put_char:
	pushl	%ebp
	movl	%esp, %ebp
	
	movl	%ebp, %esp
	popl		%ebp
	ret
